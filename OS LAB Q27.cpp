#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
void list_directory_contents(const char *path) 
{
    struct dirent *entry;
    DIR *dp;
    dp = opendir(path);
    if (dp == NULL) 
	{
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while ((entry = readdir(dp)) != NULL) 
	{
        if (entry->d_name[0] == '.') 
		{
            continue;
        }
        printf("%s\n", entry->d_name); 
    }
    closedir(dp);
}
int main(int argc, char **argv) 
{
    const char *path = ".";
    if (argc > 1) 
	{
        path = argv[1];
    }
    list_directory_contents(path);
    return 0;
}

