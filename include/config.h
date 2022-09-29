#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include "util.h"
#include "parser.h"

// Value returned by APR when comparing two equal strings
#define EQUAL_STRINGS 0

#define CURRENT_DIR "."
#define PARENT_DIR ".."

#endif // CONFIG_H
