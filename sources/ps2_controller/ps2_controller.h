#ifndef _PS2_CONTROLLER_H_
#define _PS2_CONTROLLER_H_

#include "platform_types.h"

STATUS API PS2ControllerInit(VOID);

STATUS API NO_CALLER_SAVED_REGISTERS PS2ControllerReadData(UINT8 *Data);

#endif /* _PS2_CONTROLLER_H_ */
