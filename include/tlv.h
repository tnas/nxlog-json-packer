#ifndef TLV_H
#define TLV_H

#include <stdlib.h>
#include <apr_file_io.h>
#include <apr_hash.h>
#include <apr_strings.h>

#define BOOLEAN_TYPE 0x01

typedef enum {
    BOOL_FALSE,
    BOOL_TRUE
} bool_t;

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

typedef struct {
    apr_array_header_t* entries;
    unsigned char* buffer;
    uint32_t buff_len;
} tlv_box_t;

void tlv_open_read_file(apr_file_t** jsonf, const char* jsonfname, apr_pool_t* memp);
void tlv_open_write_bfile(apr_file_t** tlvf, const char* tlvfname, apr_pool_t* memp);
void tlv_box_add_object(apr_pool_t* memp, tlv_box_t** box, json_t type, uint32_t len, void* value);
void tlv_box_add_string(apr_pool_t* memp, tlv_box_t** box, void* value);
void tlv_box_add_integer(apr_pool_t* memp, tlv_box_t** box, uint32_t value);
void tlv_box_add_boolean(apr_pool_t* memp, tlv_box_t** box, bool_t value);
void tlv_box_parse(apr_array_header_t** kvp_list);

#endif // TLV_H
