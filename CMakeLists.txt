cmake_minimum_required(VERSION 3.14)
project(retree VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Custom compiler flags for Release builds
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -fno-rtti -Wall -Wextra -Wpedantic")
endif()

set(SOURCES
    src/main.cc
)

set(HEADERS
    src/parser.hxx
    src/tokenizer.hxx
    src/tokens.hxx
    src/tree.hxx
)

include(FetchContent)
FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG        v2.3.2
)
FetchContent_MakeAvailable(CLI11)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE CLI11::CLI11)
