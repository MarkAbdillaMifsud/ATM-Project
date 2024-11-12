#include "user.h"

using namespace std;

User::User(const string& userName, const string& password):
    userName(userName), password(password){}

string User::getUsername() const{
    return userName;
}

string User::getPassword() const{
    return password;
}

void User::setUsername(string userName){
    this->userName = userName;
}

void User::setPassword(string password){
    this->password = password;
}