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

    for (int i = 0; list[i] != NULL; i++) {
        free(list[i]); // Correctly free each entry
    }
    free(list); // Finally, free the list itself
    root();
    return 0;
}