#pragma once

class MainMenu{
    public:
        MainMenu();
        void init();
        void processUserChoice(int userChoice, bool &repeat);
        int getUserOption();
        void displayMenu();
};