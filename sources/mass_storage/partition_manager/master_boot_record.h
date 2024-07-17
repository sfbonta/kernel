#ifndef _MASTER_BOOT_RECORD_H_
#define _MASTER_BOOT_RECORD_H_

#include "platform_types.h"

#define LBA_SIZE 512
#define ALIGNMENT 1ULL * 1024 * 1024 / LBA_SIZE
#define NUMBER_OF_USABLE_BLOCKS 4ULL * 1024 * 1024 * 1024 / LBA_SIZE
#define NUMBER_OF_BLOCKS ALIGNMENT * 2 + NUMBER_OF_USABLE_BLOCKS
#define SIZE_OF_PARTITION_ENTRY 128

#define EFI_SYSTEM_PARTITION_GUID                                                                      \
    {                                                                                                  \
        0x28, 0x73, 0x2A, 0xC1, 0x1F, 0xF8, 0xD2, 0x11, 0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B \
    }

typedef struct _PARTITION_RECORD
{
    UINT8 BootIndicator;
    UINT8 StartingCHS[3];
    UINT8 OsType;
    UINT8 EndingCHS[3];
    UINT32 StartingLBA;
    UINT32 SizeInLBA;
} PACKED PARTITION_RECORD;

typedef struct _PROTECTIVE_MBR
{
    UINT8 BootCode[440];
    UINT32 UniqueMbrDiskSignature;
    UINT16 Unkown;
    PARTITION_RECORD PartitionRecords[4];
    UINT16 Signature;
#if LBA_SIZE > 512
    UINT8 Reserved[LBA_SIZE - 512];
#endif /* LBA_SIZE > 512 */
} PACKED PROTECTIVE_MBR;

typedef struct _GPT_HEADER
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 HeaderCRC32;
    UINT32 Reserved;
    UINT64 MyLBA;
    UINT64 AlternateLBA;
    UINT64 FirstUsableLba;
    UINT64 LastUsableLba;
    UINT8 DiskGUID[16];
    UINT64 PartitionEntryLBA;
    UINT32 NumberOfPartitionEntries;
    UINT32 SizeOfPartitionEntries;
    UINT32 PartitionEntryCRC32;
    UINT8 ReservedPadding[LBA_SIZE - 92];
}PACKED GPT_HEADER;

typedef struct _GPT_ENTRY
{
    UINT8 PartitionTypeGUID[16];
    UINT8 UniquePartitionGUID[16];
    UINT64 StartingLBA;
    UINT64 EndingLBA;
    UINT64 Attributes;
    CHAR16 PartitionName[36];
#if SIZE_OF_PARTITION_ENTRY > 128
    UINT8 Reserved[SIZE_OF_PARTITION_ENTRY - 128];
#endif /* SIZE_OF_PARTITION_ENTRY > 128 */
} PACKED GPT_ENTRY;

typedef struct _DEVICE_ENTRY
{
    PROTECTIVE_MBR ProtectiveMbr;
    GPT_HEADER GptHeader;
    GPT_ENTRY GptEntries[ALIGNMENT * 4 - 8];
} PACKED DEVICE_ENTRY;

#endif /* _MASTER_BOOT_RECORD */
