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

    void AddOrder(Order order);
    template <typename T>
    void HelperAddOrder(T& map, Order order);
    void DeleteOrder(OrderId orderId);
    template <typename T>
    void HelperDeleteOrder(T& map, OrderId id, auto it);
    void ReplaceOrder(Order order, OrderId orderId);
    void OrderExecuted(OrderId orderId, Quantity quantity);
};

#endif //ORDERBOOK_ORDERBOOK_H
