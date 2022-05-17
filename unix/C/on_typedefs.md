On typedefs
===========

[Notes from `Expert C Programming by P V D Linden`]

typedef introduces new name for a type (note that it does not reserve
space). However, it not the same as the macro substitution.

Consider the signal declaration

```
void (*signal(int sig, void (*func)(int))) (int);
```

This can be simplified with the typedef

```
typedef void (*func_ptr) (int);
```

and the signal function becomes

```
func_ptr signal(int, func_ptr);
```

The below declaration is valid but not recommended:

```
typedef int *ptr, (*func)(), arr[5];

a. ptr is the type 'pointer to int' (for eg: ptr i ---> int *i)
b. func is the type 'pointer to function returning int'
        func foobar  ----> int (*foobar)()
c. arr is the type 'arry of 5 ints'
        arr j -----> int j[5]
```

differences: typedef and #define
--------------------------------
typedefs can be thought of as being a complete encapsulated type --- cannot be
added to it after declaring. On the contrary the macro typenames can be extended
with other type specifiers.

For example:
```
#define peach int
unsigned peach i;               /* just fine */

typedef int banana;
unsigned banana i;              /* Error! Can't extend. */
```

Another key difference:

```
#define int_ptr int *
int_ptr foo, bar;

After macro expansion this becomes

int * foo, bar;

Where foo is pointer to int and bar is an int
```

Now consider typedef for a similar scenario
```
typedef char * char_ptr;
char_ptr foo, bar;

In the above scenario, both foo and bar are pointers to char.
```
