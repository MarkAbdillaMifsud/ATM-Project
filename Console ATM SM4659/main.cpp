#include <iostream>
#include "menu.h"

using namespace std;

int main(){
    MainMenu mainMenu{};
    mainMenu.init();
    bool repeat = true;
    while(repeat){
        mainMenu.displayMainMenu();
        int userChoice = mainMenu.getUserOption();
        mainMenu.processMainMenuChoice(userChoice, repeat);
    }
    return 0;
}