#ifndef DEBUG_H
#define DEBUG_H

#include <cstring>

#include "GeneralUtil.h"

#ifdef DEBUG
#define OUTPUT_DEBUG_MSG(msg, ...) printf(msg, ##__VA_ARGS__);
#else
#define OUTPUT_DEBUG_MSG(msg, ...)
#endif

#define TYPE_COL_WIDTH 0

#ifdef DEBUG
#define LOG_COLOR(color, level, fmt, ...) \
    do { \
        printf(color); \
        printf("(%d) ", rlib::getThreadId()); \
        printf("[%s]", level); \
        printf("%*s", TYPE_COL_WIDTH - (int)strlen(level), ""); \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n"); \
        printf(RESET); \
    } while(0)

#define LOG_DEBUG(fmt, ...)   LOG_COLOR(WHITE, "DEBUG", fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)    LOG_COLOR(RESET, "INFO", fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) LOG_COLOR(YELLOW, "WARNING", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   LOG_COLOR(RED, "ERROR", fmt, ##__VA_ARGS__)
#else
#define LOG_COLOR(color, level, fmt, ...)
#define LOG_DEBUG(fmt, ...)
#define LOG_INFO(fmt, ...)
#define LOG_WARNING(fmt, ...)
#define LOG_ERROR(fmt, ...)
#endif

#endif // DEBUG_H