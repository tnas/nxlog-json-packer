#include "../include/config.h"

static char* jsonfname = "tests/input01.json";
static char* txtfname = "txt-output/input01.txt";
static char* tlvfname = "tlv-output/input01.tlv";

void check_txt_parsed_file(apr_pool_t* memp)
{
    apr_file_t* txtf;

    if (apr_file_open(&txtf, txtfname, APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not open file %s\n", txtfname);
        exit(-1);
    }

    char line[BUFFER_FILE_SIZE];

    char expected[2][BUFFER_FILE_SIZE] = {
        "key1:1,key2:2,key3:3,\n",
        "dsre:2,sadsf:1,sdfds:3,\n"
    };
    const char* sep = ",";

    unsigned int nline = 0;
    while (apr_file_gets(line, sizeof(line), txtf) == APR_SUCCESS)
    {

        if (strlen(expected[nline]) != strlen(line))
        {
            apr_file_close(txtf);
            printf("Failure! Expected: line <%s> of size %ld, but was: <%s> of size %ld\n",
                expected[nline], strlen(expected[nline]), line, strlen(line));
            exit(-1);
        }

        ++nline;
    }

    apr_file_close(txtf);
}

int main()
{
    apr_pool_t* memp;

    apr_file_t* jsonf;
    apr_file_t* txtf;
    apr_file_t* tlvf;

    apr_initialize();
    apr_pool_create(&memp, NULL);

    apr_file_remove(txtfname, memp);
    txt_open_read_file(&jsonf, jsonfname, memp);
    txt_open_write_file(&txtf, txtfname, memp);
    tlv_open_write_bfile(&tlvf, tlvfname, memp);

    json_parser_file(memp, &jsonf, &txtf, &tlvf);
    check_txt_parsed_file(memp);

    apr_file_close(jsonf);
    apr_file_close(txtf);
    apr_file_close(tlvf);

    apr_pool_destroy(memp);
    apr_terminate();

    return 0;
}
