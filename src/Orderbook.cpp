#include "../include/Orderbook.h"
#include "../include/Side.h"
#include "../include/Order.h"
#include "../include/Handle.h"
#include "../include/Types.h"
#include <list>
#include <map>

bool Orderbook::canMatch(Order order) {
    auto highestBid = bids.begin();
    auto lowestAsk = asks.begin();

    if (order.GetSide() == Side::Buy) {
        if (asks.empty()) return false;
        return order.GetPrice() >= lowestAsk->first;
    }
    else {
        if (bids.empty()) {return false;}
        return order.GetPrice() <= highestBid->first;
    };
};
void Orderbook::Add(Order order) {
    if (order.GetSide() == Side::Buy) {Matching(asks, order);}
    if (order.GetSide() == Side::Sell) {Matching(bids, order);}
};
template <typename T>
void Orderbook::Matching(T& map, Order order) {
    while (canMatch(order) && order.GetQuantity() != 0) {
        PriceLevelOrders &levelOrders = map.begin()->second;

        if (order.GetQuantity() < levelOrders.front().GetQuantity()) {
            levelOrders.front().SetQuantity(levelOrders.front().GetQuantity() - order.GetQuantity());
            order.SetQuantity(0);
            break;
        }
        if (order.GetQuantity() == levelOrders.front().GetQuantity()) {
            orders.erase(levelOrders.front().GetOrderId());
            levelOrders.pop_front();
            order.SetQuantity(0);
            if (levelOrders.empty()) {map.erase(map.begin());}
            break;
        }
        if (order.GetQuantity() > levelOrders.front().GetQuantity()) {
            order.SetQuantity(order.GetQuantity() - levelOrders.front().GetQuantity());
            orders.erase(levelOrders.front().GetOrderId());
            auto it = map.find(levelOrders.front().GetPrice());
            levelOrders.pop_front();
            if (levelOrders.empty()) {map.erase(it);}
        }
    }
    if (order.GetQuantity() != 0) {Helper(order);}
};
void Orderbook::Helper(Order order) {
    if (order.GetSide() == Side::Buy) {Rest(bids, order);}
    if (order.GetSide() == Side::Sell) {Rest(asks, order);}
};
template <typename T>
void Orderbook::Rest(T& map, Order order) {
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