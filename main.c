#include "include/config.h"

int main(int argc, const char *argv[])
{
    const char* optarg;
    apr_pool_t* memp;
    apr_dir_t* json_dir;
    apr_finfo_t finfo;

    // Initializing APR memory pool
    apr_initialize();
    apr_pool_create(&memp, NULL);

    // Parsing command arguments
    if (argc >= NUM_COMMAND_ARGS)
    {
        parse_commands(memp, argc, argv, &optarg);
        printf("Argument: %s\n", optarg);
    }

    if (optarg)
    {
        json_parser(memp, optarg, FULL_PATH_FNAME);
    }
    else
    {
        // Preparing input/outputs directories
        apr_dir_open(&json_dir, JSON_DIR, memp);
        apr_dir_make(TXT_DIR, APR_FPROT_OS_DEFAULT, memp);
        apr_dir_make(TLV_DIR, APR_FPROT_OS_DEFAULT, memp);

        // Scanning directory of JSON files
        while (apr_dir_read(&finfo, APR_FINFO_DIRENT, json_dir) == APR_SUCCESS)
        {
            if (apr_strnatcmp(finfo.name, CURRENT_DIR) == EQUAL_STRINGS ||
                apr_strnatcmp(finfo.name, PARENT_DIR) == EQUAL_STRINGS) continue;

                json_parser(memp, finfo.name, SIMPLE_FNAME);
        }
    }

    apr_pool_destroy(memp);
    apr_terminate();

    return 0;
}
