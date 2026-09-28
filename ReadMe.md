# BankAccount Class

**Author:** Jareth Franco  
**Date:** September 28, 2026

A C++ program that uses a `std::vector` of bank accounts to create accounts, list balances, deposit, withdraw, and update holder names. Accounts are kept only while the program runs.

## Data Dictionary

All attributes are private.

| Attribute | Data Type | Description |
| --- | --- | --- |
| `accountNumber` | `std::string` | Account identifier; the menu prevents duplicates. |
| `accountHolderName` | `std::string` | Account owner's name. |
| `balance` | `double` | Current nonnegative balance. |

## Methods List

All methods are public.

| Method Signature | Return Type | Description |
| --- | --- | --- |
| `BankAccount()` | Constructor | Sets number to Unassigned, name to Unknown, and balance to 0. |
| `BankAccount(const std::string& number, const std::string& name, double initialBalance)` | Constructor | Sets account details; throws `std::invalid_argument` for blank details or an invalid balance. |
| `getAccountNumber() const` | `std::string` | Returns the account number. |
| `getAccountHolderName() const` | `std::string` | Returns the holder's name. |
| `getBalance() const` | `double` | Returns the balance. |
| `setAccountHolderName(const std::string& name)` | `bool` | Updates a nonblank name; returns false if invalid. |
| `deposit(double amount)` | `bool` | Adds a positive, finite amount; returns false for invalid amounts or overflow. |
| `withdraw(double amount)` | `bool` | Subtracts a positive, finite amount; returns false for invalid amounts or insufficient funds. |

## Build and Run

With a C++11 or newer compiler:

```sh
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp BankAccount.cpp -o bank_accounts
```

Run `./bank_accounts` on Linux/macOS or `.\bank_accounts.exe` in Windows PowerShell. Choose options 1-5 to manage accounts or 0 to exit. Invalid input is rejected without changing account data. All console input/output is in `main.cpp`.
