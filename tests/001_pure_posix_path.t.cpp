#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "pathlib/pure_path.hpp"

using pathlib::PurePosixPath;

TEST(PurePosixPathTest, EmptyPath) {
  EXPECT_THAT(PurePosixPath("").parts(), ::testing::IsEmpty());
}

TEST(PurePosixPathTest, SingleComponent) {
  std::vector<std::string> expected_parts = {"first"};
  auto path = PurePosixPath("first");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_FALSE(path.is_absolute());

  path = PurePosixPath("./first");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_FALSE(path.is_absolute());

  path = PurePosixPath("./first/.");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_FALSE(path.is_absolute());

  path = PurePosixPath("././././first/././././.");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_FALSE(path.is_absolute());
}

TEST(PurePosixPathTest, RedundantSlashes) {
  std::vector<std::string> expected_parts{"first", "second", "third"};
  auto path = PurePosixPath("///first/second/third");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_TRUE(path.is_absolute());

  path = PurePosixPath("//first////second/third");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_TRUE(path.is_absolute());

  path = PurePosixPath("//first//second///third");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_TRUE(path.is_absolute());

  path = PurePosixPath("//first//second///third///");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_TRUE(path.is_absolute());
}

TEST(PurePosixPathTest, RedundantComponents) {
  std::vector<std::string> expected_parts{"first", "second", "third"};

  auto path = PurePosixPath("///first/second/third");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_TRUE(path.is_absolute());

  path = PurePosixPath(".//first/.//.//././second/third");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_FALSE(path.is_absolute());

  path = PurePosixPath("//first//second/././third");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_TRUE(path.is_absolute());

  path = PurePosixPath("././first//second///third/././");
  EXPECT_THAT(path.parts(), ::testing::ContainerEq(expected_parts));
  EXPECT_FALSE(path.is_absolute());
}

TEST(PurePosixPathTest, AbsolutePaths) {
  EXPECT_TRUE(PurePosixPath("/").is_absolute());
  EXPECT_TRUE(PurePosixPath("/./././").is_absolute());
  EXPECT_TRUE(PurePosixPath("/..").is_absolute());
  EXPECT_TRUE(PurePosixPath("/a/").is_absolute());
}

TEST(PurePosixPathTest, RelativePaths) {
  EXPECT_FALSE(PurePosixPath("").is_absolute());
  EXPECT_FALSE(PurePosixPath("./././").is_absolute());
  EXPECT_FALSE(PurePosixPath("..").is_absolute());
  EXPECT_FALSE(PurePosixPath("a/").is_absolute());
}
