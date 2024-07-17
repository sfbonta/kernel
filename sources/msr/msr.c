#include "msr.h"

STATUS API MsrWrite(IN CONST UINT32 MsrId, IN CONST UINT64 Value)
{
    ASM("wrmsr" : : "c"(MsrId), "A"(Value));
    return E_OK;
}

STATUS API MsrRead(IN CONST UINT32 MsrId, OUT UINT64 *Value)
{
    ASM("rdmsr" : "=A"(*Value) : "c"(MsrId));
    return E_OK;
}
