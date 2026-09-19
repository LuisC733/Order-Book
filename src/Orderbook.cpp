#include "../include/Orderbook.h"
#include "../include/Side.h"
#include "../include/Order.h"
#include "../include/Handle.h"
#include "../include/Types.h"
#include <list>
#include <map>
#include <iostream>

void Orderbook::AddOrder(Order order) {
    if (order.GetSide() == Side::Buy) {HelperAddOrder(bids, order);}
    if (order.GetSide() == Side::Sell) {HelperAddOrder(asks, order);}
};
template <typename T>
void Orderbook::HelperAddOrder(T& map, Order order) {
    Handle handle;

    auto pair = map.insert(std::pair<Price, PriceLevelOrders>(order.GetPrice(), PriceLevelOrders{}));
    auto it = pair.first;
    auto location = it->second.insert(it->second.end(), order);

    handle.price = order.GetPrice();
    handle.side = order.GetSide();
    handle.location = location;
    orders.insert(std::pair<OrderId, Handle> (order.GetOrderId(), handle));
}
void Orderbook::Cancel(OrderId orderId) {
    auto it = orders.find(orderId);
    if (it->second.side == Side::Buy) {HelperCancel(bids, orderId);}
    if (it->second.side == Side::Sell) {HelperCancel(asks, orderId);}
};
template <typename T>
void Orderbook::HelperCancel(T& map, OrderId id) {
    auto const it = orders.find(id);
    auto const list = map.find(it->second.price);
    PriceLevelOrders &levelOrder = list->second;
    levelOrder.erase(it->second.location); //FIX
    if (levelOrder.empty()) {map.erase(it->second.price);}
    orders.erase(id);
};