#pragma once
#include "userManager.h"
#include "BankAccountManager.h"

class MainMenu{
    public:
        MainMenu();
        void init();
        void processMainMenuChoice(int userChoice, bool &repeat);
        int getUserOption();
        void displayMainMenu();
        void displayApplicationMenu();
        void exitApplication();
    private:
        UserManager userManager;
        BankAccountManager bankAccountManager;
        void createAccount();
        void login();
        void logout();
        void applicationMenu();
        void processApplicationMenuChoice(int choice, bool &repeat);
        void createBankAccount();
        void withdrawMoney();
        void depositMoney();
        void showBalances();
        void transferMoney();
        int userOption;
};