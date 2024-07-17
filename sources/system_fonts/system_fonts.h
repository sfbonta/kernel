#ifndef _SYSTEM_FONTS_H_
#define _SYSTEM_FONTS_H_

#include "platform_types.h"
#include "hii_loader_types.h"

STATUS API SystemFontsInit(IN CONST HII_CHARACTERS* HiiCharaters);

STATUS API SystemFontsGetBitmap(IN CONST CHAR16 Character, OUT HII_LETTER_BITMAP** LetterBitmap);

#endif /* _SYSTEM_FONTS_H_ */
