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
    char* tlvfname = "tlv-output/input01.tlv";
    char line[BUFFER_FILE_SIZE];

    apr_pool_t* memp;
    apr_file_t* jsonf;
    apr_file_t* txtf;
    apr_file_t* tlvf;

    apr_initialize();
    apr_pool_create(&memp, NULL);

    txt_open_write_file(&txtf, txtfname, memp);
    tlv_open_read_file(&jsonf, jsonfname, memp);
    tlv_open_write_bfile(&tlvf, tlvfname, memp);

    cJSON* json_line;
    cJSON* kvp;
    int key_map;

    while (apr_file_gets(line, sizeof(line), jsonf) == APR_SUCCESS)
    {
        printf("%s\n", line);

        json_line = cJSON_Parse(line);
        key_map = 1;

        // Dictionary for string-integer pairs
        apr_hash_t* dict = apr_hash_make(memp);

        // KVP box list for binary TLV
        tlv_box_t* box = apr_palloc(memp, sizeof(tlv_box_t));
        box->entries = apr_array_make(memp, INITIAL_ARRAY_SIZE, sizeof(tlv_t));

        cJSON_ArrayForEach(kvp, json_line)
        {
            uint32_t* kmap = apr_palloc(memp, sizeof(uint32_t));
            *kmap = key_map++;
            apr_hash_set(dict, kvp->string, APR_HASH_KEY_STRING, kmap);

            // Adding KVP-key to box
            tlv_box_add_integer(memp, &box, *kmap);

            // Adding KVP-value to box
            if (cJSON_IsString(kvp))
            {
                tlv_box_add_string(memp, &box, kvp->valuestring);
            }
            else if (cJSON_IsNumber(kvp))
            {
                tlv_box_add_integer(memp, &box, kvp->valuedouble);
            }
            else if (cJSON_IsBool(kvp))
            {
                tlv_box_add_boolean(memp, &box, cJSON_IsFalse(kvp) ? BOOL_FALSE : BOOL_TRUE);
            }
            else
            {
                printf("JSON type not supported");
                exit(-1);
            }
        }

        tlv_box_parse(&(box->entries));
        txt_write_hash_file(memp, dict, txtf);

        cJSON_Delete(json_line);
    }

    apr_pool_destroy(memp);
    apr_file_close(jsonf);
    apr_file_close(txtf);
    apr_file_close(tlvf);
    apr_terminate();

    return 0;
}
