#include <stdio.h>
#include "overload.h"

void test1()
{
    printf("Test1: intercept called - success\n");
}

void test2()
{
    printf("Test2: intercept called - success\n");
}

void test3()
{
    printf("Test3: intercept called (orig=%p)- success\n", funcs_to_hook[0].orig_func);
}

ol_hooked_func funcs_to_hook[OL_MAX_HOOKED_FUNCS] =
{
    {"test3_internal", NULL, test3}
};

int ol_num_hooked_funcs = 1;

void ol_logger(const char* msg)
{
    printf(msg);
}
