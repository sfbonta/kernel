#include "system_fonts.h"

static CONST HII_CHARACTERS *Characters;

STATUS API SystemFontsInit(IN CONST HII_CHARACTERS *HiiCharaters)
{
    Characters = HiiCharaters;
    return E_OK;
}

STATUS API SystemFontsGetBitmap(IN CONST CHAR16 Character, OUT HII_LETTER_BITMAP **LetterBitmap)
{
    if (Character < 255)
    {
        *LetterBitmap = (HII_LETTER_BITMAP *)&Characters->Letters[Character];
    }
    else
    {
        *LetterBitmap = (HII_LETTER_BITMAP *)&Characters->Letters[u' '];
    }
    return E_OK;
}
