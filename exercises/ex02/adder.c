/*
  Take input from the user and sum the numbers
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Sums an array

  array_p: pointer to first element of array of integers
  size: number of elements input into array by user
  sum_p: pointer to location to store sum of array elements
*/
void sum_array(int* array_p, int size, int* sum_p) {
  int sum = 0;
  for (int i=0; i < size; i++) {
    printf("Element: %i", array_p[i]);
    sum += array_p[i];
  }
  *sum_p = sum;
}

/* Runs adder program

  Read input from user and outputs sum of user input integers
*/
int main() {
  int total = 0;
  int* sum_loc = &total;
  int array[10];
  char buffer[6];
  int j = 0;
  int error = 0;
  printf("Enter a series of numbers to sum: ");

  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

    if (buffer[strlen(buffer) - 1] != '\n') {
      printf("Error: Buffer length exceeded.\n");
      error = 1;
      break;
    }

    if (j > 9) {
      printf("Error: Array length Exceeded.\n");
      error = 1;
      break;
    }

    int convert = atoi(buffer);

    // This will fail if the user actually tries to input the number 0
    if (convert == 0) {
      printf("Error: Cannot convert string to int.\n");
      error = 1;
      break;
    }

    array[j] = convert;
    j++;
  }

  if (!error) {
    sum_array(array, j, sum_loc);
    printf("Array Total: %i\n", total);
  }

  return 0;
}
