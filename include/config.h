#ifndef CONFIG_H
#define CONFIG_H

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

// Value returned by APR when comparing two equal strings
#define EQUAL_STRINGS 0

#define CURRENT_DIR "."
#define PARENT_DIR ".."

#include <stdio.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include "parser.h"

#endif // CONFIG_H
