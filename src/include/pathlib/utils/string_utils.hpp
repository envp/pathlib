#ifndef PATHLIB_UTILS_STRING_UTILS_H
#define PATHLIB_UTILS_STRING_UTILS_H

#include <functional>
#include <string>
#include <string_view>
#include <vector>

/// Collects all string processing function not available here. This construct
/// makes it easier to test
namespace string_utils {

/// Concatenate the vector of strings with the given delimiting character.
/// Split a path into non-empty components based on the delimiting character.
std::string join(char delimiter, const std::vector<std::string> &parts);

/// Explode a string into components separated by a delimiting character.
std::vector<std::string> split_on(char delimiter, std::string_view data);

/// Explode a string into components separated by a delimiting character.
/// An additional predicate can also be passed so that only components matching
/// the predicate will be returned. The predicate doesn't affect the order of
/// the split.
std::vector<std::string>
split_on(char delimiter, std::string_view data,
         std::function<bool(std::string_view)> predicate);

} // namespace string_utils
#endif // PATHLIB_UTILS_STRING_UTILS_H
