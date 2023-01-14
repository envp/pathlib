#ifndef PATHLIB_ASSERTIONS_HPP
#define PATHLIB_ASSERTIONS_HPP

#include "pathlib/annotations.hpp"

#include <cstddef>
#include <cstdio>
#include <exception>
#include <string>
#include <string_view>

namespace pathlib {
namespace detail {

PATHLIB_NORETURN inline void terminate(std::string_view reason) {
  if (!reason.empty()) {
    (void)fwrite(reason.data(), sizeof(reason[0]), reason.size(), stderr);
  }
  std::terminate();
}

PATHLIB_NORETURN inline void todo(std::string_view reason) {
  std::string todo("TODO: ");
  todo += reason;
  detail::terminate(todo);
}

} // namespace detail

#define PATHLIB_TODO(reason) detail::todo(reason)

} // namespace pathlib

#endif // PATHLIB_ASSERTIONS_HPP
