cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-Wall -Ofast")


add_executable(untitled1 include/SprayRouter.h src/VenueManager.cpp include/VenueManager.h include/Logger.h include/Order.h include/OrderSide.h include/OrderType.h include/TimeInForce.h include/OrderStatus.h include/Venue.h include/VenueRank.h include/Execution.h include/ExecutionType.h src/SprayRouter.cpp src/BlockingQueue.cpp include/BlockingQueue.h include/AvgLatency.h src/AvgLatency.cpp include/RingBuffer.h src/RingBuffer.cpp include/Algorithm.h include/AlgoConfig.h include/TimingContext.h include/VWAPConfig.h include/TWAPConfig.h include/ParticipateConfig.h src/TimedAlgorithm.cpp include/TimedAlgorithm.h include/TimeUtils.h src/TWAPAlgorithm.cpp include/TWAPAlgorithm.h src/Algorithm.cpp include/VWAPAlgorithm.h src/VWAPAlgorithm.cpp include/OrderRouter.h include/RoutingConfig.h include/RoutingType.h test/test.cpp test/test.h src/TimeUtils.cpp src/CountDownLatch.cpp include/CountDownLatch.h include/ParticipateAlgorithm.h src/ParticipateAlgorithm.cpp src/AntiGaming.cpp include/AntiGaming.h src/IcebergAlgorithm.cpp include/IcebergAlgorithm.h include/IcebergConfig.h src/OrderBook.cpp include/OrderBook.h src/Node.cpp include/Node.h src/SplayTree.cpp include/SplayTree.h)