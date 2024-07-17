#include "ahci_controller.h"

#include "port_control.h"
#include "port_controller/sata_port_controller/sata_port_controller.h"
#include "system_log.h"
#include "frame_information_structure.h"
#include "system_memory.h"
#include "utils.h"

#define MODULE_TAG u"AHCI_CONTROLLER"

#define SATA_SIGNATURE 0x00000101

typedef struct _AHCI_CONTROLLER_INTERNAL
{
    CHAR16 DeviceName[32];
    SATA_PORT_CONTROLLER *SataPortControllers[32];
    UINT64 NumberOfSataPortControllers;
} AHCI_CONTROLLER_INTERNAL;

typedef volatile struct _AHCI_BASE_ADDRESS
{
    UINT32 ResourceTypeIndicator : 1;
    UINT32 Type : 2;
    UINT32 Prefetchable : 1;
    UINT32 Reserved : 9;
    UINT32 BaseAddress : 19;
} PACKED AHCI_BASE_ADDRESS;

typedef volatile struct _HOST_BUS_ADAPTER
{
    struct _HOST_BUS_ADAPTER_CAPABILITY
    {
        UINT32 NumberOfPorts : 5;
        UINT32 SupportsExternalSata : 1;
        UINT32 EnclosureManagementSupported : 1;
        UINT32 CommandCompletionCoalescingSupported : 1;
        UINT32 NumberOfCommandSlots : 5;
        UINT32 PartialStateCapable : 1;
        UINT32 SlumberStateCapable : 1;
        UINT32 PioMultipleDrqBlock : 1;
        UINT32 FisBasedSwitchingSupported : 1;
        UINT32 SupportsPortMultiplier : 1;
        UINT32 SupportsAhciModeOnly : 1;
        UINT32 Reserved : 1;
        UINT32 InterfaceSpeedSupport : 4;
        UINT32 SupportsCommandListOverride : 1;
        UINT32 SupportsActivityLef : 1;
        UINT32 SupportsAggressiveLinkPowerManagement : 1;
        UINT32 SupportsStaggeredSpinUp : 1;
        UINT32 SupportsMechanicalPresenceSwitch : 1;
        UINT32 SupportsSNotificationRegister : 1;
        UINT32 SupportsNativeCommandQueuing : 1;
        UINT32 Supports64BitAddressing : 1;
    } Capability;
    struct _HOST_BUS_ADAPTER_GLOBAL_CONTROL
    {
        UINT32 Reset : 1;
        UINT32 InterruptEnable : 1;
        UINT32 MsiRevertToSingleMessage : 1;
        UINT32 Reserved : 28;
        UINT32 AhciEnable : 1;
    } GlobalControl;
    UINT32 InterruptStatus;
    UINT32 PortsImplemented;
    UINT16 AhciVersionMinor;
    UINT16 AhciVersionMajor;
    struct _HOST_BUS_ADAPTER_COMMAND_COMPLETION_COALESCING_CONTROL
    {
        UINT32 Enable : 1;
        UINT32 Reserved : 2;
        UINT32 Interrupt : 5;
        UINT32 CommandCompletions : 8;
        UINT32 TimeoutValue : 16;
    } CommandCompletionCoalescingControl;
    UINT32 CommandCompletionCoalescingPorts;
    struct _HOST_BUS_ADAPTER_ENCLOSURE_MANAGEMENT_LOCATION
    {
        UINT32 BufferSize : 16;
        UINT32 Offset : 16;
    } EnclosureManagementLocation;
    struct _HOST_BUS_ADAPTER_ENCLOSURE_MANAGEMENT_CONTROL
    {
        UINT32 MessageReceived : 1;
        UINT32 Reserved1 : 7;
        UINT32 TransmitMessage : 1;
        UINT32 Reset : 1;
        UINT32 Reserved2 : 6;
        UINT32 LedMessageType : 1;
        UINT32 SafTeEnclosureMesssages : 1;
        UINT32 Ses2EnclosureMesssages : 1;
        UINT32 SgpioEnclosureMesssages : 1;
        UINT32 Reserved3 : 4;
        UINT32 SingleMessageBuffer : 1;
        UINT32 TransmitOnly : 1;
        UINT32 ActivityLedHardwareDriven : 1;
        UINT32 PortMultiplierSupport : 1;
        UINT32 Reserved : 4;
    } EnclosureManagementControl;
    struct _HOST_BUS_ADAPTER_CAPABILITY_EXTENDED
    {
        UINT32 BiosOSHandoff : 1;
        UINT32 NvmhciPresent : 1;
        UINT32 AutomaticPartialToSlumberTransitions : 1;
        UINT32 SupportsDeviceSleep : 1;
        UINT32 SupportsAggressiveDeviceSleepManagement : 1;
        UINT32 DeviceSleepEntranceFromSlumberModeOnly : 1;
        UINT32 Reserved : 26;
    } CapabilityExtended;
    struct _HOST_BUS_ADAPTER_BIOS_OS_HANDOFF
    {
        UINT32 BiosOwnedSemaphore : 1;
        UINT32 OsOwnedSemaphore : 1;
        UINT32 SmiOnOsOwnershipChangeEnable : 1;
        UINT32 OsOwnershipChange : 1;
        UINT32 BiosBusy : 1;
        UINT32 Reseved : 27;
    } BiosOsHandoff;
    UINT8 Reserved[0x60 - 0x2C];
    UINT8 NvmhciReserved[0xA0 - 0x60];
    UINT8 VendorSpecific[0x100 - 0xA0];
    PORT_CONTROL PortControl[32];
} PACKED HOST_BUS_ADAPTER;

