cmake_minimum_required(VERSION 3.15...3.30)

project(
  MiniRustCompiler
  VERSION 1.0
  LANGUAGES CXX)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(spdlog REQUIRED)

find_package(BISON)
BISON_TARGET(MyParser ${CMAKE_SOURCE_DIR}/src/ast/parser/parser.y
             ${CMAKE_SOURCE_DIR}/src/ast/parser/parser.cpp
             DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/ast/parser/parser.h
#             COMPILE_FLAGS -Wcounterexamples
)

find_package(FLEX)
FLEX_TARGET(MyLexer ${CMAKE_SOURCE_DIR}/src/ast/lexer/lexer.l
            ${CMAKE_SOURCE_DIR}/src/ast/lexer/lexer.cpp
            DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/ast/lexer/lexer.h
)

ADD_FLEX_BISON_DEPENDENCY(MyLexer MyParser)

message(STATUS "Flex output: ${FLEX_MyLexer_OUTPUTS}")
message(STATUS "Bison output: ${BISON_MyParser_OUTPUTS}")

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/lexer
    ${CMAKE_SOURCE_DIR}/src/ast
    ${CMAKE_SOURCE_DIR}/src/tast
    ${CMAKE_SOURCE_DIR}/src/interpreter
    ${CMAKE_SOURCE_DIR}/src/util
)

add_executable(mini-rust
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/ast_driver.cpp
    ${CMAKE_SOURCE_DIR}/src/ast/parser/parser_rules.cpp
    ${CMAKE_SOURCE_DIR}/src/tast/tast_driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyLexer_OUTPUTS}
)

target_include_directories(mini-rust PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/lexer
    ${CMAKE_SOURCE_DIR}/src/ast
)

target_link_libraries(mini-rust PRIVATE spdlog::spdlog)
target_compile_definitions(mini-rust PRIVATE SPDLOG_FMT_EXTERNAL)
add_compile_definitions(SPDLOG_FMT_EXTERNAL)
# target_link_libraries(mini-rust ${FLEX_LIBRARIES})
