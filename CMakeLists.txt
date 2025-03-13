cmake_minimum_required(VERSION 3.30)
project(hashtabelle)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(json/single_include)

add_executable(hashtabelle
    include/hashtab.h
    src/main.cpp)
