#pragma once
#include "userManager.h"

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
        void createAccount();
        void login();
        void logout();
        void applicationMenu();
        void processApplicationMenuChoice(int choice, bool &repeat);
        int userOption;
};