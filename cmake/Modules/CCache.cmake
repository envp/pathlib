# Find the ccache executable and use that as the compiler launcher
#
# Sets the global property CMAKE_<LANG>_COMPILER_LAUNCHER to `ccache` for
# LANGS: C/CXX

if(NOT DEFINED USE_CCACHE)
  option(USE_CCACHE "Use `ccache` for builds if possible." ON)
endif()

if(USE_CCACHE)
  message(STATUS "Detecting ccache location")
  find_program(
    CCACHE_EXECUTABLE
    "ccache"
    REQUIRED
    DOC "Path to ccache binary"
  )
  message(STATUS "Found ccache: ${CCACHE_EXECUTABLE}")
  set_property(GLOBAL PROPERTY CMAKE_C_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE})
  set_property(GLOBAL PROPERTY CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE})
endif()
