#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* jsonf;
    char* line;
    size_t len = 0;

    char* filenm = "json-input/input01.json";

    jsonf = fopen(filenm, "r");

    if (jsonf == NULL)
    {
        printf("Error: Could not open file %s\n", filenm);
        exit(-1);
    }

    while (getline(&line, &len, jsonf) != -1)
    {
        printf("%s\n", line);
    }

    fclose(jsonf);

    if (line)
    {
        free(line);
    }

    return 0;
}
