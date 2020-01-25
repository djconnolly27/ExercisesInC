#include <stdio.h>

/* The optimization seems to ignore unused variables and bits of code.
  Additionally, it removed the "addl" command from the code, which suggests
  that it is precomputing the output of the addition of 5 + 1 rather than actually allowing
  the code to run and wasting valuable time and space.
*/
int main() {
    int x = 5;
    // printf("Hello, World! %i\n", x);
    int y = x + 1;
    printf("%i", y);
    return 0;
}
