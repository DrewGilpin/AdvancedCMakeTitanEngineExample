#include <iostream>          // << this
#include "gtest/gtest.h"
#include "MyClass.h"

TEST(MyClass, GetSetValue) {
    std::cout << "[MyClass] ctor …\n";

    MyClass c("bob", 42);
    std::cout << "[MyClass] initial value = " << c.getValue() << '\n';

    EXPECT_EQ(c.getValue(), 42);

    c.setValue(99);
    std::cout << "[MyClass] after setValue = " << c.getValue() << '\n';

    EXPECT_EQ(c.getValue(), 99)
        << "value didn’t update correctly1 ";     // message only if it fails
}
