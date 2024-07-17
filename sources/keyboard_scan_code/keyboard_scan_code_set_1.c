#include "keyboard_scan_code.h"

#if (KEYBOARD_SCAN_CODE_SET == 1)

#define IS_EXTENDED_CODE(ScanCode) (0xE0 == (ScanCode))

#define PRINT_SCREEN_PRESSED_KEY_CODE_1 0xE0
#define PRINT_SCREEN_PRESSED_KEY_CODE_2 0x2A
#define PRINT_SCREEN_PRESSED_KEY_CODE_3 0xE0
#define PRINT_SCREEN_PRESSED_KEY_CODE_4 0x37

#define PRINT_SCREEN_RELEASED_KEY_CODE_1 0xE0
#define PRINT_SCREEN_RELEASED_KEY_CODE_2 0xB7
#define PRINT_SCREEN_RELEASED_KEY_CODE_3 0xE0
#define PRINT_SCREEN_RELEASED_KEY_CODE_4 0xAA

#define PAUSE_PRESSED_KEY_CODE_1 0xE1
#define PAUSE_PRESSED_KEY_CODE_2 0x1D
#define PAUSE_PRESSED_KEY_CODE_3 0x45
#define PAUSE_PRESSED_KEY_CODE_4 0xE1
#define PAUSE_PRESSED_KEY_CODE_5 0x9D
#define PAUSE_PRESSED_KEY_CODE_6 0xC5

typedef enum _KEYBOARD_SCAN_CODE
{
    /* Press key scan codes */
    KEY_ESC_PRESSED = 0x01,
    KEY_1_PRESSED = 0x02,
    KEY_2_PRESSED = 0x03,
    KEY_3_PRESSED = 0x04,
    KEY_4_PRESSED = 0x05,
    KEY_5_PRESSED = 0x06,
    KEY_6_PRESSED = 0x07,
    KEY_7_PRESSED = 0x08,
    KEY_8_PRESSED = 0x09,
    KEY_9_PRESSED = 0x0A,
    KEY_0_PRESSED = 0x0B,
    KEY_MINUS_PRESSED = 0x0C,
    KEY_EQUAL_PRESSED = 0x0D,
    KEY_BACKSPACE_PRESSED = 0x0E,
    KEY_TAB_PRESSED = 0x0F,
    KEY_Q_PRESSED = 0x10,
    KEY_W_PRESSED = 0x11,
    KEY_E_PRESSED = 0x12,
    KEY_R_PRESSED = 0x13,
    KEY_T_PRESSED = 0x14,
    KEY_Y_PRESSED = 0x15,
    KEY_U_PRESSED = 0x16,
    KEY_I_PRESSED = 0x17,
    KEY_O_PRESSED = 0x18,
    KEY_P_PRESSED = 0x19,
    KEY_OPEN_SQUARE_BRACET_PRESSED = 0x1A,
    KEY_CLOSE_SQUARE_BRACET_PRESSED = 0x1B,
    KEY_ENTER_PRESSED = 0x1C,
    KEY_LEFT_CONTROL_PRESSED = 0x1D,
    KEY_A_PRESSED = 0x1E,
    KEY_S_PRESSED = 0x1F,
    KEY_D_PRESSED = 0x20,
    KEY_F_PRESSED = 0x21,
    KEY_G_PRESSED = 0x22,
    KEY_H_PRESSED = 0x23,
    KEY_J_PRESSED = 0x24,
    KEY_K_PRESSED = 0x25,
    KEY_L_PRESSED = 0x26,
    KEY_SEMICOLON_PRESSED = 0x27,
    KEY_SINGLE_QUOTE_PRESSED = 0x28,
    KEY_BACK_TICK_PRESSED = 0x29,
    KEY_LEFT_SHIFT_PRESSED = 0x2A,
    KEY_BACKSLASH_PRESSED = 0x2B,
    KEY_Z_PRESSED = 0x2C,
    KEY_X_PRESSED = 0x2D,
    KEY_C_PRESSED = 0x2E,
    KEY_V_PRESSED = 0x2F,
    KEY_B_PRESSED = 0x30,
    KEY_N_PRESSED = 0x31,
    KEY_M_PRESSED = 0x32,
    KEY_COMMA_PRESSED = 0x33,
    KEY_PERIOD_PRESSED = 0x34,
    KEY_SLASH_PRESSED = 0x35,
    KEY_RIGHT_SHIFT_PRESSED = 0x36,
    KEY_KEYPAD_STAR_PRESSED = 0x37,
    KEY_LEFT_ALT_PRESSED = 0x38,
    KEY_SPACE_PRESSED = 0x39,
    KEY_CAPSLOCK_PRESSED = 0x3A,
    KEY_F1_PRESSED = 0x3B,
    KEY_F2_PRESSED = 0x3C,
    KEY_F3_PRESSED = 0x3D,
    KEY_F4_PRESSED = 0x3E,
    KEY_F5_PRESSED = 0x3F,
    KEY_F6_PRESSED = 0x40,
    KEY_F7_PRESSED = 0x41,
    KEY_F8_PRESSED = 0x42,
    KEY_F9_PRESSED = 0x43,
    KEY_F10_PRESSED = 0x44,
    KEY_NUMBER_LOCK_PRESSED = 0x45,
    KEY_SCROLL_PRESSED = 0x46,
    KEY_KEYPAD_7_PRESSED = 0x47,
    KEY_KEYPAD_8_PRESSED = 0x48,
    KEY_KEYPAD_9_PRESSED = 0x49,
    KEY_KEYPAD_MINUS_PRESSED = 0x4A,
    KEY_KEYPAD_4_PRESSED = 0x4B,
    KEY_KEYPAD_5_PRESSED = 0x4C,
    KEY_KEYPAD_6_PRESSED = 0x4D,
    KEY_KEYPAD_PLUS_PRESSED = 0x4E,
    KEY_KEYPAD_1_PRESSED = 0x4F,
    KEY_KEYPAD_2_PRESSED = 0x50,
    KEY_KEYPAD_3_PRESSED = 0x51,
    KEY_KEYPAD_0_PRESSED = 0x52,
    KEY_KEYPAD_PERIOD_PRESSED = 0x53,
    KEY_F11_PRESSED = 0x57,
    KEY_F12_PRESSED = 0x58,

    /* Release key scan codes */
    KEY_ESC_RELEASED = 0x81,
    KEY_1_RELEASED = 0x82,
    KEY_2_RELEASED = 0x83,
    KEY_3_RELEASED = 0x84,
    KEY_4_RELEASED = 0x85,
    KEY_5_RELEASED = 0x86,
    KEY_6_RELEASED = 0x87,
    KEY_7_RELEASED = 0x88,
    KEY_8_RELEASED = 0x89,
    KEY_9_RELEASED = 0x8A,
    KEY_0_RELEASED = 0x8B,
    KEY_MINUS_RELEASED = 0x8C,
    KEY_EQUAL_RELEASED = 0x8D,
    KEY_BACKSPACE_RELEASED = 0x8E,
    KEY_TAB_RELEASED = 0x8F,
    KEY_Q_RELEASED = 0x90,
    KEY_W_RELEASED = 0x91,
    KEY_E_RELEASED = 0x92,
    KEY_R_RELEASED = 0x93,
    KEY_T_RELEASED = 0x94,
    KEY_Y_RELEASED = 0x95,
    KEY_U_RELEASED = 0x96,
    KEY_I_RELEASED = 0x97,
    KEY_O_RELEASED = 0x98,
    KEY_P_RELEASED = 0x99,
    KEY_OPEN_SQUARE_BRACET_RELEASED = 0x9A,
    KEY_CLOSE_SQUARE_BRACET_RELEASED = 0x9B,
    KEY_ENTER_RELEASED = 0x9C,
    KEY_LEFT_CONTROL_RELEASED = 0x9D,
    KEY_A_RELEASED = 0x9E,
    KEY_S_RELEASED = 0x9F,
    KEY_D_RELEASED = 0xA0,
    KEY_F_RELEASED = 0xA1,
    KEY_G_RELEASED = 0xA2,
    KEY_H_RELEASED = 0xA3,
    KEY_J_RELEASED = 0xA4,
    KEY_K_RELEASED = 0xA5,
    KEY_L_RELEASED = 0xA6,
    KEY_SEMICOLON_RELEASED = 0xA7,
    KEY_SINGLE_QUOTE_RELEASED = 0xA8,
    KEY_BACK_TICK_RELEASED = 0xA9,
    KEY_LEFT_SHIFT_RELEASED = 0xAA,
    KEY_BACKSLASH_RELEASED = 0xAB,
    KEY_Z_RELEASED = 0xAC,
    KEY_X_RELEASED = 0xAD,
    KEY_C_RELEASED = 0xAE,
    KEY_V_RELEASED = 0xAF,
    KEY_B_RELEASED = 0xB0,
    KEY_N_RELEASED = 0xB1,
    KEY_M_RELEASED = 0xB2,
    KEY_COMMA_RELEASED = 0xB3,
    KEY_PERIOD_RELEASED = 0xB4,
    KEY_SLASH_RELEASED = 0xB5,
    KEY_RIGHT_SHIFT_RELEASED = 0xB6,
    KEY_KEYPAD_STAR_RELEASED = 0xB7,
    KEY_LEFT_ALT_RELEASED = 0xB8,
    KEY_SPACE_RELEASED = 0xB9,
    KEY_CAPSLOCK_RELEASED = 0xBA,
    KEY_F1_RELEASED = 0xBB,
    KEY_F2_RELEASED = 0xBC,
    KEY_F3_RELEASED = 0xBD,
    KEY_F4_RELEASED = 0xBE,
    KEY_F5_RELEASED = 0xBF,
    KEY_F6_RELEASED = 0xC0,
    KEY_F7_RELEASED = 0xC1,
    KEY_F8_RELEASED = 0xC2,
    KEY_F9_RELEASED = 0xC3,
    KEY_F10_RELEASED = 0xC4,
    KEY_NUMBER_LOCK_RELEASED = 0xC5,
    KEY_SCROLL_RELEASED = 0xC6,
    KEY_KEYPAD_7_RELEASED = 0xC7,
    KEY_KEYPAD_8_RELEASED = 0xC8,
    KEY_KEYPAD_9_RELEASED = 0xC9,
    KEY_KEYPAD_MINUS_RELEASED = 0xCA,
    KEY_KEYPAD_4_RELEASED = 0xCB,
    KEY_KEYPAD_5_RELEASED = 0xCC,
    KEY_KEYPAD_6_RELEASED = 0xCD,
    KEY_KEYPAD_PLUS_RELEASED = 0xCE,
    KEY_KEYPAD_1_RELEASED = 0xCF,
    KEY_KEYPAD_2_RELEASED = 0xD0,
    KEY_KEYPAD_3_RELEASED = 0xD1,
    KEY_KEYPAD_0_RELEASED = 0xD2,
    KEY_KEYPAD_PERIOD_RELEASED = 0xD3,
    KEY_F11_RELEASED = 0xD7,
    KEY_F12_RELEASED = 0xD8,
} KEYBOARD_SCAN_CODE;

