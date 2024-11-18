#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "user.h"
#include "userManager.h"

using namespace std;

UserManager::UserManager(){
    loadUsers();
}

bool UserManager::createUser(const string& username, const string& password){
    if(isUniqueUsername(username) && validatePassword(password)){
        users.emplace_back(username, password);
        return true;
    }
    return false;
}

bool UserManager::login(const string& username, const string& password){
    for(const User& user : users){
        if(user.getUsername() == username && user.getPassword() == password){
            return true;
        }
    }
    return false;
}

bool UserManager::isUniqueUsername(const string& username){
    for (const User &user : users){
        if(user.getUsername() == username){
            return false;
        }
    }
    return true;
}

bool UserManager::validatePassword(const string& password){
    for (const User &user : users){
        if(user.getPassword() == password){
            return false;
        }
    }
    return true;
}

void UserManager::saveUsers(){
    //TODO: Implement later (this is where we save new accounts and update users on the CSV)
    ofstream userAccountsFile{"userAccounts.csv"};

    if(userAccountsFile.fail()){
        throw invalid_argument("File not found");
    }

    for(const User& user : users){
        userAccountsFile << user.getUsername() << "," << user.getPassword() << "\n";
    }

    userAccountsFile.close();
    cout << "User data saved successfully" << endl;
}

void UserManager::loadUsers(){
    // TODO: Implement later
}