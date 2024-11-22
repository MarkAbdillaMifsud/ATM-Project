#pragma once
#include "BankAccount.h"

class CurrentAccount : public BankAccount {
    public:
        CurrentAccount(const int& accountNumber, float depositFee = 0.1f);
        void withdrawMoney(float amount) override;
        void depositMoney(float amount) override;
        float getDepositFee() const;
        bool isBalanceNegative();
    
    private:
        float depositFee;
};