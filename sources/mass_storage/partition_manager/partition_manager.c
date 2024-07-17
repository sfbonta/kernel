#include "partition_manager.h"

#include "file_systems/fat32/fat32_partition_manager.h"
#include "utils.h"
#include "system_log.h"
#include "master_boot_record.h"
#include "system_memory.h"
#include "system_mass_storage.h"

#define MODULE_TAG u"PARTITION_MANAGER"

typedef struct _PARTITION_MANAGER_INTERNAL
{
    CHAR16 DevicePath[32];
    UINT64 NumberOfFat32Partitions;
    FAT32_PARTITION_MANAGER *Fat32PartitionManagers[32];
} PARTITION_MANAGER_INTERNAL;

typedef struct _PARTITION_MANAGER_HANDLE
{
    CHAR16 PartitionName[32];
    HANDLE *Handle;
} PARTITION_MANAGER_HANDLE;

STATUS API PartitionManagerListPartitions(
    PARTITION_MANAGER *PartitionManager,
    OUT CHAR16 **Partitions,
    OUT UINT64 *NumberOfPartitions);

STATUS API PartitionManagerCreateDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *DirectoryPath);

STATUS API PartitionManagerOpenDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *DirectoryPath,
    OUT HANDLE *Handle);

STATUS API PartitionManagerCloseDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE *Handle);

STATUS API PartitionManagerReadDirectoryContent(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE Handle,
    OUT DIRECTORY_CONTENT **DirectoryContent);

STATUS API PartitionManagerRemoveDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *DirectoryPath);

STATUS API PartitionManagerCreateFile(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *FilePath);

STATUS API PartitionManagerOpenFile(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *FilePath,
    OUT HANDLE *Handle);

STATUS API PartitionManagerCloseFile(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE *Handle);

STATUS API PartitionManagerReadFile(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE Handle,
    OUT UINT8 *Buffer,
    IN OUT UINT64 *BufferSize);

STATUS API PartitionManagerWriteFile(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE Handle,
    IN CONST UINT8 *Buffer,
    IN OUT UINT64 *BufferSize);

STATUS API PartitionManagerRemoveFile(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *FilePath);

STATUS API PartitionManagerInit(CONST CHAR16 *DevicePath, OUT PARTITION_MANAGER **PartitionManager)
{
    PARTITION_MANAGER *Result = NULL_PTR;
    MemoryAllocatePool((VOID **)&Result, sizeof(*Result));

    PARTITION_MANAGER_INTERNAL *Internal = NULL_PTR;
    MemoryAllocatePool((VOID **)&Internal, sizeof(*Internal));

    DEVICE_ENTRY *DeviceEntryBuffer = NULL_PTR;
    MemoryAllocatePool((VOID **)&DeviceEntryBuffer, sizeof(*DeviceEntryBuffer));

    SystemMassStorageReadSectors(DevicePath, 0, sizeof(*DeviceEntryBuffer) / 512, DeviceEntryBuffer);
    LOG_INFO(u"Found Partion named: %s", DeviceEntryBuffer->GptEntries[0].PartitionName);
    Fat32PartitionManagerInit(DevicePath,
                              DeviceEntryBuffer->GptEntries[0].PartitionName,
                              DeviceEntryBuffer->GptEntries[0].StartingLBA,
                              DeviceEntryBuffer->GptEntries[0].EndingLBA,
                              &Internal->Fat32PartitionManagers[0]);
    Internal->NumberOfFat32Partitions++;
    Result->Internal = Internal;
    Result->ListPartitions = PartitionManagerListPartitions;
    Result->CreateDirectory = PartitionManagerCreateDirectory;
    Result->OpenDirectory = PartitionManagerOpenDirectory;
    Result->CloseDirectory = PartitionManagerCloseDirectory;
    Result->ReadDirectoryContent = PartitionManagerReadDirectoryContent;
    Result->RemoveDirectory = PartitionManagerRemoveDirectory;
    Result->CreateFile = PartitionManagerCreateFile;
    Result->OpenFile = PartitionManagerOpenFile;
    Result->CloseFile = PartitionManagerCloseFile;
    Result->ReadFile = PartitionManagerReadFile;
    Result->WriteFile = PartitionManagerWriteFile;
    Result->RemoveFile = PartitionManagerRemoveFile;

    *PartitionManager = Result;
    return E_OK;
}

