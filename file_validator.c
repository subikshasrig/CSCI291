/* file_validator.c - CSCI291 Lab 4, Task 3 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE 256
#define MIN_MARK 0
#define MAX_MARK 100

static int valid_name(const char *s)
{
    size_t i, n = strlen(s);
    if (n == 0)
        return 0;
    for (i = 0; i < n; i++) {
        unsigned char c = (unsigned char)s[i];
    if (!isprint(c) || isdigit(c))
        return 0;
}
return 1;

}
static int valid_mark(const char *s, int *out)
{
    size_t i = 0;
    long v;
    if (s[0] == '+' || s[0] == '-')
        i = 1;
    if (s[i] == '\0')
        return 0;
    for (; s[i] != '\0'; i++)
        if (!isdigit((unsigned char)s[i])) /* rejects 67.5, 7a, etc. */
        return 0;
    v = strtol(s, NULL, 10);
    if (v < MIN_MARK || v > MAX_MARK)
        return 0;
    *out = (int)v;
    return 1;
}

int main(void)
{

    FILE *fp = fopen("students.txt", "r");
    char line[MAX_LINE];
    int lineNo = 0, validCount = 0, corruptCount = 0, mark, sum = 0;
    if (fp == NULL) {
        perror("Error opening students.txt");
        return 1;
    }

    printf("=== Valid Records ===\n");
    printf("%-4s %-22s %5s\n", "Line", "Name", "Mark");
    while (fgets(line, sizeof line, fp) != NULL) {
        char *sep, *name, *markStr;
        size_t len;
        int tooLong = (strchr(line, '\n') == NULL && !feof(fp));
        lineNo++;

        if (tooLong) { /* discard rest of long line */
            int ch;

            while ((ch = fgetc(fp)) != '\n' && ch != EOF) {}
                printf(" [skipped] line %d: line too long\n", lineNo);
                corruptCount++;
                continue;
        }

        len = strlen(line); /* trim trailing whitespace */
        while (len > 0 && isspace((unsigned char)line[len - 1]))
            line[--len] = '\0';

        if (len == 0) /* blank line: ignore */
            continue;

        sep = strrchr(line, ' '); /* last space splits name/mark */
        if (sep == NULL) {
            printf(" [skipped] line %d: missing mark -> \"%s\"\n", lineNo, line);
            corruptCount++;
            continue;
        }
        *sep = '\0';
        name = line;
        markStr = sep + 1;

        if (!valid_name(name)) {
            printf(" [skipped] line %d: invalid name\n", lineNo);
            corruptCount++;
        } 
        else if (!valid_mark(markStr, &mark)) {
            printf(" [skipped] line %d: invalid mark \"%s\"\n", lineNo, markStr);
            corruptCount++;
        } 
        else {
            printf("%-4d %-22s %5d\n", lineNo, name, mark);
            sum += mark;
            validCount++;
        }
    }

    fclose(fp);
    printf("\n=== Summary ===\n");
    printf("Valid records : %d\n", validCount);
    printf("Corrupted records : %d\n", corruptCount);

    if (validCount > 0)
        printf("Average mark : %.2f\n", (double)sum / validCount);
    else
        printf("Average mark : N/A (no valid records)\n");
        return 0;
}
