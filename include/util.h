#ifndef UTIL_H
#define UTIL_H

#include <apr_getopt.h>
#include <apr_strings.h>

// The program recognizes just two arguments, i.e., -f <filename>
#define NUM_COMMAND_ARGS 3

// Value returned by APR when comparing two equal strings
#define EQUAL_STRINGS 0

#define CURRENT_DIR "."
#define PARENT_DIR ".."

void parse_commands(apr_pool_t* memp, int argc, const char* argv[], const char** optarg);
int is_parseable_file(const char* fname);

#endif // UTIL_H
