#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

#include "platform_types.h"
#include "system_keyboard_scan_codes.h"

#define KEYBOARD_CONTROLLER_INTERRUPT_SOURCE_VECTOR 0x01
#define KEYBOARD_CONTROLLER_INTERRUPT_VECTOR 0x21

VOID INTERRUPT KeyboardControllerInterruptHandler(INTERRUPT_FRAME *InterruptFrame);

STATUS API KeyboardControllerInit(VOID);

STATUS API KeyboardControllerGetNextKey(SYSTEM_KEYBOARD_SCAN_CODE *KeyCode);

#endif /* _KEYBOARD_CONTROLLER_H_ */
