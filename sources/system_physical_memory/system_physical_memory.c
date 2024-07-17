#include "system_physical_memory.h"

#define PAGE_SIZE 4096

static UINT8 *MemoryMap = NULL_PTR;
static UINT64 TotalNumberOfPages = 0;
static UINT64 FirstFreePageIndex = 0;

static VOID API MarkPageUsed(CONST UINT64 PageNumber);

static VOID API MarkPageFree(CONST UINT64 PageNumber);

static BOOLEAN API IsPageFree(CONST UINT64 PageNumber);

STATUS API SystemPhysicalMemoryInit(IN SYSTEM_MEMORY *SystemMemory)
{
    STATUS Status = E_OK;
    UINT64 MemoryMapSize = 0;
    UINT64 MemoryMapNumberOfPages = 0;
    UINT64 StartingPage = 0;
    EFI_MEMORY_DESCRIPTOR *MapEntry = NULL_PTR;
    UINT64 NumberOfEntries = 0;

    if (NULL_PTR == SystemMemory)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MapEntry = SystemMemory->MemoryMap;
    NumberOfEntries = SystemMemory->MemoryMapSize / SystemMemory->DescriptorSize;
    for (UINT64 i = 0; i < NumberOfEntries; ++i)
    {
        TotalNumberOfPages += MapEntry->NumberOfPages;
        MapEntry = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)MapEntry + SystemMemory->DescriptorSize);
    }

    MemoryMap = NULL_PTR;
    MemoryMapSize = TotalNumberOfPages / 8;
    MemoryMapNumberOfPages = MemoryMapSize / PAGE_SIZE;
    FirstFreePageIndex = 0;

    MapEntry = SystemMemory->MemoryMap;
    NumberOfEntries = SystemMemory->MemoryMapSize / SystemMemory->DescriptorSize;
    for (UINT64 i = 0; (i < NumberOfEntries) && (NULL_PTR == MemoryMap); ++i)
    {
        if (ConventionalMemory == MapEntry->Type && MapEntry->NumberOfPages >= MemoryMapNumberOfPages)
        {
            MemoryMap = (UINT32 *)MapEntry->PhysicalStart;
        }
        MapEntry = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)MapEntry + SystemMemory->DescriptorSize);
    }

    if (NULL_PTR == MemoryMap)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MapEntry = SystemMemory->MemoryMap;
    NumberOfEntries = SystemMemory->MemoryMapSize / SystemMemory->DescriptorSize;
    for (UINT64 i = 0; i < NumberOfEntries; ++i)
    {
        StartingPage = MapEntry->PhysicalStart / PAGE_SIZE;
        for (UINT64 j = 0; j < MapEntry->NumberOfPages; ++j)
        {
            if (ConventionalMemory == MapEntry->Type)
            {
                MarkPageFree(StartingPage + j);
            }
            else
            {
                MarkPageUsed(StartingPage + j);
            }
        }

        MapEntry = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)MapEntry + SystemMemory->DescriptorSize);
    }

    /* Mark the memory used by memory map as used */
    StartingPage = (UINT64)MemoryMap / PAGE_SIZE;
    for (UINT64 i = 0; i < MemoryMapNumberOfPages; ++i)
    {
        MarkPageUsed(StartingPage + i);
    }
    FirstFreePageIndex = StartingPage + MemoryMapNumberOfPages;

Cleanup:
    return Status;
}

STATUS API SystemPhysicalMemoryAllocatePages(OUT VOID **Buffer, IN CONST UINT64 NumberOfPages)
{
    STATUS Status = E_OK;
    UINT64 PhysicalAddress = 0;
    BOOLEAN FoundUsedPage = FALSE;

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

    for (UINT64 PageIndex = FirstFreePageIndex; ((PageIndex < TotalNumberOfPages) && (0 == PhysicalAddress)); ++PageIndex)
    {
        FoundUsedPage = FALSE;
        for (UINT64 j = 0; ((j < NumberOfPages) && (!FoundUsedPage)); ++j)
        {
            if (!IsPageFree(PageIndex + j))
            {
                FoundUsedPage = TRUE;
                PageIndex += j;
            }
        }

        if (!FoundUsedPage)
        {
            PhysicalAddress = PageIndex * PAGE_SIZE;
            for (UINT64 j = 0; j < NumberOfPages; ++j)
            {
                MarkPageUsed(PageIndex + j);
            }
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

STATUS API SystemPhysicalMemoryFreePages(IN OUT VOID **Buffer, IN CONST UINT64 NumberOfPages)
{
    STATUS Status = E_OK;
    UINT64 PhysicalAddress = 0;
    UINT64 PageIndex = 0;

    if (NULL_PTR == Buffer)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    PhysicalAddress = (UINT64)*Buffer;
    PageIndex = PhysicalAddress / PAGE_SIZE;
    for (UINT64 i = 0; i < NumberOfPages; ++i)
    {
        MarkPageFree(PageIndex + i);
    }

Cleanup:
    *Buffer = NULL_PTR;
    return Status;
}

STATUS API SystemPhysicalMemoryAllocatePool(OUT VOID **Buffer, IN CONST UINT64 Size)
{
    return SystemPhysicalMemoryAllocatePages(Buffer, (Size + PAGE_SIZE - 1) / PAGE_SIZE);
}

STATUS API SystemPhysicalMemoryFreePool(IN OUT VOID **Buffer, IN CONST UINT64 Size)
{
    return SystemPhysicalMemoryFreePages(Buffer, (Size + PAGE_SIZE - 1) / PAGE_SIZE);
}

static VOID API MarkPageUsed(CONST UINT64 PageNumber)
{
    UINT64 MemoryMapOffset = PageNumber / 8;
    UINT64 MemoryMapBitOffset = PageNumber % 8;

    MemoryMap[MemoryMapOffset] |= (1 << MemoryMapBitOffset);
}

static VOID API MarkPageFree(CONST UINT64 PageNumber)
{
    UINT64 MemoryMapOffset = PageNumber / 8;
    UINT64 MemoryMapBitOffset = PageNumber % 8;

    MemoryMap[MemoryMapOffset] &= (~(1 << MemoryMapBitOffset));
}

static BOOLEAN API IsPageFree(CONST UINT64 PageNumber)
{
    UINT64 MemoryMapOffset = PageNumber / 8;
    UINT64 MemoryMapBitOffset = PageNumber % 8;

    return ((MemoryMap[MemoryMapOffset] & (1 << MemoryMapBitOffset)) == 0);
}
