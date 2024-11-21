#pragma once
#include "userManager.h"

class MainMenu{
    public:
        MainMenu();
        void init();
        void processUserChoice(int userChoice, bool &repeat);
        int getUserOption();
        void displayMenu();
        void exitApplication();
    private:
        UserManager userManager;
        void createAccount();
        void login();
        int userOption;
};