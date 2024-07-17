#ifndef _LOCAL_APIC_H_
#define _LOCAL_APIC_H_

#include "platform_types.h"

STATUS API LocalApicInitialize(UINT64 BaseAddress);

STATUS API NO_CALLER_SAVED_REGISTERS LocalApicSendEndOfInterrupt(UINT32 InterruptNumber);

#endif /* _LOCAL_APIC_H_ */
