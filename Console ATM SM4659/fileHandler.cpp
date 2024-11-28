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

void FileHandler::loadFromCSV(unordered_map<string, User> &users, const string &filename)
{
    ifstream file(filename);

    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while(getline(file, line)){
        istringstream ss(line);
        string username, password;
        if(getline(ss, username, ',') && getline(ss, password)){
            users.emplace(username, User(username, password));
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
    file.close();
}

void FileHandler::saveToCSV(const unordered_map<string, User>& users, const string& filename){
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << "Username,Password,AccountType,AccountNumber,Balance\n";

    if (file.fail()) {
        cerr << "Error writing header to file: " << filename << endl;
        file.close();
        return;
    }

    for(const auto& userPair : users){
        const User &user = userPair.second;

        file << user.getUsername() << "," << user.getPassword();

        const auto& accounts = user.getAllBankAccounts();
        for(const auto& accountPair : accounts){
            int accountNumber = accountPair.first;
            auto account = accountPair.second;

            string accountType = "BankAccount";
            if(dynamic_cast<SavingsAccount*>(account.get())){
                accountType = "SavingsAccount";
            } else if (dynamic_cast<CurrentAccount*>(account.get())){
                accountType = "CurrentAccount";
            }
            file << "," << accountType << "," << account->getAccountNumber() << "," << account->getBalance();
        }
        file << "\n";

        if (file.fail())
        {
            std::cerr << "Error writing to file: " << filename << std::endl;
            file.close();
            return;
        }
    }

    file.close();
}