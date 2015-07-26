#include <stdio.h>

void test1()
{
    printf("test1: target called - failure\n");
}

void test2_internal()
{
    printf("test2: target called - failure\n");
}

void test2()
{
    test2_internal();
}

void test3_internal()
{
    printf("test2: target called - failure\n");
}

void test3()
{
    test3_internal();
}
