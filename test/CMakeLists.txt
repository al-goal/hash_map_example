enable_testing()

add_executable(
  test_hash_map
  test_hash_map.cpp
)

target_link_libraries(
  test_hash_map
  hashmap_example
  GTest::gtest_main
)

target_include_directories(
    test_hash_map PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src>
)

include(GoogleTest)
gtest_discover_tests(test_hash_map)