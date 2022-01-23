cmake_minimum_required(VERSION 3.5)

project(BankingManagementSystemProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BankingManagementSystemProject  account.cpp  customer.cpp employee.cpp loan.cpp facilityemployee.cpp manager.cpp date.cpp bank.cpp main.cpp)
