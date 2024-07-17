#include "pcie_controller.h"

#include "system_log.h"

#define MODULE_TAG u"PCIe_CONTROLLER"

#define PCIe_DEVICE_ID_VENDOR_ID_REGISTER 0x00
#define PCIe_CLASS_CODE_SUBCLASS_PROG_IF_REVISION_ID 0x02
#define PCIe_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE_SIZE 0x03

static UINT64 MemoryMappedConfiguration;

STATUS API PcieControllerInit(IN CONST UINT64 BaseAddress)
{
    MemoryMappedConfiguration = BaseAddress;
    return E_OK;
}

STATUS API PcieControllerGetDeviceList(OUT PCIe_HEADER **PCIeDevices, OUT UINT64 *NumberOfPCIeDevices)
{
    UINT64 NumberOfFoundPCIeDevices = 0;

    for (UINT64 Bus = 0; Bus < 256; ++Bus)
    {
        for (UINT64 Slot = 0; Slot < 32; ++Slot)
        {
            for (UINT64 Function = 0; Function < 8; Function++)
            {
                UINT64 Offset = MemoryMappedConfiguration + ((Bus << 20) | (Slot << 15) | (Function << 12));
                PCIe_HEADER *Header = (PCIe_HEADER *)Offset;
                if (Header->VendorId != 0xFFFF)
                {
                    PCIeDevices[NumberOfFoundPCIeDevices] = Header;
                    NumberOfFoundPCIeDevices++;
                }
            }
        }
    }

    *NumberOfPCIeDevices = NumberOfFoundPCIeDevices;
    return E_OK;
}
