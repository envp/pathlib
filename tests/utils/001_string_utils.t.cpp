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

TEST(StringUtilsTest, Split) {
  using namespace std::string_literals;
  using Container = std::vector<std::string>;

  EXPECT_THAT(string_utils::split_on(',', ""),
              ::testing::ContainerEq<Container>({}));
  EXPECT_THAT(string_utils::split_on(',', "foo"),
              ::testing::ContainerEq<Container>({"foo"}));
  EXPECT_THAT(string_utils::split_on(',', "foo,bar,qux"),
              ::testing::ContainerEq<Container>({"foo", "bar", "qux"}));

  EXPECT_THAT(string_utils::split_on('/', "foo/bar/qux"),
              ::testing::ContainerEq<Container>({"foo", "bar", "qux"}));

  EXPECT_THAT(string_utils::split_on('\\', "foo\\bar\\qux"),
              ::testing::ContainerEq<Container>({"foo", "bar", "qux"}));
  EXPECT_THAT(string_utils::split_on('\\', "foo\\bar\\qux"),
              ::testing::ContainerEq<Container>({"foo", "bar", "qux"}));

  EXPECT_THAT(string_utils::split_on('\0', "foo\0bar\0qux"s),
              ::testing::ContainerEq<Container>({"foo", "bar", "qux"}));
}