typedef enum _KEYBOARD_EXTENDED_SCAN_CODE
{
    /* Press key scan codes */
    KEY_PREVIOUS_TRACK_PRESSED = 0x10,
    KEY_NEXT_TRACK_PRESSED = 0x19,
    KEY_KEYPAD_ENTER_PRESSED = 0x1C,
    KEY_RIGHT_CONTROL_PRESSED = 0x1D,
    KEY_MUTE_PRESSED = 0x20,
    KEY_CALCULATOR_PRESSED = 0x21,
    KEY_PLAY_PRESSED = 0x22,
    KEY_STOP_PRESSED = 0x24,
    KEY_VOLUME_DOWN_PRESSED = 0x2E,
    KEY_VOLUME_UP_PRESSED = 0x30,
    KEY_WWW_HOME_PRESSED = 0x32,
    KEY_KEYPAD_SLASH_PRESSED = 0x35,
    KEY_RIGHT_ALT_PRESSED = 0x38,
    KEY_HOME_PRESSED = 0x47,
    KEY_CURSOR_UP_PRESSED = 0x48,
    KEY_PAGE_UP_PRESSED = 0x49,
    KEY_CURSOR_LEFT_PRESSED = 0x4B,
    KEY_CURSOR_RIGHT_PRESSED = 0x4D,
    KEY_END_PRESSED = 0x4F,
    KEY_CURSOR_DOWN_PRESSED = 0x50,
    KEY_PAGE_DOWN_PRESSED = 0x51,
    KEY_INSERT_PRESSED = 0x52,
    KEY_DELETE_PRESSED = 0x53,
    KEY_LEFT_GUI_PRESSED = 0x5B,
    KEY_RIGHT_GUI_PRESSED = 0x5C,
    KEY_APPS_PRESSED = 0x5D,
    KEY_POWER_PRESSED = 0x5E,
    KEY_SLEEP_PRESSED = 0x5F,
    KEY_WAKE_PRESSED = 0x63,
    KEY_WWW_SEARCH_PRESSED = 0x65,
    KEY_WWW_FAVORITES_PRESSED = 0x66,
    KEY_WWW_REFRESH_PRESSED = 0x67,
    KEY_WWW_STOP_PRESSED = 0x68,
    KEY_WWW_FORWARD_PRESSED = 0x69,
    KEY_WWW_BACK_PRESSED = 0x6A,
    KEY_MY_COMPUTER_PRESSED = 0x6B,
    KEY_EMAIL_PRESSED = 0x6C,
    KEY_MEDIA_SELECT_PRESSED = 0x6D,

    /* Release key scan codes */
    KEY_PREVIOUS_TRACK_RELEASED = 0x90,
    KEY_NEXT_TRACK_RELEASED = 0x99,
    KEY_KEYPAD_ENTER_RELEASED = 0x9C,
    KEY_RIGHT_CONTROL_RELEASED = 0x9D,
    KEY_MUTE_RELEASED = 0xA0,
    KEY_CALCULATOR_RELEASED = 0xA1,
    KEY_PLAY_RELEASED = 0xA2,
    KEY_STOP_RELEASED = 0xA4,
    KEY_VOLUME_DOWN_RELEASED = 0xAE,
    KEY_VOLUME_UP_RELEASED = 0xB0,
    KEY_WWW_HOME_RELEASED = 0xB2,
    KEY_KEYPAD_SLASH_RELEASED = 0xB5,
    KEY_RIGHT_ALT_RELEASED = 0xB8,
    KEY_HOME_RELEASED = 0xC7,
    KEY_CURSOR_UP_RELEASED = 0xC8,
    KEY_PAGE_UP_RELEASED = 0xC9,
    KEY_CURSOR_LEFT_RELEASED = 0xCB,
    KEY_CURSOR_RIGHT_RELEASED = 0xCD,
    KEY_END_RELEASED = 0xCF,
    KEY_CURSOR_DOWN_RELEASED = 0xD0,
    KEY_PAGE_DOWN_RELEASED = 0xD1,
    KEY_INSERT_RELEASED = 0xD2,
    KEY_DELETE_RELEASED = 0xD3,
    KEY_LEFT_GUI_RELEASED = 0xDB,
    KEY_RIGHT_GUI_RELEASED = 0xDC,
    KEY_APPS_RELEASED = 0xDD,
    KEY_POWER_RELEASED = 0xDE,
    KEY_SLEEP_RELEASED = 0xDF,
    KEY_WAKE_RELEASED = 0xE3,
    KEY_WWW_SEARCH_RELEASED = 0xE5,
    KEY_WWW_FAVORITES_RELEASED = 0xE6,
    KEY_WWW_REFRESH_RELEASED = 0xE7,
    KEY_WWW_STOP_RELEASED = 0xE8,
    KEY_WWW_FORWARD_RELEASED = 0xE9,
    KEY_WWW_BACK_RELEASED = 0xEA,
    KEY_MY_COMPUTER_RELEASED = 0xEB,
    KEY_EMAIL_RELEASED = 0xEC,
    KEY_MEDIA_SELECT_RELEASED = 0xED,
} KEYBOARD_EXTENDED_SCAN_CODE;

