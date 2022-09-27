#include "../include/txt.h"

void txt_write_open(apr_pool_t* memp, apr_hash_t* dict, apr_file_t* txtf)
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
