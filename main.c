#include "fops.h"
#include <stdio.h>
#include <stdlib.h>
#include <window.h>
int main(){
    const char* fpath = "./test.txt";
    char* file_contents = read_file_to_buffer(fpath);
    if(file_contents==NULL){
        return 1;
    }
    printf("%s\n", file_contents);
    free (file_contents);
    file_contents = NULL;
    root();
    return 0;
}