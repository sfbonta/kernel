#ifndef _FRAME_INFORMATION_STRUCTURE_H_
#define _FRAME_INFORMATION_STRUCTURE_H_

#include "platform_types.h"

typedef enum _FIS_TYPE
{
    FIS_TYPE_HOST_TO_DEVICE = 0x27,
    FIS_TYPE_DEVICE_TO_HOST = 0x34,
    FIS_TYPE_DMA_ACTIVATE = 0x39,
    FIS_TYPE_DMA_SETUP = 0x41,
    FIS_TYPE_DATA = 0x46,
    FIS_TYPE_BIST_ACTIVATE = 0x58,
    FIS_TYPE_PIO_SETUP = 0x5F,
    FIS_TYPE_SET_DEVICE_BITS = 0xA1,
} FIS_TYPE;

typedef struct _FIS_HOST_TO_DEVICE
{
    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved1 : 3;
    UINT32 IsComand : 1;
    UINT32 Command : 8;
    UINT32 FeatureLow : 8;

    UINT32 Lba0 : 8;
    UINT32 Lba1 : 8;
    UINT32 Lba2 : 8;
    UINT32 Reserved2 : 6;
    UINT32 IsLba : 1;
    UINT32 Reserved3 : 1;

    UINT32 Lba3 : 8;
    UINT32 Lba4 : 8;
    UINT32 Lba5 : 8;
    UINT32 FeatureHigh : 8;

    UINT32 CountLow : 8;
    UINT32 CountHigh : 8;
    UINT32 IsochronousCommandCompletion : 8;
    UINT32 Control : 8;

    UINT32 Reserved4 : 32;
} PACKED FIS_HOST_TO_DEVICE;

typedef struct _FIS_DEVICE_TO_HOST
{

    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved1 : 2;
    UINT32 InterruptBit : 1;
    UINT32 Reserved2 : 1;
    UINT32 Status : 8;
    UINT32 Error : 8;

    UINT32 Lba0 : 8;
    UINT32 Lba1 : 8;
    UINT32 Lba2 : 8;
    UINT32 Reserved3 : 6;
    UINT32 IsLba : 1;
    UINT32 Reserved4 : 1;

    UINT32 Lba3 : 8;
    UINT32 Lba4 : 8;
    UINT32 Lba5 : 8;
    UINT32 Reserved5 : 8;

    UINT32 CountLow : 8;
    UINT32 CountHigh : 8;
    UINT32 Reserved6 : 16;

    UINT32 Reserved7 : 32;
} PACKED FIS_DEVICE_TO_HOST;

typedef struct _FIS_DMA_ACTIVATE
{

    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved : 20;
} PACKED FIS_DMA_ACTIVATE;

typedef struct _FIS_DMA_SETUP
{

    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved1 : 1;
    UINT32 DataTransferDirection : 1;
    UINT32 InterruptBit : 1;
    UINT32 AutoActivate : 1;
    UINT32 Reserved2 : 16;

    UINT32 DmaBufferIdHigh : 32;

    UINT32 DmaBufferIdLow : 32;

    UINT32 Reserved3 : 32;

    UINT32 DmaBufferOffset : 32;

    UINT32 TransferCount : 32;

    UINT32 Reserved4 : 32;
} PACKED FIS_DMA_SETUP;

typedef struct _FIS_DATA
{

    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved : 20;
    UINT32 Data[];
} PACKED FIS_DATA;

typedef struct _FIS_BIST_ACTIVATE
{
    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved1 : 4;
    UINT32 VendorSpecificTestMode : 1;
    UINT32 Reserved2 : 1;
    UINT32 PrimitiveBit : 1;
    UINT32 FarEndAnalogLoopback : 1;
    UINT32 FarEndRetimedLoopback : 1;
    UINT32 BypassScrambling : 1;
    UINT32 AlignBypass : 1;
    UINT32 FarEndTransmitOnly : 1;
    UINT32 Reserved3 : 8;

    UINT32 DataHigh : 32;

    UINT32 DataLow : 32;
} PACKED FIS_BIST_ACTIVATE;

typedef struct _FIS_PIO_SETUP
{
    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved1 : 1;
    UINT32 DataTransferDirection : 1;
    UINT32 InterruptBit : 1;
    UINT32 Reserved2 : 1;
    UINT32 Status : 8;
    UINT32 Error : 8;

    UINT32 Lba0 : 8;
    UINT32 Lba1 : 8;
    UINT32 Lba2 : 8;
    UINT32 Reserved3 : 6;
    UINT32 IsLba : 1;
    UINT32 Reserved4 : 1;

    UINT32 Lba3 : 8;
    UINT32 Lba4 : 8;
    UINT32 Lba5 : 8;
    UINT32 Reserved5 : 8;

    UINT32 CountLow : 8;
    UINT32 CountHigh : 8;
    UINT32 Reserved6 : 8;
    UINT32 NewStatus : 8;

    UINT32 TransferCount : 16;
    UINT32 Reserved7 : 16;

} PACKED FIS_PIO_SETUP;

typedef struct _FIS_SET_DEVICE_BITS
{

    UINT32 FisType : 8;
    UINT32 PortMultiplier : 4;
    UINT32 Reserved1 : 2;
    UINT32 InterruptBit : 1;
    UINT32 NotificationBit : 1;
    UINT32 StatusLow : 3;
    UINT32 Reserved2 : 1;
    UINT32 StatusHigh : 3;
    UINT32 Reserved3 : 1;
    UINT32 Error : 8;

    UINT32 ProtocolSpecific : 32;

} PACKED FIS_SET_DEVICE_BITS;

#endif /* _FRAME_INFORMATION_STRUCTURE_H_ */
