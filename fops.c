#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>

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

char** list_dir_entries(char* dir_path) {
    DIR* dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return NULL;
    }

    int entrycount = dir_entries_count(dir);
    printf("Entries count is: %d\n", entrycount);

    // Allocate space for entrycount + 1 to account for the NULL terminator
    char** list = (char**)malloc(sizeof(char*) * (entrycount + 1)); 
    if (list == NULL) {
        perror("Memory allocation failed for list");
        closedir(dir);
        return NULL;
    }

    int entry_len = 0;
    struct dirent* next;

    while ((next = readdir(dir)) != NULL) {
        if (strcmp(next->d_name, ".") == 0 || strcmp(next->d_name, "..") == 0) {
            continue;
        }

        // Get the length of the directory entry name
        int entryname_len = strlen(next->d_name);
        
        // Allocate memory for the directory name
        char* str = (char*)malloc(sizeof(char) * (entryname_len + 1));
        if (str == NULL) {
            perror("Memory allocation failed for entry");
            closedir(dir);
            
            // Free previously allocated entries
            for (int i = 0; i < entry_len; i++) {
                free(list[i]);
            }
            free(list);
            return NULL;
        }

        // Copy the name into str
        strcpy(str, next->d_name);

        // Save the entry in the list
        list[entry_len++] = str;
    }

    closedir(dir);

    // Set the last element to NULL to mark the end of the list
    list[entry_len] = NULL;

    return list;
}
