#pragma once
#include "userManager.h"

class MainMenu{
    public:
        MainMenu();
        void init();
        void processUserChoice(int userChoice, bool &repeat);
        int getUserOption();
        void displayMenu();
    
    private:
        UserManager userManager;
        void createAccount();
};