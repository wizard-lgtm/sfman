#include "fops.h"
#include <stdio.h>
#include <stdlib.h>
#include <window.h>
int main(){
    const char* fpath = "./test.txt";
    const char* dir_path = ".";
    char* file_contents = read_file_to_buffer(fpath);
    if(file_contents==NULL){
        return 1;
    }
    printf("%s\n", file_contents);
    free (file_contents);
    file_contents = NULL;
    char** list = list_dir_entries(dir_path);

    for (int i = 0; list[i] != NULL; i++) {
        printf("Entry %d: %s\n", i + 1, list[i]);
    }

    // Don't forget to free the memory
    for (int i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
    root();
    return 0;
}