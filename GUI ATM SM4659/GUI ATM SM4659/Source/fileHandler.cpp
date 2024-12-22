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

void FileHandler::loadAccountsFromCSV(unordered_map<string, User>& users, const string& filename){
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
                account = make_shared<SavingsAccount>(accountNumber);
            } else if(accountType == "CurrentAccount"){
                account = make_shared<CurrentAccount>(accountNumber);
            }

            account->setBalance(balance);
            auto it = users.find(username);
            if (it == users.end()) {
                auto result = users.emplace(username, User(username, ""));
                it = result.first;
            }
            it->second.addBankAccount(account);
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

void FileHandler::saveAccountsToCSV(const unordered_map<string, User>& users, const string& filename){
    ofstream file(filename, ios::out | ios::trunc);

    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << "Username,AccountType,AccountNumber,Balance\n";

    for(const auto& pair : users){
        const auto& user = pair.second;
        for(const auto& accountPair : user.getAllBankAccounts()){
            auto account = accountPair.second;

            string accountType = dynamic_cast<SavingsAccount*>(account.get()) ? "SavingsAccount" :
                                 dynamic_cast<CurrentAccount*>(account.get()) ? "CurrentAccount" :
                                 "BankAccount";
            file << user.getUsername() << "," << accountType << "," << account->getAccountNumber() << "," << account->getBalance() << "\n";
        }
    }

    file.close();
}