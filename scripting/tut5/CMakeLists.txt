cmake_minimum_required(VERSION 3.28.2)
project(tut5 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

find_package(BISON 3.8.2)
find_package(FLEX 2.6.4)
BISON_TARGET(StringParser string.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(StringScanner string.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(StringScanner StringParser)
include_directories(${CMAKE_CURRENT_BINARY_DIR} src)
add_executable(${PROJECT_NAME}
  src/intcode.cpp
  src/main.cpp
  src/symtab.cpp
  src/synttree.cpp
  ${BISON_StringParser_OUTPUTS}
  ${FLEX_StringScanner_OUTPUTS}
)
