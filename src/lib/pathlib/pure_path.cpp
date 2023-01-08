#include "pathlib/pure_path.hpp"
#include "pathlib/assertions.hpp"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <string_view>
#include <vector>

namespace pathlib {

namespace detail {

std::string join(const std::vector<std::string> &parts, char delimiter) {
  if (parts.empty()) {
    return "";
  }
  size_t capacity =
      parts.size() + std::transform_reduce(
                         std::cbegin(parts), std::cend(parts), 0, std::plus<>(),
                         [](auto part) { return part.length(); });
  std::string result;
  result.reserve(capacity);
  auto iter = std::cbegin(parts);
  result += *iter;
  std::for_each(std::next(iter), std::cend(parts),
                [&result, &delimiter](const std::string &part) {
                  result += delimiter;
                  result += part;
                });
  return result;
}

} // namespace detail

namespace {
/// Split a path into non-empty components based on the delimiting character.
///
/// Redundant components such as '.' are omitted, same as empty components
std::vector<std::string> split_on(char delimiter, std::string_view path) {
  std::vector<std::string> components;
  if (path.empty()) {
    return components;
  }

  size_t start = 0;
  while (start < path.length()) {
    auto match = path.find(delimiter, start);
    if (match == std::string_view::npos) {
      auto part = path.substr(start);
      if (part != ".") {
        components.emplace_back(part);
      }
      break;
    }
    if (match != start) {
      auto part = path.substr(start, match - start);
      if (part != ".") {
        components.emplace_back(part);
      }
    }
    start = match + 1;
  }
  return components;
}

bool starts_with(char elem, std::string_view path) {
  return !path.empty() && path[0] == elem;
}

} // namespace

PurePosixPath::PurePosixPath(std::string_view path)
    : d_is_absolute(starts_with(PurePosixPath::PRIMARY_SEPARATOR, path)),
      d_parts(split_on(PurePosixPath::PRIMARY_SEPARATOR, path)) {}

bool PurePosixPath::is_absolute() const { return d_is_absolute; }

const std::vector<std::string> &PurePosixPath::parts() const { return d_parts; }

} // namespace pathlib
