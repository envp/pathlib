#ifndef PATHLIB_PURE_PATH_HPP
#define PATHLIB_PURE_PATH_HPP

#include <cassert>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "pathlib/annotations.hpp"

namespace pathlib {

namespace detail {

/// Concatenate the vector of strings with the given delimiting character.
std::string join(char delimiter, const std::vector<std::string> &parts);

} // namespace detail

/// Offers path operations that do not need filesystem access.
///
/// It offers an interface to manipulate the contents of a path string, without
/// any filesystem I/O.
template <class Flavour>
struct PurePath {
public:
  /// Return all the components of this path.
  PATHLIB_NODISCARD const std::vector<std::string> &parts() const {
    return static_cast<const Flavour *>(this)->parts();
  }

  /// Check if this path is an absolute.
  PATHLIB_NODISCARD bool is_absolute() const {
    return static_cast<const Flavour *>(this)->is_absolute();
  }
};

struct PurePosixPath : PurePath<PurePosixPath> {
public:
  explicit PurePosixPath(std::string_view path);

  /// Return if the contained path is absolute
  PATHLIB_NODISCARD bool is_absolute() const;

  /// Return the components of the contained path
  PATHLIB_NODISCARD const std::vector<std::string> &parts() const;

private:
  static const char PRIMARY_SEPARATOR = '/';
  bool d_is_absolute;
  std::vector<std::string> d_parts;
};

} // namespace pathlib

#endif // PATHLIB_PURE_PATH_HPP
