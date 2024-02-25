#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
void read_file_contents(int fd) 
{
    char buffer[1024];
    ssize_t bytes_read;   
    printf("Reading file contents:\n");  
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) 
	{
        fwrite(buffer, 1, bytes_read, stdout);
    }   
    printf("\n");
}
void file_stat(const char *filename) 
{
    struct stat file_stat; 
    if (stat(filename, &file_stat) == 0) 
	{
        printf("File Information:\n");
        printf("File size: %ld bytes\n", file_stat.st_size);
        printf("Number of hard links: %ld\n", file_stat.st_nlink);
        printf("File inode: %ld\n", file_stat.st_ino);
        printf("File permissions: %o\n", file_stat.st_mode);
    } 
	else 
	{
        perror("stat");
    }
}
void read_directory(const char *dir_name) 
{
    DIR *dir;
    struct dirent *entry;  
    if ((dir = opendir(dir_name)) != NULL) 
	{
        printf("Directory Contents of %s:\n", dir_name);      
        while ((entry = readdir(dir)) != NULL) 
		{
            printf("%s\n", entry->d_name);
        } 
        closedir(dir);
    } 
	else 
	{
        perror("opendir");
    }
}
int main() 
{
    const char *file_name = "example.txt";
    const char *dir_name = ".";
    int fd;
    if ((fd = open(file_name, O_RDONLY)) == -1) 
	{
        perror("open");
        exit(EXIT_FAILURE);
    }
    read_file_contents(fd);
    if (lseek(fd, 0, SEEK_SET) == -1) 
	{
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    file_stat(file_name);
    read_directory(dir_name);
    close(fd);   
    return 0;
}
