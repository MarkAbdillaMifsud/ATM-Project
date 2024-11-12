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
            break;
        case 3:
            cout << "Goodbye" << endl;
            break;
        default:
            cout << "Invalid entry" << endl;
            break;
    }
}