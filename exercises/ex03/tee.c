#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR 2;

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

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "No files provided.\n");
    return ERR;
  }

  char ch;
  int a_flag = 0;

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

  int i;
  for (i = 0; i < argc; i++) {
    char op = 'w';
    if (a_flag) {
      op = 'a';
    }
    FILE *f = fopen(argv[i], &op);
    f_array[i+1] = f;
  }
  int status = edit_files(f_array, i+1);
  if (status) {
    fprintf(stderr, "ERR in edit_files.\n");
    return ERR;
  }
  return 0;
}
