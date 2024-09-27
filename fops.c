#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///
/// Allocates buffer and reads file into it.
///
char* read_file_to_buffer(const char* file_path){


    FILE* f = fopen(file_path, "r");

    if(f == NULL){
        perror("File opening error!");
        return NULL;
    }


    // Get file size
    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    rewind(f);    

    char* buffer = malloc(sizeof(char) * fsize);

    int bytes_read = fread(buffer, sizeof(char), fsize, f); 
    buffer[bytes_read] = '\0'; // Put null character to buffer 

    fclose(f);

    return buffer;

}

char** list_file_entires(){
    int dir_entries_len; 
    char** file_list = malloc(dir_entries_len);
}