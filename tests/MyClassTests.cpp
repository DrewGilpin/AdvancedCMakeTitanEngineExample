#include "gtest/gtest.h"
#include "MyClass.h"

TEST(MyClass, GetSetValue) {
    MyClass c("bob", 42);

    EXPECT_EQ(c.getValue(), 42);

    c.setValue(99);

    EXPECT_EQ(c.getValue(), 99)
        << "value didn’t update correctly1 ";     // message only if it fails
}

TEST(MyClass, GetName) {
    MyClass c("alice", 5);

    EXPECT_EQ(c.getName(), "alice");

    c.setValue(10);
    EXPECT_EQ(c.getName(), "alice")
        << "name changed unexpectedly";
}
