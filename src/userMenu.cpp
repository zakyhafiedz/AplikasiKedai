#include "utility.hpp"
#include "storage.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

const int MAX_INVENTORY = 100;
Stock inventory[MAX_INVENTORY];
int inventoryCount = 0;
int dailySales = 0;
int dailyExpenses = 0;
const int MIN_STOCK_WARNING = 5;

// Owner Functions
void inputStock() {
    utility::clearScreen();
    if (inventoryCount >= MAX_INVENTORY) {
        cout << "Inventory is full! Cannot add more items.\n";
        utility::pauseForKey();
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
        if (inventory[i].name == stockName) {
            inventory[i].addQuantity(quantity);
            cout << "Stock updated successfully! New quantity: " << inventory[i].quantity << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        inventory[inventoryCount++] = Stock(stockName, quantity, price);
        cout << "Stock added successfully!\n";
    }
    utility::pauseForKey();
}

void checkStockWarning() {
    utility::clearScreen();
    cout << "\nStocks with low inventory:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].quantity < MIN_STOCK_WARNING) {
            cout << inventory[i].name << " - Quantity: " << inventory[i].quantity << "\n";
        }
    }
    utility::pauseForKey();
}

void viewDailyExpenses() {
    utility::clearScreen();
    cout << fixed << setprecision(2);
    cout << "\nDaily Expenses Summary:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].used > 0) {
            cout << "Item: " << inventory[i].name << " - Quantity Used: " << inventory[i].used << "\n";
        }
    }
    cout << "Total Expenses: " << dailyExpenses << "\n";
    utility::pauseForKey();
}

void viewSalesSummary() {
    utility::clearScreen();
    cout << fixed << setprecision(2);
    cout << "\nDaily Sales Summary:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].sold > 0) {
            cout << "Item: " << inventory[i].name << " - Quantity Sold: " << inventory[i].sold << "\n";
        }
    }
    cout << "Total Sales: Rp. " << dailySales << "\n";
    utility::pauseForKey();
}

// Staff Functions
void recordSale() {
    utility::clearScreen();
    string itemName;
    int quantity;
    int totalPrice = 0;
    char confirm;

    do {
        utility::clearScreen();
        cout << "Enter item name: ";
        cin >> itemName;
        transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
        cout << "Enter quantity sold: ";
        cin >> quantity;

        bool found = false;
        for (int i = 0; i < inventoryCount; ++i) {
            if (inventory[i].name == itemName) {
                if (inventory[i].quantity >= quantity) {
                    int price = inventory[i].price * quantity;
                    inventory[i].reduceQuantity(quantity);
                    inventory[i].addSold(quantity);
                    totalPrice += price;
                    cout << "Item added to sale! Subtotal: Rp. " << price << "\n";
                } else {
                    cout << "Insufficient stock for " << inventory[i].name << "!\n";
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
    utility::pauseForKey();
}

void recordUsage() {
    utility::clearScreen();
    string itemName;
    int quantity;

    cout << "Enter item name: ";
    cin >> itemName;
    transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
    cout << "Enter quantity used: ";
    cin >> quantity;

    bool found = false;
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i].name == itemName) {
            if (inventory[i].quantity >= quantity) {
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
    utility::pauseForKey();
}

void checkStock() {
    utility::clearScreen();
    cout << "\nAvailable Stock:\n";
    for (int i = 0; i < inventoryCount; ++i) {
        cout << inventory[i].name << " - Quantity: " << inventory[i].quantity << "\n";
    }
    utility::pauseForKey();
}

// Menu Functions
void ownerMenu() {
    int choice;
    do {
        utility::clearScreen();
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
        utility::clearScreen();
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
