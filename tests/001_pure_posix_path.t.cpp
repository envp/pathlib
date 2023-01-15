#include "gmock/gmock.h"
#include "gtest/gtest.h"

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
  EXPECT_TRUE(PurePosixPath("//a/").is_absolute());

  // This is somewhat non-sensical, in that it is unresolvable. but consistent?
  EXPECT_TRUE(PurePosixPath("/..").is_absolute());
}

TEST(PurePosixPathTest, RelativePaths) {
  EXPECT_FALSE(PurePosixPath("").is_absolute());
  EXPECT_FALSE(PurePosixPath("./././").is_absolute());
  EXPECT_FALSE(PurePosixPath("..").is_absolute());
  EXPECT_FALSE(PurePosixPath("a/").is_absolute());
}

TEST(PurePosixPathTest, HasNoBasename) {
  EXPECT_FALSE(PurePosixPath("").basename().has_value());
  EXPECT_FALSE(PurePosixPath("/").basename().has_value());
  EXPECT_FALSE(PurePosixPath(".").basename().has_value());
  EXPECT_FALSE(PurePosixPath("..").basename().has_value());
}

TEST(PurePosixPathTest, HasBasename) {
  EXPECT_EQ(PurePosixPath("foo").basename(), "foo");
  EXPECT_EQ(PurePosixPath("./foo").basename(), "foo");
  EXPECT_EQ(PurePosixPath("relative/path/to/foo").basename(), "foo");
  EXPECT_EQ(PurePosixPath("./relative/path/to/foo").basename(), "foo");
  EXPECT_EQ(PurePosixPath("../relative/path/to/foo").basename(), "foo");
  EXPECT_EQ(PurePosixPath("/absolute/path/to/foo").basename(), "foo");

  EXPECT_EQ(PurePosixPath("foo.tar").basename(), "foo.tar");
  EXPECT_EQ(PurePosixPath("./foo.tar").basename(), "foo.tar");
  EXPECT_EQ(PurePosixPath("relative/path/to/foo.tar").basename(), "foo.tar");
  EXPECT_EQ(PurePosixPath("./relative/path/to/foo.tar").basename(), "foo.tar");
  EXPECT_EQ(PurePosixPath("../relative/path/to/foo.tar").basename(), "foo.tar");
  EXPECT_EQ(PurePosixPath("/absolute/path/to/foo.tar").basename(), "foo.tar");

  EXPECT_EQ(PurePosixPath("foo.tar.").basename(), "foo.tar.");
  EXPECT_EQ(PurePosixPath("foo.tar.gz").basename(), "foo.tar.gz");
}

TEST(PurePosixPathTest, HasNoSuffix) {
  EXPECT_FALSE(PurePosixPath("").suffix().has_value());
  EXPECT_FALSE(PurePosixPath(".").suffix().has_value());
  EXPECT_FALSE(PurePosixPath("..").suffix().has_value());
  EXPECT_FALSE(PurePosixPath("/").suffix().has_value());
  EXPECT_FALSE(PurePosixPath("/foo").suffix().has_value());
  EXPECT_FALSE(PurePosixPath("/foo/bar/.").suffix().has_value());
  EXPECT_FALSE(PurePosixPath("foo/bar/.baz").suffix().has_value());
  EXPECT_FALSE(PurePosixPath("foo/bar/baz").suffix().has_value());
}

TEST(PurePosixPathTest, HasSuffix) {
  EXPECT_TRUE(PurePosixPath("/foo/bar/baz.tar").suffix().has_value());
  EXPECT_EQ(PurePosixPath("/foo/bar/baz.tar").suffix(), ".tar");
  EXPECT_EQ(PurePosixPath("/foo/bar/baz.tar.gz").suffix(), ".gz");
  EXPECT_EQ(PurePosixPath("foo.tar.").suffix(), ".");
}
