#define _GNU_SOURCE 1
#include <stdio.h>
#include <dlfcn.h>
#include <stdarg.h>
#include "plthook.h"
#include "overload.h"

#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)

void _ol_logger(const char* fmt, ...) 
{
    char buff[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(buff, fmt, args);
    va_end(args);
    ol_logger(buff);
}

#define LOG(...) (_ol_logger("ol[%s]: ", __func__), _ol_logger(__VA_ARGS__), _ol_logger("\n"))

void hook_em(plthook_t *plthook)
{
    int i = 0;
    for (; i < ol_num_hooked_funcs; i++)
    {
        ol_hooked_func* ohf = &funcs_to_hook[i];
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
            LOG("plthook_replace error: %s", plthook_error());
        }
    }
}

void *dlopen(const char *filename, int flag)
{
    LOG("hooked dlopen for %s", filename);

    void* (*orig_dlopen)(const char *, int) = dlsym(RTLD_NEXT, "dlopen");
    void* addr = orig_dlopen(filename, flag);

    plthook_t *plthook;
    if (plthook_open_shared_library_by_ptr(&plthook, addr) != 0)
    {
        LOG("plthook_open error: %s", plthook_error());
        return addr;
    }
    
    hook_em(plthook);

    plthook_close(plthook);
    return addr;
}

#if (defined(HOOK_ON_INIT_FUNC) && defined(HOOK_ON_INIT_LIB))

void init()
{
    LOG("Attempting to hook " STRINGIZE_VALUE_OF(HOOK_ON_INIT_FUNC));

    plthook_t *plthook;
    if (plthook_open(&plthook, STRINGIZE_VALUE_OF(HOOK_ON_INIT_LIB)) != 0)
    {
        LOG("plthook_open error: %s", plthook_error());
        return;
    }
    
    hook_em(plthook);
    plthook_close(plthook);
}
#else
void init(){}
#endif
