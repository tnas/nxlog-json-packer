#include "../include/txt.h"

void txt_open_read_file(apr_file_t** txtf, const char* txtfname, apr_pool_t* memp)
{
    if (apr_file_open(txtf, txtfname, APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not open file %s\n", txtfname);
        exit(-1);
    }
}

void txt_open_write_file(apr_file_t** txtf, const char* txtfname, apr_pool_t* memp)
{
    if (apr_file_open(txtf, txtfname, APR_FOPEN_CREATE |
        APR_FOPEN_WRITE | APR_FOPEN_APPEND, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not create|open file %s\n", txtfname);
        exit(-1);
    }
}

void txt_write_file(apr_pool_t* memp, apr_hash_t* dict, apr_file_t* txtf)
{
    void* val;
    const void* key;
    char* buff = NULL;
    apr_size_t buffsize;

    for (apr_hash_index_t* hi = apr_hash_first(memp, dict); hi; hi = apr_hash_next(hi))
    {
        apr_hash_this(hi, &key, NULL, &val);
        buff = apr_pstrcat(memp, (char *)key, ":", apr_itoa(memp, *(int *)val), ",", NULL);
        buffsize = strlen(buff);
        apr_file_write(txtf, buff, &buffsize);
    }

    buff = "\n";
    buffsize = strlen(buff);
    apr_file_write(txtf, buff, &buffsize);
}
