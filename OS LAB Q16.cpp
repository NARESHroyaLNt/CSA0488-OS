#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id;
    char name[30];
    float salary;
} Employee;
void createEmployee(FILE *fp, Employee emp) {
    fseek(fp, (emp.id - 1) * sizeof(Employee), SEEK_SET);
    fwrite(&emp, sizeof(Employee), 1, fp);
    printf("Employee with ID %d created successfully.\n", emp.id);
}
void readEmployee(FILE *fp, int id) {
    Employee emp;
    fseek(fp, (id - 1) * sizeof(Employee), SEEK_SET);
    fread(&emp, sizeof(Employee), 1, fp);
    if (emp.id != 0)
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    else
        printf("Employee with ID %d not found.\n", id);
}
void updateEmployee(FILE *fp, int id, Employee newDetails) {
    Employee emp;
    fseek(fp, (id - 1) * sizeof(Employee), SEEK_SET);
    fread(&emp, sizeof(Employee), 1, fp);

    if (emp.id != 0) {
        fseek(fp, (id - 1) * sizeof(Employee), SEEK_SET);
        fwrite(&newDetails, sizeof(Employee), 1, fp);
        printf("Employee with ID %d updated successfully.\n", id);
    } else {
        printf("Employee with ID %d not found for update.\n", id);
    }
}
void deleteEmployee(FILE *fp, int id) {
    Employee emp = {0, "", 0.0};
    fseek(fp, (id - 1) * sizeof(Employee), SEEK_SET);
    fwrite(&emp, sizeof(Employee), 1, fp);
    printf("Employee with ID %d deleted successfully.\n", id);
}
int main() {
    FILE *fp = fopen("employees.dat", "r+b");
    if (fp == NULL) {
        fp = fopen("employees.dat", "w+b"); 
        if (fp == NULL) {
            perror("Cannot open file");
            return EXIT_FAILURE;
        }
    }
    Employee emp1 = {1, "John Doe", 50000};
    Employee emp2 = {2, "Jane Doe", 60000};
    createEmployee(fp, emp1);
    createEmployee(fp, emp2);
    printf("\nReading employee details:\n");
    readEmployee(fp, 1);
    readEmployee(fp, 2);
    Employee updatedEmp = {2, "Jane Smith", 65000};
    updateEmployee(fp, 2, updatedEmp);
    printf("\nReading updated employee details:\n");
    readEmployee(fp, 2);
    deleteEmployee(fp, 1);
    printf("\nAttempting to read deleted employee details:\n");
    readEmployee(fp, 1);
    fclose(fp);
    return 0;
}

