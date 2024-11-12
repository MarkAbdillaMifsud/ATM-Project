#include <iostream>
#include "menu.h"

using namespace std;

int main(){
    MainMenu mainMenu{};
    bool repeat = true;
    while(repeat){
        mainMenu.displayMenu();
        int userChoice = mainMenu.getUserOption();
        mainMenu.processUserChoice(userChoice, repeat);
    }
    return 0;
}