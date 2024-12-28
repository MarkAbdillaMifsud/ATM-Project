#pragma once
#include "BankAccount.h"
#include <ctime>

class SavingsAccount : public BankAccount {
    public:
        SavingsAccount(const int& accountNumber, const std::string& username, float interestRate = 0.03f);
        void withdrawMoney(float amount) override;
        void applyInterest();
        float getInterestRate() const;
        std::string getAccountType() const override;
    
    private:
        float interestRate;
        std::time_t lastInterestDate;
};