#ifndef TLV_H
#define TLV_H

#include <apr_hash.h>

#define BOOLEAN_TYPE 0x01

typedef struct {
    int type;
    int length;
    unsigned char* value;
} tlv_t;

void tlv_parse_dictionary(apr_pool_t* memp, apr_hash_t* dict);

#endif // TLV_H
