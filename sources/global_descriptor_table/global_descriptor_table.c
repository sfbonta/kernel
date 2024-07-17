#include "global_descriptor_table.h"

#include "system_log.h"

#define MODULE_TAG u"GLOBAL_DESCRIPTOR_TABLE"

#define NUMBER_OF_SEGMENT_DESCRIPTORS 5

typedef struct _GLOBAL_DESCRIPTOR_TABLE_REGISTER
{
    UINT16 Size;
    UINT64 Offset;
} PACKED GLOBAL_DESCRIPTOR_TABLE_REGISTER;

typedef struct _SEGMENT_DESCRIPTOR
{
    UINT16 LimitLow;
    UINT16 BaseLow;
    UINT8 BaseMid;
    UINT8 AccessByte;
    UINT8 LimitHighFlags;
    UINT8 BaseHigh;
} PACKED SEGMENT_DESCRIPTOR;

static SEGMENT_DESCRIPTOR SegmentDescriptors[NUMBER_OF_SEGMENT_DESCRIPTORS];
static GLOBAL_DESCRIPTOR_TABLE_REGISTER GlobalDescriptorTable;

static VOID NAKED ReloadSegments(VOID);
static STATUS API SetSegmentDescriptor(IN CONST GDT_ENTRY *Entry, OUT SEGMENT_DESCRIPTOR *SegmentDescriptor);

STATUS API GlobalDescriptorTableInit(IN CONST GDT_ENTRY *Entries, IN UINT64 NumberOfEntries)
{
    for (UINT64 index = 0; index < NumberOfEntries; ++index)
    {
        SetSegmentDescriptor(&Entries[index], &SegmentDescriptors[index]);
    }

    GlobalDescriptorTable.Size = sizeof(*SegmentDescriptors) * NumberOfEntries - 1;
    GlobalDescriptorTable.Offset = (UINT64)SegmentDescriptors;

    LOG_DEBUG(u"Global Descriptor Table Size: %x", GlobalDescriptorTable.Size);
    LOG_DEBUG(u"Global Descriptor Table Offset: %x", GlobalDescriptorTable.Offset);

    ASM("lgdt %0" : : "m"(GlobalDescriptorTable));
    ReloadSegments();
    return E_OK;
}

static VOID NAKED ReloadSegments(VOID)
{
    ASM(
        ".intel_syntax noprefix\n"
        "push 0x08\n"
        "lea rax, [rip + .ReloadCS]\n"
        "push rax\n"
        "retfq\n"
        ".ReloadCS:\n"
        "mov ax, 0x10\n"
        "mov ds, ax\n"
        "mov es, ax\n"
        "mov fs, ax\n"
        "mov gs, ax\n"
        "mov ss, ax\n"
        "ret");
}

static STATUS API SetSegmentDescriptor(IN CONST GDT_ENTRY *Entry, OUT SEGMENT_DESCRIPTOR *SegmentDescriptor)
{
    SegmentDescriptor->LimitLow = ((Entry->Limit >> 0) & 0xFFFF);
    SegmentDescriptor->BaseLow = ((Entry->Base >> 0) & 0xFFFF);
    SegmentDescriptor->BaseMid = ((Entry->Base >> 16) & 0xFF);
    SegmentDescriptor->AccessByte = Entry->AccessByte;
    SegmentDescriptor->LimitHighFlags = (((Entry->Limit >> 16) & 0x0F) | ((Entry->Flags << 4) & 0xF0));
    SegmentDescriptor->BaseHigh = ((Entry->Base >> 24) & 0xFF);

    LOG_DEBUG(u"Entry Limit: %x", Entry->Limit);
    LOG_DEBUG(u"Entry Base: %x", Entry->Base);
    LOG_DEBUG(u"Entry Access Byte: %x", Entry->AccessByte);
    LOG_DEBUG(u"Entry Flags: %x", Entry->Flags);

    LOG_DEBUG(u"Segment Descriptor Limit Low: %x", SegmentDescriptor->LimitLow);
    LOG_DEBUG(u"Segment Descriptor Base Low: %x", SegmentDescriptor->BaseLow);
    LOG_DEBUG(u"Segment Descriptor Access Byte: %x", SegmentDescriptor->AccessByte);
    LOG_DEBUG(u"Segment Descriptor Limit High Flags: %x", SegmentDescriptor->LimitHighFlags);
    LOG_DEBUG(u"Segment Descriptor Base High: %x", SegmentDescriptor->BaseHigh);

    return E_OK;
}
