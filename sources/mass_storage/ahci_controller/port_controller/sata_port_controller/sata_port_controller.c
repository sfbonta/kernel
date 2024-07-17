#include "sata_port_controller.h"

#include "frame_information_structure.h"
#include "system_memory.h"
#include "utils.h"
#include "system_log.h"

#define MODULE_TAG u"SATA_PORT_CONTROLLER"

typedef struct _SATA_PORT_CONTROLLER_INTERNAL
{
    PORT_CONTROL *PortControl;
    CHAR16 *DeviceName;
} SATA_PORT_CONTROLLER_INTERNAL;

static STATUS API SataPortControllerGetDeviceName(
    IN SATA_PORT_CONTROLLER *SataPortController,
    OUT CHAR16 *DeviceName);

static STATUS API SataPortControllerReadSectors(
    IN SATA_PORT_CONTROLLER *SataPortController,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    OUT VOID *Buffer);

static STATUS API SataPortControllerWriteSectors(
    IN SATA_PORT_CONTROLLER *SataPortController,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    IN CONST VOID *Buffer);

static STATUS API RebasePort(PORT_CONTROL *PortControl);

static STATUS API StartPort(PORT_CONTROL *PortControl);

static STATUS API StopPort(PORT_CONTROL *PortControl);

STATUS API SataPortControllerInit(PORT_CONTROL *PortControl, IN CONST CHAR16 *DeviceName, OUT SATA_PORT_CONTROLLER **SataPortController)
{
    SATA_PORT_CONTROLLER *Result = NULL_PTR;
    SATA_PORT_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    MemoryAllocatePool((VOID **)&Result, sizeof(*Result));
    MemoryAllocatePool((VOID **)&Internal, sizeof(*Internal));
    Internal->PortControl = PortControl;
    RebasePort(PortControl);
    MemoryCopy(DeviceName, Internal->DeviceName, 32 * sizeof(*DeviceName));

    Result->Internal = Internal;
    Result->GetDeviceName = SataPortControllerGetDeviceName;
    Result->ReadSectors = SataPortControllerReadSectors;
    Result->WriteSectors = SataPortControllerWriteSectors;

    *SataPortController = Result;
    return E_OK;
}

static STATUS API SataPortControllerGetDeviceName(
    IN SATA_PORT_CONTROLLER *SataPortController,
    OUT CHAR16 *DeviceName)
{
    STATUS Status = E_OK;
    SATA_PORT_CONTROLLER_INTERNAL *Internal = NULL_PTR;

    if (NULL_PTR == SataPortController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = SataPortController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MemoryCopy(Internal->DeviceName, DeviceName, 32 * sizeof(*DeviceName));

Cleanup:
    return Status;
}

static STATUS API SataPortControllerReadSectors(
    IN SATA_PORT_CONTROLLER *SataPortController,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    OUT VOID *Buffer)
{
    STATUS Status = E_OK;
    SATA_PORT_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    PORT_CONTROL *PortControl = NULL_PTR;

    if (NULL_PTR == SataPortController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = SataPortController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    PortControl = Internal->PortControl;
    if (NULL_PTR == PortControl)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    UINT64 Offset = (UINT64)Buffer;
    // PortControl->InterruptStatus.Value = 0;
    UINT32 FreeSlot = 0;
    UINT32 CommandSlots = (PortControl->SerialAtaCommandIssue | PortControl->SerialAtaActive);
    for (UINT32 i = 0; i < 32; ++i)
    {
        if (CommandSlots & 1)
        {
            FreeSlot = CommandSlots;
            break;
        }
    }

    UINT64 CommandHeaderBaseAddress = PortControl->CommandListBaseAddressHigh;
    CommandHeaderBaseAddress = (CommandHeaderBaseAddress << 32) | PortControl->CommandListBaseAddressLow;
    COMMAND_HEADER *CommandHeader = (COMMAND_HEADER *)CommandHeaderBaseAddress;
    CommandHeader += FreeSlot;
    CommandHeader->FisCommandDwordLength = sizeof(FIS_HOST_TO_DEVICE) / sizeof(UINT32);
    CommandHeader->Write = 0;
    CommandHeader->PhysicalRegionDecriptorTableLenght = ((NumberOfSectors - 1) >> 4) + 1;

    UINT64 CommandTableBaseAddress = CommandHeader->CommandTableBaseAddressHigh;
    CommandTableBaseAddress = (CommandTableBaseAddress << 32) | CommandHeader->CommandTableBaseAddressLow;
    COMMAND_TABLE *CommandTable = (COMMAND_TABLE *)CommandTableBaseAddress;
    MemorySet((VOID *)CommandTable, 0, sizeof(COMMAND_TABLE) + CommandHeader->PhysicalRegionDecriptorTableLenght * sizeof(PHYSICAL_REGION_DESCRIPTOR_TABLE_ENTRY));

    UINT64 CurrentNumberOfSectors = NumberOfSectors;
    for (UINT64 i = 0; i < CommandHeader->PhysicalRegionDecriptorTableLenght - 1; ++i)
    {
        CommandTable->Entries[i].DataBaseAddressLow = ((Offset >> 0) & 0xFFFFFFFF);
        CommandTable->Entries[i].DataBaseAddressHigh = ((Offset >> 32) & 0xFFFFFFFF);
        CommandTable->Entries[i].ByteCount = 8 * 1024 - 1;
        CommandTable->Entries[i].InterruptOnCompletion = 1;

        Offset += 8 * 1024;
        CurrentNumberOfSectors -= 16;
    }

    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].DataBaseAddressLow = ((Offset >> 0) & 0xFFFFFFFF);
    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].DataBaseAddressHigh = ((Offset >> 32) & 0xFFFFFFFF);
    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].ByteCount = ((CurrentNumberOfSectors << 9) - 1);
    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].InterruptOnCompletion = 1;

    FIS_HOST_TO_DEVICE *FisHostToDevice = (FIS_HOST_TO_DEVICE *)CommandTable->FisCommand;
    FisHostToDevice->FisType = FIS_TYPE_HOST_TO_DEVICE;
    FisHostToDevice->IsComand = 1;
    FisHostToDevice->Command = 0x25;

    FisHostToDevice->Lba0 = ((SectorOffset >> 0) & 0xFF);
    FisHostToDevice->Lba1 = ((SectorOffset >> 8) & 0xFF);
    FisHostToDevice->Lba2 = ((SectorOffset >> 16) & 0xFF);
    FisHostToDevice->IsLba = 1;

    FisHostToDevice->Lba3 = ((SectorOffset >> 24) & 0xFF);
    FisHostToDevice->Lba4 = ((SectorOffset >> 32) & 0xFF);
    FisHostToDevice->Lba5 = ((SectorOffset >> 40) & 0xFF);

    FisHostToDevice->CountLow = ((NumberOfSectors >> 0) & 0xFF);
    FisHostToDevice->CountHigh = ((NumberOfSectors >> 8) & 0xFF);

    while (PortControl->TaskFileData.Status & 0x88)
        ;

    PortControl->SerialAtaCommandIssue = (1 << FreeSlot);

    while ((PortControl->SerialAtaCommandIssue & (1 << FreeSlot)) || PortControl->InterruptStatus.TaskFileErrorStatus == 1)
        ;

