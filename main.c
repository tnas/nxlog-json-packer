#include <stdio.h>
#include <stdlib.h>
#include <apr_general.h>
#include <apr_file_io.h>

int main()
{
    apr_status_t rv;
    apr_pool_t* memp;
    apr_file_t* jsonf;
    char line[1024];

    const char* fname = "json-input/input01.json";

    apr_initialize();
    apr_pool_create(&memp, NULL);

    if (apr_file_open(&jsonf, fname, APR_READ, APR_OS_DEFAULT, memp) != APR_SUCCESS) {
        printf("Error: Could not open file %s\n", fname);
        exit(-1);
    }

    while (apr_file_gets(line, sizeof(line), jsonf) == APR_SUCCESS) {
        printf("%s\n", line);
    }

    apr_file_close(jsonf);
    apr_terminate();

    return 0;
}
