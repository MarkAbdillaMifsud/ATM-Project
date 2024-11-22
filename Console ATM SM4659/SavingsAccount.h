#pragma once
#include "BankAccount.h"
#include <ctime>

class SavingsAccount : public BankAccount {
    public:
        SavingsAccount(const int& accountNumber, float interestRate = 0.03f);
        void withdrawMoney(float amount) override;
        void applyInterest();
        float getInterestRate() const;
    
    private:
        float interestRate;
        std::time_t lastInterestDate;
};