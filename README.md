Overload
========

What is overload.
----------------

A library to create shared libraries that can be LD_PRELOAD'd to intercept 
hook function calls in other shared libraries

How it works
----------------

If the executable uses dlopen and dlsym to load the library  it hooks 
dlopen and then rewrites the PLT table entries for the specified symbols.

If the executable was linked against the library it specifies an init
function that rewrites the PLT table entries for the specified symbols.


Usages
-----

If you have an executable that uses library `libfoo.so.1` and want to 
intercept a function call `recv()` without modifying the library or the executable
build a shared library that includes overload.c and defines the array `ol_funcs_to_hook`,
and puts the number of hooked functions in `ol_num_hooked_funcs`.

ol_logger must also be defined to handle logging from the overload wrapper.

Then run the executable like env LD_PRELOAD=liboverload.so exe

License
-------

MIT
