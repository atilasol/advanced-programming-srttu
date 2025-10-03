cmake_minimum_required(VERSION 3.10)
project(BankingSystemApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Collect all .cpp files automatically
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(BankingSystemApp ${SOURCES})
