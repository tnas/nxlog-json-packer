#ifndef PARSER_H
#define PARSER_H

#include "../cjson/cJSON.h"
#include "../include/tlv.h"
#include "../include/txt.h"

#include <apr_file_io.h>
#include <apr_hash.h>

// 128K of cache L1d
#define BUFFER_FILE_SIZE 131072

// APR Dynamic array initial size
#define INITIAL_ARRAY_SIZE 50

void json_parser_file(apr_pool_t* memp, apr_file_t** jsonf, apr_file_t** txtf, apr_file_t** tlvf);
void json_parser_line(apr_pool_t* memp, cJSON* json_line, tlv_box_t** box, apr_hash_t** dict);

#endif // PARSER_H
