include(GoogleTest)
find_package(GTest REQUIRED)

set(TESTS
  utils/001_string_utils
  001_pure_posix_path
)

foreach(TESTNAME ${TESTS})
  string(REPLACE "/" "_" TEST_TARGET ${TESTNAME})
  add_executable(${TEST_TARGET} ${TESTNAME}.t.cpp)
  target_link_libraries(
    ${TEST_TARGET}
    PRIVATE
    pathlib
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
  )
  gtest_discover_tests(${TEST_TARGET})
endforeach()

