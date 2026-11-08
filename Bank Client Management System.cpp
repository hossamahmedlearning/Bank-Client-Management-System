#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenuScreen();

enum enMainMenuOptions { enShowClientList = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClient = 4, enFindClient = 5, enExit = 6 };

struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

bool IsNumberInRange(short Number, short From, short To)
{
    return (Number >= From && Number <= To);
}

string ReadAccountNumber(string Message)
{
    string AccountNumber;

    cout << Message;
    getline(cin >> ws, AccountNumber);

    return AccountNumber;
}

vector <string> SplitString(string Line, string Delim = "#//#")
{
    vector <string> vTokens;
    short Pos = 0;
    string Word = "";

    while ((Pos = Line.find(Delim)) != string::npos)
    {
        Word = Line.substr(0, Pos);

        if (Word != "")
            vTokens.push_back(Word);

        Line.erase(0, Pos + Delim.length());
    }

    if (Line != "")
        vTokens.push_back(Line);

    return vTokens;
}

stClient ConvertClientLineToRecord(string ClientLine, string Delim = "#//#")
{
    stClient Client;
    vector <string> vTokens = SplitString(ClientLine);

    Client.AccountNumber = vTokens[0];
    Client.PinCode = vTokens[1];
    Client.Name = vTokens[2];
    Client.Phone = vTokens[3];
    Client.AccountBalance = stod(vTokens[4]);

    return Client;
}

vector <stClient> LoadClientsFromFile(string FileName)
{
    vector <stClient> vClients;
    fstream File;

    File.open(FileName, ios::in);

    if (File.is_open())
    {
        stClient Client;
        string Line = "";

        while (getline(File, Line))
        {
            Client = ConvertClientLineToRecord(Line);
            vClients.push_back(Client);
        }

        File.close();
    }

    return vClients;
}

void PrintClientRecord(stClient Client)
{
    cout << "| " << left << setw(20) << Client.AccountNumber;
    cout << "| " << left << setw(15) << Client.PinCode;
    cout << "| " << left << setw(30) << Client.Name;
    cout << "| " << left << setw(15) << Client.Phone;
    cout << "| " << left << setw(10) << Client.AccountBalance;
}

void ShowClientListScreen()
{
    vector <stClient> vClients = LoadClientsFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

    cout << "\n___________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(15) << "Pin Code";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(15) << "Phone";
    cout << "| " << left << setw(10) << "Balance";
    cout << "\n___________________________________________________________________________________________________\n\n";

    if (vClients.empty())
    {
        cout << "\t\t\t\t\tNo Clients Available In The System!";
    }
    else
    {
        for (stClient& Client : vClients)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
    }

    cout << "\n___________________________________________________________________________________________________\n\n";
}

bool FindClientByAccountNumber(string AccountNumber, string FileName)
{
    fstream File;

    File.open(FileName, ios::in);

    if (File.is_open())
    {
        stClient Client;
        string Line = "";

        while (getline(File, Line))
        {
            Client = ConvertClientLineToRecord(Line);

            if (Client.AccountNumber == AccountNumber)
            {
                File.close();
                return true;
            }
        }

        File.close();
    }

    return false;
}

