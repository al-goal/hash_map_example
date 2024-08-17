#include <gtest/gtest.h> // Include the Google Test framework
#include <hash_map.hpp> // Include the header file for the class we are testing


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}