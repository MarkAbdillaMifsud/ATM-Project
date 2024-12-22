#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "BankAccount.h"

class User{
    public:
        User(const std::string& username, const std::string& password);
        std::string getUsername() const;
        std::string getPassword() const;
        void setUsername(const std::string& username);
        void setPassword(const std::string& password);

        void addBankAccount(std::shared_ptr<BankAccount> account);
        void removeBankAccount(int accountNumber);
        BankAccount* getBankAccount(int accountNumber);
        std::unordered_map<int, std::shared_ptr<BankAccount>> getAllBankAccounts() const;
        bool isZeroBankAccounts();

    private:
        std::string username;
        std::string password;
        std::unordered_map<int, std::shared_ptr<BankAccount>> bankAccounts;
};