#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
void printPermissions(mode_t mode) {
    printf("User: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf("\nGroup: ");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf("\nOthers: ");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}
int main(int argc, char *argv[]) {
    struct stat fileStat; 
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }  
    if(stat(argv[1], &fileStat) < 0) {
        perror("Error getting file stats");
        exit(EXIT_FAILURE);
    }  
    printf("File: %s\n", argv[1]);
    printf("Owner UID: %d\n", fileStat.st_uid);
    printf("Group GID: %d\n", fileStat.st_gid);
    printf("Permissions: ");
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((S_ISLNK(fileStat.st_mode)) ? "l" : "");
    printPermissions(fileStat.st_mode); 
    return EXIT_SUCCESS;
}

