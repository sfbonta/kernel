#include "ps2_controller.h"

#include "port.h"

#define PS2_CONTROLLER_DATA_PORT 0x60
#define PS2_CONTROLLER_STATUS_PORT 0x64
#define PS2_CONTROLLER_COMMAND_PORT 0x64

#define PS2_CONTROLLER_READ_CONFIGURATION_BYTE 0x20
#define PS2_CONTROLLER_WRITE_CONFIGURATION_BYTE 0x60
#define PS2_CONTROLLER_DISABLE_SECOND_PS2_PORT 0xA7
#define PS2_CONTROLLER_ENABLE_SECOND_PS2_PORT 0xA8
#define PS2_CONTROLLER_TEST_SECOND_PS2_PORT 0xA9
#define PS2_CONTROLLER_TEST_PS2_CONTROLLER 0xAA
#define PS2_CONTROLLER_TEST_FIRST_PS2_PORT 0xAB
#define PS2_CONTROLLER_DIAGNOSTIC_DUMP 0xAC
#define PS2_CONTROLLER_DISABLE_FIRST_PS2_PORT 0xAD
#define PS2_CONTROLLER_ENABLE_FIRST_PS2_PORT 0xAE
#define PS2_CONTROLLER_READ_CONTROLLER_INPUT_PORT 0xC0
#define PS2_CONTROLLER_READ_CONTROLLER_OUTPUT_PORT 0xC0
#define PS2_CONTROLLER_RESET 0xFF

typedef union _PS2_CONTROLLER_STATUS_REGISTER
{
    struct _PS2_CONTROLLER_STATUS_REGISTER_FIELDS
    {
        UINT8 OutputBufferStatus : 1;
        UINT8 InputBufferStatus : 1;
        UINT8 SystemFlag : 1;
        UINT8 CommandData : 1;
        UINT8 Reserved1 : 1;
        UINT8 Reserved2 : 1;
        UINT8 TimeoutError : 1;
        UINT8 ParityError : 1;
    } Fields;
    UINT8 Value;
} PS2_CONTROLLER_STATUS_REGISTER;

typedef union _PS2_CONTROLLER_CONFIGURATION
{
    struct _PS2_CONTROLLER_CONFIGURATION_FIELDS
    {
        UINT8 FirstPS2PortEnable : 1;
        UINT8 SecondPS2PortEnable : 1;
        UINT8 SystemFlag : 1;
        UINT8 Reserved1 : 1;
        UINT8 FirstPS2ClockDisable : 1;
        UINT8 SecondPS2ClockDisable : 1;
        UINT8 FirstPS2PortTranslationEnable : 1;
        UINT8 Reserved2 : 1;
    } Fields;
    UINT8 Value;
} PS2_CONTROLLER_CONFIGURATION;

typedef union _PS2_CONTROLLER_OUTPUT_PORT
{
    struct _FIELDS
    {
        UINT8 SystemReset : 1;
        UINT8 A20Gate : 1;
        UINT8 SecondPS2PortClock : 1;
        UINT8 SecondPS2PortData : 1;
        UINT8 OuputIRQ1BufferFull : 1;
        UINT8 OutputIRQ12BufferFull : 1;
        UINT8 FirstPS2PortClock : 1;
        UINT8 FirstPS2PortData : 1;
    } Fields;
    UINT8 Value;
} PS2_CONTROLLER_OUTPUT_PORT;

STATUS API PS2ControllerInit(VOID)
{
    return E_OK;
}

STATUS API NO_CALLER_SAVED_REGISTERS PS2ControllerReadData(UINT8 *Data)
{
    PortReadByte(PS2_CONTROLLER_DATA_PORT, Data);

    return E_OK;
}
