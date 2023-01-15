include(GoogleTest)
find_package(GTest REQUIRED)

set(TESTS
  utils/001_string_utils
  001_pure_posix_path
)

set(CTEST_OUTPUT_ON_FAILURE ON)

foreach(TESTNAME ${TESTS})
  string(REPLACE "/" "_" TESTNAME_SANITIZED ${TESTNAME})
  set(TEST_TARGET "${TESTNAME_SANITIZED}.test")
  add_executable(${TEST_TARGET} ${TESTNAME}.t.cpp)
  target_link_libraries(
    ${TEST_TARGET}
    PRIVATE
    pathlib
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
  )
  gtest_discover_tests(
    ${TEST_TARGET}
    EXTRA_ARGS --gtest_color=yes --gtest_brief=1
  )
endforeach()
