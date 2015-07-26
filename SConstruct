lib      = SharedLibrary('target', 'target.c', CFLAGS=['-g'], LINKFLAGS=['-rdynamic'])
overload = SharedLibrary('overload', ['overload.c', 'plthook/plthook_elf.c'], CFLAGS=['-g'], LINKFLAGS=['-Wl,-init,init'])
testapp  = Program('testapp', 'main.c', LIBS=['dl', lib], CFLAGS=['-g'], LINKFLAGS=['-Wl,-rpath=.'])
