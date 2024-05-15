
#include "test.hpp"
#include <hen/net/header1.hpp>

TEST(TypeName, net_fun1)
{
    auto r = add(1, 1);
    GTEST_ASSERT_EQ(r, 2);
}
