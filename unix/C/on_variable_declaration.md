Using precedence rule
=====================

Consider a couple of declarations:

Example 1:
```
   char* const *(*next)();
   ___________ |   |    |
       |       |  (1)  (2)
       |       |   \-----------> (Directly enclosed by paranthesis, and
       |       |        |         has a * in paranthesis, hence next is a
       |      (3)       |         pointer to something...)
       |       |        |
       |       |        \------> (Paranthesis takes higher precedence over *.
       |       |                  Hence, next is a pointer to a function
       |       |                  returning something...)
       |       |
      (4)      |
       |       \-----------(Process the prefix *. And we get "pointer to")
       |
       |
       \--------(Finally take "char * const", as constant pointer to a
                 character)
```

Putting (1), (2), (3), and (4) together we get

"next is a pointer to a function returning a pointer to a const
pointer-to-char".


Example 2:
```
   char *(*c[10])(int **p);
    (3)   ------      |
             |        |
             |        |
             |       (2)
             |        |
             |        \-------> (p is a pointer to array of integers)
            (1)
             |
             |
             \---- (c is an array[0..9] of pointer to a function returning a
                    pointer-to-char)
```
Or more specifically:

c is an array[0..9] of pointer to a function returning a pointer-to-char and the
function takes `pointer to array of integers` as the parameter.

Example 3:

```
   void (*signal(int sig, void (*func)(int))) (int);
    |    |  |
    |    | (1)
    |    |  |
    |    |  |
    |    |  \------- (signal is a function with two arguments)
    |   (2)
    |    |
    |    \------------ (signal retuns a pointer to a function, which doesn't
    \------------------ return anything (void), it takes one int parameter)
```
