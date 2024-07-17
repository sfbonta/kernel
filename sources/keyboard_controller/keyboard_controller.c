#include "keyboard_controller.h"

#include "local_apic.h"
#include "ps2_controller.h"
#include "port.h"
#include "keyboard_scan_code.h"

#define KEY_CODES_BUFFER_LENGTH 1024
#define PREPROCESS_KEY_CODES_BUFFER_LENGTH 16

static volatile UINT64 KeyCodesBufferStart;
static volatile UINT64 KeyCodesBufferEnd;
static UINT8 KeyCodesBuffer[KEY_CODES_BUFFER_LENGTH];

static UINT64 PreprocessKeyCodesBufferLength;
static UINT8 PreprocessKeyCodesBuffer[PREPROCESS_KEY_CODES_BUFFER_LENGTH];

VOID INTERRUPT KeyboardControllerInterruptHandler(INTERRUPT_FRAME *InterruptFrame)
{
    (VOID) InterruptFrame;

    UINT8 DiscardedKey;
    UINT64 KeyCodesBuffeNextEnd = KeyCodesBufferEnd + 1;
    if (KeyCodesBuffeNextEnd >= KEY_CODES_BUFFER_LENGTH)
    {
        KeyCodesBuffeNextEnd -= KEY_CODES_BUFFER_LENGTH;
    }

    /* Buffer is not full  */
    if (KeyCodesBuffeNextEnd != KeyCodesBufferStart)
    {
        PS2ControllerReadData(&KeyCodesBuffer[KeyCodesBufferEnd]);
        KeyCodesBufferEnd = KeyCodesBuffeNextEnd;
    }
    else
    {
        PS2ControllerReadData(&DiscardedKey);
    }

    LocalApicSendEndOfInterrupt(KEYBOARD_CONTROLLER_INTERRUPT_SOURCE_VECTOR);
}

STATUS API KeyboardControllerInit(VOID)
{
    for (UINT64 i = 0; i < KEY_CODES_BUFFER_LENGTH; ++i)
    {
        KeyCodesBuffer[i] = 0;
    }
    KeyCodesBufferStart = 0;
    KeyCodesBufferEnd = 0;

    for (UINT64 i = 0; i < PREPROCESS_KEY_CODES_BUFFER_LENGTH; ++i)
    {
        PreprocessKeyCodesBuffer[i] = 0;
    }
    PreprocessKeyCodesBufferLength = 0;

    return E_OK;
}

STATUS API KeyboardControllerGetNextKey(SYSTEM_KEYBOARD_SCAN_CODE *KeyCode)
{
    BOOLEAN IsReadyForProcess = FALSE;
    SYSTEM_KEYBOARD_SCAN_CODE ScanCode = SYSTEM_KEY_INVALID;

    KeyboardScanCodeIsBufferReady(PreprocessKeyCodesBuffer, PreprocessKeyCodesBufferLength, &IsReadyForProcess);
    while (!IsReadyForProcess)
    {
        while (KeyCodesBufferStart == KeyCodesBufferEnd)
            ;

        PreprocessKeyCodesBuffer[PreprocessKeyCodesBufferLength] = KeyCodesBuffer[KeyCodesBufferStart];
        PreprocessKeyCodesBufferLength++;
        KeyCodesBufferStart++;
        if (KeyCodesBufferStart >= KEY_CODES_BUFFER_LENGTH)
        {
            KeyCodesBufferStart -= KEY_CODES_BUFFER_LENGTH;
        }

        KeyboardScanCodeIsBufferReady(PreprocessKeyCodesBuffer, PreprocessKeyCodesBufferLength, &IsReadyForProcess);
    }

    KeyboardScanCodeGetSystemScanCode(PreprocessKeyCodesBuffer, PreprocessKeyCodesBufferLength, &ScanCode);
    PreprocessKeyCodesBufferLength = 0;
    *KeyCode = ScanCode;

    return E_OK;
}
