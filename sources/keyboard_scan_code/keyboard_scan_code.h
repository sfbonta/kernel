#ifndef _KEYBOARD_SCAN_CODE_H_
#define _KEYBOARD_SCAN_CODE_H_

#include "platform_types.h"
#include "system_keyboard_scan_codes.h"

#define KEYBOARD_SCAN_CODE_SET 1

#if ((KEYBOARD_SCAN_CODE_SET != 1))
#error "Scan Code Set is not supported"
#endif

STATUS API KeyboardScanCodeIsBufferReady(IN CONST UINT8 *ScanCodes, IN CONST UINT64 NumberOfScanCodes, OUT BOOLEAN* Ready);
STATUS API KeyboardScanCodeGetSystemScanCode(IN CONST UINT8* ScanCodes, IN CONST UINT64 NumberOfScanCodes, OUT SYSTEM_KEYBOARD_SCAN_CODE* SystemScanCode);

#endif /* _KEYBOARD_SCAN_CODE_H_ */
