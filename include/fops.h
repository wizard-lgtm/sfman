#ifndef FOPS_H

#define FOPS_H


char* read_file_to_buffer(const char* file_path);
char** list_dir_entries(const char* file_path);

#endif