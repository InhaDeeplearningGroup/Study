cmake_minimum_required(VERSION 3.9)
project(Queue)

set(CMAKE_CXX_STANDARD 11)

add_executable(Queue main.cpp CircleArrayQueue.cpp CircleArrayQueue.h DynArrayQueue.h DynArrayQueue.cpp ListQueue.cpp ArrayStack.cpp ArrayStack.h)