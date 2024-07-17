#include "port.h"

#define PORT_UNUSED 0x0080

static STATUS API NO_CALLER_SAVED_REGISTERS WaitOneCycle(VOID);

STATUS API NO_CALLER_SAVED_REGISTERS PortWriteByte(IN UINT16 Port, IN UINT8 Value)
{
    ASM("outb %0, %w1" : : "a"(Value), "Nd"(Port) : "memory");
    WaitOneCycle();
    return E_OK;
}

STATUS API NO_CALLER_SAVED_REGISTERS PortWriteWord(IN CONST UINT16 Port, IN CONST UINT16 Value)
{
    ASM("outw %0, %w1" : : "a"(Value), "Nd"(Port) : "memory");
    WaitOneCycle();
    return E_OK;
}

STATUS API NO_CALLER_SAVED_REGISTERS PortWriteDoubleWord(IN CONST UINT16 Port, IN CONST UINT32 Value)
{
    ASM("outl %0, %w1" : : "a"(Value), "Nd"(Port) : "memory");
    WaitOneCycle();
    return E_OK;
}

STATUS API NO_CALLER_SAVED_REGISTERS PortReadByte(IN CONST UINT16 Port, OUT UINT8 *Value)
{
    ASM("inb %w1, %0" : "=a"(*Value) : "Nd"(Port) : "memory");
    WaitOneCycle();
    return E_OK;
}

STATUS API NO_CALLER_SAVED_REGISTERS PortReadWord(IN CONST UINT16 Port, OUT UINT16 *Value)
{
    ASM("inw %w1, %0" : "=a"(*Value) : "Nd"(Port) : "memory");
    WaitOneCycle();
    return E_OK;
}

STATUS API NO_CALLER_SAVED_REGISTERS PortReadDoubleWord(IN CONST UINT16 Port, OUT UINT32 *Value)
{
    ASM("inl %w1, %0" : "=a"(*Value) : "Nd"(Port) : "memory");
    WaitOneCycle();
    return E_OK;
}

static STATUS API NO_CALLER_SAVED_REGISTERS WaitOneCycle(VOID)
{
    ASM("outb %%al, $0x80" : : "a"(0));
    return E_OK;
}
