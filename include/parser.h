#ifndef PARSER_H
#define PARSER_H

#include "../cjson/cJSON.h"
#include "../include/tlv.h"
#include "../include/txt.h"
#include <apr_file_io.h>
#include <apr_hash.h>

// Directory from which JSON files are read
#define JSON_DIR "json-input/"

// Directory in which TXT files are written
#define TXT_DIR "txt-output/"

// Directory in which TLV files are written
#define TLV_DIR "tlv-output/"

// Suffix added to the TXT files
#define FTXT_SUFFIX "_txt"

// Suffix added to the TLV files
#define FTLV_SUFFIX "_tlv"

#define DEFAULT_TXT_FNAME "output.txt"
#define DEFAULT_TLV_FNAME "output.tlv"

// 128K of cache L1d
#define BUFFER_FILE_SIZE 131072

// APR Dynamic array initial size
#define INITIAL_ARRAY_SIZE 50

typedef enum {
    FULL_PATH_FNAME,
    SIMPLE_FNAME
} fpath_t;

void json_parser(apr_pool_t* memp, const char* jsonfname, fpath_t tpath);
void json_parser_file(apr_pool_t* memp, apr_file_t** jsonf, apr_file_t** txtf, apr_file_t** tlvf);
void json_parser_line(apr_pool_t* memp, cJSON* json_line, tlv_box_t** box, apr_hash_t** dict);

#endif // PARSER_H
