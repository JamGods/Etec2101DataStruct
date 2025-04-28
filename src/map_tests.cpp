// map_tests.cpp
#include <gtest/gtest.h>
#include <map.h>

using namespace ssuds;

TEST(MapTests, InsertAndAccess)
{
    Map<std::string, int> m;
    m["Bob"] = 42;
    m["Sue"] = 99;
    m["Carl"] = -1;

    EXPECT_EQ(m["Bob"], 42);
    EXPECT_EQ(m["Sue"], 99);
    EXPECT_EQ(m["Carl"], -1);
}

TEST(MapTests, ContainsTest)
{
    Map<std::string, int> m;
    m["Bob"] = 42;
    EXPECT_TRUE(m.contains("Bob"));
    EXPECT_FALSE(m.contains("Sue"));
}

TEST(MapTests, RemoveTest)
{
    Map<std::string, int> m;
    m["Bob"] = 42;
    m["Sue"] = 99;
    EXPECT_TRUE(m.remove("Bob"));
    EXPECT_FALSE(m.contains("Bob"));
    EXPECT_FALSE(m.remove("Carl"));
}

TEST(MapTests, GrowTest)
{
    Map<int, int> m;
    for (int i = 0; i < 100; ++i)
    {
        m[i] = i * 2;
    }
    for (int i = 0; i < 100; ++i)
    {
        EXPECT_TRUE(m.contains(i));
        EXPECT_EQ(m[i], i * 2);
    }
    EXPECT_GE(m.size(), 100);
}

TEST(MapTests, OutputTest)
{
    Map<std::string, int> m;
    m["Alice"] = 1;
    m["Bob"] = 2;

    std::stringstream ss;
    ss << m;
    std::string output = ss.str();

    EXPECT_TRUE(output.find("Alice:1") != std::string::npos);
    EXPECT_TRUE(output.find("Bob:2") != std::string::npos);
}
