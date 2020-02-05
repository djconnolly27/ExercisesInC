/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}

/* 1. Intended program:
  - create integer i
  - call foo()
    - print memory address of local array of size 5
    - set every value in the array to 42
    - return pointer to start of array
  - call bar()
    - print memory address of local array of size 5
    - set every value in the array equal to its index
    - array disappears at end of stack frame
  - run for loop
    - print value at each index in the array returned by foo
  - return and exit program
*/

/* 2. I get a warning that the function foo returns the address of a local variable.
  This means that we are creating an array in foo that will disappear at the end of the stack frame.
  In other words, when the function foo() completes, the array will disappear, so the address we return
  will be meaningless.
*/

/* 3. I get a segmentation fault. It appears that when we return a pointer to an array created on the stack,
  and then the stack frame containing that array disappears, we lose access to the data. Thus, we try to
  access a memory address that we should be accessing and get a segmentation fault.
*/

/* 4. It seems that I am still getting a segmentation fault.
  I may ask for some guidance after class to see if I executed something incorrectly.
*/
