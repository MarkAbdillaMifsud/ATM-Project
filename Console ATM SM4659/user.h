#pragma once
#include <string>

using namespace std;

class User{
    public:
        User(const string& userName, const string& password);
        string getUsername() const;
        string getPassword() const;
        void setUsername(string userName);
        void setPassword(string password);
    
    private:
        string userName;
        string password;
};