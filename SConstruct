# Setup common build params
env = Environment(CPPPATH=['.'], CFLAGS=['-g', '-Wall'])

# building test overload
overload = env.SharedLibrary('overload', ['overload.c', 'plthook_elf.c', 'test/intercept.c'], CFLAGS=['-DHOOK_ON_INIT_FUNC=test2_internal', '-DHOOK_ON_INIT_LIB=libtarget.so'], LINKFLAGS=['-Wl,-init,init'])
testlibrary = env.SharedLibrary('target', 'test/target.c')
test        = env.Program('overload_test', ['test/test.c'],  LIBS=['dl', testlibrary], LINKFLAGS=['-Wl,-rpath=.'])
