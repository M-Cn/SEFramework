#ifndef DEBUG_H
#define DEBUG_H

#include "GeneralUtil.h"

#ifdef DEBUG
#define OUTPUT_DEBUG_MSG(msg, ...) printf(msg, ##__VA_ARGS__);
#else
#define OUTPUT_DEBUG_MSG(msg, ...)
#endif

#define TYPE_COL_WIDTH 10

#define PRINT_DEBUG_COLOR(color, type, fmt, ...) \
    do { \
        printf(color); \
        printf("[%s]", type); \
        printf("%*s | ", TYPE_COL_WIDTH - (int)strlen(type), ""); \
        printf(fmt, ##__VA_ARGS__); \
        printf(RESET); \
    } while(0)

#ifdef DEBUG
#define LOG_DEBUG(fmt, ...)   PRINT_DEBUG_COLOR(WHITE, "DEBUG", fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif

#define LOG_INFO(fmt, ...)    PRINT_DEBUG_COLOR(RESET, "INFO", fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) PRINT_DEBUG_COLOR(YELLOW, "WARNING", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   PRINT_DEBUG_COLOR(RED, "ERROR", fmt, ##__VA_ARGS__)

#endif // DEBUG_H