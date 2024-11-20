#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "user.h"
#include "userManager.h"
#include "fileHandler.h"

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
    try{
        FileHandler fileHandler;
        fileHandler.saveToCSV(users, "userAccounts.csv");
        cout << "User data saved successfully" << endl;
    } catch (const exception& e){
        cerr << "Error saving user data: " << e.what() << endl;
    }
}

void UserManager::loadUsers(){
    try{
        users.clear();
        FileHandler fileHandler;
        fileHandler.loadFromCSV(users, "userAccounts.csv");
        cout << "User data loaded successfully" << endl;
    } catch(const exception& e){
        cerr << "Error loading user data: " << e.what() << endl;
    }
}