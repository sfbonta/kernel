#ifndef _SATA_PORT_CONTROLLER_H_
#define _SATA_PORT_CONTROLLER_H_

#include "platform_types.h"
#include "port_control.h"

typedef struct _SATA_PORT_CONTROLLER SATA_PORT_CONTROLLER;

typedef struct _SATA_PORT_CONTROLLER_INTERNAL SATA_PORT_CONTROLLER_INTERNAL;

typedef STATUS(API *SATA_PORT_CONTROLLER_GET_DEVICE_NAME)(
    IN SATA_PORT_CONTROLLER *SataController,
    OUT CHAR16 *DeviceName);

typedef STATUS(API *SATA_PORT_CONTROLLER_READ_SECTORS)(
    IN SATA_PORT_CONTROLLER *SataController,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    OUT VOID *Buffer);

typedef STATUS(API *SATA_PORT_CONTROLLER_WRITE_SECTORS)(
    IN SATA_PORT_CONTROLLER *SataController,
    IN CONST UINT64 SectorOffset,
    IN CONST UINT64 NumberOfSectors,
    IN CONST VOID *Buffer);

typedef struct _SATA_PORT_CONTROLLER
{
    SATA_PORT_CONTROLLER_INTERNAL *Internal;
    SATA_PORT_CONTROLLER_GET_DEVICE_NAME GetDeviceName;
    SATA_PORT_CONTROLLER_READ_SECTORS ReadSectors;
    SATA_PORT_CONTROLLER_WRITE_SECTORS WriteSectors;
} SATA_PORT_CONTROLLER;

STATUS API SataPortControllerInit(PORT_CONTROL *PortControl, IN CONST CHAR16 *DeviceName, OUT SATA_PORT_CONTROLLER **SataPortController);

#endif /* _SATA_PORT_CONTROLLER_H_ */
