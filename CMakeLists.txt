cmake_minimum_required(VERSION 3.17)
project(xopenhd)

set(CMAKE_CXX_STANDARD 17)

add_executable(xopenhd main.cpp fec.c WFBTransmitter.cpp WFBTransmitter.h)
