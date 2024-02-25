#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 25
typedef struct {
    char filename[MAX_FILENAME_LENGTH];
} File;
typedef struct {
    File files[MAX_FILES];
    int fileCount;
} Directory;
void initializeDirectory(Directory* directory) 
{
    directory->fileCount = 0;
}
void createFile(Directory* directory, const char* filename) 
{
    if (directory->fileCount < MAX_FILES) 
	{
        strcpy(directory->files[directory->fileCount].filename, filename);
        directory->fileCount++;
        printf("File '%s' created successfully.\n", filename);
    } else {
        printf("Directory is full, cannot create more files.\n");
    }
}
void deleteFile(Directory* directory, const char* filename) 
{
    for (int i = 0; i < directory->fileCount; i++) 
	{
        if (strcmp(directory->files[i].filename, filename) == 0) 
		{
            for (int j = i; j < directory->fileCount - 1; j++) 
			{
                strcpy(directory->files[j].filename, directory->files[j + 1].filename);
            }
            directory->fileCount--;
            printf("File '%s' deleted successfully.\n", filename);
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}
void searchFile(const Directory* directory, const char* filename) 
{
    for (int i = 0; i < directory->fileCount; i++) 
	{
        if (strcmp(directory->files[i].filename, filename) == 0) 
		{
            printf("File '%s' found.\n", filename);
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}
void listFiles(const Directory* directory) 
{
    if (directory->fileCount == 0) 
	{
        printf("Directory is empty.\n");
    } 
	else 
	{
        printf("Files in directory:\n");
        for (int i = 0; i < directory->fileCount; i++) 
		{
            printf("%d: %s\n", i + 1, directory->files[i].filename);
        }
    }
}
int main() 
{
    Directory dir;
    initializeDirectory(&dir);
    int choice;
    char filename[MAX_FILENAME_LENGTH];
    while (1) 
	{
        printf("\n1. Create File\n2. Delete File\n3. Search File\n4. List Files\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) 
		{
            case 1:
                printf("Enter filename to create: ");
                scanf("%s", filename);
                createFile(&dir, filename);
                break;
            case 2:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(&dir, filename);
                break;
            case 3:
                printf("Enter filename to search: ");
                scanf("%s", filename);
                searchFile(&dir, filename);
                break;
            case 4:
                listFiles(&dir);
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

