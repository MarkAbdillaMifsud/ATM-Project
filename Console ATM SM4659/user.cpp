#include "user.h"

using namespace std;

User::User(const string& userName, const string& password) : username(userName), password(password) {}

string User::getUsername() const{
    return username;
}

string User::getPassword() const{
    return password;
}

void User::setUsername(const string& username) {
    this->username = username;
}

void User::setPassword(const string& password){
    this->password = password;
}