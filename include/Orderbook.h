#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H
#include <map>
#include <unordered_map>
#include "Types.h"
#include "Handle.h"

class Orderbook {
public:
    std::map<Price, PriceLevelOrders, std::greater<>> bids;
    std::map<Price, PriceLevelOrders, std::less<>> asks;
    std::unordered_map<OrderId, Handle> orders;

    bool canMatch(Order order);
    void Add(Order order);
    template <typename T>
    void Matching(T& map, Order order);
    void Helper(Order order);
    template <typename T>
    void Rest(T& map, Order order);
    void Cancel(OrderId orderId);
    template <typename T>
    void HelperCancel(T& map, OrderId id);
};

#endif //ORDERBOOK_ORDERBOOK_H
