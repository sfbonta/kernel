#ifndef _AHCI_CONTROLLER_H_
#define _AHCI_CONTROLLER_H_

#include "platform_types.h"
#include "pcie_controller.h"

typedef struct _AHCI_CONTROLLER AHCI_CONTROLLER;

typedef struct _AHCI_CONTROLLER_INTERNAL AHCI_CONTROLLER_INTERNAL;

typedef STATUS (API *AHCI_CONTROLLER_LIST_DEVICES) (
    IN AHCI_CONTROLLER* AhciController,
    OUT CHAR16** DevicePaths,
    OUT UINT64* NumberOfDevices
);

typedef STATUS (API *AHCI_CONTROLLER_GET_DEVICE_NAME) (
    IN AHCI_CONTROLLER* AhciController,
    OUT CHAR16* DeviceName
);

typedef STATUS (API *AHCI_CONTROLLER_READ_SECTORS) (
    IN AHCI_CONTROLLER* AhciController,
    IN CONST CHAR16* DevicePath,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    OUT VOID *Buffer
);

typedef STATUS (API *AHCI_CONTROLLER_WRITE_SECTORS) (
    IN AHCI_CONTROLLER* AhciController,
    IN CONST CHAR16* DevicePath,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    IN CONST VOID *Buffer
);

typedef struct _AHCI_CONTROLLER
{
    AHCI_CONTROLLER_INTERNAL *Internal;
    AHCI_CONTROLLER_GET_DEVICE_NAME GetDeviceName;
    AHCI_CONTROLLER_LIST_DEVICES ListDevices;
    AHCI_CONTROLLER_READ_SECTORS ReadSectors;
    AHCI_CONTROLLER_WRITE_SECTORS WriteSectors;
} AHCI_CONTROLLER;

STATUS API AhciControllerInit(IN CONST PCIe_HEADER *PCIeHeader, IN CONST CHAR16* DeviceName, OUT AHCI_CONTROLLER **AhciController);

#endif /* _AHCI_CONTROLLER_H_ */
