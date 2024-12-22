#include <unordered_map>
#include "BankAccountManager.h"

using namespace std;

BankAccountManager::BankAccountManager(){}

bool BankAccountManager::isUniqueAccountNumber(const int& accountNumber){
    return bankAccounts.find(accountNumber) == bankAccounts.end();
}