static STATUS API AhciControllerListDevices(
    IN AHCI_CONTROLLER *AhciController,
    OUT CHAR16 **DevicePaths,
    OUT UINT64 *NumberOfDevices);

static STATUS API AhciControllerGetDeviceName(
    IN AHCI_CONTROLLER *AhciController,
    OUT CHAR16 *DeviceName);

static STATUS API AhciControllerReadSectors(
    IN AHCI_CONTROLLER *AhciController,
    IN CONST CHAR16 *DevicePath,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    OUT VOID *Buffer);

static STATUS API AhciControllerWriteSectors(
    IN AHCI_CONTROLLER *AhciController,
    IN CONST CHAR16 *DevicePath,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    IN CONST VOID *Buffer);

static BOOLEAN API IsSataDevice(VOID *Signature);

STATUS API AhciControllerInit(IN CONST PCIe_HEADER *PCIeHeader, IN CONST CHAR16 *DeviceName, OUT AHCI_CONTROLLER **AhciController)
{
    AHCI_BASE_ADDRESS *AhciBaseAddress = (AHCI_BASE_ADDRESS *)&PCIeHeader->BaseAddressRegisters[5];
    UINT64 Offset = AhciBaseAddress->BaseAddress;
    Offset <<= 13;
    LOG_DEBUG(u"BAR Base Address: 0x%x", Offset);
    HOST_BUS_ADAPTER *Hba = (HOST_BUS_ADAPTER *)Offset;
    LOG_DEBUG(u"HBA Interrupt Status: 0x%x", Hba->InterruptStatus);
    LOG_DEBUG(u"HBA Ports Implemented: 0x%x", Hba->PortsImplemented);
    LOG_DEBUG(u"HBA AHCI Version Major: 0x%x", Hba->AhciVersionMajor);
    LOG_DEBUG(u"HBA AHCI Version Minor: 0x%x", Hba->AhciVersionMinor);
    LOG_DEBUG(u"HBA Command Completion Coalescing Control: 0x%x", Hba->CommandCompletionCoalescingControl);
    LOG_DEBUG(u"HBA Command Completion Coalescing Ports: 0x%x", Hba->CommandCompletionCoalescingPorts);
    LOG_DEBUG(u"HBA Enclosure Management Location: 0x%x", Hba->EnclosureManagementLocation);
    LOG_DEBUG(u"HBA Enclosure Management Control: 0x%x", Hba->EnclosureManagementControl);
    LOG_DEBUG(u"HBA Capability Extended: 0x%x", Hba->CapabilityExtended);
    LOG_DEBUG(u"HBA Bios Os Handoff: 0x%x", Hba->BiosOsHandoff);

    LOG_DEBUG(u"Sizeof HBA: 0x%x", sizeof(*Hba));
    LOG_DEBUG(u"Sizeof PortControl: 0x%x", sizeof(*Hba->PortControl));

    AHCI_CONTROLLER *Result = NULL_PTR;
    AHCI_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    MemoryAllocatePool((VOID **)&Result, sizeof(*Result));
    MemoryAllocatePool((VOID **)&Internal, sizeof(*Internal));
    Internal->NumberOfSataPortControllers = 0;
    MemoryCopy(DeviceName, Internal->DeviceName, 32 * sizeof(*DeviceName));

    Result->Internal = Internal;
    Result->GetDeviceName = AhciControllerGetDeviceName;
    Result->ListDevices = AhciControllerListDevices;
    Result->ReadSectors = AhciControllerReadSectors;
    Result->WriteSectors = AhciControllerWriteSectors;

    *AhciController = Result;

    for (UINT64 i = 0; i < 6; ++i)
    {
        if (0x3 == Hba->PortControl[i].SerialAtaStatus.DeviceDetection && 0x1 == Hba->PortControl->SerialAtaStatus.InterfacePowerManagement)
        {
            if (IsSataDevice((VOID *)&Hba->PortControl[i].Signature))
            {
                SataPortControllerInit(&Hba->PortControl[i], u"sata0", &Internal->SataPortControllers[Internal->NumberOfSataPortControllers]);
                Internal->NumberOfSataPortControllers++;
            }
        }
    }

    return E_OK;
}

