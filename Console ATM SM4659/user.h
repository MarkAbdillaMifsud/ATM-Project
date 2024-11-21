#pragma once
#include <string>

class User{
    public:
        User(const string& username, const string& password);
        string getUsername() const;
        string getPassword() const;
        void setUsername(const string& username);
        void setPassword(const string& password);
    
    private:
        string username;
        string password;
};