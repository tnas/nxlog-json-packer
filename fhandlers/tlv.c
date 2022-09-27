#include "../include/tlv.h"

void tlv_open_read_file(apr_file_t** jsonf, const char* jsonfname, apr_pool_t* memp)
{
    if (apr_file_open(jsonf, jsonfname, APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, memp) != APR_SUCCESS)
    {
        printf("Error: Could not open file %s\n", jsonfname);
        exit(-1);
    }
}

void tlv_parse_kvp_list(apr_array_header_t** kvp_list)
{
    tlv_t** tlv_item = NULL;

    while ((tlv_item = (tlv_t **) apr_array_pop(*kvp_list)) != NULL)
    {
        switch ((*tlv_item)->type)
        {
            case INTEGER:
                printf("Integer: %d\n", *(uint32_t *) (*tlv_item)->value);
                break;
            case STRING:
                printf("String: %s\n", (char *) (*tlv_item)->value);
                break;
            case BOOLEAN:
                printf("Boolean: %d\n", *(uint8_t *) (*tlv_item)->value);
                break;
            default:
                printf("Json mapped type not supported: %d\n", (*tlv_item)->type);
                exit(-1);
        }
    }
}
