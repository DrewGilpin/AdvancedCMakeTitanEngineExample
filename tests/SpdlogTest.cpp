#include <spdlog/spdlog.h>        // pulls in <fcntl.h> → defines LOCK_READ/WRITE
#ifdef LOCK_READ                  // kill the macros – they’re only for fcntl(2)
#  undef LOCK_READ
#endif
#ifdef LOCK_WRITE
#  undef LOCK_WRITE
#endif

#include "gtest/gtest.h"
#include "MyClass.h"              // -> EsenthelEngine.h -> Image.h (uses enums)

TEST(MyClass, GetSetValueSpdlog)
{
    spdlog::info("constructing MyClass …");
    MyClass c("bob", 42);

    spdlog::debug("initial value = {}", c.getValue());
    EXPECT_EQ(c.getValue(), 42);

    c.setValue(99);
    spdlog::warn("after setValue = {}", c.getValue());

    EXPECT_EQ(c.getValue(), 99) << "value didn’t update correctly";
}
