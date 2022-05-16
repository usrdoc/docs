Understanding tricky local variables
====================================

Consider the below piece of program

```
char *
localdate(char *filename)
{
    struct stat filestatus;
    struct tm *tm_ptr;
    char datestr[128]

    stat(filename, &filestatus);
    tm_ptr = localtime(&filestatus.st_mtime);
    strftime(datestr, 128, "%a %b %e %T %Y", tm_ptr);
    return(datestr);
}
```
Though it looks like we are returning a character pointer we are returning a
pointer to an automatic array, local to the function. And the value is
unpredictable once the function returns.

Possible solutions for such problems:

1. Return a string literal. For eg: return "Hello, World";
   However that is not possible in this case since the string we are returning
   is not pre-defined.
   Note: String literals are stored in read-only memory.

2. Use globally declared array.
   Note: Anyone can modify the global array, next time the function is called
         the contents of the string are overwritten by most recent call.

3. Use static array.
   Look up the finer details when used with threads.

4. Use malloc()
   No problem of overwriting. Each invocation allocates fresh memory. However,
   there is a risk of memory leak if not freed upon use. Or risk of corruption
   if freed prematuredly.

5. Make the caller allocate the memory and free it upon use than the function
   allocating the memory. Because the caller knows when the result is no longer
   needed and can free the memory.

