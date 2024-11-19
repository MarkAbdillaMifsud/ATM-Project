#include <iostream>
#include "menu.h"
#include "userManager.h"

using namespace std;

MainMenu::MainMenu(){}
int userOption;

void MainMenu::displayMenu(){
    cout << "***********************************" << endl;
    cout << "Welcome to user's ATM" << endl;
    cout << "***********************************" << endl;
    cout << "1) Login to system" << endl;
    cout << "2) Create new user account" << endl;
    cout << "3) Quit" << endl;
    cout << "***********************************" << endl;
    cout << "Enter your choice: " << endl;
}

int MainMenu::getUserOption(){
    cin >> userOption;
    return userOption;
}

void MainMenu::processUserChoice(int userChoice, bool &repeat){
    switch(userChoice){
        case 1: 
            cout << "Time to login" << endl;
            login();
            break;
        case 2: 
            cout << "Create account" << endl;
            createAccount();
            break;
        case 3:
            cout << "Goodbye" << endl;
            break;
        default:
            cout << "Invalid entry" << endl;
            break;
    }
}

void MainMenu::login(){
    string username, password;
    
    cout << "Enter your username" << endl;
    cin >> username;
    cout << "Enter your password" << endl;
    cin >> password;

    if(userManager.login(username, password)){
        cout << "Login successful. Welcome, " << username << ". \n";
        //Send user to account menu
    } else {
        cout << "Login unsuccessful. Please try again" << endl;
    }
}

void MainMenu::createAccount(){
    string username, password, confirmPassword;
    bool validUsername = false; 
    bool validPassword = false;
    cout << "Please enter a username for your account." << endl;
    do{
        cin >> username;
        if(!userManager.isUniqueUsername(username)){
            cout << "That username already exists. Please enter another username." << endl;
        } else {
            validUsername = true;
        }
    } while(!validUsername);
    cout << "Please enter a password. Password should be between 8 and 15 characters long and contain at least 1 number and 1 symbol." << endl;
    do{
        cin >> password;
        cout << "Enter the same password again." << endl;
        cin >> confirmPassword;
        if(password != confirmPassword){
            cout << "Your confirm password does not match your password. Please try again." << endl;
            continue;
        }
        if(!userManager.validatePassword(password)){
            cout << "That password is invalid. Please try again." << endl;
            continue;
        } else {
            validPassword = true;
        }
    } while(!validPassword);

    if(userManager.createUser(username, password)){
        cout << "Account created successfully" << endl;
        userManager.saveUsers();
    }
}
    