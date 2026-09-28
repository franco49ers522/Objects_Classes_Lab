// Author: Jareth Franco
// Date: September 28, 2026
// Purpose: Declare a bank account with private data and public operations.

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public:
    BankAccount();
    BankAccount(const std::string& number, const std::string& name,
                double initialBalance);

    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;
    bool setAccountHolderName(const std::string& name);
    bool deposit(double amount);
    bool withdraw(double amount);
};

#endif
