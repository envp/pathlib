#include "pathlib/pure_path.hpp"
#include "pathlib/assertions.hpp"
#include "pathlib/utils/string_utils.hpp"

#include <cassert>
#include <iterator>
#include <string_view>
#include <vector>

namespace pathlib {

namespace {
/// Split a path into non-empty components based on the delimiting character.
///
/// Redundant components such as '.' are omitted, same as empty components
std::vector<std::string> split_path(char delimiter, std::string_view path) {
  return string_utils::split_on(delimiter, path, [](std::string_view fragment) {
    return fragment != ".";
  });
}

bool starts_with(char elem, std::string_view path) {
  return !path.empty() && path[0] == elem;
}

} // namespace

PurePosixPath::PurePosixPath(std::string_view path)
    : d_is_absolute(starts_with(PurePosixPath::PRIMARY_SEPARATOR, path)),
      d_parts(split_path(PurePosixPath::PRIMARY_SEPARATOR, path)) {}

bool PurePosixPath::is_absolute() const { return d_is_absolute; }

bool PurePosixPath::is_root() const { return d_is_absolute && d_parts.empty(); }

const std::vector<std::string> &PurePosixPath::parts() const { return d_parts; }

} // namespace pathlib
