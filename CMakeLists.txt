cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 include/SerialRouter.h src/VenueManager.cpp include/VenueManager.h include/Logger.h include/Order.h include/OrderSide.h include/OrderType.h include/TimeInForce.h include/OrderStatus.h include/Venue.h include/VenueRank.h include/Execution.h include/ExecutionType.h src/SerialRouter.cpp src/Main.cpp)