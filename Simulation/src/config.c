/*
 * File name: config.c
 * Description: Configuration file for running processor
 *
 * Notes:
 *
 */

#include <stdio.h>
#include <stdarg.h>

#include "../include/config.h"

int current_debug_level = DEBUG_LEVEL_0;

void
debug_printf(int debug_level, const char *format, ...)
{
    if(debug_level <= current_debug_level)
    {
        va_list args;
        va_start(args, format);

        vprintf(format, args);
        printf("\n");

        va_end(args);
    }
}

/* End of file: config.c */
