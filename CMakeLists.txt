cmake_minimum_required(VERSION 3.23)
project(pathlib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

include(ColorDiagnostics)
include(CCache REQUIRED)

include(GNUInstallDirs)

set(INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")
set(LIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

add_library(pathlib STATIC)
target_include_directories(pathlib PUBLIC ${INCLUDEDIR})
target_sources(
  pathlib
  PUBLIC
  ${LIBDIR}/pathlib/annotations.cpp
  ${LIBDIR}/pathlib/assertions.cpp
  ${LIBDIR}/pathlib/pure_path.cpp
  ${LIBDIR}/pathlib/utils/string_utils.cpp
)
target_compile_options(pathlib PRIVATE -Wextra -Wall -pedantic)

include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
add_subdirectory(tests)

if(PATHLIB_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

install(
  TARGETS pathlib
  EXPORT pathlib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pathlib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pathlib
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pathlib
)
install(
  DIRECTORY ${INCLUDEDIR}/pathlib
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
