#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char filename[100], pattern[100], line[500];

    printf("Enter filename: ");
    scanf("%s", filename);

    printf("Enter pattern to search: ");
    scanf("%s", pattern);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Unable to open file");
        return 1;
    }

    printf("\nLines containing pattern \"%s\":\n", pattern);
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
