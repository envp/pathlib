#ifndef PATHLIB_PURE_PATH_HPP
#define PATHLIB_PURE_PATH_HPP

#include "pathlib/annotations.hpp"
#include "pathlib/assertions.hpp"
#include "pathlib/utils/string_utils.hpp"

#include <algorithm>
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
  PATHLIB_NODISCARD std::optional<std::string_view> basename() const {
    auto *path_flavour = static_cast<const Flavour *>(this);
    if (path_flavour->is_root()) {
      return std::nullopt;
    }
    const auto &components = parts();
    if (components.empty()) {
      return std::nullopt;
    }
    std::string_view name = components.back();
    if (name == "..") {
      return std::nullopt;
    }
    return name;
  }

  /// Return the suffix part of the filename, if any.
  PATHLIB_NODISCARD std::optional<std::string_view> suffix() const {
    std::optional<std::string_view> name = this->basename();
    // std::function<bool(std::string_view)> func = &std::string_view::empty;
    if (!name || name->empty()) {
      return std::nullopt;
    }
    auto dotpos = name->rfind('.');
    if (0 == dotpos || std::string_view::npos == dotpos) {
      return std::nullopt;
    }
    name->remove_prefix(dotpos);
    return name;
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
  static constexpr char PRIMARY_SEPARATOR = '/';
  bool d_is_absolute;
  std::vector<std::string> d_parts;
};

} // namespace pathlib

#endif // PATHLIB_PURE_PATH_HPP
