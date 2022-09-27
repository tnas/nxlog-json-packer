#ifndef TLV_H
#define TLV_H

#include <stdlib.h>
#include <apr_file_io.h>
#include <apr_hash.h>

#define BOOLEAN_TYPE 0x01

typedef enum {
    INTEGER,
    STRING,
    BOOLEAN
} json_t;

typedef struct {
    json_t type;
    uint32_t length;
    void* value;
} tlv_t;


void tlv_open_read_file(apr_file_t** jsonf, const char* jsonfname, apr_pool_t* memp);
void tlv_parse_kvp_list(apr_array_header_t** kvp_list);
void tlv_parse_dictionary(apr_pool_t* memp, apr_hash_t* dict);

#endif // TLV_H
