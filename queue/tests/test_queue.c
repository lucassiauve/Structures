#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(print, first_test)
{
    int var = 0;
    cr_expect_eq(var, 0);
}
