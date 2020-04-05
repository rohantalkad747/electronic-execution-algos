cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp include/SerialRouter.h src/VenueManager.cpp include/VenueManager.h include/Logger.h src/Order.cpp include/Order.h include/OrderSide.h include/OrderType.h include/TimeInForce.h include/OrderStatus.h)