#include "console_controller.h"

#include "system_physical_memory.h"
#include "system_fonts.h"

#define DEFAULT_CONSOLE_BACKGROUND_COLOR 0x00000000
#define DEFAULT_CONSOLE_TEXT_COLOR 0x00FFFFFF

#define LETTER_WIDTH 10
#define LETTER_HEIGTH 20

STATUS API ConsoleControllerSetBackgroundColor(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN UINT32 Color);

STATUS API ConsoleControllerSetTextColor(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN UINT32 Color);

STATUS API ConsoleControllerFlush(
    IN CONSOLE_CONTROLLER *ConsoleController);

STATUS API ConsoleControllerPrintText(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN CONST CHAR16 *Text);

STATUS API ConsoleControllerInit(
    IN CONST UINT64 PositionX,
    IN CONST UINT64 PositionY,
    IN CONST UINT64 Width,
    IN CONST UINT64 Heigth,
    OUT CONSOLE_CONTROLLER **ConsoleController)
{
    STATUS Status = E_OK;
    CONSOLE_CONTROLLER *ConsoleControllerOutput = NULL_PTR;

    if (NULL_PTR == ConsoleController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    if (NULL_PTR != *ConsoleController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    SystemPhysicalMemoryAllocatePool((VOID **)&ConsoleControllerOutput, sizeof(*ConsoleControllerOutput));
    if (NULL_PTR == ConsoleControllerOutput)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ConsoleControllerOutput->Internal = NULL_PTR;
    SystemPhysicalMemoryAllocatePool((VOID **)&ConsoleControllerOutput->Internal, sizeof(*ConsoleControllerOutput->Internal));
    if (NULL_PTR == ConsoleControllerOutput->Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ConsoleControllerOutput->Internal->ApplicationView = NULL_PTR;
    ApplicationViewInit(PositionX, PositionY, Width, Heigth, &ConsoleControllerOutput->Internal->ApplicationView);
    if (NULL_PTR == ConsoleControllerOutput->Internal->ApplicationView)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ConsoleControllerOutput->Internal->PositionX = 0;
    ConsoleControllerOutput->Internal->PositionY = 0;
    ConsoleControllerOutput->Internal->BackgroundColor = DEFAULT_CONSOLE_BACKGROUND_COLOR;
    ConsoleControllerOutput->Internal->TextColor = DEFAULT_CONSOLE_TEXT_COLOR;
    ConsoleControllerOutput->SetBackgroundColor = ConsoleControllerSetBackgroundColor;
    ConsoleControllerOutput->SetTextColor = ConsoleControllerSetTextColor;
    ConsoleControllerOutput->Flush = ConsoleControllerFlush;
    ConsoleControllerOutput->PrintText = ConsoleControllerPrintText;

Cleanup:
    *ConsoleController = ConsoleControllerOutput;
    return Status;
}

STATUS API ConsoleControllerSetBackgroundColor(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN UINT32 Color)
{
    STATUS Status = E_OK;
    CONSOLE_CONTROLLER_INTERNAL *Internal = NULL_PTR;

    if (NULL_PTR == ConsoleController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = ConsoleController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal->BackgroundColor = Color;

Cleanup:
    return Status;
}

STATUS API ConsoleControllerSetTextColor(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN UINT32 Color)
{
    STATUS Status = E_OK;
    CONSOLE_CONTROLLER_INTERNAL *Internal = NULL_PTR;

    if (NULL_PTR == ConsoleController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = ConsoleController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal->TextColor = Color;

Cleanup:
    return Status;
}

STATUS API ConsoleControllerFlush(
    IN CONSOLE_CONTROLLER *ConsoleController)
{
    STATUS Status = E_OK;
    CONSOLE_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    APPLICATION_VIEW *ApplicationView = NULL_PTR;

    if (NULL_PTR == ConsoleController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = ConsoleController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationView = Internal->ApplicationView;
    if (NULL_PTR == ApplicationView)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationView->FillBackground(ApplicationView, Internal->BackgroundColor);

Cleanup:
    return Status;
}

STATUS API ConsoleControllerPrintText(
    IN CONSOLE_CONTROLLER *ConsoleController,
    IN CONST CHAR16 *Text)
{
    STATUS Status = E_OK;
    CONSOLE_CONTROLLER_INTERNAL *Internal = NULL_PTR;
    APPLICATION_VIEW *ApplicationView = NULL_PTR;
    HII_LETTER_BITMAP *HiiLetterBitmap = NULL_PTR;

    if (NULL_PTR == ConsoleController)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    Internal = ConsoleController->Internal;
    if (NULL_PTR == Internal)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationView = Internal->ApplicationView;
    if (NULL_PTR == ApplicationView)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; u'\0' != Text[i]; ++i)
    {
        if (u'\n' != Text[i])
        {
            HiiLetterBitmap = NULL_PTR;
            SystemFontsGetBitmap(Text[i], &HiiLetterBitmap);

            if (NULL_PTR != HiiLetterBitmap)
            {
                ApplicationView->DrawHiiLetterBitmap(ApplicationView,
                                                     Internal->PositionX,
                                                     Internal->PositionY,
                                                     Internal->BackgroundColor,
                                                     Internal->TextColor,
                                                     HiiLetterBitmap);

                Internal->PositionX += LETTER_WIDTH;
            }
        }
        else
        {
            Internal->PositionY += LETTER_HEIGTH;
            Internal->PositionX = 0;
        }
    }

    ApplicationView->NotifyCallback();

Cleanup:
    return Status;
}
