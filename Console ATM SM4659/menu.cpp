#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include "menu.h"
#include "userManager.h"

using namespace std;

MainMenu::MainMenu(){}

void MainMenu::init(){
    userManager.loadUsers();
}

void MainMenu::displayMainMenu(){
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
    while (!(cin >> userOption))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    return userOption;
}

void MainMenu::processMainMenuChoice(int userChoice, bool &repeat){
    try{
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (userChoice)
        {
        case 1:
            login();
            break;
        case 2:
            createAccount();
            break;
        case 3:
            exitApplication();
            repeat = false; // Stop repeating the menu
            break;
        default:
            std::cout << "Invalid entry. Please select a valid option." << std::endl;
            break;
        }
    } catch(invalid_argument& e){
        cout << "Error: " << e.what() << endl;
    } catch(exception& e){
        cout << "An unexpected error occurred: " << e.what() << endl;
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
        applicationMenu();
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

void MainMenu::exitApplication(){
    userManager.saveUsers();
    exit(0);
}

void MainMenu::displayApplicationMenu()
{
    cout << "===================================" << endl;
    User* user = userManager.getLoggedInUser();
    if(user != nullptr){
        cout << "Welcome " << user->getUsername() << endl;
    } else {
        cout << "Welcome username" << endl;
    }
    cout << "===================================" << endl;
    cout << "1) Withdraw money" << endl;
    cout << "2) Deposit money" << endl;
    cout << "3) Request balance" << endl;
    cout << "4) Create bank account" << endl;
    cout << "5) Transfer money between accounts" << endl;
    cout << "6) Logout" << endl;
    cout << "===================================" << endl;
    cout << "Enter your choice: " << endl;
}

void MainMenu::applicationMenu(){
    bool repeat = true;
    while(repeat){
        displayApplicationMenu();
        int userChoice = getUserOption();
        processApplicationMenuChoice(userChoice, repeat);
    }
}

void MainMenu::processApplicationMenuChoice(int userChoice, bool &repeat){
    try{
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch(userChoice){
            case 1:
                cout << "Withdraw money" << endl;
                break;
            case 2:
                cout << "Deposit money" << endl;
                break;
            case 3:
                cout << "Display Balance" << endl;
                break;
            case 4:
                cout << "Create bank account" << endl;
                break;
            case 5:
                cout << "Transfer money" << endl;
                break;
            case 6:
                logout();
                repeat = false;
                break;
            default:
                cout << "Invalid entry. Please select a valid option" << endl;
                break;
        }
    } catch(const exception& e){
        cout << "An unexpected error occurred: " << e.what() << endl;
    }
}

void MainMenu::logout(){
    userManager.logout();
    cout << "You have logged out of your account. " << endl;
}