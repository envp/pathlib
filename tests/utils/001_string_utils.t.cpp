#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "pathlib/utils/string_utils.hpp"

TEST(StringUtilsTest, Join) {
  using namespace std::string_literals;

  EXPECT_EQ(string_utils::join(',', {}), "");
  EXPECT_EQ(string_utils::join(',', {"foo"}), "foo");
  EXPECT_EQ(string_utils::join(',', {"foo", "bar", "qux"}), "foo,bar,qux");

  EXPECT_EQ(string_utils::join('/', {"foo", "bar", "qux"}), "foo/bar/qux");

  EXPECT_EQ(string_utils::join('\\', {"foo", "bar", "qux"}), "foo\\bar\\qux");
  EXPECT_EQ(string_utils::join('\\', {"foo", "bar", "qux"}), "foo\\bar\\qux");

  EXPECT_THAT(string_utils::join('\0', {"foo", "bar", "qux"}),
              "foo\0bar\0qux"s);
}
