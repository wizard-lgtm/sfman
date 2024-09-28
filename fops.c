#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <Kernel/sys/dirent.h>
#include <sys/dirent.h>

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

int dir_entries_count(DIR* dir){
    int n = 0;
    
    while(1){
        struct dirent* next;
        next = readdir(dir);
        

        if(next == NULL){
            break;
        }
         // Skip "." and ".."
        if (strcmp(next->d_name, ".") == 0 || strcmp(next->d_name, "..") == 0) {
            continue;
        }
        else{
            n++;
        }
    }
    rewinddir(dir); // Don't forget rewind it
    return n;

}

char** list_dir_entries(const char* dir_path){

    DIR* dir = opendir(dir_path);

    int entrycount = dir_entries_count(dir);

    printf("Entries count is: %d\n", entrycount);

    int entry_len = 0; // How many entries are there currently in the list 
    int entry_max = 2; // List max
    char** list = (char**)malloc(sizeof(char*) * entry_max); // Alloc for string pointers

    // Add entry one by one 

    while(1){
        struct dirent* next;
        next = readdir(dir);
        if(next == NULL){
            break;
        }
        // get entry size name
        int entryname_len = strlen(next->d_name);
        char* str = malloc(sizeof(char) * entryname_len);

        // Copy name to str 
        strcpy(str,next->d_name + 1);

        // Resize list 
        entry_max++;
        list = realloc(list, sizeof(char*) * entry_max);

        if(list == NULL){
            perror("Memory allocation failed!");
        }

        // Save 
        list[entrycount] = str;
        entrycount++;
    }


    closedir(dir);
    
    return list;

}