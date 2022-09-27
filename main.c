#include <stdio.h>
#include <stdlib.h>

#include <apr_general.h>
#include <apr_file_io.h>

#include "cjson/cJSON.h"
#include "include/tlv.h"
#include "include/txt.h"

// 128K of cache L1d
#define BUFFER_FILE_SIZE 131072

int main()
{
    char* jsonfname = "json-input/input01.json";
    char* txtfname = "txt-output/input01.txt";
    char line[BUFFER_FILE_SIZE];

    apr_pool_t* memp;
    apr_file_t* jsonf;
    apr_file_t* txtf;

    apr_initialize();
    apr_pool_create(&memp, NULL);

    if (apr_file_open(&txtf, txtfname, APR_FOPEN_CREATE | APR_FOPEN_WRITE | APR_FOPEN_APPEND, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not create|open file %s\n", txtfname);
        exit(-1);
    }

    if (apr_file_open(&jsonf, jsonfname, APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not open file %s\n", jsonfname);
        exit(-1);
    }

    apr_hash_t* dict = apr_hash_make(memp);
    cJSON* json_line;
    cJSON* kvp;
//    apr_ssize_t klen;
    int key_map;

    while (apr_file_gets(line, sizeof(line), jsonf) == APR_SUCCESS)
    {
        apr_hash_t* kmapper = apr_hash_make(memp);
        printf("%s\n", line);
        json_line = cJSON_Parse(line);
        key_map = 1;

        cJSON_ArrayForEach(kvp, json_line)
        {
            uint32_t* kmap = apr_palloc(memp, sizeof(uint32_t));
            *kmap = key_map;
            apr_hash_set(kmapper, kvp->string, APR_HASH_KEY_STRING, kmap);
//
//            char* key_str = apr_itoa(memp, key_map);
//            char* val_str = NULL;
//
//            if (cJSON_IsString(kvp))
//            {
//                val_str = apr_pstrdup(memp, kvp->valuestring);
//                apr_hash_set(dict, key_str, APR_HASH_KEY_STRING, val_str);
//            }
//            else if (cJSON_IsNumber(kvp))
//            {
//                val_str = apr_itoa(memp, kvp->valuedouble);
//            }
//            else if (cJSON_IsBool(kvp))
//            {
//                val_str = cJSON_IsFalse(kvp) ? apr_pstrdup(memp, "FALSE") :
//                    apr_pstrdup(memp, "TRUE");
//            }
//            else
//            {
//                printf("JSON type not supported");
//                exit(-1);
//            }
//
//            apr_hash_set(dict, key_str, APR_HASH_KEY_STRING, val_str);
            ++key_map;
        }

        txt_write_open(memp, kmapper, txtf);
//        tlv_parse_dictionary(memp, dict);

        cJSON_Delete(json_line);
        apr_hash_clear(dict);
        apr_hash_clear(kmapper);
    }

    apr_pool_destroy(memp);
    apr_file_close(jsonf);
    apr_file_close(txtf);
    apr_terminate();

    return 0;
}
