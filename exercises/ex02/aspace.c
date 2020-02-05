/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void test() {
  int a = 5;
  printf ("Address of a is %p\n", &a);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    char *s = "Hello, World";

    // Yes, the heap grows towards larger addresses.
    void *t = malloc(128);

    // The stack grows towards larger addresses.
    test();

    // There are 32 bits (8 bytes) between the two variables.
    int x = 31;
    void *q = malloc(sizeof(x));
    void *r = malloc(sizeof(x));

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);
    printf ("t points to %p\n", t);
    printf ("q points to %p\n", q);
    printf ("r points to %p\n", r);

    return 0;
}