static STATUS API AhciControllerListDevices(
    IN AHCI_CONTROLLER *AhciController,
    OUT CHAR16 **DevicePaths,
    OUT UINT64 *NumberOfDevices)
{
    STATUS Status = E_OK;
    AHCI_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    SATA_PORT_CONTROLLER *SataPortController = NULL_PTR;

    if (NULL_PTR == AhciController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = AhciController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; i < Internal->NumberOfSataPortControllers; ++i)
    {
        SataPortController = Internal->SataPortControllers[i];
        if (NULL_PTR == SataPortController)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }

        SataPortController->GetDeviceName(SataPortController, DevicePaths[i]);
    }
    *NumberOfDevices = Internal->NumberOfSataPortControllers;

Cleanup:
    return Status;
}

static STATUS API AhciControllerGetDeviceName(
    IN AHCI_CONTROLLER *AhciController,
    OUT CHAR16 *DeviceName)
{
    STATUS Status = E_OK;
    AHCI_CONTROLLER_INTERNAL *Internal = NULL_PTR;

    if (NULL_PTR == AhciController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = AhciController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MemoryCopy(Internal->DeviceName, DeviceName, 32 * sizeof(*DeviceName));

Cleanup:
    return Status;
}

static STATUS API AhciControllerReadSectors(
    IN AHCI_CONTROLLER *AhciController,
    IN CONST CHAR16 *DevicePath,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    OUT VOID *Buffer)
{
    STATUS Status = E_OK;
    AHCI_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    SATA_PORT_CONTROLLER *SataPortController = NULL_PTR;
    CHAR16 DeviceName[32];

    if (NULL_PTR == AhciController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = AhciController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; i < Internal->NumberOfSataPortControllers; ++i)
    {
        SataPortController = Internal->SataPortControllers[i];
        if (NULL_PTR == SataPortController)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }
        SataPortController->GetDeviceName(SataPortController, DeviceName);
        if (0 == MemoryCompare(DeviceName, DevicePath, 32 * sizeof(*DeviceName)))
        {
            Status = SataPortController->ReadSectors(SataPortController, SectorOffset, NumberOfSectors, Buffer);
        }
    }

Cleanup:
    return Status;
}

static STATUS API AhciControllerWriteSectors(
    IN AHCI_CONTROLLER *AhciController,
    IN CONST CHAR16 *DevicePath,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    IN CONST VOID *Buffer)
{
    STATUS Status = E_OK;
    AHCI_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    SATA_PORT_CONTROLLER *SataPortController = NULL_PTR;
    CHAR16 DeviceName[32];

    if (NULL_PTR == AhciController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = AhciController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; i < Internal->NumberOfSataPortControllers; ++i)
    {
        SataPortController = Internal->SataPortControllers[i];
        if (NULL_PTR == SataPortController)
        {
            Status = E_NOT_OK;
            goto Cleanup;
        }
        SataPortController->GetDeviceName(SataPortController, DeviceName);
        if (0 == MemoryCompare(DeviceName, DevicePath, 32 * sizeof(*DeviceName)))
        {
            Status = SataPortController->WriteSectors(SataPortController, SectorOffset, NumberOfSectors, Buffer);
        }
    }

Cleanup:
    return Status;
}

static BOOLEAN API IsSataDevice(VOID *Signature)
{
    UINT32 SignatureValue = *(UINT32 *)Signature;

    return SATA_SIGNATURE == SignatureValue;
}
