#include <stdexcept>
#include <ctime>
#include "SavingsAccount.h"

using namespace std;

SavingsAccount::SavingsAccount(const int& accountNumber, float interestRate):
    BankAccount(accountNumber), interestRate(interestRate){
    // set last interest date to time of account creation
    lastInterestDate = time(nullptr);
    }

void SavingsAccount::withdrawMoney(float amount){
    if(amount > getBalance()){
        throw std::runtime_error("Insufficient balance. Withdrawals cannot exceed the current balance.");
    }
    setBalance(getBalance() - amount);
}

void SavingsAccount::applyInterest(){
    time_t currentTime = time(nullptr);

    double secondsSinceLastInterest = difftime(currentTime, lastInterestDate);

    const double SECONDS_IN_A_YEAR = 365.25 * 24 * 60 * 60;

    if(secondsSinceLastInterest >= SECONDS_IN_A_YEAR){
        int yearsElapsed = static_cast<int>(secondsSinceLastInterest / SECONDS_IN_A_YEAR);

        for(int i = 0; i < yearsElapsed; ++i){
            setBalance(getBalance() * (1.0f + interestRate));
        }

        lastInterestDate += static_cast<time_t>(yearsElapsed * SECONDS_IN_A_YEAR);
    }
}

float SavingsAccount::getInterestRate() const {
    return interestRate;
}



