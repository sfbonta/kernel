#include "system_memory.h"

#define PAGE_SIZE 4096

typedef struct _MEMORY_MAP_ENTRY
{
    UINT64 StartAddress;
    UINT64 NumberOfPages;
    UINT64 Attribute;
    UINT32 Type;
} MEMORY_MAP_ENTRY;

static UINT64 NumberOfEntries = 0;
static MEMORY_MAP_ENTRY *MemoryMap = NULL_PTR;
static BOOLEAN IsInitialized = FALSE;

STATUS API SystemMemoryInit(IN SYSTEM_MEMORY *SystemMemory)
{
    STATUS Status = E_OK;
    UINT64 MemoryMapSize = 0;
    UINT64 MemoryMapNumberOfPages = 0;
    EFI_MEMORY_DESCRIPTOR *MapEntry = NULL_PTR;

    if (NULL_PTR == SystemMemory)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    if (TRUE == IsInitialized)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MemoryMap = NULL_PTR;
    MapEntry = SystemMemory->MemoryMap;
    NumberOfEntries = SystemMemory->MemoryMapSize / SystemMemory->DescriptorSize;
    MemoryMapSize = NumberOfEntries * sizeof(*MemoryMap);
    MemoryMapNumberOfPages = MemoryMapSize / PAGE_SIZE;

    for (UINT64 i = 0; (i < NumberOfEntries) && (NULL_PTR == MemoryMap); ++i)
    {
        if (ConventionalMemory == MapEntry->Type && MapEntry->NumberOfPages >= MemoryMapNumberOfPages)
        {
            MemoryMap = (MEMORY_MAP_ENTRY *)MapEntry->PhysicalStart;
            MapEntry->PhysicalStart += (MemoryMapNumberOfPages * PAGE_SIZE);
            MapEntry->NumberOfPages -= MemoryMapNumberOfPages;
        }
        MapEntry = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)MapEntry + SystemMemory->DescriptorSize);
    }

    if (NULL_PTR == MemoryMap)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MapEntry = SystemMemory->MemoryMap;
    for (UINT64 i = 0; i < NumberOfEntries; ++i)
    {
        MemoryMap[i].StartAddress = MapEntry->PhysicalStart;
        MemoryMap[i].NumberOfPages = MapEntry->NumberOfPages;
        MemoryMap[i].Attribute = MapEntry->Attribute;
        MemoryMap[i].Type = MapEntry->Type;
        MapEntry = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)MapEntry + SystemMemory->DescriptorSize);
    }

    IsInitialized = TRUE;

Cleanup:
    return Status;
}

STATUS API MemoryAllocatePages(OUT VOID **Buffer, IN CONST UINT64 NumberOfPages)
{
    STATUS Status = E_OK;
    UINT64 PhysicalAddress = 0;

    if (FALSE == IsInitialized)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    if (NULL_PTR == Buffer)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    if (NULL_PTR != *Buffer)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; (i < NumberOfEntries) && (0 == PhysicalAddress); ++i)
    {
        if (ConventionalMemory == MemoryMap[i].Type && MemoryMap[i].NumberOfPages >= NumberOfPages)
        {
            PhysicalAddress = MemoryMap[i].StartAddress;
            MemoryMap[i].NumberOfPages -= NumberOfPages;
            MemoryMap[i].StartAddress += (NumberOfPages * PAGE_SIZE);
        }
    }

    if (0 == PhysicalAddress)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

Cleanup:
    *Buffer = (VOID *)PhysicalAddress;
    return Status;
}

STATUS API MemoryFreePages(IN OUT VOID **Buffer)
{
    (VOID) Buffer;
    return E_OK;
}

STATUS API MemoryAllocatePool(OUT VOID **Buffer, IN CONST UINT64 Size)
{
    return MemoryAllocatePages(Buffer, (Size + PAGE_SIZE - 1) / PAGE_SIZE);
}

STATUS API MemoryFreePool(IN OUT VOID **Buffer)
{
    (VOID) Buffer;
    return E_OK;
}
