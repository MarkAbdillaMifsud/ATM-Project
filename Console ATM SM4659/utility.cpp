#include <cctype>
#include <string>
#include "utility.h"

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