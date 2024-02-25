#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
void search_in_file(const char *filename, const char *pattern) 
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int found = 0;
    file = fopen(filename, "r");
    if (file == NULL) 
	{
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) 
	{
        line_number++;
        if (strstr(line, pattern) != NULL) 
		{
            printf("%s:%d:%s", filename, line_number, line);
            found = 1;
        }
    }
    if (!found) 
	{
        printf("No match found for '%s' in %s\n", pattern, filename);
    }
    fclose(file);
}
int main(int argc, char *argv[]) 
{
    if (argc < 3) 
	{
        fprintf(stderr, "Usage: %s <pattern> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    search_in_file(argv[2], argv[1]);
    return 0;
}