STATUS API PartitionManagerListPartitions(
    PARTITION_MANAGER *PartitionManager,
    OUT CHAR16 **Partitions,
    OUT UINT64 *NumberOfPartitions)
{
    STATUS Status = E_OK;
    PARTITION_MANAGER_INTERNAL *Internal = NULL_PTR;
    FAT32_PARTITION_MANAGER *Fat32PartitionManager = NULL_PTR;

    if (NULL_PTR == PartitionManager)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = PartitionManager->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; i < Internal->NumberOfFat32Partitions; ++i)
    {
        Fat32PartitionManager = Internal->Fat32PartitionManagers[i];
        if (NULL_PTR == Fat32PartitionManager)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }

        Fat32PartitionManager->GetPartitionName(Fat32PartitionManager, Partitions[i]);
    }
    *NumberOfPartitions = Internal->NumberOfFat32Partitions;

Cleanup:
    return Status;
}

STATUS API PartitionManagerCreateDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *DirectoryPath)
{
    STATUS Status = E_OK;
    PARTITION_MANAGER_INTERNAL *Internal = NULL_PTR;
    FAT32_PARTITION_MANAGER *Fat32PartitionManager = NULL_PTR;
    CHAR16 CurrentPartitionName[32];
    CHAR16 PartitionName[32];
    CHAR16 RestOfThePath[128];

    if (NULL_PTR == PartitionManager)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = PartitionManager->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    SplitPath(DirectoryPath, PartitionName, RestOfThePath);
    for (UINT64 i = 0; i < Internal->NumberOfFat32Partitions; ++i)
    {
        Fat32PartitionManager = Internal->Fat32PartitionManagers[i];
        if (NULL_PTR == Fat32PartitionManager)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }

        Fat32PartitionManager->GetPartitionName(Fat32PartitionManager, CurrentPartitionName);
        if (0 == MemoryCompare(PartitionName, CurrentPartitionName, 7 * sizeof(*PartitionName)))
        {
            Fat32PartitionManager->CreateDirectory(Fat32PartitionManager, RestOfThePath);
        }
    }

Cleanup:
    return Status;
}

STATUS API PartitionManagerOpenDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *DirectoryPath,
    OUT HANDLE *Handle)
{
    STATUS Status = E_OK;
    PARTITION_MANAGER_INTERNAL *Internal = NULL_PTR;
    FAT32_PARTITION_MANAGER *Fat32PartitionManager = NULL_PTR;
    PARTITION_MANAGER_HANDLE *PartitionManagerHandle = NULL_PTR;
    CHAR16 CurrentPartitionName[32];
    CHAR16 PartitionName[32];
    CHAR16 RestOfThePath[128];

    if (NULL_PTR == PartitionManager)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = PartitionManager->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MemoryAllocatePool((VOID **)&PartitionManagerHandle, sizeof(*PartitionManagerHandle));
    if (NULL_PTR == PartitionManagerHandle)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    SplitPath(DirectoryPath, PartitionName, RestOfThePath);
    for (UINT64 i = 0; i < Internal->NumberOfFat32Partitions; ++i)
    {
        Fat32PartitionManager = Internal->Fat32PartitionManagers[i];
        if (NULL_PTR == Fat32PartitionManager)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }

        Fat32PartitionManager->GetPartitionName(Fat32PartitionManager, CurrentPartitionName);
        if (0 == MemoryCompare(PartitionName, CurrentPartitionName, 32 * sizeof(*PartitionName)))
        {
            MemoryCopy(PartitionName, PartitionManagerHandle->PartitionName, 32 * sizeof(*PartitionName));
            Fat32PartitionManager->OpenDirectory(Fat32PartitionManager, RestOfThePath, PartitionManagerHandle->Handle);
        }
    }

Cleanup:
    *Handle = (HANDLE)PartitionManagerHandle;
    return Status;
}

STATUS API PartitionManagerCloseDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE *Handle)
{
    return E_OK;
}

STATUS API PartitionManagerReadDirectoryContent(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE Handle,
    OUT DIRECTORY_CONTENT **DirectoryContent)
{
    return E_OK;
}

STATUS API PartitionManagerRemoveDirectory(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *DirectoryPath)
{
    return E_OK;
}

