#pragma once
#include "user.h"
#include <vector>

#using namespace std;

class UserManager{
    public:
        UserManager();
        bool login(const string& userName, const string& password);
        bool createUser(const string& userName, const string& password);
        void saveUsers();
        void loadUsers();
    
    private:
        vector<User> users;
        bool isUniqueUsername(const string& username);
        bool validatePassword(const string& password);
};