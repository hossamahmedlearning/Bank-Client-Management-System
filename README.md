# 🏦 Bank System (C++ Console Application)

A robust and modular **Bank System** console application built using C++ as part of the advanced programming curriculum. This project demonstrates practical implementation of file handling, CRUD operations, structured programming principles, and clean code architecture.

---

## 🚀 Features & Main Menu Operations

The application provides an interactive menu-driven interface allowing users to perform complete client management:

1. **Show Client List:** Displays a formatted table of all registered clients loaded from a text file, including account count metrics.
2. **Add New Clients:** Allows adding single or multiple new clients with built-in validation to prevent duplicate account numbers.
3. **Find Client:** Searches for a specific client by their account number and displays their client card details.
4. **Update Client Info:** Modifies existing client records (Pin Code, Name, Phone, Balance) by account number with persistent file updates.
5. **Delete Client:** Safely removes a client record from the file using a marker-based deletion and confirmation workflow.
6. **Exit:** Gracefully terminates the program session.

---

## 🛠️ Technical Highlights & Concepts Applied

- **File I/O Streams (`<fstream>`):** Persistent data storage utilizing text files (`Clients.txt`) for saving, loading, updating, and deleting records without losing data upon exit.
- **String Parsing & Formatting:** Custom delimiters (`#//#`) to serialize and deserialize structured records into line-based text formats (`vector <string> SplitString`).
- **Data Structures (`struct`):** Custom `stClient` data models encapsulating attributes like `AccountNumber`, `PinCode`, `Name`, `Phone`, `AccountBalance`, and deletion flags.
- **Modular Architecture:** Strictly adheres to the **Single Responsibility Principle (SRP)**, separating user interface screens, business logic validation, and file data access layers into clean functions.
- **Input Validation & Safety:** Robust range-checking routines and stream state management (`cin >> ws`) to handle user inputs cleanly.

---

## 📂 Code Structure Overview

```text
├── Clients.txt            # Local database text file storing client records
├── main.cpp               # Core application source code containing screens & logic
└── README.md              # Project documentation
💻 How to Run
Clone or download the repository to your local machine.

Open the project in an IDE supporting C++ (such as Visual Studio or Code::Blocks).

Compile and run main.cpp.

Ensure Clients.txt is in the working directory (the program will create or manage it automatically during runtime).

👤 Author
Hossam Ahmed Ragab
