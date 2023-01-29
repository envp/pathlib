include(FetchContent)
FetchContent_Declare(Cargs
  GIT_REPOSITORY https://github.com/likle/cargs.git
  GIT_TAG 5bbcfca833eeb504996afb85ad5b8470c96dc752 # (v1.0.3)
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(cargs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(basename)

add_custom_target(examples)
add_dependencies(examples basename)
