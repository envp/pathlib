cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

include(ColorDiagnostics)
include(CCache REQUIRED)

project(pathlib LANGUAGES CXX)

set(INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")
set(LIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

add_library(pathlib-utils STATIC)
target_sources(
  pathlib-utils
  PUBLIC
  ${LIBDIR}/pathlib/utils/string_utils.cpp
)
target_include_directories(pathlib-utils PUBLIC ${INCLUDEDIR})

add_library(pathlib STATIC)
target_include_directories(pathlib PUBLIC ${INCLUDEDIR})
target_sources(
  pathlib
  PUBLIC
  ${LIBDIR}/pathlib/annotations.cpp
  ${LIBDIR}/pathlib/assertions.cpp
  ${LIBDIR}/pathlib/pure_path.cpp
)
message(STATUS "Linker: ${CMAKE_CXX_LINK_EXECUTABLE}")

if (ENABLE_TESTS)
  enable_testing()
  list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
  add_subdirectory(tests)
endif()
