#include "pic.h"

#include "port.h"

#define PIC_1_COMMAND 0x0020
#define PIC_1_DATA 0x0021

#define PIC_1_ICW1 0x11
#define PIC_1_ICW2 0x20
#define PIC_1_ICW3 0x04
#define PIC_1_ICW4 0x05

#define PIC_2_COMMAND 0x00A0
#define PIC_2_DATA 0x00A1

#define PIC_2_ICW1 0x11
#define PIC_2_ICW2 0x28
#define PIC_2_ICW3 0x02
#define PIC_2_ICW4 0x01

#define PIC_DISABLE 0xFF

STATUS API PicInit(VOID)
{
    /* ICW1 */
    PortWriteByte(PIC_1_COMMAND, PIC_1_ICW1);
    PortWriteByte(PIC_2_COMMAND, PIC_2_ICW1);

    /* ICW2 */
    PortWriteByte(PIC_1_DATA, PIC_1_ICW2);
    PortWriteByte(PIC_2_DATA, PIC_2_ICW2);

    /* ICW3 */
    PortWriteByte(PIC_1_DATA, PIC_1_ICW3);
    PortWriteByte(PIC_2_DATA, PIC_2_ICW3);

    /* ICW4 */
    PortWriteByte(PIC_1_DATA, PIC_1_ICW4);
    PortWriteByte(PIC_2_DATA, PIC_2_ICW4);


    return E_OK;
}

STATUS API PicDisable(VOID)
{
    PortWriteByte(PIC_2_DATA, PIC_DISABLE);
    PortWriteByte(PIC_1_DATA, PIC_DISABLE);

    return E_OK;
}

STATUS API PicRemapIrq(IN CONST UINT8 Offset)
{
    (VOID) Offset;
    return E_OK;
}

STATUS API PicSetInterruptMask(VOID)
{
    return E_OK;
}
