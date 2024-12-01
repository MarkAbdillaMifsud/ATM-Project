#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include <cctype>
#include <string>
#include "menu.h"
#include "userManager.h"
#include "utility.h"
#include "BankAccount.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

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
        repeat = true; //Allows return to menu in case of failure
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
        //userManager.saveUsers();
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
                withdrawMoney();
                break;
            case 2:
                cout << "Deposit money" << endl;
                depositMoney();
                break;
            case 3:
                cout << "Display Balance" << endl;
                showBalances();
                break;
            case 4:
                cout << "Create bank account" << endl;
                createBankAccount();
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
    } catch (invalid_argument &e) {
        cout << "Error: " << e.what() << endl;
    } catch (exception &e) {
        cout << "An unexpected error occurred: " << e.what() << endl;
        repeat = true; // Allows return to menu in case of failure
    }
}

void MainMenu::createBankAccount(){
    string accountNumberEntry;
    int bankAccountNumber;
    string accountType;
    bool isValidAccountNumber = false;

    cout << "Select the type of account you want to create: Savings or Current" << endl;
    do{
        cin >> accountType;
        if(!Utility::isValidAccountType(accountType)){
            cout << accountType << " is not a valid account. Enter Savings or Current" << endl;
        }
    } while(!Utility::isValidAccountType(accountType));  

    cout << "Enter an account number for your new bank account: " << endl;
    do{
        try
        {
            cin >> accountNumberEntry;
            bankAccountNumber = stoi(accountNumberEntry); // Attempt conversion
            if (!bankAccountManager.isUniqueAccountNumber(bankAccountNumber))
            {
                cout << bankAccountNumber << " already belongs to another bank account. Please enter a unique account number." << endl;
            }
            else
            {
                cout << "Account number: " << bankAccountNumber << " is valid!" << endl;
                isValidAccountNumber = true;
            }
        }
        catch (const std::invalid_argument &) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid account number. Please enter a valid integer." << endl;
        }
        catch (const std::out_of_range &) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Account number is out of range. Please try again." << endl;
        }
    } while(!isValidAccountNumber);

    shared_ptr<BankAccount> newAccount;

    if (Utility::isValidAccountType(accountType)) {
        if (accountType == "savings") {
            newAccount = make_shared<SavingsAccount>(bankAccountNumber);
        } else {
            newAccount = make_shared<CurrentAccount>(bankAccountNumber);
        }
    } else {
        cout << "Error: Invalid account type detected unexpectedly. Please retry." << endl;
        return;
    }

    userManager.getLoggedInUser()->addBankAccount(newAccount);

    cout << "Account with account number " << bankAccountNumber << " successfully created" << endl;
    return;
}

void MainMenu::withdrawMoney(){
    if(userManager.getLoggedInUser()->isZeroBankAccounts()){
        cout << "There are no bank accounts registered on this user. Please create one first." << endl;
        return;
    }
}

void MainMenu::depositMoney(){
    int accountNumber;
    float depositAmount;
    shared_ptr<BankAccount> selectedAccount;

    User *loggedInUser = userManager.getLoggedInUser();
    if (loggedInUser->isZeroBankAccounts()){
        cout << "There are no bank accounts registered on this user. Please create one first." << endl;
        return;
    }

    const auto &bankAccounts = loggedInUser->getAllBankAccounts();

    if (bankAccounts.size() == 1) {
        const auto &accountPair = *bankAccounts.begin();
        accountNumber = accountPair.first;
        selectedAccount = accountPair.second;

        cout << "Single bank account detected with account number: " << accountNumber << endl;
    } else {
        cout << "You have multiple accounts. Please enter the number of the account you wish to deposit into:" << endl;
        for (const auto &accountPair : bankAccounts)
        {
            cout << "Account Number: " << accountPair.first
                 << ", Balance: EUR " << accountPair.second->getBalance() << endl;
        }
        cout << "Enter the account number: ";
        while (!(cin >> accountNumber) || bankAccounts.find(accountNumber) == bankAccounts.end()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid account number. Please select a valid account: ";
        }

        selectedAccount = bankAccounts.at(accountNumber);
    }

    // Prompt for deposit amount
    cout << "Enter the amount to deposit: ";
    while (!(cin >> depositAmount) || depositAmount <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount. Please enter a positive number: ";
    }
    
    selectedAccount->depositMoney(depositAmount);
    cout << "You have deposited EUR " << depositAmount << " to account number " << accountNumber << endl;
    cout << "Updated Balance: EUR " << selectedAccount->getBalance() << endl;
}

void MainMenu::showBalances(){
    if (userManager.getLoggedInUser()->isZeroBankAccounts()) {
        cout << "There are no bank accounts registered on this user. Please create one first." << endl;
        return;
    }

    User* loggedInUser = userManager.getLoggedInUser();
    const auto& bankAccounts = loggedInUser->getAllBankAccounts();

    cout << "Account Details:" << endl;
    cout << "================" << endl;

    for(const auto& accountPair : bankAccounts){
        auto account = accountPair.second;

        string accountType = "Bank Account";
        if(dynamic_cast<SavingsAccount*>(account.get())){
            accountType = "Savings Account";
        } else if (dynamic_cast<CurrentAccount*>(account.get())){
            accountType = "Current Account";
        }

        cout << "Account Number: " << account->getAccountNumber() << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: EUR " << account->getBalance() << endl;
        cout << "-------------------------" << endl;
    }
}

void MainMenu::logout(){
    userManager.logout();
    cout << "You have logged out of your account. " << endl;
}