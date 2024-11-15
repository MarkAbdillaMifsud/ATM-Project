#include <iostream>
#include "menu.h"

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

void MainMenu::createAccount(){
    string username, password, confirmPassword;
    cout << "Please enter a username for your account." << endl;
    do{
        cin >> username;
        if(!userManager.isUniqueUsername(username)){
            cout << "That username already exists. Please enter another username." << endl;
        }
    } while(!userManager.isUniqueUsername(username));
    cout << "Please enter a password. Password should be between 8 and 15 characters long and contain at least 1 number and 1 symbol." << endl;
    do{
        cin >> password;
        cout << "Enter the same password again." << endl;
        cin >> confirmPassword;
        if(!password.compare(confirmPassword)){
            cout << "Your confirm password does not match your password. Please try again." << endl;
            cin >> password;
            cout << "Enter the same password again." << endl;
            cin >> confirmPassword;
        }
        if(!userManager.validatePassword(password)){
            cout << "That password is invalid. Please try again." << endl;
        }
    } while(!userManager.validatePassword(password));
}