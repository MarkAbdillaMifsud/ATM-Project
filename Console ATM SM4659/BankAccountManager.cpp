#include <iostream>
#include <unordered_map>
#include "BankAccountManager.h"
#include "fileHandler.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

using namespace std;

BankAccountManager::BankAccountManager(UserManager& userManager) : userManager(userManager){}

bool BankAccountManager::isUniqueAccountNumber(const int& accountNumber){
    return bankAccounts.find(accountNumber) == bankAccounts.end();
}

void BankAccountManager::loadAccounts(){
    try
    {
        bankAccounts.clear();
        FileHandler::loadAccountsFromCSV(bankAccounts, "bankAccounts.csv");
        cout << "Bank Account data loaded successfully" << endl;

        // Associate each account with the corresponding user
        for (auto &pair : bankAccounts)
        {
            auto account = pair.second;
            string username = account->getUsername();

            auto &users = userManager.getUsers();
            auto userIt = users.find(username);
            if (userIt != users.end())
            {
                userIt->second.addBankAccount(account);
            }
            else
            {
                cerr << "User " << username << " not found for account " << account->getAccountNumber() << endl;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Error loading bank account data: " << e.what() << endl;
    }
}

void BankAccountManager::saveAccounts(){
    try
    {
        FileHandler::saveAccountsToCSV(bankAccounts, "bankAccounts.csv");
        cout << "Bank account data saved successfully" << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error saving bank account data: " << e.what() << endl;
    }
}

void BankAccountManager::addBankAccount(std::shared_ptr<BankAccount> account)
{
    int accountNumber = account->getAccountNumber();
    string username = account->getUsername();
    if (!isUniqueAccountNumber(accountNumber))
    {
        cerr << "An account with account number: " << accountNumber << " already exists." << endl;
        return;
    }

    bankAccounts.emplace(accountNumber, account);
    // Associate with user
    auto &users = userManager.getUsers();
    auto userIt = users.find(username);
    if (userIt != users.end())
    {
        userIt->second.addBankAccount(account);
        cout << "Account with account number: " << accountNumber << " successfully created for user " << username << endl;
    }
    else
    {
        cerr << "User " << username << " not found for account " << accountNumber << endl;
    }
}