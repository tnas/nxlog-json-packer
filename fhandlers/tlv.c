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

void tlv_box_add_object(apr_pool_t* memp, tlv_box_t** box, json_t type, uint32_t len, void* value)
{
    tlv_t* tlv = apr_palloc(memp, sizeof(tlv_t));
    tlv->type = type;
    tlv->length = len;
    tlv->value = value;

    (*box)->buff_len += len;
    *(tlv_t **) apr_array_push((*box)->entries) = tlv;
}

void tlv_box_add_string(apr_pool_t* memp, tlv_box_t** box, void* value)
{
    tlv_box_add_object(memp, box, STRING, strlen(value), apr_pstrdup(memp, value));
}

void tlv_box_add_integer(apr_pool_t* memp, tlv_box_t** box, uint32_t value)
{
    uint32_t* m_val = apr_palloc(memp, sizeof(uint32_t));
    *m_val = value;
    tlv_box_add_object(memp, box, INTEGER, sizeof(uint32_t), m_val);
}

void tlv_box_add_boolean(apr_pool_t* memp, tlv_box_t** box, bool_t value)
{
    uint8_t* m_val = apr_palloc(memp, sizeof(uint8_t));
    *m_val = value;
    tlv_box_add_object(memp, box, BOOLEAN, sizeof(uint8_t), m_val);
}

void tlv_box_parse(apr_array_header_t** kvp_list)
{
    tlv_t** tlv_item = NULL;

    while ((tlv_item = (tlv_t **) apr_array_pop(*kvp_list)) != NULL)
    {
        uint32_t length = (uint32_t) (*tlv_item)->length;

        switch ((*tlv_item)->type)
        {
            case INTEGER:
                printf("Integer: %d - sizeof: %u\n", *(uint32_t *) (*tlv_item)->value, length);
                break;
            case STRING:
                printf("String: %s - sizeof: %u\n", (char *) (*tlv_item)->value, length);
                break;
            case BOOLEAN:
                printf("Boolean: %d - sizeof: %u\n", *(uint8_t *) (*tlv_item)->value, length);
                break;
            default:
                printf("Json mapped type not supported: %d\n", (*tlv_item)->type);
                exit(-1);
        }
    }
}
