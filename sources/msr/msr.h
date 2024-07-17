#ifndef _MSR_H_
#define _MSR_H_

#include "platform_types.h"

STATUS API MsrWrite(IN CONST UINT32 MsrId, IN CONST UINT64 Value);

STATUS API MsrRead(IN CONST UINT32 MsrId, OUT UINT64* Value);

#endif /* _MSR_H_ */
