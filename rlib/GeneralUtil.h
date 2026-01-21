#ifndef GENERALUTIL_H
#define GENERALUTIL_H

#include <cstdio>
#include <cmath>
#include <string>

namespace rlib
{
    enum class PanicMode
    {
        kPanicModeAbort,
        kPanicModeThrowException
    };

    /*
    Reports a fatal error with file and line information, then exits the program.
    Parameters:
    - file: The name of the file where the error occurred.
    - line: The line number where the error occurred.
    - msg: The error message.
    */
    void reportPanic(const char* file, int line, const char* msg);

    void setPanicMode(PanicMode mode);
}

#define REPORT_PANIC(msg) \
    do { \
        std::string _panic_msg(msg); \
        rlib::reportPanic(__FILE__, __LINE__, _panic_msg.c_str()); \
    } while(0)

// Text formatting macros
#define RESET       "\033[0m"

// Styles
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define REVERSED    "\033[7m"

// Colors
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

#define PRINT_COLOR(color, fmt, ...) \
    do { \
        printf(color); \
        printf(fmt, ##__VA_ARGS__); \
        printf(RESET); \
    } while(0)

#define PRINT_SUCCESS(fmt, ...) PRINT_COLOR(GREEN, fmt, ##__VA_ARGS__)
#define PRINT_FAILURE(fmt, ...)   PRINT_COLOR(RED, fmt, ##__VA_ARGS__)

#define REPORT_TEST_RESULT(expr, fmt, ...) \
    do { \
        if (expr) { \
            PRINT_SUCCESS("Test passed: " fmt "\n", ##__VA_ARGS__); \
        } else { \
            PRINT_FAILURE("Test failed: " fmt "\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define FLOAT_EPSILON 1e-6
#define REAL_EPSILON 1e-12

#define ARE_FLOATS_EQUAL(a, b) (std::fabs((a) - (b)) < FLOAT_EPSILON)
#define ARE_REALS_EQUAL(a, b) (std::fabs((a) - (b)) < REAL_EPSILON)
#endif // GENERALUTIL_H