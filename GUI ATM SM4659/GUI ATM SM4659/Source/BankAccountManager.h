#pragma once
#include "BankAccount.h"
#include <unordered_map>

class BankAccountManager {
    public:
        BankAccountManager();
        bool isUniqueAccountNumber(const int &accountNumber);
    
    private:
        std::unordered_map<int, BankAccount> bankAccounts;
};