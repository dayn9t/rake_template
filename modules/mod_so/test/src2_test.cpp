
#include "test.hpp"
#include <hen/mod_so/header2.hpp>

TEST(TypeName, net_fun1)
{
    auto r = multiply(1, 1);
    GTEST_ASSERT_EQ(r, 2);
}
