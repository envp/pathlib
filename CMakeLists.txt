cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

include(ColorDiagnostics)
include(CCache REQUIRED)

project(example LANGUAGES CXX)
add_library(example STATIC)

set(INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")
set(LIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

target_include_directories(example PUBLIC ${INCLUDEDIR})
target_sources(example PUBLIC ${LIBDIR}/hello.cpp)
