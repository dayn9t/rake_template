
#include "test.hpp"
#include <rat/mod_a/header1.hpp>

TEST(TypeName, mod_a_fun1)
{
    auto r = fun1(1, 1);
    GTEST_ASSERT_EQ(r, 2);
}
