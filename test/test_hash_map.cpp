#include <gtest/gtest.h> // Include the Google Test framework
#include <hash_map.hpp> // Include the header file for the class we are testing

TEST(MyHashMapTest, BasicFunctionality)
{
    hash_map_example::HashMap<std::string, int> map;
    EXPECT_THROW(map.get_first(), std::out_of_range);
    EXPECT_THROW(map.get_last(), std::out_of_range);
    EXPECT_EQ(map.begin(), map.end());

    map.insert("one", 1);
    EXPECT_EQ(map.get("one"), 1);
    EXPECT_EQ(map.get_first().first, "one");
    EXPECT_EQ(map.get_last().first, "one");
    EXPECT_NE(map.begin(), map.end());
    EXPECT_EQ((*map.begin()).first, "one");
    EXPECT_EQ((*map.begin()).second, 1);
 
    map.insert("two", 2);
    EXPECT_EQ(map.get("one"), 1);
    EXPECT_EQ(map.get("two"), 2);
    EXPECT_EQ(map.get_first().first, "one");
    EXPECT_EQ(map.get_last().first, "two");

    map.insert("one", -1);
    EXPECT_EQ(map.get("one"), -1);
    EXPECT_EQ(map.get("two"), 2);
    EXPECT_EQ(map.get_last().first, "one");

    map.remove("two");
    EXPECT_THROW(map.get("two"), std::out_of_range);
}