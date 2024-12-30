#include "utility.hpp"
#include <iostream>

using namespace std;

// clear screen
void utility::clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// pause
void utility::pauseForKey(){
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}