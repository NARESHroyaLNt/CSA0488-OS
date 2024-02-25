#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRS 10
#define MAX_FILES 50
#define MAX_FILENAME_LENGTH 25
#define MAX_DIRNAME_LENGTH 25

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
} File;

typedef struct {
    char dirname[MAX_DIRNAME_LENGTH];
    File files[MAX_FILES];
    int fileCount;
} Directory;

typedef struct {
    Directory dirs[MAX_DIRS];
    int dirCount;
} TwoLevelDirectory;

void initializeTwoLevelDirectory(TwoLevelDirectory* fs) {
    fs->dirCount = 0;
}

void createDirectory(TwoLevelDirectory* fs, const char* dirname) {
    if (fs->dirCount < MAX_DIRS) {
        strcpy(fs->dirs[fs->dirCount].dirname, dirname);
        fs->dirs[fs->dirCount].fileCount = 0;
        fs->dirCount++;
        printf("Directory '%s' created successfully.\n", dirname);
    } else {
        printf("File system is full, cannot create more directories.\n");
    }
}

void createFile(TwoLevelDirectory* fs, const char* dirname, const char* filename) {
    for (int i = 0; i < fs->dirCount; i++) {
        if (strcmp(fs->dirs[i].dirname, dirname) == 0) {
            if (fs->dirs[i].fileCount < MAX_FILES) {
                strcpy(fs->dirs[i].files[fs->dirs[i].fileCount].filename, filename);
                fs->dirs[i].fileCount++;
                printf("File '%s' created in directory '%s'.\n", filename, dirname);
                return;
            } else {
                printf("Directory is full, cannot create more files in '%s'.\n", dirname);
                return;
            }
        }
    }
    printf("Directory '%s' not found.\n", dirname);
}

void listDirectories(const TwoLevelDirectory* fs) {
    if (fs->dirCount == 0) {
        printf("File system is empty.\n");
    } else {
        printf("Directories in the file system:\n");
        for (int i = 0; i < fs->dirCount; i++) {
            printf("%d: %s\n", i + 1, fs->dirs[i].dirname);
        }
    }
}

void listFilesInDirectory(const TwoLevelDirectory* fs, const char* dirname) {
    for (int i = 0; i < fs->dirCount; i++) {
        if (strcmp(fs->dirs[i].dirname, dirname) == 0) {
            if (fs->dirs[i].fileCount == 0) {
                printf("Directory '%s' is empty.\n", dirname);
            } else {
                printf("Files in directory '%s':\n", dirname);
                for (int j = 0; j < fs->dirs[i].fileCount; j++) {
                    printf("%d: %s\n", j + 1, fs->dirs[i].files[j].filename);
                }
            }
            return;
        }
    }
    printf("Directory '%s' not found.\n", dirname);
}

int main() {
    TwoLevelDirectory fs;
    initializeTwoLevelDirectory(&fs);
    createDirectory(&fs, "Documents");
    createDirectory(&fs, "Music");

    createFile(&fs, "Documents", "Resume.docx");
    createFile(&fs, "Music", "song.mp3");

    listDirectories(&fs);

    printf("\nListing Files in Documents:\n");
    listFilesInDirectory(&fs, "Documents");

    printf("\nListing Files in Music:\n");
    listFilesInDirectory(&fs, "Music");

    return 0;
}

