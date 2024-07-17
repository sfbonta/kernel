#ifndef _SYSTEM_MASS_STORAGE_H_
#define _SYSTEM_MASS_STORAGE_H_

#include "platform_types.h"
#include "pcie_controller.h"

STATUS API SystemMassStorageInit(VOID);

STATUS API SystemMassStorageRegisterAhciController(PCIe_HEADER *PCIeHeader);

STATUS API SystemMassStorageReadSectors(IN CONST CHAR16 *DevicePath, IN CONST UINT64 SectorOffset, IN CONST UINT64 NumberOfSectors, OUT VOID *Buffer);

STATUS API SystemMassStorageWriteSectors(IN CONST CHAR16 *DevicePath, IN CONST UINT64 SectorOffset, IN CONST UINT64 NumberOfSectors, IN CONST VOID *Buffer);

#endif /* _STSTEM_MASS_STORAGE_H_ */