Cleanup:
    return Status;
}

static STATUS API SataPortControllerWriteSectors(
    IN SATA_PORT_CONTROLLER *SataPortController,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    IN CONST VOID *Buffer)
{
    STATUS Status = E_OK;
    SATA_PORT_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    PORT_CONTROL *PortControl = NULL_PTR;

    if (NULL_PTR == SataPortController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = SataPortController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    PortControl = Internal->PortControl;
    if (NULL_PTR == PortControl)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    UINT64 Offset = (UINT64)Buffer;
    // PortControl->InterruptStatus.Value = 0;
    UINT32 FreeSlot = 0;
    UINT32 CommandSlots = (PortControl->SerialAtaCommandIssue | PortControl->SerialAtaActive);
    for (UINT32 i = 0; i < 32; ++i)
    {
        if (CommandSlots & 1)
        {
            FreeSlot = CommandSlots;
            break;
        }
    }

    UINT64 CommandHeaderBaseAddress = PortControl->CommandListBaseAddressHigh;
    CommandHeaderBaseAddress = (CommandHeaderBaseAddress << 32) | PortControl->CommandListBaseAddressLow;
    COMMAND_HEADER *CommandHeader = (COMMAND_HEADER *)CommandHeaderBaseAddress;
    CommandHeader += FreeSlot;
    CommandHeader->FisCommandDwordLength = sizeof(FIS_HOST_TO_DEVICE) / sizeof(UINT32);
    CommandHeader->Write = 1;
    CommandHeader->PhysicalRegionDecriptorTableLenght = ((NumberOfSectors - 1) >> 4) + 1;

    UINT64 CommandTableBaseAddress = CommandHeader->CommandTableBaseAddressHigh;
    CommandTableBaseAddress = (CommandTableBaseAddress << 32) | CommandHeader->CommandTableBaseAddressLow;
    COMMAND_TABLE *CommandTable = (COMMAND_TABLE *)CommandTableBaseAddress;
    MemorySet((VOID *)CommandTable, 0, sizeof(COMMAND_TABLE) + CommandHeader->PhysicalRegionDecriptorTableLenght * sizeof(PHYSICAL_REGION_DESCRIPTOR_TABLE_ENTRY));

    UINT64 CurrentNumberOfSectors = NumberOfSectors;
    for (UINT64 i = 0; i < CommandHeader->PhysicalRegionDecriptorTableLenght - 1; ++i)
    {
        CommandTable->Entries[i].DataBaseAddressLow = ((Offset >> 0) & 0xFFFFFFFF);
        CommandTable->Entries[i].DataBaseAddressHigh = ((Offset >> 32) & 0xFFFFFFFF);
        CommandTable->Entries[i].ByteCount = 8 * 1024 - 1;
        CommandTable->Entries[i].InterruptOnCompletion = 1;

        Offset += 8 * 1024;
        CurrentNumberOfSectors -= 16;
    }

    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].DataBaseAddressLow = ((Offset >> 0) & 0xFFFFFFFF);
    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].DataBaseAddressHigh = ((Offset >> 32) & 0xFFFFFFFF);
    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].ByteCount = ((CurrentNumberOfSectors << 9) - 1);
    CommandTable->Entries[CommandHeader->PhysicalRegionDecriptorTableLenght - 1].InterruptOnCompletion = 1;

    FIS_HOST_TO_DEVICE *FisHostToDevice = (FIS_HOST_TO_DEVICE *)CommandTable->FisCommand;
    FisHostToDevice->FisType = FIS_TYPE_HOST_TO_DEVICE;
    FisHostToDevice->IsComand = 1;
    FisHostToDevice->Command = 0x35;

    FisHostToDevice->Lba0 = ((SectorOffset >> 0) & 0xFF);
    FisHostToDevice->Lba1 = ((SectorOffset >> 8) & 0xFF);
    FisHostToDevice->Lba2 = ((SectorOffset >> 16) & 0xFF);
    FisHostToDevice->IsLba = 1;

    FisHostToDevice->Lba3 = ((SectorOffset >> 24) & 0xFF);
    FisHostToDevice->Lba4 = ((SectorOffset >> 32) & 0xFF);
    FisHostToDevice->Lba5 = ((SectorOffset >> 40) & 0xFF);

    FisHostToDevice->CountLow = ((NumberOfSectors >> 0) & 0xFF);
    FisHostToDevice->CountHigh = ((NumberOfSectors >> 8) & 0xFF);

    while (PortControl->TaskFileData.Status & 0x88)
        ;

    PortControl->SerialAtaCommandIssue = (1 << FreeSlot);

    while ((PortControl->SerialAtaCommandIssue & (1 << FreeSlot)) || PortControl->InterruptStatus.TaskFileErrorStatus == 1)
        ;

