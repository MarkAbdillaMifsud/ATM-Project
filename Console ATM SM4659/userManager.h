#pragma once
#include "user.h"
#include <vector>

class UserManager{
    public:
        UserManager();
        bool login(const string& userName, const string& password);
        bool createUser(const string& userName, const string& password);
        void saveUsers();
        void loadUsers();
        bool isUniqueUsername(const string &username);
        bool validatePassword(const string &password);

    private:
        vector<User> users;
};