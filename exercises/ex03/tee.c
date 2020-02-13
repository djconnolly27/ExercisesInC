#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR 2;

/* edit_files: writes or appends data from stdin to stdout files in array

Handles file stream closing

files: FILE array
num_files: number of files in files array
returns: int status code
*/
int edit_files(FILE *files[], int num_files) {
  char buffer[80];
  while (fscanf(stdin, "%79[^\n]\n", buffer) == 1) {
    for (int j = 0; j < num_files; j++) {
      fprintf(files[j], "%s\n", buffer);
    }
  }
  for (int j = 1; j < num_files; j++) {
    fclose(files[j]);
  }
  return 0;
}

/* Handles command line arguments
*/
int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "No files provided.\n");
    return ERR;
  }

  char ch;
  int a_flag = 0;

  // Handle command line options
  while ((ch = getopt(argc, argv, "a")) != EOF) {
    switch (ch) {
      case 'a':
        a_flag = 1;
        break;
      default:
        fprintf(stderr, "Unknown option: '%s'\n", optarg);
        return ERR;
    }
  }
  argc -= optind;
  argv += optind;

  FILE *f_array[10];
  f_array[0] = stdout;

  if (argc > 8) {
    fprintf(stderr, "Too many files for buffer.\n");
    return ERR;
  }

  // Open files in write or append mode
  int i;
  for (i = 0; i < argc; i++) {
    char op = 'w';
    if (a_flag) {
      op = 'a';
    }
    FILE *f = fopen(argv[i], &op);
    f_array[i+1] = f;
  }

  // Write data to files
  int status = edit_files(f_array, i+1);
  if (status) {
    fprintf(stderr, "ERR in edit_files.\n");
    return ERR;
  }
  return 0;
}

/*
 Question 3:
 After reading the portion of HFC in chapter 3 related to the getopt() function, I felt
 fairly confident in my ability to complete this assignment. My largest concern was
 that I was not sure what the intracacies of working with the FILE type were, but that
 was not a problem in solving the problem. Additionally, my current solution assumes
 each line of the data input from stdin is less than 80 characters long.

 Question 4:
 The largest difference I see is that professional code has better error handling. It
 simultaneously handles the complexity of a variety of cases while remaining wholly
 readable. Overall, my approach is fairly similar to the second of the two professional
 examples in design. Additionally, both use structs to achieve a somewhat object-oriented
 looking style that manages increasing complexity with ease. Finally, both use the read()
 c function rather than fscanf, which I chose to use. It appears that this allows them to
 worry less about what the input from stdin will lood like, whereas my solution requires
 knowledge that the input has no more than 80 characters per line.

*/
