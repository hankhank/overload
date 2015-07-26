#include <stdio.h>
#include "overload.h"

void test1()
{
    printf("Test1: intercept called - success\n");
}

void nonpreload_test2()
{
    printf("Test2: intercept called - success\n");
}

void test3()
{
    printf("Test3: intercept called (orig=%p)- success\n", funcs_to_hook[0].orig_func);
}

ol_hooked_func funcs_to_hook[OL_MAX_HOOKED_FUNCS] =
{
    {"test2_internal", NULL, nonpreload_test2},
    {"test3_internal", NULL, test3}
};

int ol_num_hooked_funcs = 2;

void ol_logger(const char* msg)
{
    printf(msg);
}
