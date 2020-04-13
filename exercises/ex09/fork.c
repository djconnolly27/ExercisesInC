/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

To test the global, heap, and stack segments of memory, I had the parent process create integer variables and set them to some values. I then had the child process modify those values, and then at the end, I checked their values from the parent process. Based upon these results, it seems that the parent and child do not share these segments of memory. However, I found that the parent and child return the same addresses for where these variables were located, which makes me believe that fork() creates a copy of the entire address space of the parent process. Most of my ideas for checking the code and static segments of memory revolved around checking the addresses of functions and static variables, but given my findings with respect to heap/stack/global variables not being shared but appearing to share addresses I could not devise a good method for checking whether the parent and child processes shared these segments of code. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

int global_test = 87;

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    // sleep(i);
    printf("Hello from child %d.\n", i);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    int* heap_test = (int*) malloc(sizeof(int));
    *heap_test = 76;

    int stack_test = 98;
    printf("Parent heap_test is %i and is located at %p.\n", *heap_test, heap_test);
    printf("Parent stack_test is %i.\n", stack_test);
    printf("Parent global_test is %i.\n", global_test);
    printf("Parent address of child_code is %p.\n", child_code);

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            *heap_test = 1;
            printf("Child %i heap_test is %i and is located at %p.\n", i, *heap_test, heap_test);

            stack_test = 2;
            printf("Child %i stack_test is %i.\n", i, stack_test);

            global_test = 3;
            printf("Child %i global_test is %i.\n", i, global_test);

            printf("Child %i address of child_code is %p.\n", i, child_code);
            child_code(i);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    printf("Parent heap_test is now %i and is located at %p.\n", *heap_test, heap_test);
    printf("Parent stack_test is now %i.\n", stack_test);
    printf("Parent global_test is now %i.\n", global_test);
    exit(0);
}
