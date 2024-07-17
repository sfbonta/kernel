#ifndef _PORT_CONTROL_H_
#define _PORT_CONTROL_H_

#include "platform_types.h"
#include "frame_information_structure.h"

typedef volatile struct _PORT_CONTROL
{
    UINT32 CommandListBaseAddressLow;
    UINT32 CommandListBaseAddressHigh;
    UINT32 FisBaseAddressLow;
    UINT32 FisBaseAddressHigh;
    struct _PORT_CONTROL_INTERRUPT_STATUS
    {
        UINT32 DeviceToHostRegisterFisInterrupt : 1;
        UINT32 PioSetupFisInterrupt : 1;
        UINT32 DmaSetupFisInterrupt : 1;
        UINT32 SetDeviceBitsInterrupt : 1;
        UINT32 UknownFisInterrupt : 1;
        UINT32 DescriptorProcessed : 1;
        UINT32 PortConnectChangeStatus : 1;
        UINT32 DeviceMechanicalPresenceStatus : 1;
        UINT32 Reserved1 : 14;
        UINT32 PhyRdyChangeStatus : 1;
        UINT32 IncorrectPortMultiplierStatus : 1;
        UINT32 OverflowStatus : 1;
        UINT32 Reserved2 : 1;
        UINT32 InterfaceNonFatalErrorStatus : 1;
        UINT32 InterfaceFatalErrorStatus : 1;
        UINT32 HostBusDataErrorStatus : 1;
        UINT32 HostBusFatalErrorStatus : 1;
        UINT32 TaskFileErrorStatus : 1;
        UINT32 ColdPortDetectStatus : 1;
    } InterruptStatus;
    struct _PORT_CONTROL_INTERRUPT_ENABLE
    {
        UINT32 DeviceToHostRegisterFisInterruptEnable : 1;
        UINT32 PioSetupFisInterruptEnable : 1;
        UINT32 DmaSetupFisInterruptEnable : 1;
        UINT32 SetDeviceBitsInterruptEnable : 1;
        UINT32 UknownFisInterruptEnable : 1;
        UINT32 DescriptorProcessedEnable : 1;
        UINT32 PortConnectChangeStatusEnable : 1;
        UINT32 DeviceMechanicalPresenceStatusEnable : 1;
        UINT32 Reserved1Enable : 14;
        UINT32 PhyRdyChangeStatusEnable : 1;
        UINT32 IncorrectPortMultiplierStatusEnable : 1;
        UINT32 OverflowStatusEnable : 1;
        UINT32 Reserved2Enable : 1;
        UINT32 InterfaceNonFatalErrorStatusEnable : 1;
        UINT32 InterfaceFatalErrorStatusEnable : 1;
        UINT32 HostBusDataErrorStatusEnable : 1;
        UINT32 HostBusFatalErrorStatusEnable : 1;
        UINT32 TaskFileErrorStatusEnable : 1;
        UINT32 ColdPortDetectStatusEnable : 1;
    } InterruptEnable;
    struct _PORT_CONTROL_COMMAND_AND_STATUS
    {
        UINT32 Start : 1;
        UINT32 SpinUpDevice : 1;
        UINT32 PowerOnDevice : 1;
        UINT32 CommandListOverride : 1;
        UINT32 FisReceiveEnable : 1;
        UINT32 Reserved : 3;
        UINT32 CurrentCommandSlot : 5;
        UINT32 MechanicalPresenceSwitchState : 1;
        UINT32 FisReceiveRunning : 1;
        UINT32 CommandListRunning : 1;
        UINT32 ColdPresenceState : 1;
        UINT32 PortMultiplierAtached : 1;
        UINT32 HotPlugCapablePort : 1;
        UINT32 MechanicalPresenceSwitchAttachedToPort : 1;
        UINT32 ColdPresenceDetection : 1;
        UINT32 ExternalSataPort : 1;
        UINT32 FisBasedSwitchingCapablePort : 1;
        UINT32 AutomaticPartialToSlumberTransitionAllowed : 1;
        UINT32 DeviceIsAtapi : 1;
        UINT32 DriveLedOnAtapiEnable : 1;
        UINT32 AggressiveSlumberPartial : 1;
        UINT32 InterfaceCommunicationControl : 5;
    } CommandAndStatus;
    UINT8 Reserved1[0x20 - 0x1C];
    struct _PORT_CONTROL_TASK_FILE_DATA
    {
        UINT32 Status : 8;
        UINT32 Error : 8;
        UINT32 Reserved : 16;
    } TaskFileData;
    struct _PORT_CONTROL_SIGNATURE
    {
        UINT32 SectorCount : 8;
        UINT32 LbaLow : 8;
        UINT32 LbaMid : 8;
        UINT32 LbaHigh : 8;
    } Signature;
    struct _PORT_CONTROL_SERIAL_ATA_STATUS
    {
        UINT32 DeviceDetection : 4;
        UINT32 CurrentInterfaceSpeed : 4;
        UINT32 InterfacePowerManagement : 4;
        UINT32 Reserved : 20;
    } SerialAtaStatus;
    struct _PORT_CONTROL_SERIAL_ATA_CONTROL
    {
        UINT32 DeviceDetectionInitialization : 4;
        UINT32 SpeedAllowed : 4;
        UINT32 InterfacePowerManagementTransitionsAllowed : 4;
        UINT32 SelectPowerManagement : 4;
        UINT32 PortMultiplier : 4;
        UINT32 Reserved : 12;
    } SerialAtaControl;
    struct _PORT_CONTROL_SERIAL_ATA_ERROR
    {
        UINT32 RecoveredDataIntegrityError : 1;
        UINT32 RecoveredCommunicationError : 1;
        UINT32 Reserved1 : 6;
        UINT32 TransientDataIntegrityError : 1;
        UINT32 PersistentCommunicationOrDataIntegrityError : 1;
        UINT32 ProtocolError : 1;
        UINT32 InternalError : 1;
        UINT32 Reserved2 : 4;
        UINT32 PhyRdyChange : 1;
        UINT32 PhyInternalError : 1;
        UINT32 CommWake : 1;
        UINT32 DecodeError : 1;
        UINT32 DisparityError : 1;
        UINT32 CrcError : 1;
        UINT32 HandshakeError : 1;
        UINT32 LinkSequenceError : 1;
        UINT32 TansportStateTransitionError : 1;
        UINT32 UknownFisType : 1;
        UINT32 Exchanged : 1;
        UINT32 Reserved3 : 5;
    } SerialAtaError;
    UINT32 SerialAtaActive;
    UINT32 SerialAtaCommandIssue;
    UINT32 SerialAtaNotification;
    struct _PORT_CONTROL_FIS_BASED_SWITCHING_CONTROL
    {
        UINT32 Enable : 1;
        UINT32 DeviceErrorClear : 1;
        UINT32 SingleDeviceError : 1;
        UINT32 Reserved1 : 5;
        UINT32 DeviceToIssue : 4;
        UINT32 ActiveDeviceOptimization : 4;
        UINT32 DeviceWithError : 4;
        UINT32 Reserved2 : 12;
    } FisBasedSwitchingControl;
    struct _PORT_CONTROL_DEVICE_SLEEP
    {
        UINT32 AggressiveDeviceSleepEnable : 1;
        UINT32 DeviceSleepPresent : 1;
        UINT32 DeviceSleepExitTimeout : 8;
        UINT32 MinimumDeviceSleepAssertionTime : 5;
        UINT32 DeviceSleepIdleTimeout : 10;
        UINT32 DeviceSleepIdleTimeoutMultiplier : 4;
        UINT32 Reserved : 3;
    } DeviceSleep;
    UINT8 Reserved2[0x70 - 0x48];
    UINT8 VendorSpecific[0x80 - 0x70];
} PACKED PORT_CONTROL;

