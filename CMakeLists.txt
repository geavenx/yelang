cmake_minimum_required(VERSION 3.25)

project(yelang)

set(CMAKE_CXX_STANDARD 20)

# Add debugging information
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Enable all warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Add optimization flags (optional)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(yelang src/main.cpp)
