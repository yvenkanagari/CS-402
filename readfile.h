#include <stdlib.h>
#include <stdio.h>

int open_file(char *filename);
int read_float(float *f);
int read_int(int *i);
int read_string(char *addr);
int close_file(FILE *stream);