stClient ReadNewClient()
{
    stClient Client;

    cout << "\n\nEnter Account Number : ";
    getline(cin >> ws, Client.AccountNumber);

    while (FindClientByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with Account Number [" << Client.AccountNumber << "] already exist, Enter another Account Number : ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter Pin Code : ";
    getline(cin, Client.PinCode);

    cout << "Enter Name : ";
    getline(cin, Client.Name);

    cout << "Enter Phone : ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}

void SaveClientToFile(string FileName, string ClientLine)
{
    fstream File;

    File.open(FileName, ios::out | ios::app);

    if (File.is_open())
    {
        File << ClientLine << endl;
        File.close();
    }
}

string ConvertClientRecordToLine(stClient Client, string Delim = "#//#")
{
    string ClientLine = "";

    ClientLine = Client.AccountNumber + Delim;
    ClientLine += Client.PinCode + Delim;
    ClientLine += Client.Name + Delim;
    ClientLine += Client.Phone + Delim;
    ClientLine += to_string(Client.AccountBalance);

    return ClientLine;
}

void AddNewClient()
{
    stClient Client = ReadNewClient();
    SaveClientToFile(ClientsFileName, ConvertClientRecordToLine(Client));
}

void AddNewClients()
{
    char Answer = 'n';

    do
    {
        cout << "Adding New Client : ";
        AddNewClient();

        cout << "\nClient added successfully, Do you want to add more clients? Y/N? ";
        cin >> Answer;

    } while (tolower(Answer) == 'y');
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details : ";
    cout << "\n-----------------------------------";
    cout << "\nAccount Number  : " << Client.AccountNumber;
    cout << "\nPin Code        : " << Client.PinCode;
    cout << "\nName            : " << Client.Name;
    cout << "\nPhone           : " << Client.Phone;
    cout << "\nAccount Balance : " << Client.AccountBalance;
    cout << "\n-----------------------------------";
}

void MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    for (stClient& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            Client.MarkForDelete = true;
            break;
        }
    }
}

void SaveClientsToFile(string FileName, vector <stClient> vClients)
{
    fstream File;

    File.open(FileName, ios::out);

    if (File.is_open())
    {
        for (stClient& Client : vClients)
        {
            if (!Client.MarkForDelete)
                File << ConvertClientRecordToLine(Client) << endl;
        }

        File.close();
    }
}

void DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;
    char Answer = 'y';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want delete this client? Y/N? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsToFile(ClientsFileName, vClients);

            cout << "\nClient Deleted Successfully.";

            vClients = LoadClientsFromFile(ClientsFileName);
        }
    }
    else
    {
        cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";
    }
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    string AccountNumber = ReadAccountNumber("\nPlease Enter Account Number : ");
    vector <stClient> vClients = LoadClientsFromFile(ClientsFileName);

    DeleteClientByAccountNumber(AccountNumber, vClients);
}

stClient UpdateClientInfo(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\nEnter Pin Code : ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name : ";
    getline(cin, Client.Name);

    cout << "Enter Phone : ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}

void UpdateClientInfoByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;
    char Answer = 'y';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want update this client? Y/N? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = UpdateClientInfo(C.AccountNumber);
                    break;
                }
            }

            SaveClientsToFile(ClientsFileName, vClients);

            cout << "\nClient updated Successfully.";
        }
    }
    else
    {
        cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";
    }
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    string AccountNumber = ReadAccountNumber("\nPlease Enter Account Number : ");
    vector <stClient> vClients = LoadClientsFromFile(ClientsFileName);

    UpdateClientInfoByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    stClient Client;
    string AccountNumber = ReadAccountNumber("\nPlease Enter Account Number : ");
    vector <stClient> vClients = LoadClientsFromFile(ClientsFileName);

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";
    }
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
    system("pause > 0");
}

short ReadMainMenuChoice()
{
    short MainMenuChoice = 0;

    cout << "Choose what do you want to do? [1 to 6]? ";
    cin >> MainMenuChoice;

    while (!IsNumberInRange(MainMenuChoice, 1, 6))
    {
        cout << "Invalid choice, Please choose what do you want to do? [1 to 6]? ";
        cin >> MainMenuChoice;
    }

    return MainMenuChoice;
}

void GoBackToMainMenuScreen()
{
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause > 0");
    ShowMainMenuScreen();
}

void PerformMainMenuOption(enMainMenuOptions Choice)
{
    switch (Choice)
    {
    case enMainMenuOptions::enShowClientList:
        system("cls");
        ShowClientListScreen();
        GoBackToMainMenuScreen();
        break;

    case enMainMenuOptions::enAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenuScreen();
        break;

    case enMainMenuOptions::enDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenuScreen();
        break;

    case enMainMenuOptions::enUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenuScreen();
        break;

    case enMainMenuOptions::enFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenuScreen();
        break;

    case enMainMenuOptions::enExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}

void ShowMainMenuScreen()
{
    system("CLS");
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";
    PerformMainMenuOption((enMainMenuOptions)ReadMainMenuChoice());
}

int main()
{
    ShowMainMenuScreen();

    return 0;
}