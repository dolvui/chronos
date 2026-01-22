cmake_minimum_required (VERSION 3.18)
project (CHRONOS)

file(GLOB_RECURSE sources      src/*.cpp src/*.hpp)
file(GLOB_RECURSE sources      src/types/*.cpp src/types/*.hpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(Parser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.hpp)

FLEX_TARGET(Lexer src/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

# set_source_files_properties(${FLEX_Lexer_OUTPUTS} PROPERTIES
#     COMPILE_FLAGS "-Wno-unused-function"
# )

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

add_executable(chronos
  src/main.cpp
  src/runtime.cpp
  src/types/int_ch.cpp
  ${BISON_Parser_OUTPUTS}
  ${FLEX_Lexer_OUTPUTS}
)
target_compile_features(chronos PRIVATE cxx_std_20)
target_compile_options(chronos PRIVATE -Wall -Wextra)
