
#include "test.hpp"
#include <rat/mod_so/header2.hpp>

TEST(TypeName, mod_a_fun1)
{
    auto r = fun2(1, 1);
    GTEST_ASSERT_EQ(r, 2);
}
