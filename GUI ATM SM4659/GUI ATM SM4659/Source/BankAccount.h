#pragma once

class BankAccount{
    public:
        BankAccount(const int& accountNumber);
        int getAccountNumber() const;
        float getBalance() const;
        void setAccountNumber(int accountNumber);
        void setBalance(float balance);
        virtual void withdrawMoney(float amount);
        virtual void depositMoney(float amount);
        void displayBalance();

    private:
        int accountNumber;
        float balance;
};