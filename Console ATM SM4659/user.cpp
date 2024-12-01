#include <memory>
#include <iostream>
#include "user.h"

using namespace std;

User::User(const string& userName, const string& password) : username(userName), password(password) {}

string User::getUsername() const{
    return username;
}

string User::getPassword() const{
    return password;
}

void User::setUsername(const string& username) {
    this->username = username;
}

void User::setPassword(const string& password){
    this->password = password;
}

void User::addBankAccount(shared_ptr<BankAccount> account){
    int accountNumber = account->getAccountNumber();
    if(bankAccounts.find(accountNumber) != bankAccounts.end()){
        cerr << "An account with account number: " << accountNumber << " already exists." << endl;
        return;
    }

    bankAccounts[accountNumber] = account;
    cout << "Account with account number: " << accountNumber << " successfully created" << endl;
}

void User::removeBankAccount(int accountNumber){
    if(bankAccounts.find(accountNumber) == bankAccounts.end()){
        cerr << "An account with account number: " << accountNumber << " does not exist." << endl;
        return;
    }
        bankAccounts.erase(accountNumber);
        cout << "Account with account number: " << accountNumber << " successfully erased" << endl;
}

BankAccount* User::getBankAccount(int accountNumber){
    auto it = bankAccounts.find(accountNumber);
    if(it != bankAccounts.end()){
        return it->second.get();
    }

    cerr << "An account with account number: " << accountNumber << " does not exist." << endl;
    return nullptr;
}

unordered_map<int, shared_ptr<BankAccount>> User::getAllBankAccounts() const {
    return bankAccounts;
}

bool User::isZeroBankAccounts(){
    return getAllBankAccounts().empty();
}