#pragma once
#include <string>

class User{
    public:
        User(const std::string& username, const std::string& password);
        std::string getUsername() const;
        std::string getPassword() const;
        void setUsername(const std::string& username);
        void setPassword(const std::string& password);
    
    private:
        std::string username;
        std::string password;
};