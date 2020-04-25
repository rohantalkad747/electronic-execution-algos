cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 include/SprayRouter.h src/VenueManager.cpp include/VenueManager.h include/Logger.h include/Order.h include/OrderSide.h include/OrderType.h include/TimeInForce.h include/OrderStatus.h include/Venue.h include/VenueRank.h include/Execution.h include/ExecutionType.h src/SprayRouter.cpp src/Main.cpp src/BlockingQueue.cpp include/BlockingQueue.h include/AvgLatency.h src/AvgLatency.cpp include/RingBuffer.h src/RingBuffer.cpp include/Algorithm.h include/AlgoConfig.h include/TimingContext.h include/VWAPConfig.h include/TWAPConfig.h include/POVConfig.h)