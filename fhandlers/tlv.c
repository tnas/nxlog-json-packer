#include "../include/tlv.h"


void tlv_parse_dictionary(apr_pool_t* memp, apr_hash_t* dict)
{
    apr_hash_index_t* hi;

    void* val;
    for (hi = apr_hash_first(memp, dict); hi; hi = apr_hash_next(hi))
    {
        apr_hash_this(hi, NULL, NULL, &val);

//        printf("Iterated value: %s\n", (char *)val);
    }
}
