#define _GNU_SOURCE 1
#include <stdio.h>
#include <dlfcn.h>
#include "plthook.h"

void _ol_logger(const char* fmt, ...) 
{
    char buff[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(buff, fmt, args);
    va_end(args);
    ol_logger(buff);
}

#define LOG(...) (_ol_logger("ol[%s]:", __func__), _ol_logger(__VA_ARGS))

void *dlopen(const char *filename, int flag)
{
    LOG("hooked dlopen for %s\n", filename);

    void* (*orig_dlopen)(const char *, int) = dlsym(RTLD_NEXT, "dlopen");
    void* addr = orig_dlopen(filename, flag);

    plthook_t *plthook;
    if (plthook_open_shared_library_by_ptr(&plthook, addr) != 0)
    {
        LOG("plthook_open error: %s\n", plthook_error());
        return addr;
    }
    
    for (int i = 0; i < ol_num_hooked_funcs; i++)
    {
        ol_hooked_func* ohf = funcs_to_hook[i];
        if 
        (
            plthook_replace
            (
                plthook,
                ohf->func_name,
                ohf->replacement_func,
                &ohf->orig_func
            ) != 0
        )
        {
            LOG("plthook_replace error: %s\n", plthook_error());
        }
    }

    plthook_close(plthook);
    return addr;
}
