# main
cmake_minimum_required(VERSION 3.14)
project(GoL VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(GDIPLUS_LIB gdiplus)

set(SOURCES src/main.cpp src/board.cpp)
set(HEADERS src/board.h)

add_executable(
  ${PROJECT_NAME}
  ${SOURCES}
  ${HEADERS}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${GDIPLUS_LIB}
  -lgdi32
  -luser32
  -lkernel32
  -lcomctl32
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  "${GDIplus_INCLUDE_DIR}"
  src
  test
)

# Testing suite
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  GoL_test
  test/test.cpp
  src/board.cpp
  ${HEADERS}
)

target_link_libraries(
  GoL_test
  GTest::gtest_main
)

target_include_directories(
  GoL_test
  PRIVATE
  src
)

include(GoogleTest)
gtest_discover_tests(GoL_test)