typedef volatile struct _RECEIVED_FIS_STRUCTURE
{
    FIS_DMA_SETUP DmaSetup;
    UINT8 Reserved1[0x20 - 0x1C];
    FIS_PIO_SETUP PioSetup;
    UINT8 Reserved2[0x40 - 0x34];
    FIS_DEVICE_TO_HOST DeviceToHost;
    UINT8 Reserved3[0x58 - 0x54];
    FIS_SET_DEVICE_BITS SetDeviceBits;
    UINT8 UnkownFis[0xA0 - 0x60];
    UINT8 Reserved4[0x100 - 0xA0];
} PACKED RECEIVED_FIS_STRUCTURE;

typedef volatile struct _COMMAND_HEADER
{
    UINT32 FisCommandDwordLength : 5;
    UINT32 Atapi : 1;
    UINT32 Write : 1;
    UINT32 Prefetchable : 1;
    UINT32 Reset : 1;
    UINT32 Bist : 1;
    UINT32 ClearBusy : 1;
    UINT32 Reserved1 : 1;
    UINT32 PortMultiplier : 4;
    UINT32 PhysicalRegionDecriptorTableLenght : 16;
    UINT32 PhysicalRegionDecriptorTransferByteCount : 32;
    UINT32 CommandTableBaseAddressLow : 32;
    UINT32 CommandTableBaseAddressHigh : 32;
    UINT32 Reserved2 : 32;
    UINT32 Reserved3 : 32;
    UINT32 Reserved4 : 32;
    UINT32 Reserved5 : 32;
} PACKED COMMAND_HEADER;

typedef volatile struct _PHYSICAL_REGION_DESCRIPTOR_TABLE_ENTRY
{

    UINT32 DataBaseAddressLow : 32;

    UINT32 DataBaseAddressHigh : 32;

    UINT32 Reserved1 : 32;

    UINT32 ByteCount : 22;
    UINT32 Reserved2 : 9;
    UINT32 InterruptOnCompletion : 1;
} PACKED PHYSICAL_REGION_DESCRIPTOR_TABLE_ENTRY;

typedef volatile struct _COMMAND_TABLE
{
    UINT8 FisCommand[0x40 - 0x00];
    UINT8 AtapiCommand[0x50 - 0x40];
    UINT8 Reserved[0x80 - 0x50];
    PHYSICAL_REGION_DESCRIPTOR_TABLE_ENTRY Entries[];
} COMMAND_TABLE;

#endif /* _PORT_CONTROL_H_ */
