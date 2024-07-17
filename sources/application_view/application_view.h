#ifndef _APPLICATION_VIEW_CONTROLLER_H_
#define _APPLICATION_VIEW_CONTROLLER_H_

#include "platform_types.h"
#include "hii_loader_types.h"

typedef struct _APPLICATION_VIEW APPLICATION_VIEW;

typedef STATUS(API *APPLICATION_VIEW_FILL_BACKGROUND)(
    IN APPLICATION_VIEW *ApplicationView,
    IN UINT32 Color);

typedef STATUS(API *APPLICATION_VIEW_DRAW_HII_LETTER_BITMAP)(
    IN APPLICATION_VIEW *ApplicationView,
    IN CONST UINT64 PositionX,
    IN CONST UINT64 PositionY,
    IN CONST UINT32 BackgroundColor,
    IN CONST UINT32 TextColor,
    IN CONST HII_LETTER_BITMAP *HiiLetterBitmap);

typedef struct _APPLICATION_VIEW
{
    APPLICATION_VIEW_INFO *Info;
    NOTIFY_CALLBACK NotifyCallback;
    APPLICATION_VIEW_FILL_BACKGROUND FillBackground;
    APPLICATION_VIEW_DRAW_HII_LETTER_BITMAP DrawHiiLetterBitmap;
} APPLICATION_VIEW;

STATUS API ApplicationViewInit(
    IN UINT64 PositionX,
    IN UINT64 PositionY,
    IN UINT64 Width,
    IN UINT64 Height,
    OUT APPLICATION_VIEW **ApplicationView);

#endif /* _APPLICATION_VIEW_CONTROLLER_H_ */
