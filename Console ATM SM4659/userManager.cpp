#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include "user.h"
#include "userManager.h"
#include "fileHandler.h"
#include "utility.h"

using namespace std;

UserManager::UserManager(){
    loadUsers();
}

bool UserManager::createUser(const string& username, const string& password){
    if(isUniqueUsername(username) && validatePassword(password)){
        users.emplace(username, User(username, password));
        return true;
    }
    return false;
}

bool UserManager::login(const string& username, const string& password){
    auto it = users.find(username);
    if(it != users.end() && it->second.getPassword() == password){
        loggedInUser = &(it->second);
        return true;
    }
    return false;
}

bool UserManager::isUniqueUsername(const string& username){
    return users.find(username) == users.end();
}

bool UserManager::validatePassword(const string& password){
    return Utility::isValidPassword(password);
}

void UserManager::saveUsers(){
    static int saveCallCount = 0;
    saveCallCount++;
    cout << "saveUsers() called " << saveCallCount << " times." << endl;
    
    try{
        FileHandler::saveUsersToCSV(users, "users.csv");
        cout << "User data saved successfully" << endl;
    } catch (const exception& e){
        cerr << "Error saving user data: " << e.what() << endl;
    }
}

void UserManager::loadUsers(){
    try{
        users.clear();
        FileHandler::loadUsersFromCSV(users, "users.csv");
        cout << "User data loaded successfully" << endl;
    } catch(const exception& e){
        cerr << "Error loading user data: " << e.what() << endl;
    }
}

User* UserManager::getLoggedInUser() const {
    return loggedInUser;
}

unordered_map<string, User>& UserManager::getUsers()
{
    return users;
}

void UserManager::logout(){
    loggedInUser = nullptr;
}