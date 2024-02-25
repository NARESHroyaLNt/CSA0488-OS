#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define FILE_PATH "example.txt"
#define BUFFER_SIZE 1024
int main() 
{
    int fd;
    ssize_t bytes_written, bytes_read;
    char buffer[BUFFER_SIZE] = "Hello, this is a test message written to the file.\n";
    fd = open(FILE_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) 
	{
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    bytes_written = write(fd, buffer, strlen(buffer));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return EXIT_FAILURE;
    }
    close(fd);
    fd = open(FILE_PATH, O_RDONLY);
    if (fd == -1) 
	{
        perror("Error reopening file");
        return EXIT_FAILURE;
    }
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) 
	{
        perror("Error reading from file");
        close(fd);
        return EXIT_FAILURE;
    }
    buffer[bytes_read] = '\0';
    printf("Content read from the file:\n%s", buffer);
    if (close(fd) == -1) 
	{
        perror("Error closing file");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

