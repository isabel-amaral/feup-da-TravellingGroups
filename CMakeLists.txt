cmake_minimum_required(VERSION 3.20)
project(feup_da_TravellingGroups)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dataset")

add_executable(feup_da_TravellingGroups src/main.cpp src/MinHeap.h src/Graph.cpp src/Graph.h)
