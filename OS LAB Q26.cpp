#include <stdio.h>
#include <stdlib.h>
void create_and_write_file(const char *filename, const char *content) 
{
    FILE *file = fopen(filename, "w"); 
    if (file == NULL) 
	{
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", content);
    fclose(file); 
    printf("File '%s' created and content written.\n", filename);
}
void read_file(const char *filename) 
{
    char buffer[1024];
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
	{
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    printf("Reading content of '%s':\n", filename);
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
	{
        printf("%s", buffer);
    }
    fclose(file); 
}
void delete_file(const char *filename) 
{
    if (remove(filename) == 0) 
	{
        printf("File '%s' deleted successfully.\n", filename);
    }
	else 
	{
        perror("Failed to delete file");
        exit(EXIT_FAILURE);
    }
}
int main() 
{
    const char *filename = "test_file.txt";
    const char *content = "Hello, this is a test file.\n";
    create_and_write_file(filename, content); 
    read_file(filename); 
    delete_file(filename); 
    return 0;
}

