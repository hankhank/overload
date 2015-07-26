#include <stdio.h>
#include <dlfcn.h>

int main()
{
    printf("Starting\n");
    printf("test helloworld\n");
    helloworld();

    printf("test goodbyeworld\n");
    void* lib = dlopen("./libtarget.so", RTLD_NOW);
    void (*gw)() = dlsym(lib, "goodbyeworld");
    gw();
    return 0;
}
