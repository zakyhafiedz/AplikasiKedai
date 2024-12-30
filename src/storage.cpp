#include "storage.hpp"
using namespace std;

// Stock Data
Stock::Stock(std::string n, int q, int p) 
    : name(n), quantity(q), price(p), sold(0), used(0) {}

void Stock::addQuantity(int q) { quantity += q; }
void Stock::reduceQuantity(int q) { quantity -= q; }
void Stock::addSold(int q) { sold += q; }
void Stock::addUsed(int q) { used += q; }