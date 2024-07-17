#ifndef _PCIE_CONTROLLER_H_
#define _PCIE_CONTROLLER_H_

#include "platform_types.h"

typedef volatile struct _PCIe_HEADER
{
    UINT16 DeviceId;
    UINT16 VendorId;
    union _PCIe_HEADER_COMMAND_REGISTER
    {
        struct _PCIe_HEADER_COMMAND_REGISTER_FIELDS
        {
            UINT16 IoSpaceEnable : 1;
            UINT16 MemorySpaceEnable : 1;
            UINT16 BusMasterEnable : 1;
            UINT16 SpecialCyclesEnable : 1;
            UINT16 MemoryWriteAndInvalidateEnable : 1;
            UINT16 VgaPaletteSnoopingEnable : 1;
            UINT16 ParityErrorResponseEnable : 1;
            UINT16 WaitCycleEnable : 1;
            UINT16 SerrEnable : 1;
            UINT16 FastBackToBackEnable : 1;
            UINT16 InterruptDisable : 1;
            UINT16 Reserved : 5;
        } Fields;
        UINT16 Value;
    } CommandRegister;
    union _PCIe_HEADER_DEVICE_STATUS
    {
        struct _PCIe_HEADER_DEVICE_STATUS_FIELDS
        {
            UINT16 Reserved1 : 3;
            UINT16 InterruptStatus : 1;
            UINT16 CapabilitiesList : 1;
            UINT16 Capabile66Mhz : 1;
            UINT16 Reserved2 : 1;
            UINT16 FastBackToBackCapabile : 1;
            UINT16 MasterDataParityErrorDetected : 1;
            UINT16 DevselTiming : 2;
            UINT16 SignaledTargetAbort : 1;
            UINT16 ReceivedTargetAbort : 1;
            UINT16 ReceivedMasterAbort : 1;
            UINT16 SignaledSystemError : 1;
            UINT16 DetectedParityError : 1;
        } Fields;
        UINT16 Value;
    } DeviceStatus;
    UINT8 RevisionId;
    UINT8 ProgrammingInterface;
    UINT8 SubclassCode;
    UINT8 ClassCode;
    UINT8 CacheLineSize;
    UINT8 MasterLatencyTimer;
    union _PCIe_HEADER_TYPE
    {
        struct _PCIe_HEADER_TYPE_FIELDS
        {
            UINT8 HeaderLayout : 7;
            UINT8 MultiFunctionDevice : 1;
        } Fields;
        UINT8 Value;
    } Type;
    union _PCIe_HEADER_BULT_IN_SELF_TEST
    {
        struct _PCIe_HEADER_BULT_IN_SELF_TEST_FIELDS
        {
            UINT8 CompletionCode : 4;
            UINT8 Reserved : 2;
            UINT8 StartBist : 1;
            UINT8 BistCapable : 1;
        } Fields;
        UINT8 Value;
    } BultInSelfTest;
    UINT32 BaseAddressRegisters[6];
    UINT32 CardBusCisPointer;
    UINT16 SubsystemVendorId;
    UINT16 SubsystemId;
    UINT32 RomBaseAddress;
    UINT32 CapabilityPointer;
    union _PCIe_HEADER_INTERRUPT_INFORMATION
    {
        struct _PCIe_HEADER_INTERRUPT_INFORMATION_FIELDS
        {
            UINT16 InterruptLine : 8;
            UINT16 InterruptPin : 8;
        } Fields;
        UINT16 Value;
    } InterruptInformation;
    UINT8 MinmumGrant;
    UINT8 MaximumLatency;
} PACKED PCIe_HEADER;

STATUS API PcieControllerInit(IN CONST UINT64 BaseAddress);

STATUS API PcieControllerGetDeviceList(OUT PCIe_HEADER **PCIeDevices, OUT UINT64 *NumberOfPCIeDevices);

#endif /* _PCIE_CONTROLLER_H_ */
