#ifndef TLV_H
#define TLV_H

#include <stdlib.h>
#include <apr_file_io.h>
#include <apr_hash.h>
#include <apr_strings.h>

#define BYTES_UINT8 1
#define BYTES_UINT32 4

#define TLV_TAG_SIZE 1
#define TLV_BOOLEAN_SIZE 3
#define TLV_INTEGER_SIZE 9
#define TLV_STRING_TAG_LEN_SIZE 5

#define TAG_BOOLEAN 0x01
#define TAG_STRING 0x0C
#define TAG_INTEGER 0x02

typedef enum {
    BOOL_FALSE,
    BOOL_TRUE
} bool_t;

typedef struct {
    unsigned char tag;
    uint32_t length;
    void* value;
} tlv_t;

typedef struct {
    apr_array_header_t* entries;
    unsigned char* buffer;
    apr_size_t buff_len;
} tlv_box_t;

void tlv_open_read_file(apr_file_t** jsonf, const char* jsonfname, apr_pool_t* memp);
void tlv_open_write_bfile(apr_file_t** tlvf, const char* tlvfname, apr_pool_t* memp);
void tlv_box_add_object(apr_pool_t* memp, tlv_box_t** box, unsigned char tag, uint32_t len, void* value);
void tlv_box_add_string(apr_pool_t* memp, tlv_box_t** box, void* value);
void tlv_box_add_integer(apr_pool_t* memp, tlv_box_t** box, uint32_t value);
void tlv_box_add_boolean(apr_pool_t* memp, tlv_box_t** box, bool_t value);
void tlv_box_parse_kvp(apr_pool_t* memp, tlv_box_t** box);
void tlv_write_bin_file(tlv_box_t* box, apr_file_t* tlvf);

#endif // TLV_H
