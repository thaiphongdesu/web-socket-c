#include <stdio.h>
#include <stdarg.h>
#include "log.h"

void log_message(const char *func, const char *msg, ...) {
    printf("[%s] ", func);
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
}