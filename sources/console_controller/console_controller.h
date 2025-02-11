#ifndef _CONSOLE_CONTROLLER_H_
#define _CONSOLE_CONTROLLER_H_

#include "platform_types.h"
#include "application_view.h"

typedef struct _CONSOLE_CONTROLLER_INTERNAL
{
    UINT64 PositionX;
    UINT64 PositionY;
    UINT32 BackgroundColor;
    UINT32 TextColor;
    APPLICATION_VIEW *ApplicationView;
} CONSOLE_CONTROLLER_INTERNAL;

typedef struct _CONSOLE_CONTROLLER CONSOLE_CONTROLLER;

typedef STATUS(API *CONSOLE_CONTROLLER_SET_BACKGROUND_COLOR)(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN UINT32 Color);

typedef STATUS(API *CONSOLE_CONTROLLER_SET_TEXT_COLOR)(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN UINT32 Color);

typedef STATUS(API *CONSOLE_CONTROLLER_FLUSH)(
    IN CONSOLE_CONTROLLER *ConsoleController);

typedef STATUS(API *CONSOLE_CONTROLLER_PRINT_TEXT)(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN CONST CHAR16 *Text);

typedef struct _CONSOLE_CONTROLLER
{
    CONSOLE_CONTROLLER_INTERNAL *Internal;
    CONSOLE_CONTROLLER_SET_BACKGROUND_COLOR SetBackgroundColor;
    CONSOLE_CONTROLLER_SET_TEXT_COLOR SetTextColor;
    CONSOLE_CONTROLLER_FLUSH Flush;
    CONSOLE_CONTROLLER_PRINT_TEXT PrintText;
} CONSOLE_CONTROLLER;

STATUS API ConsoleControllerInit(
    IN CONST UINT64 PositionX,
    IN CONST UINT64 PositionY,
    IN CONST UINT64 Width,
    IN CONST UINT64 Heigth,
    OUT CONSOLE_CONTROLLER **ConsoleController);

#endif /* _CONSOLE_CONTROLLER_H_ */
