#include "../include/parser.h"

void json_parser(apr_pool_t* memp, const char* fname, fpath_t tpath)
{
    apr_file_t* jsonf;
    apr_file_t* txtf;
    apr_file_t* tlvf;

    const char* jsonfname;
    const char* txtfname;
    const char* tlvfname;

    if (tpath == SIMPLE_FNAME)
    {
        jsonfname = apr_pstrcat(memp, JSON_DIR, fname, NULL);
        txtfname = apr_pstrcat(memp, TXT_DIR, fname, FTXT_SUFFIX, NULL);
        tlvfname = apr_pstrcat(memp, TLV_DIR, fname, FTLV_SUFFIX, NULL);
    }
    else // FULL_FNAME
    {
        jsonfname = fname;
        txtfname = DEFAULT_TXT_FNAME;
        tlvfname = DEFAULT_TLV_FNAME;
    }

    // Reading JSON file
    txt_open_read_file(&jsonf, jsonfname, memp);
    printf("Parsing file: %s\n", jsonfname);

    // Opening TXT file
    apr_file_remove(txtfname, memp);
    txt_open_write_file(&txtf, txtfname, memp);

    // Opening TLV file
    apr_file_remove(tlvfname, memp);
    tlv_open_write_bfile(&tlvf, tlvfname, memp);

    // Parsing JSON file and saving into TXT and TLV files
    json_parser_file(memp, &jsonf, &txtf, &tlvf);

    // Closing files
    apr_file_close(jsonf);
    apr_file_close(txtf);
    apr_file_close(tlvf);
}

void json_parser_file(apr_pool_t* memp, apr_file_t** jsonf, apr_file_t** txtf, apr_file_t** tlvf)
{
    char line[BUFFER_FILE_SIZE];
    cJSON* json_line;

    while (apr_file_gets(line, sizeof(line), *jsonf) == APR_SUCCESS)
    {
        json_line = cJSON_Parse(line);

        // Dictionary for string-integer pairs
        apr_hash_t* dict = apr_hash_make(memp);

        // KVP box list for binary TLV
        tlv_box_t* box = apr_palloc(memp, sizeof(tlv_box_t));
        box->entries = apr_array_make(memp, INITIAL_ARRAY_SIZE, sizeof(tlv_t));
        box->buff_len = 0;
        box->offset = 0;

        json_parser_line(memp, json_line, &box, &dict);

        tlv_box_parse_kvp(memp, &box);
        tlv_write_bin_file(box, *tlvf);
        txt_write_file(memp, dict, *txtf);

        cJSON_Delete(json_line);
    }
}

void json_parser_line(apr_pool_t* memp, cJSON* json_line, tlv_box_t** box, apr_hash_t** dict)
{
    cJSON* kvp;
    int key_map = 1;

    cJSON_ArrayForEach(kvp, json_line)
    {
        uint32_t* kmap = apr_palloc(memp, sizeof(uint32_t));
        *kmap = key_map++;
        apr_hash_set(*dict, kvp->string, APR_HASH_KEY_STRING, kmap);

        // Adding KVP-key to box
        tlv_box_add_integer(memp, box, *kmap);

        // Adding KVP-value to box
        if (cJSON_IsString(kvp))
        {
            tlv_box_add_string(memp, box, kvp->valuestring);
        }
        else if (cJSON_IsNumber(kvp))
        {
            tlv_box_add_integer(memp, box, kvp->valuedouble);
        }
        else if (cJSON_IsBool(kvp))
        {
            tlv_box_add_boolean(memp, box, cJSON_IsFalse(kvp) ? BOOL_FALSE : BOOL_TRUE);
        }
        else
        {
            printf("JSON type not supported");
            exit(-1);
        }
    }
}
