#pragma once
#include "Types.h"
#include "Side.h"
#ifndef ORDERBOOK_ORDER_H
#define ORDERBOOK_ORDER_H

class Order {
public:
    Order(Price price, Quantity quantity, Side side, OrderId orderId);
    Price GetPrice() const;
    Quantity GetQuantity() const;
    Side GetSide() const;
    OrderId GetOrderId() const;
    void SetQuantity(Quantity quantity);

private:
    Price price;
    Quantity quantity;
    OrderId orderId;
    Side side;
};

#endif //ORDERBOOK_ORDER_H
