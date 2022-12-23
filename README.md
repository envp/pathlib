# cpp-lib-template

This is a minimal template I use for creating a C++ static library.
It is intentionally minimal only going so far as to enforce naming conventions through `.clang-tidy`.

## Structure

The structure I follow is to make sure that *every* header file has a corresponding `.cpp` file, even if the C++ file is otherwise empty.

This is a habit I've picked up from my workplace, one of the big advantages is that it ends up generating compile commands for the
"header-only" files, which provides useful auto-completion.
