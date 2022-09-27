#ifndef TXT_H
#define TXT_H

#include <stdio.h>
#include <string.h>

#include <apr_file_io.h>
#include <apr_hash.h>
#include <apr_strings.h>

void txt_write_open(apr_pool_t* memp, apr_hash_t* dict, apr_file_t* txtf);

#endif // TXT_H
