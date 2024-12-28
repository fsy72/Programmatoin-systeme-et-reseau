#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct f_record {
    char file_name[255];
    long int file_size;
    mode_t file_permissions;
};

void progress_bar(char *prefix, int current, int max);
void create_archive(char *archive_filename);
void archive_file(char *archive_filename, char *file_name);
void extract_file(char *file_name, char *archive_filename, char *newname);
void show_files(char *archive_filename);
#endif //ARCHIVE_H