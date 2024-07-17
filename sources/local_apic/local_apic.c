#include "local_apic.h"

#include "msr.h"
#include "system_log.h"

#define MODULE_TAG u"LOCAL_APIC"

#define END_OF_INTERRUPT_OFFSET 0xB0
#define SPURIOUS_INTERRUPT_VECTOR_OFFSET 0xF0

#define LOCAL_APIC_MSR_ID 0x1B

static UINT64 LocalApicAddress;

STATUS API LocalApicInitialize(UINT64 BaseAddress)
{
    LocalApicAddress = BaseAddress;

    LOG_INFO(u"Initializing with base address: %x", BaseAddress);

    UINT32 Value = *(volatile UINT32 *)(LocalApicAddress + SPURIOUS_INTERRUPT_VECTOR_OFFSET);
    LOG_INFO(u"Read Spurious interrupt vector value: %x", Value);
    Value |= 0x000001FF;
    LOG_INFO(u"Written Spurious interrupt vector value: %x", Value);
    *(volatile UINT32 *)(LocalApicAddress + SPURIOUS_INTERRUPT_VECTOR_OFFSET) = Value;

    return E_OK;
}

STATUS API NO_CALLER_SAVED_REGISTERS LocalApicSendEndOfInterrupt(UINT32 InterruptNumber)
{
    LOG_DEBUG(u"Sending end of interrupt for :%x", InterruptNumber);
    *(volatile UINT32 *)(LocalApicAddress + END_OF_INTERRUPT_OFFSET) = InterruptNumber;
    return E_OK;
}
