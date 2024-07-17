#ifndef _IO_APIC_H_
#define _IO_APIC_H_

#include "platform_types.h"

STATUS API IoApicInit(IN CONST UINT64 BaseAddress);

STATUS API IoApicWriteRegister(IN CONST UINT8 Register, IN CONST UINT32 Value);

STATUS API IoApicReadRegister(IN CONST UINT8 Register, OUT UINT32 *Value);

STATUS API IoApicRedirectInterrupt(IN CONST UINT8 Source, IN CONST UINT8 InterruptVector);

#endif /* _IO_APIC_ */
