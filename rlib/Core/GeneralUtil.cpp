#include "GeneralUtil.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <sys/syscall.h>
#include <cstdarg>

namespace rlib
{
    PanicMode g_panicMode = PanicMode::kPanicModeCoreDump;

    void reportPanic(const char* file, int line, const char* msg, ...)
    {
        char errorMsg[1024];
        va_list args;
        va_start(args, msg);
        vsnprintf(errorMsg, sizeof(errorMsg), msg, args);
        va_end(args);

        switch (g_panicMode)
        {
        default:
        case PanicMode::kPanicModeCoreDump:
            fprintf(stderr, "---------------------PANIC---------------------\n");
            fprintf(stderr, "\n%s(%d): %s\n\n", file, line, errorMsg);
            fprintf(stderr, "-----------------------------------------------\n");
            fprintf(stderr, "Generating core dump.\n");
            abort();
            break;
        case PanicMode::kPanicModeThrowException:
            throw PanicException(errorMsg);
            break;
        }
    }

    void setPanicMode(PanicMode mode)
    {
        g_panicMode = mode;
    }

    pid_t getThreadId()
    {
        return syscall(SYS_gettid);
    }
} // namespace rlib