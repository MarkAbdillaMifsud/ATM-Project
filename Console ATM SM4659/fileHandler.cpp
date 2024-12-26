#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include "fileHandler.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

using namespace std;

void FileHandler::loadUsersFromCSV(unordered_map<string, User> &users, const string &filename)
{
    ifstream file(filename);

    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    bool isFirstLine = true;

    while(getline(file, line)){
        if(isFirstLine){ //skip header row
            isFirstLine = false;
            continue;
        }

        istringstream ss(line);
        string username, password;
        if(getline(ss, username, ',') && getline(ss, password, ',')){
            if(users.find(username) == users.end()){
                users.emplace(username, User(username, password));
            }
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
    file.close();
}

void FileHandler::loadAccountsFromCSV(std::unordered_map<int, std::shared_ptr<BankAccount>> &bankAccounts, const std::string &filename)
{
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    bool isFirstLine = true;

    while(getline(file, line)){
        if(isFirstLine){
            isFirstLine = false;
            continue;
        }

        istringstream ss(line);
        string username, accountType, accountNumberStr, balanceStr;
        if (getline(ss, username, ',') && getline(ss, accountType, ',') && getline(ss, accountNumberStr, ',') && getline(ss, balanceStr, ',')) {
            int accountNumber = stoi(accountNumberStr);
            float balance = stof(balanceStr);

            shared_ptr<BankAccount> account;
            if(accountType == "SavingsAccount"){
                account = make_shared<SavingsAccount>(accountNumber, username);
            } else if(accountType == "CurrentAccount"){
                account = make_shared<CurrentAccount>(accountNumber, username);
            }

            account->setBalance(balance);
            bankAccounts.emplace(accountNumber, account);
        }
    }
    file.close();
}

void FileHandler::saveUsersToCSV(const unordered_map<string, User>& users, const string& filename) {
    ofstream file(filename, ios::out | ios::trunc);

    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Write the header
    file << "Username,Password\n";

    if (file.fail()) {
        cerr << "Error writing header to file: " << filename << endl;
        file.close();
        return;
    }

    // Write user data
    for (const auto& pair : users) {
        file << pair.first << "," << pair.second.getPassword() << "\n";
    }

    if (file.fail()) {
        cerr << "Error writing to file: " << filename << endl;
    }

    file.close();
}

void FileHandler::saveAccountsToCSV(const unordered_map<int, shared_ptr<BankAccount>> &bankAccounts, const string &filename)
{
    ofstream file(filename, ios::out | ios::trunc);
    if (!file.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Write header
    file << "Username,AccountNumber,AccountType,Balance\n";

    for (const auto &pair : bankAccounts)
    {
        int accountNumber = pair.first;
        auto account = pair.second;

        string accountType = "BankAccount"; // Default
        if (dynamic_cast<SavingsAccount *>(account.get()))
        {
            accountType = "SavingsAccount";
        }
        else if (dynamic_cast<CurrentAccount *>(account.get()))
        {
            accountType = "CurrentAccount";
        }

        string username = account->getUsername();
        file << username << "," << accountNumber << "," << accountType << "," << account->getBalance() << "\n";
    }

    file.close();
}