STATUS API KeyboardScanCodeIsBufferReady(IN CONST UINT8 *ScanCodes, IN CONST UINT64 NumberOfScanCodes, OUT BOOLEAN *Ready)
{
    BOOLEAN IsReady = TRUE;

    if (0 == NumberOfScanCodes)
    {
        IsReady = FALSE;
    }

    if ((1 == NumberOfScanCodes) && (IS_EXTENDED_CODE(ScanCodes[0])))
    {
        IsReady = FALSE;
    }

    if (NumberOfScanCodes >= 2)
    {
        if ((4 != NumberOfScanCodes) &&
            (0xE0 == ScanCodes[0]) &&
            ((PRINT_SCREEN_PRESSED_KEY_CODE_2 == ScanCodes[1] || (PRINT_SCREEN_RELEASED_KEY_CODE_2 == ScanCodes[1]))))
        {
            IsReady = FALSE;
        }

        if ((6 != NumberOfScanCodes) && (0xE1 == ScanCodes[0]))
        {
            IsReady = FALSE;
        }
    }

    *Ready = IsReady;
    return E_OK;
}

STATUS API KeyboardScanCodeGetSystemScanCode(IN CONST UINT8 *ScanCodes, IN CONST UINT64 NumberOfScanCodes, OUT SYSTEM_KEYBOARD_SCAN_CODE *SystemScanCode)
{
    BOOLEAN IsReady = FALSE;
    SYSTEM_KEYBOARD_SCAN_CODE ScanCode = SYSTEM_KEY_INVALID;
    KeyboardScanCodeIsBufferReady(ScanCodes, NumberOfScanCodes, &IsReady);
    if (!IsReady)
    {
        return E_NOT_OK;
    }

    if (1 == NumberOfScanCodes)
    {
        switch (ScanCodes[0])
        {
        /* Press key scan codes */
        case KEY_ESC_PRESSED:
            ScanCode = SYSTEM_KEY_ESC_PRESSED;
            break;
        case KEY_1_PRESSED:
            ScanCode = SYSTEM_KEY_1_PRESSED;
            break;
        case KEY_2_PRESSED:
            ScanCode = SYSTEM_KEY_2_PRESSED;
            break;
        case KEY_3_PRESSED:
            ScanCode = SYSTEM_KEY_3_PRESSED;
            break;
        case KEY_4_PRESSED:
            ScanCode = SYSTEM_KEY_4_PRESSED;
            break;
        case KEY_5_PRESSED:
            ScanCode = SYSTEM_KEY_5_PRESSED;
            break;
        case KEY_6_PRESSED:
            ScanCode = SYSTEM_KEY_6_PRESSED;
            break;
        case KEY_7_PRESSED:
            ScanCode = SYSTEM_KEY_7_PRESSED;
            break;
        case KEY_8_PRESSED:
            ScanCode = SYSTEM_KEY_8_PRESSED;
            break;
        case KEY_9_PRESSED:
            ScanCode = SYSTEM_KEY_9_PRESSED;
            break;
        case KEY_0_PRESSED:
            ScanCode = SYSTEM_KEY_0_PRESSED;
            break;
        case KEY_MINUS_PRESSED:
            ScanCode = SYSTEM_KEY_MINUS_PRESSED;
            break;
        case KEY_EQUAL_PRESSED:
            ScanCode = SYSTEM_KEY_EQUAL_PRESSED;
            break;
        case KEY_BACKSPACE_PRESSED:
            ScanCode = SYSTEM_KEY_BACKSPACE_PRESSED;
            break;
        case KEY_TAB_PRESSED:
            ScanCode = SYSTEM_KEY_TAB_PRESSED;
            break;
        case KEY_Q_PRESSED:
            ScanCode = SYSTEM_KEY_Q_PRESSED;
            break;
        case KEY_W_PRESSED:
            ScanCode = SYSTEM_KEY_W_PRESSED;
            break;
        case KEY_E_PRESSED:
            ScanCode = SYSTEM_KEY_E_PRESSED;
            break;
        case KEY_R_PRESSED:
            ScanCode = SYSTEM_KEY_R_PRESSED;
            break;
        case KEY_T_PRESSED:
            ScanCode = SYSTEM_KEY_T_PRESSED;
            break;
        case KEY_Y_PRESSED:
            ScanCode = SYSTEM_KEY_Y_PRESSED;
            break;
        case KEY_U_PRESSED:
            ScanCode = SYSTEM_KEY_U_PRESSED;
            break;
        case KEY_I_PRESSED:
            ScanCode = SYSTEM_KEY_I_PRESSED;
            break;
        case KEY_O_PRESSED:
            ScanCode = SYSTEM_KEY_O_PRESSED;
            break;
        case KEY_P_PRESSED:
            ScanCode = SYSTEM_KEY_P_PRESSED;
            break;
        case KEY_OPEN_SQUARE_BRACET_PRESSED:
            ScanCode = SYSTEM_KEY_OPEN_SQUARE_BRACET_PRESSED;
            break;
        case KEY_CLOSE_SQUARE_BRACET_PRESSED:
            ScanCode = SYSTEM_KEY_CLOSE_SQUARE_BRACET_PRESSED;
            break;
        case KEY_ENTER_PRESSED:
            ScanCode = SYSTEM_KEY_ENTER_PRESSED;
            break;
        case KEY_LEFT_CONTROL_PRESSED:
            ScanCode = SYSTEM_KEY_LEFT_CONTROL_PRESSED;
            break;
        case KEY_A_PRESSED:
            ScanCode = SYSTEM_KEY_A_PRESSED;
            break;
        case KEY_S_PRESSED:
            ScanCode = SYSTEM_KEY_S_PRESSED;
            break;
        case KEY_D_PRESSED:
            ScanCode = SYSTEM_KEY_D_PRESSED;
            break;
        case KEY_F_PRESSED:
            ScanCode = SYSTEM_KEY_F_PRESSED;
            break;
        case KEY_G_PRESSED:
            ScanCode = SYSTEM_KEY_G_PRESSED;
            break;
        case KEY_H_PRESSED:
            ScanCode = SYSTEM_KEY_H_PRESSED;
            break;
        case KEY_J_PRESSED:
            ScanCode = SYSTEM_KEY_J_PRESSED;
            break;
        case KEY_K_PRESSED:
            ScanCode = SYSTEM_KEY_K_PRESSED;
            break;
        case KEY_L_PRESSED:
            ScanCode = SYSTEM_KEY_L_PRESSED;
            break;
        case KEY_SEMICOLON_PRESSED:
            ScanCode = SYSTEM_KEY_SEMICOLON_PRESSED;
            break;
        case KEY_SINGLE_QUOTE_PRESSED:
            ScanCode = SYSTEM_KEY_SINGLE_QUOTE_PRESSED;
            break;
        case KEY_BACK_TICK_PRESSED:
            ScanCode = SYSTEM_KEY_BACK_TICK_PRESSED;
            break;
        case KEY_LEFT_SHIFT_PRESSED:
            ScanCode = SYSTEM_KEY_LEFT_SHIFT_PRESSED;
            break;
        case KEY_BACKSLASH_PRESSED:
            ScanCode = SYSTEM_KEY_BACKSLASH_PRESSED;
            break;
        case KEY_Z_PRESSED:
            ScanCode = SYSTEM_KEY_Z_PRESSED;
            break;
        case KEY_X_PRESSED:
            ScanCode = SYSTEM_KEY_X_PRESSED;
            break;
        case KEY_C_PRESSED:
            ScanCode = SYSTEM_KEY_C_PRESSED;
            break;
        case KEY_V_PRESSED:
            ScanCode = SYSTEM_KEY_V_PRESSED;
            break;
        case KEY_B_PRESSED:
            ScanCode = SYSTEM_KEY_B_PRESSED;
            break;
        case KEY_N_PRESSED:
            ScanCode = SYSTEM_KEY_N_PRESSED;
            break;
        case KEY_M_PRESSED:
            ScanCode = SYSTEM_KEY_M_PRESSED;
            break;
        case KEY_COMMA_PRESSED:
            ScanCode = SYSTEM_KEY_COMMA_PRESSED;
            break;
        case KEY_PERIOD_PRESSED:
            ScanCode = SYSTEM_KEY_PERIOD_PRESSED;
            break;
        case KEY_SLASH_PRESSED:
            ScanCode = SYSTEM_KEY_SLASH_PRESSED;
            break;
        case KEY_RIGHT_SHIFT_PRESSED:
            ScanCode = SYSTEM_KEY_RIGHT_SHIFT_PRESSED;
            break;
        case KEY_KEYPAD_STAR_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_STAR_PRESSED;
            break;
        case KEY_LEFT_ALT_PRESSED:
            ScanCode = SYSTEM_KEY_LEFT_ALT_PRESSED;
            break;
        case KEY_SPACE_PRESSED:
            ScanCode = SYSTEM_KEY_SPACE_PRESSED;
            break;
        case KEY_CAPSLOCK_PRESSED:
            ScanCode = SYSTEM_KEY_CAPSLOCK_PRESSED;
            break;
        case KEY_F1_PRESSED:
            ScanCode = SYSTEM_KEY_F1_PRESSED;
            break;
        case KEY_F2_PRESSED:
            ScanCode = SYSTEM_KEY_F2_PRESSED;
            break;
        case KEY_F3_PRESSED:
            ScanCode = SYSTEM_KEY_F3_PRESSED;
            break;
        case KEY_F4_PRESSED:
            ScanCode = SYSTEM_KEY_F4_PRESSED;
            break;
        case KEY_F5_PRESSED:
            ScanCode = SYSTEM_KEY_F5_PRESSED;
            break;
        case KEY_F6_PRESSED:
            ScanCode = SYSTEM_KEY_F6_PRESSED;
            break;
        case KEY_F7_PRESSED:
            ScanCode = SYSTEM_KEY_F7_PRESSED;
            break;
        case KEY_F8_PRESSED:
            ScanCode = SYSTEM_KEY_F8_PRESSED;
            break;
        case KEY_F9_PRESSED:
            ScanCode = SYSTEM_KEY_F9_PRESSED;
            break;
        case KEY_F10_PRESSED:
            ScanCode = SYSTEM_KEY_F10_PRESSED;
            break;
        case KEY_NUMBER_LOCK_PRESSED:
            ScanCode = SYSTEM_KEY_NUMBER_LOCK_PRESSED;
            break;
        case KEY_SCROLL_PRESSED:
            ScanCode = SYSTEM_KEY_SCROLL_PRESSED;
            break;
        case KEY_KEYPAD_7_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_7_PRESSED;
            break;
        case KEY_KEYPAD_8_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_8_PRESSED;
            break;
        case KEY_KEYPAD_9_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_9_PRESSED;
            break;
        case KEY_KEYPAD_MINUS_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_MINUS_PRESSED;
            break;
        case KEY_KEYPAD_4_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_4_PRESSED;
            break;
        case KEY_KEYPAD_5_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_5_PRESSED;
            break;
        case KEY_KEYPAD_6_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_6_PRESSED;
            break;
        case KEY_KEYPAD_PLUS_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_PLUS_PRESSED;
            break;
        case KEY_KEYPAD_1_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_1_PRESSED;
            break;
        case KEY_KEYPAD_2_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_2_PRESSED;
            break;
        case KEY_KEYPAD_3_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_3_PRESSED;
            break;
        case KEY_KEYPAD_0_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_0_PRESSED;
            break;
        case KEY_KEYPAD_PERIOD_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_PERIOD_PRESSED;
            break;
        case KEY_F11_PRESSED:
            ScanCode = SYSTEM_KEY_F11_PRESSED;
            break;
        case KEY_F12_PRESSED:
            ScanCode = SYSTEM_KEY_F12_PRESSED;
            break;

        /* Release key scan codes */
        case KEY_ESC_RELEASED:
            ScanCode = SYSTEM_KEY_ESC_RELEASED;
            break;
        case KEY_1_RELEASED:
            ScanCode = SYSTEM_KEY_1_RELEASED;
            break;
        case KEY_2_RELEASED:
            ScanCode = SYSTEM_KEY_2_RELEASED;
            break;
        case KEY_3_RELEASED:
            ScanCode = SYSTEM_KEY_3_RELEASED;
            break;
        case KEY_4_RELEASED:
            ScanCode = SYSTEM_KEY_4_RELEASED;
            break;
        case KEY_5_RELEASED:
            ScanCode = SYSTEM_KEY_5_RELEASED;
            break;
        case KEY_6_RELEASED:
            ScanCode = SYSTEM_KEY_6_RELEASED;
            break;
        case KEY_7_RELEASED:
            ScanCode = SYSTEM_KEY_7_RELEASED;
            break;
        case KEY_8_RELEASED:
            ScanCode = SYSTEM_KEY_8_RELEASED;
            break;
        case KEY_9_RELEASED:
            ScanCode = SYSTEM_KEY_9_RELEASED;
            break;
        case KEY_0_RELEASED:
            ScanCode = SYSTEM_KEY_0_RELEASED;
            break;
        case KEY_MINUS_RELEASED:
            ScanCode = SYSTEM_KEY_MINUS_RELEASED;
            break;
        case KEY_EQUAL_RELEASED:
            ScanCode = SYSTEM_KEY_EQUAL_RELEASED;
            break;
        case KEY_BACKSPACE_RELEASED:
            ScanCode = SYSTEM_KEY_BACKSPACE_RELEASED;
            break;
        case KEY_TAB_RELEASED:
            ScanCode = SYSTEM_KEY_TAB_RELEASED;
            break;
        case KEY_Q_RELEASED:
            ScanCode = SYSTEM_KEY_Q_RELEASED;
            break;
        case KEY_W_RELEASED:
            ScanCode = SYSTEM_KEY_W_RELEASED;
            break;
        case KEY_E_RELEASED:
            ScanCode = SYSTEM_KEY_E_RELEASED;
            break;
        case KEY_R_RELEASED:
            ScanCode = SYSTEM_KEY_R_RELEASED;
            break;
        case KEY_T_RELEASED:
            ScanCode = SYSTEM_KEY_T_RELEASED;
            break;
        case KEY_Y_RELEASED:
            ScanCode = SYSTEM_KEY_Y_RELEASED;
            break;
        case KEY_U_RELEASED:
            ScanCode = SYSTEM_KEY_U_RELEASED;
            break;
        case KEY_I_RELEASED:
            ScanCode = SYSTEM_KEY_I_RELEASED;
            break;
        case KEY_O_RELEASED:
            ScanCode = SYSTEM_KEY_O_RELEASED;
            break;
        case KEY_P_RELEASED:
            ScanCode = SYSTEM_KEY_P_RELEASED;
            break;
        case KEY_OPEN_SQUARE_BRACET_RELEASED:
            ScanCode = SYSTEM_KEY_OPEN_SQUARE_BRACET_RELEASED;
            break;
        case KEY_CLOSE_SQUARE_BRACET_RELEASED:
            ScanCode = SYSTEM_KEY_CLOSE_SQUARE_BRACET_RELEASED;
            break;
        case KEY_ENTER_RELEASED:
            ScanCode = SYSTEM_KEY_ENTER_RELEASED;
            break;
        case KEY_LEFT_CONTROL_RELEASED:
            ScanCode = SYSTEM_KEY_LEFT_CONTROL_RELEASED;
            break;
        case KEY_A_RELEASED:
            ScanCode = SYSTEM_KEY_A_RELEASED;
            break;
        case KEY_S_RELEASED:
            ScanCode = SYSTEM_KEY_S_RELEASED;
            break;
        case KEY_D_RELEASED:
            ScanCode = SYSTEM_KEY_D_RELEASED;
            break;
        case KEY_F_RELEASED:
            ScanCode = SYSTEM_KEY_F_RELEASED;
            break;
        case KEY_G_RELEASED:
            ScanCode = SYSTEM_KEY_G_RELEASED;
            break;
        case KEY_H_RELEASED:
            ScanCode = SYSTEM_KEY_H_RELEASED;
            break;
        case KEY_J_RELEASED:
            ScanCode = SYSTEM_KEY_J_RELEASED;
            break;
        case KEY_K_RELEASED:
            ScanCode = SYSTEM_KEY_K_RELEASED;
            break;
        case KEY_L_RELEASED:
            ScanCode = SYSTEM_KEY_L_RELEASED;
            break;
        case KEY_SEMICOLON_RELEASED:
            ScanCode = SYSTEM_KEY_SEMICOLON_RELEASED;
            break;
        case KEY_SINGLE_QUOTE_RELEASED:
            ScanCode = SYSTEM_KEY_SINGLE_QUOTE_RELEASED;
            break;
        case KEY_BACK_TICK_RELEASED:
            ScanCode = SYSTEM_KEY_BACK_TICK_RELEASED;
            break;
        case KEY_LEFT_SHIFT_RELEASED:
            ScanCode = SYSTEM_KEY_LEFT_SHIFT_RELEASED;
            break;
        case KEY_BACKSLASH_RELEASED:
            ScanCode = SYSTEM_KEY_BACKSLASH_RELEASED;
            break;
        case KEY_Z_RELEASED:
            ScanCode = SYSTEM_KEY_Z_RELEASED;
            break;
        case KEY_X_RELEASED:
            ScanCode = SYSTEM_KEY_X_RELEASED;
            break;
        case KEY_C_RELEASED:
            ScanCode = SYSTEM_KEY_C_RELEASED;
            break;
        case KEY_V_RELEASED:
            ScanCode = SYSTEM_KEY_V_RELEASED;
            break;
        case KEY_B_RELEASED:
            ScanCode = SYSTEM_KEY_B_RELEASED;
            break;
        case KEY_N_RELEASED:
            ScanCode = SYSTEM_KEY_N_RELEASED;
            break;
        case KEY_M_RELEASED:
            ScanCode = SYSTEM_KEY_M_RELEASED;
            break;
        case KEY_COMMA_RELEASED:
            ScanCode = SYSTEM_KEY_COMMA_RELEASED;
            break;
        case KEY_PERIOD_RELEASED:
            ScanCode = SYSTEM_KEY_PERIOD_RELEASED;
            break;
        case KEY_SLASH_RELEASED:
            ScanCode = SYSTEM_KEY_SLASH_RELEASED;
            break;
        case KEY_RIGHT_SHIFT_RELEASED:
            ScanCode = SYSTEM_KEY_RIGHT_SHIFT_RELEASED;
            break;
        case KEY_KEYPAD_STAR_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_STAR_RELEASED;
            break;
        case KEY_LEFT_ALT_RELEASED:
            ScanCode = SYSTEM_KEY_LEFT_ALT_RELEASED;
            break;
        case KEY_SPACE_RELEASED:
            ScanCode = SYSTEM_KEY_SPACE_RELEASED;
            break;
        case KEY_CAPSLOCK_RELEASED:
            ScanCode = SYSTEM_KEY_CAPSLOCK_RELEASED;
            break;
        case KEY_F1_RELEASED:
            ScanCode = SYSTEM_KEY_F1_RELEASED;
            break;
        case KEY_F2_RELEASED:
            ScanCode = SYSTEM_KEY_F2_RELEASED;
            break;
        case KEY_F3_RELEASED:
            ScanCode = SYSTEM_KEY_F3_RELEASED;
            break;
        case KEY_F4_RELEASED:
            ScanCode = SYSTEM_KEY_F4_RELEASED;
            break;
        case KEY_F5_RELEASED:
            ScanCode = SYSTEM_KEY_F5_RELEASED;
            break;
        case KEY_F6_RELEASED:
            ScanCode = SYSTEM_KEY_F6_RELEASED;
            break;
        case KEY_F7_RELEASED:
            ScanCode = SYSTEM_KEY_F7_RELEASED;
            break;
        case KEY_F8_RELEASED:
            ScanCode = SYSTEM_KEY_F8_RELEASED;
            break;
        case KEY_F9_RELEASED:
            ScanCode = SYSTEM_KEY_F9_RELEASED;
            break;
        case KEY_F10_RELEASED:
            ScanCode = SYSTEM_KEY_F10_RELEASED;
            break;
        case KEY_NUMBER_LOCK_RELEASED:
            ScanCode = SYSTEM_KEY_NUMBER_LOCK_RELEASED;
            break;
        case KEY_SCROLL_RELEASED:
            ScanCode = SYSTEM_KEY_SCROLL_RELEASED;
            break;
        case KEY_KEYPAD_7_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_7_RELEASED;
            break;
        case KEY_KEYPAD_8_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_8_RELEASED;
            break;
        case KEY_KEYPAD_9_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_9_RELEASED;
            break;
        case KEY_KEYPAD_MINUS_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_MINUS_RELEASED;
            break;
        case KEY_KEYPAD_4_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_4_RELEASED;
            break;
        case KEY_KEYPAD_5_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_5_RELEASED;
            break;
        case KEY_KEYPAD_6_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_6_RELEASED;
            break;
        case KEY_KEYPAD_PLUS_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_PLUS_RELEASED;
            break;
        case KEY_KEYPAD_1_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_1_RELEASED;
            break;
        case KEY_KEYPAD_2_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_2_RELEASED;
            break;
        case KEY_KEYPAD_3_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_3_RELEASED;
            break;
        case KEY_KEYPAD_0_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_0_RELEASED;
            break;
        case KEY_KEYPAD_PERIOD_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_PERIOD_RELEASED;
            break;
        case KEY_F11_RELEASED:
            ScanCode = SYSTEM_KEY_F11_RELEASED;
            break;
        case KEY_F12_RELEASED:
            ScanCode = SYSTEM_KEY_F12_RELEASED;
            break;

        /* Unkown key scan code */
        default:
            ScanCode = SYSTEM_KEY_INVALID;
            break;
        }
    }
    else if ((2 == NumberOfScanCodes) && (IS_EXTENDED_CODE(ScanCodes[0])))
    {
        switch (ScanCodes[1])
        {
        /* Press key scan codes */
        case KEY_PREVIOUS_TRACK_PRESSED:
            ScanCode = SYSTEM_KEY_PREVIOUS_TRACK_PRESSED;
            break;
        case KEY_NEXT_TRACK_PRESSED:
            ScanCode = SYSTEM_KEY_NEXT_TRACK_PRESSED;
            break;
        case KEY_KEYPAD_ENTER_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_ENTER_PRESSED;
            break;
        case KEY_RIGHT_CONTROL_PRESSED:
            ScanCode = SYSTEM_KEY_RIGHT_CONTROL_PRESSED;
            break;
        case KEY_MUTE_PRESSED:
            ScanCode = SYSTEM_KEY_MUTE_PRESSED;
            break;
        case KEY_CALCULATOR_PRESSED:
            ScanCode = SYSTEM_KEY_CALCULATOR_PRESSED;
            break;
        case KEY_PLAY_PRESSED:
            ScanCode = SYSTEM_KEY_PLAY_PRESSED;
            break;
        case KEY_STOP_PRESSED:
            ScanCode = SYSTEM_KEY_STOP_PRESSED;
            break;
        case KEY_VOLUME_DOWN_PRESSED:
            ScanCode = SYSTEM_KEY_VOLUME_DOWN_PRESSED;
            break;
        case KEY_VOLUME_UP_PRESSED:
            ScanCode = SYSTEM_KEY_VOLUME_UP_PRESSED;
            break;
        case KEY_WWW_HOME_PRESSED:
            ScanCode = SYSTEM_KEY_WWW_HOME_PRESSED;
            break;
        case KEY_KEYPAD_SLASH_PRESSED:
            ScanCode = SYSTEM_KEY_KEYPAD_SLASH_PRESSED;
            break;
        case KEY_RIGHT_ALT_PRESSED:
            ScanCode = SYSTEM_KEY_RIGHT_ALT_PRESSED;
            break;
        case KEY_HOME_PRESSED:
            ScanCode = SYSTEM_KEY_HOME_PRESSED;
            break;
        case KEY_CURSOR_UP_PRESSED:
            ScanCode = SYSTEM_KEY_CURSOR_UP_PRESSED;
            break;
        case KEY_PAGE_UP_PRESSED:
            ScanCode = SYSTEM_KEY_PAGE_UP_PRESSED;
            break;
        case KEY_CURSOR_LEFT_PRESSED:
            ScanCode = SYSTEM_KEY_CURSOR_LEFT_PRESSED;
            break;
        case KEY_CURSOR_RIGHT_PRESSED:
            ScanCode = SYSTEM_KEY_CURSOR_RIGHT_PRESSED;
            break;
        case KEY_END_PRESSED:
            ScanCode = SYSTEM_KEY_END_PRESSED;
            break;
        case KEY_CURSOR_DOWN_PRESSED:
            ScanCode = SYSTEM_KEY_CURSOR_DOWN_PRESSED;
            break;
        case KEY_PAGE_DOWN_PRESSED:
            ScanCode = SYSTEM_KEY_PAGE_DOWN_PRESSED;
            break;
        case KEY_INSERT_PRESSED:
            ScanCode = SYSTEM_KEY_INSERT_PRESSED;
            break;
        case KEY_DELETE_PRESSED:
            ScanCode = SYSTEM_KEY_DELETE_PRESSED;
            break;
        case KEY_LEFT_GUI_PRESSED:
            ScanCode = SYSTEM_KEY_LEFT_GUI_PRESSED;
            break;
        case KEY_RIGHT_GUI_PRESSED:
            ScanCode = SYSTEM_KEY_RIGHT_GUI_PRESSED;
            break;
        case KEY_APPS_PRESSED:
            ScanCode = SYSTEM_KEY_APPS_PRESSED;
            break;
        case KEY_POWER_PRESSED:
            ScanCode = SYSTEM_KEY_POWER_PRESSED;
            break;
        case KEY_SLEEP_PRESSED:
            ScanCode = SYSTEM_KEY_SLEEP_PRESSED;
            break;
        case KEY_WAKE_PRESSED:
            ScanCode = SYSTEM_KEY_WAKE_PRESSED;
            break;
        case KEY_WWW_SEARCH_PRESSED:
            ScanCode = SYSTEM_KEY_WWW_SEARCH_PRESSED;
            break;
        case KEY_WWW_FAVORITES_PRESSED:
            ScanCode = SYSTEM_KEY_WWW_FAVORITES_PRESSED;
            break;
        case KEY_WWW_REFRESH_PRESSED:
            ScanCode = SYSTEM_KEY_WWW_REFRESH_PRESSED;
            break;
        case KEY_WWW_STOP_PRESSED:
            ScanCode = SYSTEM_KEY_WWW_STOP_PRESSED;
            break;
        case KEY_WWW_FORWARD_PRESSED:
            ScanCode = SYSTEM_KEY_WWW_FORWARD_PRESSED;
            break;
        case KEY_WWW_BACK_PRESSED:
            ScanCode = SYSTEM_KEY_WWW_BACK_PRESSED;
            break;
        case KEY_MY_COMPUTER_PRESSED:
            ScanCode = SYSTEM_KEY_MY_COMPUTER_PRESSED;
            break;
        case KEY_EMAIL_PRESSED:
            ScanCode = SYSTEM_KEY_EMAIL_PRESSED;
            break;
        case KEY_MEDIA_SELECT_PRESSED:
            ScanCode = SYSTEM_KEY_MEDIA_SELECT_PRESSED;
            break;

        /* Release key scan codes */
        case KEY_PREVIOUS_TRACK_RELEASED:
            ScanCode = SYSTEM_KEY_PREVIOUS_TRACK_RELEASED;
            break;
        case KEY_NEXT_TRACK_RELEASED:
            ScanCode = SYSTEM_KEY_NEXT_TRACK_RELEASED;
            break;
        case KEY_KEYPAD_ENTER_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_ENTER_RELEASED;
            break;
        case KEY_RIGHT_CONTROL_RELEASED:
            ScanCode = SYSTEM_KEY_RIGHT_CONTROL_RELEASED;
            break;
        case KEY_MUTE_RELEASED:
            ScanCode = SYSTEM_KEY_MUTE_RELEASED;
            break;
        case KEY_CALCULATOR_RELEASED:
            ScanCode = SYSTEM_KEY_CALCULATOR_RELEASED;
            break;
        case KEY_PLAY_RELEASED:
            ScanCode = SYSTEM_KEY_PLAY_RELEASED;
            break;
        case KEY_STOP_RELEASED:
            ScanCode = SYSTEM_KEY_STOP_RELEASED;
            break;
        case KEY_VOLUME_DOWN_RELEASED:
            ScanCode = SYSTEM_KEY_VOLUME_DOWN_RELEASED;
            break;
        case KEY_VOLUME_UP_RELEASED:
            ScanCode = SYSTEM_KEY_VOLUME_UP_RELEASED;
            break;
        case KEY_WWW_HOME_RELEASED:
            ScanCode = SYSTEM_KEY_WWW_HOME_RELEASED;
            break;
        case KEY_KEYPAD_SLASH_RELEASED:
            ScanCode = SYSTEM_KEY_KEYPAD_SLASH_RELEASED;
            break;
        case KEY_RIGHT_ALT_RELEASED:
            ScanCode = SYSTEM_KEY_RIGHT_ALT_RELEASED;
            break;
        case KEY_HOME_RELEASED:
            ScanCode = SYSTEM_KEY_HOME_RELEASED;
            break;
        case KEY_CURSOR_UP_RELEASED:
            ScanCode = SYSTEM_KEY_CURSOR_UP_RELEASED;
            break;
        case KEY_PAGE_UP_RELEASED:
            ScanCode = SYSTEM_KEY_PAGE_UP_RELEASED;
            break;
        case KEY_CURSOR_LEFT_RELEASED:
            ScanCode = SYSTEM_KEY_CURSOR_LEFT_RELEASED;
            break;
        case KEY_CURSOR_RIGHT_RELEASED:
            ScanCode = SYSTEM_KEY_CURSOR_RIGHT_RELEASED;
            break;
        case KEY_END_RELEASED:
            ScanCode = SYSTEM_KEY_END_RELEASED;
            break;
        case KEY_CURSOR_DOWN_RELEASED:
            ScanCode = SYSTEM_KEY_CURSOR_DOWN_RELEASED;
            break;
        case KEY_PAGE_DOWN_RELEASED:
            ScanCode = SYSTEM_KEY_PAGE_DOWN_RELEASED;
            break;
        case KEY_INSERT_RELEASED:
            ScanCode = SYSTEM_KEY_INSERT_RELEASED;
            break;
        case KEY_DELETE_RELEASED:
            ScanCode = SYSTEM_KEY_DELETE_RELEASED;
            break;
        case KEY_LEFT_GUI_RELEASED:
            ScanCode = SYSTEM_KEY_LEFT_GUI_RELEASED;
            break;
        case KEY_RIGHT_GUI_RELEASED:
            ScanCode = SYSTEM_KEY_RIGHT_GUI_RELEASED;
            break;
        case KEY_APPS_RELEASED:
            ScanCode = SYSTEM_KEY_APPS_RELEASED;
            break;
        case KEY_POWER_RELEASED:
            ScanCode = SYSTEM_KEY_POWER_RELEASED;
            break;
        case KEY_SLEEP_RELEASED:
            ScanCode = SYSTEM_KEY_SLEEP_RELEASED;
            break;
        case KEY_WAKE_RELEASED:
            ScanCode = SYSTEM_KEY_WAKE_RELEASED;
            break;
        case KEY_WWW_SEARCH_RELEASED:
            ScanCode = SYSTEM_KEY_WWW_SEARCH_RELEASED;
            break;
        case KEY_WWW_FAVORITES_RELEASED:
            ScanCode = SYSTEM_KEY_WWW_FAVORITES_RELEASED;
            break;
        case KEY_WWW_REFRESH_RELEASED:
            ScanCode = SYSTEM_KEY_WWW_REFRESH_RELEASED;
            break;
        case KEY_WWW_STOP_RELEASED:
            ScanCode = SYSTEM_KEY_WWW_STOP_RELEASED;
            break;
        case KEY_WWW_FORWARD_RELEASED:
            ScanCode = SYSTEM_KEY_WWW_FORWARD_RELEASED;
            break;
        case KEY_WWW_BACK_RELEASED:
            ScanCode = SYSTEM_KEY_WWW_BACK_RELEASED;
            break;
        case KEY_MY_COMPUTER_RELEASED:
            ScanCode = SYSTEM_KEY_MY_COMPUTER_RELEASED;
            break;
        case KEY_EMAIL_RELEASED:
            ScanCode = SYSTEM_KEY_EMAIL_RELEASED;
            break;
        case KEY_MEDIA_SELECT_RELEASED:
            ScanCode = SYSTEM_KEY_MEDIA_SELECT_RELEASED;

        /* Unkown scan code */
        default:
            ScanCode = SYSTEM_KEY_INVALID;
            break;
        }
    }
    else if (4 == NumberOfScanCodes)
    {
        if ((PRINT_SCREEN_PRESSED_KEY_CODE_1 == ScanCodes[0]) && (PRINT_SCREEN_PRESSED_KEY_CODE_2 == ScanCodes[1]) &&
            (PRINT_SCREEN_PRESSED_KEY_CODE_3 == ScanCodes[2]) && (PRINT_SCREEN_PRESSED_KEY_CODE_4 == ScanCodes[3]))
        {
            ScanCode = SYSTEM_KEY_PRINT_SCREEN_PRESSED;
        }

        if ((PRINT_SCREEN_RELEASED_KEY_CODE_1 == ScanCodes[0]) && (PRINT_SCREEN_RELEASED_KEY_CODE_2 == ScanCodes[1]) &&
            (PRINT_SCREEN_RELEASED_KEY_CODE_3 == ScanCodes[2]) && (PRINT_SCREEN_RELEASED_KEY_CODE_4 == ScanCodes[3]))
        {
            ScanCode = SYSTEM_KEY_PRINT_SCREEN_RELEASED;
        }
    }
    else if (6 == NumberOfScanCodes)
    {
        if ((PAUSE_PRESSED_KEY_CODE_1 == ScanCodes[0]) && (PAUSE_PRESSED_KEY_CODE_2 == ScanCodes[1]) &&
            (PAUSE_PRESSED_KEY_CODE_3 == ScanCodes[2]) && (PAUSE_PRESSED_KEY_CODE_4 == ScanCodes[3]) &&
            (PAUSE_PRESSED_KEY_CODE_5 == ScanCodes[4]) && (PAUSE_PRESSED_KEY_CODE_6 == ScanCodes[5]))
        {
            ScanCode = SYSTEM_KEY_PAUSE_PRESSED;
        }
    }

    *SystemScanCode = ScanCode;
    return E_OK;
}

#endif
