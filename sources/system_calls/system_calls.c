#include "system_calls.h"

VOID NAKED SystemCallDispatcher(VOID)
{
    ASM(
        ".intel_syntax noprefix\n"
        "iretq\n");
}
