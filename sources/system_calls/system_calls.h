#ifndef _SYSTEM_CALLS_H_
#define _SYSTEM_CALLS_H_

#include "platform_types.h"

#define SYSTEM_CALL_INTERRUPT_VECTOR 0x80

VOID NAKED SystemCallDispatcher(VOID);

#endif /* _SYSTEM_CALLS_H_ */
