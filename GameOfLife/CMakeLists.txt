cmake_minimum_required(VERSION 3.14)

project(GoL VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(GDIPLUS_LIB gdiplus)

set(SOURCES main.cpp)
set(HEADERS board.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${GDIPLUS_LIB} -lgdi32 -luser32 -lkernel32 -lcomctl32)

target_include_directories(${PROJECT_NAME} PRIVATE "${GDIplus_INCLUDE_DIR}")