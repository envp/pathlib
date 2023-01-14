#ifndef PATHLIB_PURE_PATH_HPP
#define PATHLIB_PURE_PATH_HPP

#include "pathlib/annotations.hpp"
#include "pathlib/utils/string_utils.hpp"

#include <cassert>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace pathlib {

/// Offers path operations that do not need filesystem access.
///
/// It offers an interface to manipulate the contents of a path string,
/// without any filesystem I/O.
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

  /// Return the filename component of the path. The contained
  PATHLIB_NODISCARD std::optional<std::string_view> name() const {
    auto *path_flavour = static_cast<const Flavour *>(this);
    if (path_flavour->is_root()) {
      return std::nullopt;
    }
    return path_flavour->d_parts.back();
  }
};

struct PurePosixPath : PurePath<PurePosixPath> {
public:
  explicit PurePosixPath(std::string_view path);

  /// Return if the contained path is absolute
  PATHLIB_NODISCARD bool is_absolute() const;

  /// Return true if the path is a root
  PATHLIB_NODISCARD bool is_root() const;

  /// Return the components of the contained path
  PATHLIB_NODISCARD const std::vector<std::string> &parts() const;

private:
  static const char PRIMARY_SEPARATOR = '/';
  bool d_is_absolute;
  std::vector<std::string> d_parts;
};

} // namespace pathlib

#endif // PATHLIB_PURE_PATH_HPP
