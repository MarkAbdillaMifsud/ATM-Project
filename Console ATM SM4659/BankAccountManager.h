#pragma once
#include "BankAccount.h"
#include <unordered_map>
#include <string>
#include "userManager.h"

class BankAccountManager {
    public:
        BankAccountManager(UserManager& userManager);
        bool isUniqueAccountNumber(const int &accountNumber);

        void loadAccounts();
        void saveAccounts();

        void addBankAccount(std::shared_ptr<BankAccount> account);

    private:
        std::unordered_map<int, std::shared_ptr<BankAccount>> bankAccounts;
        UserManager& userManager;
};