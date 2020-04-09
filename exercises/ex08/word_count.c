#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

/* Prints out the frequency with which each word is found in the file
*/
void print_frequencies(GHashTable* table) {
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init(&iter, table);
  char* word;
  int freq;
  while (g_hash_table_iter_next (&iter, &key, &value)) {
    word = (char*) key;
    freq = *((int*)value);
    printf("%s: %d\n", word, freq);
  }
}
/* Splits up lines into their constitutive words
*/
void split_lines(char* line, GHashTable* table) {
  int* x;
  for (char* token = strtok(line, " "); token != NULL; token = strtok(NULL, " ")) {
    char* scpy = strdup(token);
    x = (int*) g_hash_table_lookup(table, scpy);
    if (x == NULL) {
      x = malloc(sizeof(int));
      *x = 0;
    }
    *x += 1;
    g_hash_table_insert(table, scpy, (gpointer) x);
  }
}

/* Run this file with "./word_count.c {txt_file_name}"
*/
int main(int argc, char** argv) {

    char const* const fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    if (!file) {
      return 1;
    }
    char line[256];

    GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);
    while (fgets(line, sizeof(line), file)) {
      split_lines(line, map);
    }
    fclose(file);
    print_frequencies(map);


    return 0;
}
