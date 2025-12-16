# 🏦 Banking System (Sistema Bancário em C)

A modular command-line banking system developed in **C**. This project simulates core banking operations managing accounts, balances, and transactions.

## 🚀 Features
- **Account Management:** Open new accounts, update contact info, and close accounts.
- **Transactions:** Deposit, Withdraw, and Transfer between accounts.
- **Search & Listing:** Find accounts by ID or CPF, and list active/closed accounts.
- **Data Persistence:** Uses `structs` to manage data in memory during execution.

## 🛠️ Tech Stack
- **Language:** C (Standard C99)
- **Concepts:** Structs, Pointers, Modularization (.h/.c), Arrays.

## 💻 How to Compile and Run
You can compile this project using **GCC**.

1. Open your terminal in the project folder.
2. Run the compilation command:
   ```bash
   gcc main.c conta.c -o banco
   Windows: .\banco.exe
   Linux/Mac: ./banco
   
## 📋 Project Structure
- `main.c`: Entry point and menu loop.
- `conta.c`: Implementation of banking logic (withdraw, deposit, etc.).
- `conta.h`: Prototypes and Struct definitions.

---
Made by [Rachel Coelho](https://www.linkedin.com/in/rdcoelho)

   