STATUS API PartitionManagerCreateFile(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *FilePath)
{
    STATUS Status = E_OK;
    PARTITION_MANAGER_INTERNAL *Internal = NULL_PTR;
    FAT32_PARTITION_MANAGER *Fat32PartitionManager = NULL_PTR;
    CHAR16 CurrentPartitionName[32];
    CHAR16 PartitionName[32];
    CHAR16 RestOfThePath[128];

    if (NULL_PTR == PartitionManager)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = PartitionManager->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    SplitPath(FilePath, PartitionName, RestOfThePath);
    for (UINT64 i = 0; i < Internal->NumberOfFat32Partitions; ++i)
    {
        Fat32PartitionManager = Internal->Fat32PartitionManagers[i];
        if (NULL_PTR == Fat32PartitionManager)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }

        Fat32PartitionManager->GetPartitionName(Fat32PartitionManager, CurrentPartitionName);
        if (0 == MemoryCompare(PartitionName, CurrentPartitionName, 7 * sizeof(*PartitionName)))
        {
            Fat32PartitionManager->CreateFile(Fat32PartitionManager, RestOfThePath);
        }
    }

Cleanup:
    return Status;
}

STATUS API PartitionManagerOpenFile(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *FilePath,
    OUT HANDLE *Handle)
{
    STATUS Status = E_OK;
    PARTITION_MANAGER_INTERNAL *Internal = NULL_PTR;
    FAT32_PARTITION_MANAGER *Fat32PartitionManager = NULL_PTR;
    PARTITION_MANAGER_HANDLE *PartitionManagerHandle = NULL_PTR;
    CHAR16 CurrentPartitionName[32];
    CHAR16 PartitionName[32];
    CHAR16 RestOfThePath[128];

    if (NULL_PTR == PartitionManager)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = PartitionManager->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MemoryAllocatePool((VOID **)&PartitionManagerHandle, sizeof(*PartitionManagerHandle));
    if (NULL_PTR == PartitionManagerHandle)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    SplitPath(FilePath, PartitionName, RestOfThePath);

    for (UINT64 i = 0; i < Internal->NumberOfFat32Partitions; ++i)
    {
        Fat32PartitionManager = Internal->Fat32PartitionManagers[i];
        if (NULL_PTR == Fat32PartitionManager)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }

        Fat32PartitionManager->GetPartitionName(Fat32PartitionManager, CurrentPartitionName);
        if (0 == MemoryCompare(PartitionName, CurrentPartitionName, 5 * sizeof(*PartitionName)))
        {
            MemoryCopy(PartitionName, PartitionManagerHandle->PartitionName, 32 * sizeof(*PartitionName));
            Fat32PartitionManager->OpenFile(Fat32PartitionManager, RestOfThePath, PartitionManagerHandle->Handle);
        }
    }

Cleanup:
    *Handle = (HANDLE)PartitionManagerHandle;
    return Status;
}

STATUS API PartitionManagerCloseFile(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE *Handle)
{
    return E_OK;
}

STATUS API PartitionManagerReadFile(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE Handle,
    OUT UINT8 *Buffer,
    IN OUT UINT64 *BufferSize)
{
    return E_OK;
}

STATUS API PartitionManagerWriteFile(
    PARTITION_MANAGER *PartitionManager,
    IN OUT HANDLE Handle,
    IN CONST UINT8 *Buffer,
    IN OUT UINT64 *BufferSize)
{
    STATUS Status = E_OK;
    PARTITION_MANAGER_INTERNAL *Internal = NULL_PTR;
    FAT32_PARTITION_MANAGER *Fat32PartitionManager = NULL_PTR;
    PARTITION_MANAGER_HANDLE *PartitionManagerHandle = NULL_PTR;
    CHAR16 CurrentPartitionName[32];

    if (NULL_PTR == PartitionManager)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = PartitionManager->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    PartitionManagerHandle = (PARTITION_MANAGER_HANDLE *)Handle;
    if (NULL_PTR == PartitionManagerHandle)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; i < Internal->NumberOfFat32Partitions; ++i)
    {
        Fat32PartitionManager = Internal->Fat32PartitionManagers[i];
        if (NULL_PTR == Fat32PartitionManager)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }

        Fat32PartitionManager->GetPartitionName(Fat32PartitionManager, CurrentPartitionName);
        if (0 == MemoryCompare(PartitionManagerHandle->PartitionName, CurrentPartitionName, 5 * sizeof(*PartitionManagerHandle->PartitionName)))
        {
            LOG_INFO(u"Called write: ", "%s")
            Fat32PartitionManager->WriteFile(Fat32PartitionManager, PartitionManagerHandle->Handle, Buffer, BufferSize);
        }
    }

Cleanup:
    return Status;
}

STATUS API PartitionManagerRemoveFile(
    PARTITION_MANAGER *PartitionManager,
    IN CONST CHAR16 *FilePath)
{
    return E_OK;
}
