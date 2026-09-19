cmake_minimum_required(VERSION 4.3)
project(OrderBook)

set(CMAKE_CXX_STANDARD 20)

add_executable(OrderBook main.cpp
        src/Order.cpp
        src/Orderbook.cpp
)

target_include_directories(OrderBook PUBLIC include)
