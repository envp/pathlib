#ifndef PATHLIB_ASSERTIONS_HPP
#define PATHLIB_ASSERTIONS_HPP

#include "pathlib/annotations.hpp"

#include <cstddef>
#include <cstdio>
#include <exception>
#include <string>
#include <string_view>
#include <utility>

namespace pathlib {
namespace detail {

PATHLIB_NORETURN constexpr inline void terminate(std::string_view prefix,
                                                 std::string_view reason) {
  if (!prefix.empty()) {
    (void)fwrite(prefix.data(), sizeof(reason[0]), prefix.size(), stderr);
  }
  if (!reason.empty()) {
    (void)fwrite(reason.data(), sizeof(reason[0]), reason.size(), stderr);
  }
  std::terminate();
}

PATHLIB_NORETURN constexpr inline void unreachable(std::string_view message) {
  detail::terminate("UNREACHABLE: ", message);
}

PATHLIB_NORETURN constexpr inline void todo(std::string_view message) {
  detail::terminate("TODO: ", message);
}

} // namespace detail

#define PATHLIB_TODO ::pathlib::detail::todo
#define PATHLIB_UNREACHABLE ::pathlib::detail::unreachable

} // namespace pathlib

#endif // PATHLIB_ASSERTIONS_HPP
