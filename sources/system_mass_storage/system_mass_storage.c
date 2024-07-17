#include "system_mass_storage.h"
#include "ahci_controller.h"
#include "partition_manager.h"

static UINT64 NumberOfAhciControllers;
static AHCI_CONTROLLER *AhciControllers[32];

STATUS API SystemMassStorageInit(VOID)
{
    NumberOfAhciControllers = 0;
    return E_OK;
}

STATUS API SystemMassStorageRegisterAhciController(PCIe_HEADER *PCIeHeader)
{
    AhciControllerInit(PCIeHeader, u"ahci0", &AhciControllers[NumberOfAhciControllers]);
    PARTITION_MANAGER *PartitionManager = NULL_PTR;
    PartitionManagerInit(u"sata0", &PartitionManager);
    PartitionManager->CreateDirectory(PartitionManager, u"BontaOS.hdd1/A");
    PartitionManager->CreateDirectory(PartitionManager, u"BontaOS.hdd1/B");
    PartitionManager->CreateDirectory(PartitionManager, u"BontaOS.hdd1/C");
    PartitionManager->CreateDirectory(PartitionManager, u"BontaOS.hdd1/C/D");
    PartitionManager->CreateDirectory(PartitionManager, u"BontaOS.hdd1/C/D/E");
    PartitionManager->CreateFile(PartitionManager, u"BontaOS.hdd1/A/T.TXT");
    PartitionManager->CreateFile(PartitionManager, u"BontaOS.hdd1/C/U.TXT");
    PartitionManager->CreateFile(PartitionManager, u"BontaOS.hdd1/C/W.TXT");
    PartitionManager->CreateFile(PartitionManager, u"BontaOS.hdd1/C/D/E/V.TXT");

    HANDLE Handle = NULL_PTR;
    UINT8 Buffer[] = {1, 2, 3, 4, 5};
    UINT64 BufferSize = 5;
    PartitionManager->OpenFile(PartitionManager, u"BontaOS.hdd1/C/D/E/V.TXT", &Handle);
    PartitionManager->WriteFile(PartitionManager, Handle, Buffer, &BufferSize);

    NumberOfAhciControllers++;
    return E_OK;
}

STATUS API SystemMassStorageReadSectors(IN CONST CHAR16 *DevicePath, IN CONST UINT64 SectorOffset, IN CONST UINT64 NumberOfSectors, OUT VOID *Buffer)
{
    AhciControllers[0]->ReadSectors(AhciControllers[0], u"sata0", SectorOffset, NumberOfSectors, Buffer);
    return E_OK;
}

STATUS API SystemMassStorageWriteSectors(IN CONST CHAR16 *DevicePath, IN CONST UINT64 SectorOffset, IN CONST UINT64 NumberOfSectors, IN CONST VOID *Buffer)
{
    AhciControllers[0]->WriteSectors(AhciControllers[0], u"sata0", SectorOffset, NumberOfSectors, Buffer);
    return E_OK;
}
