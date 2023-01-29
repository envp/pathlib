add_executable(basename)
target_sources(basename PUBLIC main.cpp)
target_link_libraries(basename SYSTEM pathlib cargs)
