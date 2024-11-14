cmake_minimum_required(VERSION 3.15...3.30)

project(
  MiniRustCompiler
  VERSION 1.0
  LANGUAGES CXX)

# set(FLEX_USE_STATIC_LIB ON)

find_package(BISON)
BISON_TARGET(MyParser ${CMAKE_SOURCE_DIR}/src/parser/parser.y
             ${CMAKE_SOURCE_DIR}/src/parser/parser.cpp
             DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/parser/parser.h
)

find_package(FLEX)
FLEX_TARGET(MyLexer ${CMAKE_SOURCE_DIR}/src/parser/lexer.l
            ${CMAKE_SOURCE_DIR}/src/parser/lexer.cpp
            DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/parser/lexer.h
)

ADD_FLEX_BISON_DEPENDENCY(MyLexer MyParser)

message(STATUS "Flex output: ${FLEX_MyLexer_OUTPUTS}")
message(STATUS "Bison output: ${BISON_MyParser_OUTPUTS}")

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/parser
)

add_executable(mini-rust
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyLexer_OUTPUTS}
)

target_include_directories(mini-rust PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/parser
)

# target_link_libraries(mini-rust ${FLEX_LIBRARIES})
