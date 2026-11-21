# 🏦 Bank System (C++ Console Application)

A modular **Bank System** console application written in C++ featuring client CRUD operations, a dedicated **Transactions** sub-menu, input validation, and persistent text-file storage (`Clients.txt`).

---

## 🚀 Features

### Main Menu (`enMainMenuOptions`)
1. **Show Client List:** Loads records from `Clients.txt` and displays all clients in a formatted table along with the total client count.
2. **Add New Client:** Adds one or more clients with duplicate account number checks and positive balance validation.
3. **Delete Client:** Searches by account number, prints the client card, asks for confirmation, marks the record for deletion, and updates `Clients.txt`.
4. **Update Client:** Updates a client's Pin Code, Name, Phone, and Balance with confirmation and file persistence.
5. **Find Client:** Searches for a client by account number and displays their full details card.
6. **Transactions:** Opens the **Transactions Menu** (`enTransactionsMenuOptions`):
   - **Deposit:** Adds a validated positive amount to a client's balance and saves the updated records.
   - **Withdraw:** Checks that the withdrawal amount is positive and does not exceed the client's available balance before updating the file.
   - **Total Balances:** Displays each client's account number, name, and balance alongside the combined total balance.
7. **Exit:** Displays the exit screen and cleanly terminates the application.

---

## 🛠️ Technical Highlights

- **File Persistence (`<fstream>`):** Reads, appends, and rewrites client records in `Clients.txt`.
- **Serialization & Parsing:** Uses `#//#` delimiters (`SplitString`, `ConvertClientLineToRecord`, `ConvertClientRecordToLine`) to convert between `stClient` structs and text lines.
- **Input & Stream Safety:** Clears invalid stream states (`cin.clear()` / `cin.ignore()`) on non-numeric input, checks menu ranges, and enforces positive monetary amounts.
- **Iterative Menu Loop:** Uses `while` loops for the Main Menu and Transactions Menu to avoid recursive call-stack growth during extended sessions.

---

## 📂 Project Structure

```text
├── Clients.txt          # Persistent text file storing serialized client records
├── main.cpp             # Core application source code (menus, CRUD, transactions)
└── README.md            # Project documentation
