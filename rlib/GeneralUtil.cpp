#include "GeneralUtil.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <unistd.h>
#include <sys/syscall.h>

namespace rlib
{
    PanicMode g_panicMode = PanicMode::kPanicModeAbort;

    void reportPanic(const char* file, int line, const char* msg)
    {
        char errorMsg[1024];
        snprintf(errorMsg, sizeof(errorMsg), "PANIC at %s:%d: %s\n", file, line, msg);

        switch (g_panicMode)
        {
        default:
        case PanicMode::kPanicModeAbort:
            fprintf(stderr, "---------------------PANIC---------------------\n");
            fprintf(stderr, "%s", errorMsg);
            fprintf(stderr, "Aborting the program.\n");
            abort();
            break;
        case PanicMode::kPanicModeThrowException:
            throw std::runtime_error(errorMsg);
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