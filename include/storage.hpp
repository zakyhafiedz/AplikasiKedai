#ifndef STOCK_H
#define STOCK_H

#include <string>
using namespace std;

class Stock {
public:
    string name;
    int quantity;
    int price;
    int sold;
    int used;

    Stock(string n = "", int q = 0, int p = 0);

    void addQuantity(int q);
    void reduceQuantity(int q);
    void addSold(int q);
    void addUsed(int q);
};

#endif