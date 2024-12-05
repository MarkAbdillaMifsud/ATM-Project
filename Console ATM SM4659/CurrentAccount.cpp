#include <iostream>
#include "CurrentAccount.h"

using namespace std;

CurrentAccount::CurrentAccount(const int &accountNumber, float depositFee) 
    : BankAccount(accountNumber), depositFee(depositFee) {}

void CurrentAccount::withdrawMoney(float amount){
    if(amount <= 0){
        cerr << "Withdrawal amount must be positive." << endl;
        return;
    }

    float currentBalance = getBalance();

    if(currentBalance >= amount){
        setBalance(currentBalance - amount);
    } else {
        float overdraft = amount - currentBalance;
        float penalty = overdraft * getDepositFee();
        setBalance(currentBalance - amount - penalty);
    }
}

bool CurrentAccount::isBalanceNegative(){
    return getBalance() < 0;
}

void CurrentAccount::depositMoney(float amount){
    if (amount <= 0) {
        cerr << "Deposit amount must be positive." << endl;
        return;
    }

    setBalance(getBalance() + amount);
}

float CurrentAccount::getDepositFee() const {
    return depositFee;
}
