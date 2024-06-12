cmake_minimum_required(VERSION 3.28.2)
project(tut2 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

find_package(FLEX 2.6.4)
FLEX_TARGET(String string.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR} src)
add_executable(${PROJECT_NAME} src/main.cpp ${FLEX_String_OUTPUTS})
