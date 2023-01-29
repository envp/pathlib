#include "cargs.h"
#include "pathlib/assertions.hpp"
#include "pathlib/pure_path.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <optional>
#include <string_view>

template <std::size_t NUM_OPTS>
void print_usage(const cag_option (&options)[NUM_OPTS]) {
  std::cerr << R"(Usage: basename [OPTION...] PATH...
Print PATH with any leading directory components removed.
If -s is specified, also trim the provided SUFFIX from any PATH.

)";
  cag_option_print(options, NUM_OPTS, stderr);
  std::cerr << R"(
Examples:
    basename /usr/bin/sort          -> "sort"
    basename -s .h include/stdio.h  -> "stdio"
    basename any/str1 any/str2   -> "str1" followed by "str2"
)";
}

int main(int argc, char *argv[]) {

  const cag_option OPTIONS[] = {
      {.identifier = 'z',
       .access_letters = "z",
       .access_name = "zero",
       .value_name = nullptr,
       .description =
           "End each line of output with NUL('\\0') instead of a newline."},
      {.identifier = 's',
       .access_letters = "s",
       .access_name = "suffix",
       .value_name = "SUFFIX",
       .description = "Remove the given trailing suffix, implies -a."},
      {.identifier = 'h',
       .access_letters = "h",
       .access_name = "help",
       .value_name = nullptr,
       .description = "Print help and exit."},
  };

  cag_option_context context;
  bool null_terminate_output = false;
  // This is a view into argv, so should be fine.
  std::optional<std::string_view> suffix;

  cag_option_prepare(&context, OPTIONS, CAG_ARRAY_SIZE(OPTIONS), argc, argv);

  while (cag_option_fetch(&context)) {
    char identifier = cag_option_get(&context);
    switch (identifier) {
    case 'z':
      null_terminate_output = true;
      break;
    case 's':
      suffix = cag_option_get_value(&context);
      break;
    case 'h':
      print_usage(OPTIONS);
      return EXIT_SUCCESS;
    default:
      PATHLIB_TODO("Figure out error handling in libcargs.");
      break;
    }
  }
  // Process positional args:
  std::vector<pathlib::PurePosixPath> positional_args;
  positional_args.reserve(argc - context.index);
  const char LINE_TERMINATOR = null_terminate_output ? '\0' : '\n';
  for (size_t idx = context.index; idx != argc; ++idx) {
    std::string_view arg = argv[idx];
    pathlib::PurePosixPath path(arg);
    auto result = path.basename().value_or(arg);
    if (suffix.has_value() && path.suffix() == suffix) {
      result.remove_suffix(suffix->size());
    }
    std::cout << result << LINE_TERMINATOR;
  }

  return EXIT_SUCCESS;
}
