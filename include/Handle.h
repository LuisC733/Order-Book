#ifndef ORDERBOOK_HANDLE_H
#define ORDERBOOK_HANDLE_H
#include "Types.h"
#include "Side.h"

struct Handle{
    Price price;
    Side side;
    PriceLevelOrders::iterator location;
};

#endif //ORDERBOOK_HANDLE_H
