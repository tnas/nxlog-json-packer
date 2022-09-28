#ifndef TXT_H
#define TXT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <apr_file_io.h>
#include <apr_hash.h>
#include <apr_strings.h>

void txt_open_write_file(apr_file_t** txtf, const char* txtfname, apr_pool_t* memp);
void txt_write_txt_file(apr_pool_t* memp, apr_hash_t* dict, apr_file_t* txtf);

#endif // TXT_H
