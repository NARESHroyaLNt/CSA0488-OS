#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct DiskBlock {
    char data[128]; 
    struct DiskBlock *next; 
} DiskBlock;
typedef struct {
    DiskBlock *firstBlock; 
    DiskBlock *lastBlock;
} File;
File* createFile() {
    File* file = (File*)malloc(sizeof(File));
    if (!file) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    file->firstBlock = file->lastBlock = NULL;
    return file;
}
void addBlock(File *file, const char* data) {
    DiskBlock* newBlock = (DiskBlock*)malloc(sizeof(DiskBlock));
    if (!newBlock) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newBlock->data, data);
    newBlock->next = NULL;

    if (file->firstBlock == NULL) {
        file->firstBlock = file->lastBlock = newBlock;
    } else {
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }
}
void readFile(File *file) {
    DiskBlock *currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        printf("%s ", currentBlock->data);
        currentBlock = currentBlock->next;
    }
    printf("\n");
}
void freeFile(File *file) {
    DiskBlock *currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        DiskBlock *nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }
    free(file);
}
int main() {
    File* file = createFile();
    if (!file) return 1;
    addBlock(file, "Hello,");
    addBlock(file, "world!");
    addBlock(file, "This");
    addBlock(file, "is");
    addBlock(file, "a");
    addBlock(file, "test.");
    printf("File contents: ");
    readFile(file);
    freeFile(file);
    return 0;
}

