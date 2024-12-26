#include <iostream>
#include "BankAccount.h"

using namespace std;

BankAccount::BankAccount(const int &accountNumber, const string &username)
    : accountNumber(accountNumber), username(username) {}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

float BankAccount::getBalance() const {
    return balance;
}

void BankAccount::setAccountNumber(int accountNumber){
    this->accountNumber = accountNumber;
}

void BankAccount::setBalance(float balance){
    this->balance = balance;
}

void BankAccount::withdrawMoney(float amount) {
    balance -= amount;
}

void BankAccount::depositMoney(float amount){
    balance += amount;
}

void BankAccount::displayBalance(){
    cout << "The current balance of account: " << accountNumber << " is EUR" << balance << endl;
}

string BankAccount::getUsername() const {
    return username;
}