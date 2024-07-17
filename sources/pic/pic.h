#ifndef _PIC_H_
#define _PIC_H_

#include "platform_types.h"

STATUS API PicInit(VOID);

STATUS API PicDisable(VOID);

STATUS API PicRemapIrq(IN CONST UINT8 Offset);

STATUS API PicSetInterruptMask(VOID);

#endif /* _PIC_H_ */
