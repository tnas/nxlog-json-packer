#include <stdio.h>
#include <stdlib.h>

#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_hash.h>
#include <apr_strings.h>

#include "cjson/cJSON.h"

// 128K of cache L1d
#define BUFFER_FILE_SIZE 131072

int main()
{
    apr_pool_t* memp;
    apr_file_t* jsonf;
    char line[BUFFER_FILE_SIZE];

    const char* fname = "json-input/input01.json";

    apr_initialize();
    apr_pool_create(&memp, NULL);

    if (apr_file_open(&jsonf, fname, APR_READ, APR_OS_DEFAULT, memp) != APR_SUCCESS) {
        printf("Error: Could not open file %s\n", fname);
        exit(-1);
    }

    cJSON* json_line;
    cJSON* kvp;

    char* current_key;
    apr_hash_t* dict = apr_hash_make(memp);

    while (apr_file_gets(line, sizeof(line), jsonf) == APR_SUCCESS)
    {
        printf("%s\n", line);

        json_line = cJSON_Parse(line);
        int key_map = 1;

        cJSON_ArrayForEach(kvp, json_line)
        {
            char* key_str = apr_itoa(memp, key_map++);
            char* val_str = NULL;

            if (cJSON_IsString(kvp))
            {
                val_str = apr_pstrdup(memp, kvp->valuestring);
            }
            else if (cJSON_IsNumber(kvp))
            {
                val_str = apr_itoa(memp, kvp->valuedouble);
            }
            else if (cJSON_IsBool(kvp))
            {
                val_str = cJSON_IsFalse(kvp) ? apr_pstrdup(memp, "FALSE") :
                    apr_pstrdup(memp, "TRUE");
            }
            else
            {
                printf(stderr, "JSON type not supported");
                exit(-1);
            }

            printf("Key: %s - Int Map: %s - Value: %s\n", kvp->string, key_str, val_str);
            apr_hash_set(dict, key_str, APR_HASH_KEY_STRING, val_str);
        }

        cJSON_Delete(json_line);
    }

    apr_pool_destroy(memp);
    apr_file_close(jsonf);
    apr_terminate();

    return 0;
}
