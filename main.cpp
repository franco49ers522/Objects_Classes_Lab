// Author: Jareth Franco
// Date: September 28, 2026
// Purpose: Manage bank accounts through a menu using a vector of objects.

#include "BankAccount.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Read a nonempty line and remove surrounding whitespace.
bool readText(const std::string& prompt, std::string& value) {
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, value)) {
            return false;
        }
        const auto first = value.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            const auto last = value.find_last_not_of(" \t\r\n");
            value = value.substr(first, last - first + 1);
            return true;
        }
        std::cout << "Input cannot be blank.\n";
    }
}

// Parse the entire line so entries such as 25abc are rejected.
bool readAmount(const std::string& prompt, double& amount, bool allowZero) {
    std::string line;
    while (readText(prompt, line)) {
        std::istringstream input(line);
        if (input >> amount) {
            input >> std::ws;
            if (input.eof() && std::isfinite(amount) &&
                (allowZero ? amount >= 0.0 : amount > 0.0)) {
                return true;
            }
        }
        std::cout << (allowZero ? "Enter a finite number of 0 or more.\n"
                               : "Enter a finite number greater than 0.\n");
    }
    return false;
}

int findAccount(const std::vector<BankAccount>& accounts,
                const std::string& number) {
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNumber() == number) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void displayAccount(const BankAccount& account) {
    std::cout << "Account: " << account.getAccountNumber()
              << " | Holder: " << account.getAccountHolderName()
              << " | Balance: $" << account.getBalance() << '\n';
}

int main() {
    std::vector<BankAccount> accounts;
    std::cout << std::fixed << std::setprecision(2);
    std::string choice;

    while (true) {
        std::cout << "\nBank Account Management\n"
                  << "1. Create account\n"
                  << "2. List accounts\n"
                  << "3. Deposit\n"
                  << "4. Withdraw\n"
                  << "5. Change account holder name\n"
                  << "0. Exit\n";
        if (!readText("Choose an option: ", choice) || choice == "0") {
            break;
        }

        if (choice == "1") {
            std::string number;
            std::string name;
            double initialBalance;
            if (!readText("Account number: ", number)) {
                break;
            }
            if (findAccount(accounts, number) != -1) {
                std::cout << "That account number already exists.\n";
                continue;
            }
            if (!readText("Account holder name: ", name) ||
                !readAmount("Initial balance: $", initialBalance, true)) {
                break;
            }
            accounts.push_back(BankAccount(number, name, initialBalance));
            std::cout << "Account created.\n";
        } else if (choice == "2") {
            if (accounts.empty()) {
                std::cout << "No accounts available.\n";
            }
            for (const BankAccount& account : accounts) {
                displayAccount(account);
            }
        } else if (choice == "3" || choice == "4" || choice == "5") {
            if (accounts.empty()) {
                std::cout << "No accounts available.\n";
                continue;
            }
            std::string number;
            if (!readText("Account number: ", number)) {
                break;
            }
            const int index = findAccount(accounts, number);
            if (index == -1) {
                std::cout << "Account not found.\n";
                continue;
            }

            // A reference updates the object stored in the vector.
            BankAccount& account = accounts[index];
            if (choice == "5") {
                std::string name;
                if (!readText("New account holder name: ", name)) {
                    break;
                }
                if (account.setAccountHolderName(name)) {
                    std::cout << "Name updated.\n";
                }
            } else {
                double amount;
                if (!readAmount("Amount: $", amount, false)) {
                    break;
                }
                if (choice == "3") {
                    std::cout << (account.deposit(amount)
                        ? "Deposit successful.\n"
                        : "Deposit rejected: balance would be too large.\n");
                } else {
                    std::cout << (account.withdraw(amount)
                        ? "Withdrawal successful.\n"
                        : "Withdrawal rejected: insufficient funds.\n");
                }
            }
            displayAccount(account);
        } else {
            std::cout << "Invalid option. Choose 0 through 5.\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
