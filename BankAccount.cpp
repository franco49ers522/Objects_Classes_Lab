// Author: Jareth Franco
// Date: September 28, 2026
// Purpose: Implement account initialization and validated balance changes.

#include "BankAccount.h"
#include <cmath>
#include <stdexcept>

BankAccount::BankAccount()
    : accountNumber("Unassigned"), accountHolderName("Unknown"), balance(0.0) {}

BankAccount::BankAccount(const std::string& number, const std::string& name,
                         double initialBalance)
    : accountNumber(number), accountHolderName(name), balance(initialBalance) {
    if (number.find_first_not_of(" \t\r\n") == std::string::npos ||
        name.find_first_not_of(" \t\r\n") == std::string::npos ||
        !std::isfinite(initialBalance) || initialBalance < 0.0) {
        throw std::invalid_argument("Invalid account details.");
    }
}

std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

double BankAccount::getBalance() const {
    return balance;
}

bool BankAccount::setAccountHolderName(const std::string& name) {
    if (name.find_first_not_of(" \t\r\n") == std::string::npos) {
        return false;
    }
    accountHolderName = name;
    return true;
}

bool BankAccount::deposit(double amount) {
    // Reject invalid amounts and balance overflow before changing the account.
    if (!std::isfinite(amount) || amount <= 0.0 ||
        !std::isfinite(balance + amount)) {
        return false;
    }
    balance += amount;
    return true;
}

bool BankAccount::withdraw(double amount) {
    if (!std::isfinite(amount) || amount <= 0.0 || amount > balance) {
        return false;
    }
    balance -= amount;
    return true;
}
