#pragma once
#include "user.h"
#include <unordered_map>

class UserManager{
    public:
        UserManager();
        bool login(const std::string &userName, const std::string &password);
        bool createUser(const std::string &userName, const std::string &password);
        void saveUsers();
        void loadUsers();
        void logout();
        bool isUniqueUsername(const std::string &username);
        bool validatePassword(const std::string &password);
        User* getLoggedInUser() const;

    private:
        std::unordered_map<std::string, User> users;
        User* loggedInUser;
};