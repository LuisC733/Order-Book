#include "../include/Order.h"
#include "../include/Types.h"
#include "../include/Side.h"

Order::Order(Price price, Quantity quantity, Side side, OrderId orderId) {
    this->price = price;
    this->quantity = quantity;
    this->side = side;
    this->orderId = orderId;
}
Price Order::GetPrice() const {return price;}
Quantity Order::GetQuantity() const {return quantity;}
Side Order::GetSide() const {return side;}
OrderId Order::GetOrderId() const {return orderId;}
void Order::SetQuantity(Quantity quantity) {this->quantity = quantity;}