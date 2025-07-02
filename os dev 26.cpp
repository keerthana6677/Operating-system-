#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[100];

    // 1. Create & write to file
    fp = fopen("file_demo.txt", "w");
    if(fp == NULL) {
        perror("File creation failed");
        exit(1);
    }
    fprintf(fp, "Hello! This is a demo file.\n");
    fprintf(fp, "File management in C.\n");
    fclose(fp);
    printf("File created and data written successfully.\n");

    // 2. Read from file
    fp = fopen("file_demo.txt", "r");
    if(fp == NULL) {
        perror("File open failed");
        exit(1);
    }
    printf("\nContents of file:\n");
    while(fgets(buffer, sizeof(buffer), fp) != NULL)
        printf("%s", buffer);
    fclose(fp);

    // 3. Append data to file
    fp = fopen("file_demo.txt", "a");
    if(fp == NULL) {
        perror("File open failed for append");
        exit(1);
    }
    fputs("Appending this new line.\n", fp);
    fclose(fp);
    printf("\nData appended to file.\n");

    // 4. Read again to see changes
    fp = fopen("file_demo.txt", "r");
    printf("\nUpdated contents of file:\n");
    while(fgets(buffer, sizeof(buffer), fp) != NULL)
        printf("%s", buffer);
    fclose(fp);

    // 5. Delete the file
    if(remove("file_demo.txt") == 0)
        printf("\nFile deleted successfully.\n");
    else
        perror("File deletion failed");

    return 0;
}
