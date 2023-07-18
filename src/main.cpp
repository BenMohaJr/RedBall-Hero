#include "Controller.h"


int main(){
    // Try and catch for all the constructors and files that needs to be open
    try {
        Controller Game;
        Game.runMenu();
    }

    catch (const std::invalid_argument& e) { std::cout << e.what() << "Pictures are missing, fix and try again\n"; }
}