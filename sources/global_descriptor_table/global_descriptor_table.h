#ifndef _GLOBABL_DESCRIPTOR_TABLE_H_
#define _GLOBABL_DESCRIPTOR_TABLE_H_

#include "platform_types.h"

#define GLOBAL_DESCRIPTOR_TABLE_MAXIMUM_NUMBER_OF_SEGMENTS 10

typedef struct _GDT_ENTRY
{
    UINT64 Base;
    UINT32 Limit;
    UINT8 Flags;
    UINT8 AccessByte;
} GDT_ENTRY;

STATUS API GlobalDescriptorTableInit(IN CONST GDT_ENTRY* Entries, IN UINT64 NumberOfEntries);

#endif /* _GLOBABL_DESCRIPTOR_TABLE_H_ */
