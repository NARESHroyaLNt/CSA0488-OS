#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BLOCKS 10
#define BLOCK_SIZE 256
typedef struct {
    char data[BLOCK_SIZE];
} DataBlock;
typedef struct {
    DataBlock* blocks[MAX_BLOCKS]; 
    int numBlocks; 
} IndexedFile;
void initIndexedFile(IndexedFile* file) {
    file->numBlocks = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        file->blocks[i] = NULL;
    }
}
int addBlock(IndexedFile* file, const char* data) {
    if (file->numBlocks >= MAX_BLOCKS) {
        printf("Error: Maximum number of blocks reached.\n");
        return -1;
    }
    DataBlock* newBlock = (DataBlock*)malloc(sizeof(DataBlock));
    if (newBlock == NULL) {
        printf("Memory allocation error.\n");
        return -1;
    }
    strncpy(newBlock->data, data, BLOCK_SIZE);
    file->blocks[file->numBlocks++] = newBlock;
    return file->numBlocks - 1; 
}
void readBlock(IndexedFile* file, int blockIndex) {
    if (blockIndex < 0 || blockIndex >= file->numBlocks) {
        printf("Invalid block index.\n");
        return;
    }
    DataBlock* block = file->blocks[blockIndex];
    if (block != NULL) {
        printf("Data in block %d: %s\n", blockIndex, block->data);
    } else {
        printf("Block %d is empty.\n", blockIndex);
    }
}
void cleanup(IndexedFile* file) {
    for (int i = 0; i < file->numBlocks; i++) {
        if (file->blocks[i] != NULL) {
            free(file->blocks[i]);
            file->blocks[i] = NULL;
        }
    }
}
int main() {
    IndexedFile file;
    initIndexedFile(&file);
    addBlock(&file, "Hello, this is block 0.");
    addBlock(&file, "This is another block, block 1.");
    addBlock(&file, "And this is block 2.");
    readBlock(&file, 0); 
    readBlock(&file, 1);
    readBlock(&file, 2); 
    cleanup(&file);
    return 0;
}

