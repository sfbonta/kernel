#include "io_apic.h"

#include "system_log.h"

#define MODULE_TAG u"IO_APIC"

static UINT64 IoApicAddress;

typedef union _IO_APIC_REDIRECT_REGISTER
{
    struct _FIELDS
    {
        UINT64 InterruptVector : 8;
        UINT64 DeliveryMode : 3;
        UINT64 DestinationMode : 1;
        UINT64 DeliveryStatus : 1;
        UINT64 InterruptInputPolarityPin : 1;
        UINT64 RemoteIrr : 1;
        UINT64 TriggerMode : 1;
        UINT64 InterruptMask : 1;
        UINT64 Reserved : 39;
        UINT64 Destination : 8;
    } Fields;
    UINT64 Value;
} IO_APIC_REDIRECT_REGISTER;

STATUS API IoApicInit(IN CONST UINT64 BaseAddress)
{
    IoApicAddress = BaseAddress;
    LOG_INFO(u"Initializing with base address: %x", BaseAddress);
    return E_OK;
}

STATUS API IoApicWriteRegister(IN CONST UINT8 Register, IN CONST UINT32 Value)
{
    *(volatile UINT32 *)(IoApicAddress + 0x00) = Register;
    *(volatile UINT32 *)(IoApicAddress + 0x10) = Value;
    return E_OK;
}

STATUS API IoApicReadRegister(IN CONST UINT8 Register, OUT UINT32 *Value)
{
    *(volatile UINT32 *)(IoApicAddress + 0x00) = Register;
    *Value = *(volatile UINT32 *)(IoApicAddress + 0x10);
    return E_OK;
}

STATUS API IoApicRedirectInterrupt(IN CONST UINT8 Source, IN CONST UINT8 InterruptVector)
{
    UINT32 ValueHigh = 0;
    UINT32 ValueLow = 0;
    IO_APIC_REDIRECT_REGISTER RedirectRegister;

    IoApicReadRegister(Source * 2 + 0x10, &ValueLow);
    IoApicReadRegister(Source * 2 + 0x11, &ValueHigh);
    RedirectRegister.Value = ValueHigh;
    RedirectRegister.Value = ((RedirectRegister.Value << 32) | ValueLow);
    LOG_DEBUG(u"Read Redirect register value: %x", RedirectRegister.Value);

    RedirectRegister.Fields.InterruptMask = 0;
    RedirectRegister.Fields.InterruptVector = InterruptVector;

    ValueLow = ((RedirectRegister.Value >> 0) & 0xFFFFFFFF);
    ValueHigh = ((RedirectRegister.Value >> 32) & 0xFFFFFFFF);
    IoApicWriteRegister(Source * 2 + 0x10, ValueLow);
    IoApicWriteRegister(Source * 2 + 0x11, ValueHigh);
    LOG_DEBUG(u"Written Redirect register value: %x", RedirectRegister.Value);

    return E_OK;
}
