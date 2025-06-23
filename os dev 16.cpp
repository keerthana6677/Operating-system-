#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[20];
    float salary;
};

void addEmployee(FILE *fp) {
    struct Employee e;
    printf("Enter ID, Name, Salary: ");
    scanf("%d %s %f", &e.id, e.name, &e.salary);

    fseek(fp, (e.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&e, sizeof(struct Employee), 1, fp);
    printf("Employee record added.\n");
}

void displayAll(FILE *fp) {
    struct Employee e;
    rewind(fp);
    printf("\nEmployee Records:\n");
    while (fread(&e, sizeof(struct Employee), 1, fp)) {
        if (e.id != 0)
            printf("ID: %d, Name: %s, Salary: %.2f\n", e.id, e.name, e.salary);
    }
}

void searchEmployee(FILE *fp, int id) {
    struct Employee e;
    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&e, sizeof(struct Employee), 1, fp)) {
        if (e.id != 0)
            printf("Found - ID: %d, Name: %s, Salary: %.2f\n", e.id, e.name, e.salary);
        else
            printf("No record found.\n");
    } else {
        printf("Error reading file.\n");
    }
}

int main() {
    FILE *fp;
    fp = fopen("employees.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employees.dat", "wb+"); // Create if not exists
    }

    int choice, id;

    while (1) {
        printf("\n1. Add Employee\n2. Display All\n3. Search by ID\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addEmployee(fp); break;
            case 2: displayAll(fp); break;
            case 3:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                searchEmployee(fp, id);
                break;
            case 4:
                fclose(fp);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

