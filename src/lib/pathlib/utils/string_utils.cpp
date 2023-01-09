#include "pathlib/utils/string_utils.hpp"

#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace string_utils {

std::string join(char delimiter, const std::vector<std::string> &parts) {
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

std::vector<std::string> split_on(char delimiter, std::string_view data) {
  // TODO(self): Use std::identity(true) for C++20
  return split_on(delimiter, data, [](std::string_view) { return true; });
}

std::vector<std::string>
split_on(char delimiter, std::string_view data,
         std::function<bool(std::string_view)> predicate) {
  std::vector<std::string> components;
  if (data.empty()) {
    return components;
  }

  size_t start = 0;
  while (start < data.length()) {
    auto match = data.find(delimiter, start);
    if (match == std::string_view::npos) {
      auto part = data.substr(start);
      if (predicate(part)) {
        components.emplace_back(part);
      }
      break;
    }
    if (match != start) {
      auto part = data.substr(start, match - start);
      if (predicate(part)) {
        components.emplace_back(part);
      }
    }
    start = match + 1;
  }
  return components;
}

} // namespace string_utils
