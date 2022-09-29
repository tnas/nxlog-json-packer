#include "../include/util.h"

static const apr_getopt_option_t opt_option[] =
{
    // long-option, short-option, has-arg flag, description
    { "file", 'f', TRUE, "JSON input file" }, // -f name or --file name
    { NULL, 0, 0, NULL }, // end (a.k.a. sentinel)
};

void parse_commands(apr_pool_t* memp, int argc, const char* argv[], const char** optarg)
{
    apr_getopt_t* opt;
    int optch;

    // Initializing command argument parsing
    apr_getopt_init(&opt, memp, argc, argv);

    if (apr_getopt_long(opt, opt_option, &optch, optarg) == APR_SUCCESS)
    {
        switch (optch)
        {
        case 'f':
            break;
        }
    }
}
