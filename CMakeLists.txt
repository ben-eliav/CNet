include(CMakePrintHelpers)

cmake_minimum_required(VERSION 3.23)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 14)

file( GLOB SRC_FILES *.cpp *.h)

list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

cmake_print_variables(SRC_FILES)

add_executable(NeuralNetwork main.cpp ${SRC_FILES})
