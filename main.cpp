#include <iostream>
#include <map>
#include "include/Order.h"
#include "include/Orderbook.h"
#include "include/Side.h"
#include "include/Print.h"

int main() {
    Orderbook book;

    // Erwartung: Trade 5 @ 100, Ask bei 100 hat danach noch 5 übrig, Bids leer
    book.Add(Order(100, 10, Side::Sell, 1));
    book.Add(Order(100, 5, Side::Buy, 2));
    std::cout << "--- Test 1 ---" << std::endl;
    std::cout << "Asks:";
    Print(book.asks);
    std::cout << "Bids:";
    Print(book.bids);
    std::cout << "" << std::endl;

    // Erwartung: Trade 5 @ 99, dann Trade 7 @ 100
    // Asks: [100: 3], Bids: leer, Preisniveau 99 komplett weg
    Orderbook book2;
    book2.Add(Order(99, 5, Side::Sell, 1));
    book2.Add(Order(100, 10, Side::Sell, 2));
    book2.Add(Order(100, 12, Side::Buy, 3));
    std::cout << "--- Test 2 ---" << std::endl;
    std::cout << "Asks:";
    Print(book2.asks);
    std::cout << "Bids:";
    Print(book2.bids);
    std::cout << "" << std::endl;

    // Erwartung nach Add: Bids [98: 5], Asks [100: 10]
    // Erwartung nach Cancel: Bids leer (Preisniveau 98 muss weg sein), Asks [100: 10]
    Orderbook book3;
    book3.Add(Order(100, 10, Side::Sell, 1));
    book3.Add(Order(98, 5, Side::Buy, 2));
    std::cout << "--- Test 3 ---" << std::endl;
    std::cout << "Asks:";
    Print(book3.asks);
    std::cout << "Bids:";
    Print(book3.bids);
    std::cout << "" << std::endl;
    book3.Cancel(2);
    std::cout << "--- Test 3 ---" << std::endl;
    std::cout << "Asks:";
    Print(book3.asks);
    std::cout << "Bids:";
    Print(book3.bids);

    return 0;
}
