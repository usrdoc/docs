Understanding the const keyword
===============================

Let's consider two cases:
      a. const with variables
      b. const with pointers

const with variables
--------------------

If a variable is declared with const keyword, further assignment or modification
of variable value causes it to fail.

```
int
main(void)
{
    const int constvar = 10;
    constvar++;          /* error: increment of read-only variable 'constvar' */
    constvar = 12;      /* error: assignment of read-only variable 'constvar' */

    return(0);
}
```

const keyword with variables is straight forward. Things get hairy when used
with pointers.


const with pointers
-------------------

In case of pointers, the location pointed by the variable is read-only. However
the variable itself can be assigned a new address.

Consider a simple example with an integer pointer.

```
int
main(void)
{
    const int *i;
    int j = 44;

    i = &j;                     /* Okay. Modifying the variable. */
    *i = j;                     /* error: assignment of read-only location *i */

    return(0);
}
```

Consider another example with char *

```
int
main(void)
{
    char *foo;
    foo = strdup("Hello");
    *foo = 'O';                 /* Okay. *foo is now Oello */
    return(0);
}


=====

This is invalid (now we have a const)

int
main(void)
{
    const char *foo;
    foo = strdup("Hello");
    *foo = 'O';               /* error: assignment of read-only location *foo */
    return(0);
}

```

Now consider the case of assignment. i.e assigning a nonqualified variable with
a const qualified variable and vice-versa.


```
int
main(void)
{
    const char *foo;
    char *bar;

    foo = bar;                  /* Okay. */
    bar = foo;                  /* warning: assignment discards const qualifier
                                 * from pointer target type */
    return(0);
}
```

* What does this mean?
  `bar' does not become a `const' by assignment. And manipulation of storage
  pointed to by `bar' is perfectly legal. Also `foo' does not become an
  unqualified variable by assignment. The storage pointed to by `foo' is still
  read-only.

Now consider another example.

```
int
main(void)
{
    const char *foo;
    char *bar;

    bar = strdup("Hello");
    foo = bar;                  /* Does this make foo unqualified? No. */
    bar = foo;                  /* Does this make bar qualified. No. */

    *bar = 'O';                /* Perfectly fine */
    *foo = 'O';                /* error: assignment of read-only location foo */

    return(0);
}
```

However since `bar' and `foo' point to same location, we can do the
manipulations to the same memory location pointed to by `foo'. :-|
