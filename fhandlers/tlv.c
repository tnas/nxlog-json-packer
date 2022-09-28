#include "../include/tlv.h"

void tlv_open_read_file(apr_file_t** jsonf, const char* jsonfname, apr_pool_t* memp)
{
    if (apr_file_open(jsonf, jsonfname, APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not open file %s\n", jsonfname);
        exit(-1);
    }
}

void tlv_open_write_bfile(apr_file_t** tlvf, const char* tlvfname, apr_pool_t* memp)
{
    if (apr_file_open(tlvf, tlvfname, APR_FOPEN_CREATE | APR_FOPEN_BINARY |
        APR_FOPEN_WRITE | APR_FOPEN_APPEND, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not create|open file %s\n", tlvfname);
        exit(-1);
    }
}

void tlv_box_add_object(apr_pool_t* memp, tlv_box_t** box, unsigned char tag, uint32_t len, void* value)
{
    tlv_t* tlv = apr_palloc(memp, sizeof(tlv_t));
    tlv->tag = tag;
    tlv->length = len;
    tlv->value = value;

    (*box)->buff_len += len;
    *(tlv_t **) apr_array_push((*box)->entries) = tlv;
}

void tlv_box_add_string(apr_pool_t* memp, tlv_box_t** box, void* value)
{
    tlv_box_add_object(memp, box, TAG_STRING, TLV_STRING_TAG_LEN_SIZE + strlen(value),
        apr_pstrdup(memp, value));
}

void tlv_box_add_integer(apr_pool_t* memp, tlv_box_t** box, uint32_t value)
{
    uint32_t* m_val = apr_palloc(memp, sizeof(uint32_t));
    *m_val = value;
    tlv_box_add_object(memp, box, TAG_INTEGER, TLV_INTEGER_SIZE, m_val);
}

void tlv_box_add_boolean(apr_pool_t* memp, tlv_box_t** box, bool_t value)
{
    uint8_t* m_val = apr_palloc(memp, sizeof(uint8_t));
    *m_val = value;
    tlv_box_add_object(memp, box, TAG_BOOLEAN, TLV_BOOLEAN_SIZE, m_val);
}

/**
 * The box's dynamic array is traversed according to a first-in, last-out policy.
 * As it is built on key-value pairs, there is an even number of items.
 * So, it is safe to call the pop function twice.
 */
void tlv_box_parse_kvp(apr_pool_t* memp, tlv_box_t** box)
{
    tlv_t** tlv_val = NULL;
//    tlv_t** tlv_key = NULL;

    unsigned int length_size = 0;
    unsigned int offset = 0;
    (*box)->buffer = apr_palloc(memp, (*box)->buff_len);

    while ((tlv_val = (tlv_t **) apr_array_pop((*box)->entries)) != NULL)
    {
//        tlv_key = (tlv_t **) apr_array_pop((*box)->entries);

        memcpy((*box)->buffer, &((*tlv_val)->tag), TLV_TAG_SIZE);
        offset += TLV_TAG_SIZE;

        length_size = (*tlv_val)->tag == TAG_BOOLEAN ? BYTES_UINT8 : BYTES_UINT32;

        memcpy((*box)->buffer + offset, &((*tlv_val)->length), length_size);
        offset += length_size;

        memcpy((*box)->buffer + offset, (*tlv_val)->value, (*tlv_val)->length);
    }
}

void tlv_write_bin_file(tlv_box_t* box, apr_file_t* tlvf)
{
//    printf("--->>box-buffer-size: %d\n", box->buff_len);
    apr_file_write(tlvf, box->buffer, &(box->buff_len));
}
