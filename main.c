#include "include/config.h"

int main()
{
    apr_pool_t* memp;

    char* jsonfname;
    char* txtfname;
    char* tlvfname;

    apr_file_t* jsonf;
    apr_file_t* txtf;
    apr_file_t* tlvf;

    apr_dir_t* json_dir;
    apr_finfo_t finfo;

    // Initializing APR memory pool
    apr_initialize();
    apr_pool_create(&memp, NULL);

    apr_dir_open(&json_dir, JSON_DIR, memp);

    // Scanning directory of JSON files
    while (apr_dir_read(&finfo, APR_FINFO_DIRENT, json_dir) == APR_SUCCESS)
    {
        if (apr_strnatcmp(finfo.name, CURRENT_DIR) == EQUAL_STRINGS ||
            apr_strnatcmp(finfo.name, PARENT_DIR) == EQUAL_STRINGS) continue;

        // Reading JSON file
        jsonf = finfo.filehand;
        jsonfname = apr_pstrcat(memp, JSON_DIR, finfo.name, NULL);
        tlv_open_read_file(&jsonf, jsonfname, memp);
        printf("Parsing file: %s\n", jsonfname);

        // Opening TXT file
        txtfname = apr_pstrcat(memp, TXT_DIR, finfo.name, FTXT_SUFFIX, NULL);
        apr_file_remove(txtfname, memp);
        txt_open_write_file(&txtf, txtfname, memp);

        // Opening TLV file
        tlvfname = apr_pstrcat(memp, TLV_DIR, finfo.name, FTLV_SUFFIX, NULL);
        apr_file_remove(tlvfname, memp);
        tlv_open_write_bfile(&tlvf, tlvfname, memp);

        // Parsing JSON file and saving into TXT and TLV files
        json_parser_file(memp, &jsonf, &txtf, &tlvf);

        // Closing files
        apr_file_close(jsonf);
        apr_file_close(txtf);
        apr_file_close(tlvf);
    }

    apr_pool_destroy(memp);
    apr_terminate();

    return 0;
}
