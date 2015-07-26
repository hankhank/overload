#include <stdio.h>
#include <dlfcn.h>

void test1();
void test2();
void test3();

int main()
{
    printf("Starting test\n");   

    printf("Test1: Dynamic library call - Preloaded\n");   
    test1();
    
    printf("Test2: Dynamic library call - Plthook\n");   
    test2();

    printf("Test3: dlopen'd  function call\n");
    void* lib = dlopen("./libtarget.so", RTLD_NOW);
    void (*test3)() = dlsym(lib, "test3");
    test3();

    return 0;
}
