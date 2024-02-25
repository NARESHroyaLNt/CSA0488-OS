#include <stdio.h>
#define MAX_PROCESSES 5
#define RESOURCE_TYPES 
int available[RESOURCE_TYPES]; 
int maximum[MAX_PROCESSES][RESOURCE_TYPES]; 
int allocation[MAX_PROCESSES][RESOURCE_TYPES]; 
int need[MAX_PROCESSES][RESOURCE_TYPES]; 
int checkFinish(int process, int work[], int finish[]) {
    for (int i = 0; i < RESOURCE_TYPES; i++) {
        if (need[process][i] > work[i]) {
            return 0; 
        }
    }

    for (int i = 0; i < RESOURCE_TYPES; i++) {
        work[i] += allocation[process][i];
    }
    finish[process] = 1;

    return 1;
}

int bankersAlgorithm() {
    int work[RESOURCE_TYPES]; 
    int finish[MAX_PROCESSES] = {0}; 

    for (int i = 0; i < RESOURCE_TYPES; i++) {
        work[i] = available[i];
    }

    int done;
    do {
        done = 1;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i] && checkFinish(i, work, finish)) {
                printf("Process %d can finish.\n", i);
                done = 0; 
            }
        }
    } while (!done);

    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (!finish[i]) {
            return 0; 
        }
    }

    return 1; 
}

int main() {
    available[0] = 3; available[1] = 3; available[2] = 2;
    maximum[0][0] = 7; maximum[0][1] = 5; maximum[0][2] = 3;
    maximum[1][0] = 3; maximum[1][1] = 2; maximum[1][2] = 2;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < RESOURCE_TYPES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    if (bankersAlgorithm()) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is in an unsafe state.\n");
    }
    return 0;
}

