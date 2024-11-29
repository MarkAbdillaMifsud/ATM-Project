#include <cctype>
#include <string>
#include <algorithm>
#include "utility.h"

using namespace std;

bool Utility::isValidPassword(const string& password){
    if(password.length() < 8 || password.length() > 15){
        return false;
    }
    bool hasNumber = false;
    bool hasSymbol = false;
    for (char ch : password){
        if(isdigit(ch)){
            hasNumber = true;
        }
        if(ispunct(ch)){
            hasSymbol = true;
        }
    }
    return hasNumber && hasSymbol;
}

bool Utility::isValidAccountType(string accountType)
{
    transform(accountType.begin(), accountType.end(), accountType.begin(),[](unsigned char c)
    {
        return tolower(c);
    });

    return accountType == "savings" || accountType == "current";
}