Cleanup:
    return Status;
}

static STATUS API StopPort(PORT_CONTROL *PortControl)
{
    PortControl->CommandAndStatus.Start = 0;
    PortControl->CommandAndStatus.FisReceiveEnable = 0;

    while (PortControl->CommandAndStatus.FisReceiveRunning || PortControl->CommandAndStatus.CommandListRunning)
        ;

    return E_OK;
}

static STATUS API StartPort(PORT_CONTROL *PortControl)
{
    while (PortControl->CommandAndStatus.CommandListRunning)
        ;

    PortControl->CommandAndStatus.FisReceiveEnable = 1;
    PortControl->CommandAndStatus.Start = 1;

    return E_OK;
}

static STATUS API RebasePort(PORT_CONTROL *PortControl)
{
    StopPort(PortControl);

    COMMAND_HEADER *CommandHeader = NULL_PTR;
    VOID *MemoryZone = NULL_PTR;
    UINT64 Offset = 0;
    MemoryAllocatePool(&MemoryZone, 32 * sizeof(COMMAND_HEADER));
    MemorySet(MemoryZone, 0, 32 * sizeof(COMMAND_HEADER));
    Offset = (UINT64)MemoryZone;
    PortControl->CommandListBaseAddressLow = ((Offset >> 0) & 0xFFFFFFFF);
    PortControl->CommandListBaseAddressHigh = ((Offset >> 32) & 0xFFFFFFFF);
    CommandHeader = (COMMAND_HEADER *)MemoryZone;

    MemoryZone = NULL_PTR;
    Offset = 0;
    MemoryAllocatePool(&MemoryZone, sizeof(RECEIVED_FIS_STRUCTURE));
    MemorySet(MemoryZone, 0, sizeof(RECEIVED_FIS_STRUCTURE));
    Offset = (UINT64)MemoryZone;
    PortControl->FisBaseAddressLow = ((Offset >> 0) & 0xFFFFFFFF);
    PortControl->FisBaseAddressHigh = ((Offset >> 32) & 0xFFFFFFFF);

    for (UINT64 i = 0; i < 32; ++i)
    {
        MemoryZone = NULL_PTR;
        Offset = 0;
        MemoryAllocatePool(&MemoryZone, sizeof(COMMAND_TABLE) + 1024 * sizeof(PHYSICAL_REGION_DESCRIPTOR_TABLE_ENTRY));
        MemorySet(MemoryZone, 0, sizeof(COMMAND_TABLE) + 1024 * sizeof(PHYSICAL_REGION_DESCRIPTOR_TABLE_ENTRY));
        Offset = (UINT64)MemoryZone;

        CommandHeader[i].PhysicalRegionDecriptorTableLenght = 1024;
        CommandHeader[i].CommandTableBaseAddressLow = ((Offset >> 0) & 0xFFFFFFFF);
        CommandHeader[i].CommandTableBaseAddressHigh = ((Offset >> 32) & 0xFFFFFFFF);
    }

    StartPort(PortControl);

    return E_OK;
}
