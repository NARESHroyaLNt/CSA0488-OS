#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id; 
    char data[256]; 
} Record;
void writeRecords(const char* filename, Record* records, int numRecords) {
    FILE* file = fopen(filename, "wb"); 
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < numRecords; i++) {
        fwrite(&records[i], sizeof(Record), 1, file);
    }

    fclose(file);
}
void readRecord(const char* filename, int recordId) {
    FILE* file = fopen(filename, "rb"); 
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    Record record;
    int found = 0;
    while (fread(&record, sizeof(Record), 1, file)) {
        if (record.id == recordId) {
            printf("Record ID: %d, Data: %s\n", record.id, record.data);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Record with ID %d not found.\n", recordId);
    }
    fclose(file);
}
int main() {
    Record records[] = {
        {1, "First record"},
        {2, "Second record"},
        {3, "Third record"}
    };
    int numRecords = sizeof(records) / sizeof(records[0]);
    const char* filename = "records.bin";
    writeRecords(filename, records, numRecords);
    int recordId;
    printf("Enter record ID to read: ");
    scanf("%d", &recordId);
    readRecord(filename, recordId);
    return 0;
}

