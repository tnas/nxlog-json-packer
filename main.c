#include <stdio.h>
#include <apr_general.h>
#include <apr_file_io.h>

#include "cjson/cJSON.h"
#include "include/tlv.h"
#include "include/txt.h"

// 128K of cache L1d
#define BUFFER_FILE_SIZE 131072

#define INITIAL_ARRAY_SIZE 50

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

    txt_open_write_file(&txtf, txtfname, memp);
    tlv_open_read_file(&jsonf, jsonfname, memp);

    cJSON* json_line;
    cJSON* kvp;
    int key_map;

    while (apr_file_gets(line, sizeof(line), jsonf) == APR_SUCCESS)
    {
        printf("%s\n", line);

        apr_array_header_t* tlv_list = apr_array_make(memp, INITIAL_ARRAY_SIZE, sizeof(tlv_t));
        apr_hash_t* dict = apr_hash_make(memp);

        json_line = cJSON_Parse(line);
        key_map = 1;

        cJSON_ArrayForEach(kvp, json_line)
        {
            uint32_t* kmap = apr_palloc(memp, sizeof(uint32_t));
            *kmap = key_map++;
            apr_hash_set(dict, kvp->string, APR_HASH_KEY_STRING, kmap);

            // Adding key to dynamic array
            tlv_t* key_tlv = apr_palloc(memp, sizeof(tlv_t));
            key_tlv->type = INTEGER;
            key_tlv->length = sizeof(uint32_t);
            key_tlv->value = apr_palloc(memp, sizeof(uint32_t));
            *(uint32_t *) key_tlv->value = *kmap;
            *(tlv_t **) apr_array_push(tlv_list) = key_tlv;

            // Adding value to dynamic array
            tlv_t* val_tlv = apr_palloc(memp, sizeof(tlv_t));

            if (cJSON_IsString(kvp))
            {
                val_tlv->type = STRING;
                val_tlv->length = strlen(kvp->valuestring);
                val_tlv->value = apr_pstrdup(memp, kvp->valuestring);
            }
            else if (cJSON_IsNumber(kvp))
            {
                val_tlv->type = INTEGER;
                val_tlv->length = sizeof(uint32_t);
                val_tlv->value = apr_palloc(memp, sizeof(uint32_t));
                *(uint32_t *) val_tlv->value = kvp->valuedouble;
            }
            else if (cJSON_IsBool(kvp))
            {
                val_tlv->type = BOOLEAN;
                val_tlv->length = sizeof(uint32_t);
                val_tlv->value = apr_palloc(memp, sizeof(uint8_t));
                *(uint8_t *) val_tlv->value = cJSON_IsFalse(kvp) ? 0 : 1;
            }
            else
            {
                printf("JSON type not supported");
                exit(-1);
            }

            *(tlv_t **) apr_array_push(tlv_list) = val_tlv;
        }

        tlv_parse_kvp_list(&tlv_list);
        txt_write_hash_file(memp, dict, txtf);

        cJSON_Delete(json_line);
    }

    apr_pool_destroy(memp);
    apr_file_close(jsonf);
    apr_file_close(txtf);
    apr_terminate();

    return 0;
}
