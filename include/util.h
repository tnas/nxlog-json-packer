#ifndef UTIL_H
#define UTIL_H

#include <apr_getopt.h>

// The program recognizes just two arguments, i.e., -f <filename>
#define NUM_COMMAND_ARGS 3

void parse_commands(apr_pool_t* memp, int argc, const char* argv[], const char** optarg);

#endif // UTIL_H
