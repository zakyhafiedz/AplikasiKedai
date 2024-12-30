# Tugas Akhir Implementasi

### Anggota Kelompok 5:
- Zaky Hafiedz (24130500006)
- Vincensius Anthony (24130400001)


# Kedai Management System

This is an Kedai Management System implemented in C++ for a retail business. The program allows for managing stock, sales, and expenses, with a menu-driven interface for both owners and staff.

## Features

### Owner Functions:
- **Input Stock**: Add new stock items or update the quantity of existing items.
- **Check Stock Warnings**: View items with low stock (below a minimum threshold).
- **View Daily Expenses**: Check the expenses of used items for the day.
- **View Sales Summary**: Check the total sales and quantity sold for the day.

### Staff Functions:
- **Record Sale**: Record sales transactions, deducting the sold quantity from stock.
- **Record Expense**: Record usage of stock items, and track daily expenses.
- **Check Stock**: View the current stock levels.

## Requirements

To run this program, you need:
- A C++ compiler (e.g., GCC or Clang)
- Standard C++11 or later

## How to Compile and Run

### For Windows:
1. Open a terminal (Command Prompt or PowerShell).
2. Navigate to the folder where the C++ file is saved.
3. Compile the program using:
    ```bash
    g++ -I./include src/main.cpp src/utility.cpp src/storage.cpp src/userMenu.cpp -o kedai_management
    ```
4. Run the program:
    ```bash
    ./kedai_management
    ```

### For Linux or macOS:
1. Open a terminal.
2. Navigate to the folder where the C++ file is saved.
3. Compile the program using:
    ```bash
    g++ -I./include src/main.cpp src/utility.cpp src/storage.cpp src/userMenu.cpp -o kedai_management
    ```
4. Run the program:
    ```bash
    ./kedai_management
    ```

### Functions:
- **Input Stock**: This function allows the owner to add or update the inventory by specifying the item name, quantity, and price.
- **Check Stock Warnings**: The owner can check items with low stock (less than 5 units).
- **View Daily Expenses**: The owner can view daily expenses based on items used.
- **View Sales Summary**: The owner can view a summary of sales made throughout the day.
- **Record Sale**: The staff records a sale by specifying the item and quantity sold, updating the inventory accordingly.
- **Record Expense**: The staff records the usage of inventory items, which decreases the available stock and increases the daily expenses.
- **Check Stock**: The staff can check the current stock of each item in the inventory.

### User Roles:
1. **Owner**: The owner can manage the inventory, view daily sales, expenses, and check stock warnings.
2. **Staff**: The staff can record sales, record usage of items, and check stock levels.
