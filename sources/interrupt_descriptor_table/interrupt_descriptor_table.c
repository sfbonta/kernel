#include "interrupt_descriptor_table.h"

#define TYPE_ATTRIBUTES_TRAP 0x8F
#define TYPE_ATTRIBUTES_INTERRUPT 0x8E
#define TYPE_ATTRIBUTES_SYSCALL 0xEE

#define HAS_ERROR_CODE(IsrNumber) ((IsrNumber == 8) || (IsrNumber == 10) || (IsrNumber == 11) ||  \
                                   (IsrNumber == 12) || (IsrNumber == 13) || (IsrNumber == 14) || \
                                   (IsrNumber == 17) || (IsrNumber == 21))

typedef struct _INTERRUPT_DESCRIPTOR
{
    UINT16 OffsetLow;
    UINT16 SegmentSelector;
    UINT8 InterruptStackTable;
    UINT8 TypeAttributes;
    UINT16 OffsetMid;
    UINT32 OffsetHigh;
    UINT32 Reserved;
} PACKED INTERRUPT_DESCRIPTOR;

typedef struct _INTERRUPT_DECRIPTOR_TABLE_REGISTER
{
    UINT16 Size;
    UINT64 Offset;
} PACKED INTERRUPT_DECRIPTOR_TABLE_REGISTER;

static VOID INTERRUPT DefaultExceptionHandler(INTERRUPT_FRAME *InterruptFrame);
static VOID INTERRUPT DefaultExceptionHandlerErrorCode(INTERRUPT_FRAME *InterruptFrame, UINT64 ErrorCode);
static VOID INTERRUPT DefaultInterruptHandler(INTERRUPT_FRAME *InterruptFrame);

static INTERRUPT_DESCRIPTOR InterruptDescriptors[256];
static INTERRUPT_DECRIPTOR_TABLE_REGISTER InterruptDescriptorRegister;

STATUS API InterruptDescriptorTableInit(VOID)
{
    for (UINT64 IsrNumber = 0; IsrNumber < 32; ++IsrNumber)
    {
        if (HAS_ERROR_CODE(IsrNumber))
        {
            InterruptDescriptorTableSetISR((UINT8)IsrNumber, (UINT64)DefaultExceptionHandlerErrorCode, TYPE_ATTRIBUTES_TRAP);
        }
        else
        {
            InterruptDescriptorTableSetISR((UINT8)IsrNumber, (UINT64)DefaultExceptionHandler, TYPE_ATTRIBUTES_TRAP);
        }
    }

    for (UINT64 IsrNumber = 32; IsrNumber < 256; ++IsrNumber)
    {
        InterruptDescriptorTableSetISR((UINT8)IsrNumber, (UINT64)DefaultInterruptHandler, TYPE_ATTRIBUTES_INTERRUPT);
    }

    InterruptDescriptorRegister.Size = sizeof(InterruptDescriptors);
    InterruptDescriptorRegister.Offset = (UINT64)InterruptDescriptors;

    ASM("lidt %0" : : "memory"(InterruptDescriptorRegister));

    return E_OK;
}

STATUS API InterruptDescriptorTableSetISR(IN CONST UINT8 IsrNumber, IN CONST UINT64 IsrAddress, IN CONST UINT8 TypeAttributes)
{
    INTERRUPT_DESCRIPTOR *InterruptDescriptor = &InterruptDescriptors[IsrNumber];

    InterruptDescriptor->OffsetLow = ((IsrAddress >> 0) & 0xFFFF);
    InterruptDescriptor->SegmentSelector = 0x08;
    InterruptDescriptor->InterruptStackTable = 0x00;
    InterruptDescriptor->TypeAttributes = TypeAttributes;
    InterruptDescriptor->OffsetMid = ((IsrAddress >> 16) & 0xFFFF);
    InterruptDescriptor->OffsetHigh = ((IsrAddress >> 32) & 0xFFFFFFFF);
    InterruptDescriptor->Reserved = 0;

    return E_OK;
}

static VOID INTERRUPT DefaultExceptionHandler(INTERRUPT_FRAME *InterruptFrame)
{
    (VOID) InterruptFrame;
}

static VOID INTERRUPT DefaultExceptionHandlerErrorCode(INTERRUPT_FRAME *InterruptFrame, UINT64 ErrorCode)
{
    (VOID) InterruptFrame;
    (VOID) ErrorCode;
}

static VOID INTERRUPT DefaultInterruptHandler(INTERRUPT_FRAME *InterruptFrame)
{
    (VOID) InterruptFrame;
}
