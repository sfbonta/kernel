#ifndef _SYSTEM_MEMORY_H_
#define _SYSTEM_MEMORY_H_

#include "platform_types.h"
#include "system_memory_types.h"

STATUS API SystemMemoryInit(IN SYSTEM_MEMORY *SystemMemory);

STATUS API MemoryAllocatePages(OUT VOID **Buffer, IN CONST UINT64 NumberOfPages);

STATUS API MemoryFreePages(IN OUT VOID **Buffer);

STATUS API MemoryAllocatePool(OUT VOID **Buffer, IN CONST UINT64 Size);

STATUS API MemoryFreePool(IN OUT VOID **Buffer);

#endif /* _SYSTEM_MEMORY_H_ */
