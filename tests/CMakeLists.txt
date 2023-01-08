include(GoogleTest)
find_package(GTest REQUIRED)

set(TESTS
  001_pure_posix_path
)

foreach(TESTNAME ${TESTS})
  add_executable(${TESTNAME} ${TESTNAME}.t.cpp)
  target_link_libraries(
    ${TESTNAME}
    PRIVATE
    pathlib
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
  )
  gtest_discover_tests(${TESTNAME})
endforeach()

