#include <iostream>
#include "userMenu.hpp"
#include "utility.hpp"

using namespace std;

int main() {
    int role;
    do {
        utility::clearScreen();
        cout << "\nMain Menu:\n";
        cout << "1. Owner\n";
        cout << "2. Staff\n";
        cout << "3. Exit\n";
        cout << "Enter your role: ";
        cin >> role;

        switch (role) {
            case 1: ownerMenu(); break;
            case 2: staffMenu(); break;
            case 3: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (role != 3);

    return 0;
}
