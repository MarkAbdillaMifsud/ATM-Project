#pragma once

class BankAccount{
    public:
        BankAccount(const int& accountNumber, const std::string& username);
        int getAccountNumber() const;
        float getBalance() const;
        void setAccountNumber(int accountNumber);
        void setBalance(float balance);
        virtual void withdrawMoney(float amount);
        virtual void depositMoney(float amount);
        void displayBalance();
        std::string getUsername() const;
        virtual std::string getAccountType() const;

    private:
        int accountNumber;
        float balance;
        std::string username;
};