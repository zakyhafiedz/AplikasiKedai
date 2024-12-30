#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
using namespace std;

// Stock Class
class Stock {
private:
    string name;
    int quantity;
    int price;
    int sold;
    int used;

public:
    // Constructor
    Stock(string n = "", int q = 0, int p = 0) 
        : name(n), quantity(q), price(p), sold(0), used(0) {}

    // Getters and Setters
    string getName() const { return name; }
    void setName(const string& n) { name = n; }

    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }

    int getPrice() const { return price; }
    void setPrice(int p) { price = p; }

    int getSold() const { return sold; }
    void setSold(int s) { sold = s; }

    int getUsed() const { return used; }
    void setUsed(int u) { used = u; }

    void addQuantity(int q) { quantity += q; }
    void reduceQuantity(int q) { quantity -= q; }
    void addSold(int q) { sold += q; }
    void addUsed(int q) { used += q; }
};

// Constants
const int MAX_INVENTORY = 100;
Stock inventory[MAX_INVENTORY];
int inventoryCount = 0;
int dailySales = 0;
int dailyExpenses = 0;
const int MIN_STOCK_WARNING = 5;

// Clear screen function
void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Unix
    #endif
}

// Function to pause for user input
void pauseForKey() {
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}

// Owner Functions
void inputStock() {
    clearScreen();
    if (inventoryCount >= MAX_INVENTORY) {
        cout << "Inventory is full! Cannot add more items.\n";
        pauseForKey();
        return;
    }

    string stockName;
    int quantity, price;
    cout << "Enter stock name: ";
    cin >> stockName;
    transform(stockName.begin(), stockName.end(), stockName.begin(), ::tolower);

    cout << "Enter quantity: ";
    cin >> quantity;
    cout << "Enter price: ";
    cin >> price;

    bool found = false;

    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].getName() == stockName) {
            inventory[i].addQuantity(quantity);
            cout << "Stock updated successfully! New quantity: " << inventory[i].getQuantity() << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        inventory[inventoryCount++] = Stock(stockName, quantity, price);
        cout << "Stock added successfully!\n";
    }
    pauseForKey();
}

void checkStockWarning() {
    clearScreen();
    cout << "\nStocks with low inventory:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].getQuantity() < MIN_STOCK_WARNING) {
            cout << inventory[i].getName() << " - Quantity: " << inventory[i].getQuantity() << "\n";
        }
    }
    pauseForKey();
}

void viewDailyExpenses() {
    clearScreen();
    cout << fixed << setprecision(2);
    cout << "\nDaily Expenses Summary:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].getUsed() > 0) {
            cout << "Item: " << inventory[i].getName() << " - Quantity Used: " << inventory[i].getUsed() << "\n";
        }
    }
    cout << "Total Expenses: " << dailyExpenses << "\n";
    pauseForKey();
}

void viewSalesSummary() {
    clearScreen();
    cout << fixed << setprecision(2);
    cout << "\nDaily Sales Summary:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].getSold() > 0) {
            cout << "Item: " << inventory[i].getName() << " - Quantity Sold: " << inventory[i].getSold() << "\n";
        }
    }
    cout << "Total Sales: Rp. " << dailySales << "\n";
    pauseForKey();
}

// Staff Functions
void recordSale() {
    clearScreen();
    string itemName;
    int quantity;
    int totalPrice = 0;
    char confirm;

    do {
        clearScreen();
        cout << "Enter item name: ";
        cin >> itemName;
        transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
        cout << "Enter quantity sold: ";
        cin >> quantity;

        bool found = false;
        for (int i = 0; i < inventoryCount; ++i) {
            if (inventory[i].getName() == itemName) {
                if (inventory[i].getQuantity() >= quantity) {
                    int price = inventory[i].getPrice() * quantity;
                    inventory[i].reduceQuantity(quantity);
                    inventory[i].addSold(quantity);
                    totalPrice += price;
                    cout << "Item added to sale! Subtotal: Rp. " << price << "\n";
                } else {
                    cout << "Insufficient stock for " << inventory[i].getName() << "!\n";
                }
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Item not found!\n";
        }

        cout << "\nDo you want to add another item to this sale? (y/n): ";
        cin >> confirm;

    } while (tolower(confirm) == 'y');

    dailySales += totalPrice;
    cout << fixed << setprecision(2);
    cout << "\nTotal price for this sale: Rp. " << totalPrice << "\n";
    pauseForKey();
}

void recordUsage() {
    clearScreen();
    string itemName;
    int quantity;

    cout << "Enter item name: ";
    cin >> itemName;
    transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
    cout << "Enter quantity used: ";
    cin >> quantity;

    bool found = false;
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].getName() == itemName) {
            if (inventory[i].getQuantity() >= quantity) {
                inventory[i].reduceQuantity(quantity);
                inventory[i].addUsed(quantity);
                dailyExpenses += quantity;
                cout << "Stock updated successfully!\n";
            } else {
                cout << "Insufficient stock!\n";
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Item not found!\n";
    }
    pauseForKey();
}

void checkStock() {
    clearScreen();
    cout << "\nAvailable Stock:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        cout << inventory[i].getName() << " - Quantity: " << inventory[i].getQuantity() << "\n";
    }
    pauseForKey();
}

// Menu Functions
void ownerMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\nOwner Menu:\n";
        cout << "1. Input Stock\n";
        cout << "2. Check Stock Warnings\n";
        cout << "3. View Daily Expenses\n";
        cout << "4. View Sales Summary\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: inputStock(); break;
            case 2: checkStockWarning(); break;
            case 3: viewDailyExpenses(); break;
            case 4: viewSalesSummary(); break;
            case 5: cout << "Exiting Owner Menu...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

void staffMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\nStaff Menu:\n";
        cout << "1. Record Sale\n";
        cout << "2. Record Expense\n";
        cout << "3. Check Stock\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: recordSale(); break;
            case 2: recordUsage(); break;
            case 3: checkStock(); break;
            case 4: cout << "Exiting Staff Menu...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

int main() {
    int role;
    do {
        clearScreen();
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
