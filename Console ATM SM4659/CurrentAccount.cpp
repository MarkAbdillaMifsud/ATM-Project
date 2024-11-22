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
    setBalance(getBalance() - amount);
}

bool CurrentAccount::isBalanceNegative(){
    return getBalance() < 0;
}

void CurrentAccount::depositMoney(float amount){
    if (amount <= 0) {
        cerr << "Withdrawal amount must be positive." << endl;
        return;
    }
    if(!isBalanceNegative()){
        setBalance(getBalance() + amount);
    } else {
        setBalance((amount * (1.0f + getDepositFee())) + getBalance());
    }
}

float CurrentAccount::getDepositFee() const {
    return depositFee;
}
