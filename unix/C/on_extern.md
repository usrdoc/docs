Understanding extern
====================

In a nutshell, extern is used to declare a symbol which is defined
elsewhere (but note that this has got nothing to do with function
declarations).

For example:
    If you want to use errno to print the error message the declaration ```extern
    int errno;``` is not necessary in programs where '<errno.h>' is included, This
    declaration is taken care by ```errno.h```. If ```errno.h``` is not included, then
    ```extern int errno;``` is required (Works on most systems. On linux, compilation
    errors out. You are forced to include errno.h). However, if the program
    wants to use any of EXXXX constants, then there is no escape from ```errno.h```.

extern with functions
---------------------

Whenever a function is defined in C it is globally visible by default. Prefixing
the function name with the extern keyword is redundant, doesn't add any value.
The function is visible to anything that links with that object file. However,
to restrict the visibility of the function name, the static keyword is
necessary. Prefixing the function name with static makes it visible only in that
object file.

Also note that use of static on a variable inside a function makes it retain its
value between the calls.
