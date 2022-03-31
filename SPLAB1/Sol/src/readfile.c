#include "readfile.h"

// Open a file by calling: open_file(), passing in the name of the file to open as a string; open_file() returns 0 if the
// file is successfully opened, and -1 if the file cannot be opened.
int open_file(char *filename){
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp== NULL){
        return -1;
    }
    close_file(fp);
    return 0;
}


int read_float(float *f){
   int status = scanf("%f",f);
   if (status > 0 && status != EOF){
       return 0;
   }
   return -1;
}


int read_int(int *i){
    int status = scanf("%d",i);
    if (status > 0 && status != EOF){
        return 0;
    }
    return -1;
}

int read_string(char *addr){
    int status = scanf("%s",addr);
    if (status > 0 && status != EOF){
        return 0;
    }
    return -1;
}

// Close file
int close_file(FILE *stream){
    return fclose(stream);
}