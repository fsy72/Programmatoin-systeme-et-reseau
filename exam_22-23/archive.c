#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "archive.h"

void progress_bar(char *prefix, int current, int max) {
    int i; printf("\r[ %s ] ", prefix);
    for(int i=1; i<=(max%100); i++) { printf("=");}
    if(current >= max) { printf("100.00%%\n");}
    else printf("%.2f%%", 100.0*current/max);
}
struct f_record get_file_record (char *file_name) {
    struct f_record file_r;
    memset(&file_r, 0, sizeof(struct f_record));
    strcpy(file_r.file_name, file_name);
    struct stat st_file; stat(file_name, &st_file);
    file_r.file_size = st_file.st_size;
    file_r.file_permissions = st_file.st_mode;
    return file_r;
}
void create_archive(char *archive_filename) {
    // A FAIRE
    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH; // 755 permissions
    int fd_archive_file = open(archive_filename, O_CREAT | O_TRUNC | O_WRONLY, mode);
    if(fd_archive_file == -1) {
        perror("Erreur d'ouverture de fichier");
        return;
    }
    close(fd_archive_file);
}
void archive_file(char *archive_filename, char *file_name) {
    int fd_archive_file = open(archive_filename, O_WRONLY | O_APPEND);
    if(fd_archive_file == -1) {
        perror("Erreur d'ouverture de fichier");
        return;
    }
    int fd_file_src = open(file_name, O_RDONLY);
    if(fd_file_src == -1) {
        perror("Erreur d'ouverture de fichier source");
        return;
    }
    printf("Ecriture  de l'entete du fichier\n");
    struct f_record file_r = get_file_record(file_name);

    int nbwrite = write(fd_archive_file, &file_r, sizeof(struct f_record));
    if(nbwrite <= 0) {
        perror("Erreur d'ecriture de l'entete");
        return;
    }

    printf(">>>>>>>>>> Ecriture des données de %s\n", file_name);
    char buffer[1024];
    int nbreads = read(fd_file_src, buffer, 1024*sizeof(char));

    while(nbreads > 0) {
        write(fd_archive_file, buffer, nbreads*sizeof(char));
        progress_bar(file_name, nbreads, file_r.file_size);
        nbreads = read(fd_file_src, buffer, 1024*sizeof(char));
    }
    progress_bar(file_name, file_r.file_size, file_r.file_size);
    close(fd_archive_file);
    close(fd_file_src);
}

void extract_file(char *file_name, char *archive_filename, char *newname) {
    // A FAIRE
    int fd_archive_file = open(archive_filename, O_RDONLY);
    if(fd_archive_file == -1) {
        perror("Erreur d'ouverture de fichier archive");
        return;
    }

    struct f_record file_r;
    int nbread;
    while((nbread = read(fd_archive_file, &file_r, sizeof(struct f_record))) > 0) {
        if(strcmp(file_r.file_name, file_name) == 0) {
            break;
        }
    }

    if(nbread <= 0) {
        perror("Fichier introuvable dans l'archive");
        close(fd_archive_file);
        return;
    }

    int fd_new_file = open(newname, O_CREAT | O_TRUNC | O_WRONLY, file_r.file_permissions);
    if(fd_new_file == -1) {
        perror("Erreur d'ouverture de nouveau fichier");
        close(fd_archive_file);
        return;
    }

    char buffer[1024];
    while((nbread = read(fd_archive_file, buffer, 1024*sizeof(char))) > 0) {
        write(fd_new_file, buffer, nbread*sizeof(char));
    }

    close(fd_archive_file);
    close(fd_new_file);
}
void show_files(char *archive_filename) {
    // A FAIRE
    int fd_archive_file = open(archive_filename, O_RDONLY);
    if(fd_archive_file == -1) {
        perror("Erreur d'ouverture de fichier archive");
        return;
    }

    struct f_record file_r;
    int nbread;
    while((nbread = read(fd_archive_file, &file_r, sizeof(struct f_record))) > 0) {
        printf("Nom du fichier : %s\n", file_r.file_name);
        printf("Taille du fichier : %ld octets\n", file_r.file_size);
        printf("Permissions du fichier : %o\n", file_r.file_permissions);
    }

    close(fd_archive_file);
}