#include "application_view.h"

#include "system_memory.h"
#include "system_video.h"
#include "utils.h"

STATUS API ApplicationViewFillBackground(
    IN APPLICATION_VIEW *ApplicationView,
    IN UINT32 Color);

STATUS API ApplicationViewDrawHiiLetterBitmap(
    IN APPLICATION_VIEW *ApplicationView,
    IN CONST UINT64 PositionX,
    IN CONST UINT64 PositionY,
    IN CONST UINT32 BackgroundColor,
    IN CONST UINT32 TextColor,
    IN CONST HII_LETTER_BITMAP *HiiLetterBitmap);

STATUS API ApplicationViewInit(
    IN UINT64 PositionX,
    IN UINT64 PositionY,
    IN UINT64 Width,
    IN UINT64 Height,
    OUT APPLICATION_VIEW **ApplicationView)
{
    STATUS Status = E_OK;
    APPLICATION_VIEW *ApplicationViewOutput = NULL_PTR;

    if (NULL_PTR == ApplicationView)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    if (NULL_PTR != *ApplicationView)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    MemoryAllocatePool((VOID **)&ApplicationViewOutput, sizeof(*ApplicationViewOutput));
    if (NULL_PTR == ApplicationViewOutput)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationViewOutput->Info = NULL_PTR;
    MemoryAllocatePool((VOID **)&ApplicationViewOutput->Info, sizeof(*ApplicationViewOutput->Info));
    if (NULL_PTR == ApplicationViewOutput->Info)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationViewOutput->Info->FrameBuffer = NULL_PTR;
    MemoryAllocatePool((VOID **)&ApplicationViewOutput->Info->FrameBuffer, Width * Height * sizeof(*ApplicationViewOutput->Info->FrameBuffer));
    if (NULL_PTR == ApplicationViewOutput->Info->FrameBuffer)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationViewOutput->Info->PositionX = PositionX;
    ApplicationViewOutput->Info->PositionY = PositionY;
    ApplicationViewOutput->Info->Width = Width;
    ApplicationViewOutput->Info->Height = Height;
    for (UINT64 i = 0; i < ApplicationViewOutput->Info->Width * ApplicationViewOutput->Info->Height; ++i)
    {
        ApplicationViewOutput->Info->FrameBuffer[i] = 0x00969696;
    }
    ApplicationViewOutput->NotifyCallback = SystemVideoRedraw;
    ApplicationViewOutput->FillBackground = ApplicationViewFillBackground;
    ApplicationViewOutput->DrawHiiLetterBitmap = ApplicationViewDrawHiiLetterBitmap;
    SystemVideoRegisterApplicationView(ApplicationViewOutput);

Cleanup:
    if (E_OK != Status)
    {
        if (NULL_PTR != ApplicationViewOutput)
        {
            if (NULL_PTR != ApplicationViewOutput->Info)
            {
                if (NULL_PTR != ApplicationViewOutput->Info->FrameBuffer)
                {
                    MemoryFreePool((VOID **)&ApplicationViewOutput->Info->FrameBuffer);
                    ApplicationViewOutput->Info->FrameBuffer = NULL_PTR;
                }

                MemoryFreePool((VOID **)&ApplicationViewOutput->Info);
                ApplicationViewOutput->Info = NULL_PTR;
            }
            MemoryFreePool((VOID **)&ApplicationViewOutput);
            ApplicationViewOutput = NULL_PTR;
        }
    }

    *ApplicationView = ApplicationViewOutput;
    return Status;
}

STATUS API ApplicationViewFillBackground(
    IN APPLICATION_VIEW *ApplicationView,
    IN UINT32 Color)
{
    STATUS Status = E_OK;
    APPLICATION_VIEW_INFO *ApplicationViewInfo = NULL_PTR;

    if (NULL_PTR == ApplicationView)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationViewInfo = ApplicationView->Info;
    if (NULL_PTR == ApplicationViewInfo)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    if (NULL_PTR == ApplicationViewInfo->FrameBuffer)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    for (UINT64 i = 0; i < ApplicationViewInfo->Width * ApplicationViewInfo->Height; ++i)
    {
        ApplicationViewInfo->FrameBuffer[i] = Color;
    }
    SystemVideoRedraw();

Cleanup:
    return Status;
}

STATUS API ApplicationViewDrawHiiLetterBitmap(
    IN APPLICATION_VIEW *ApplicationView,
    IN CONST UINT64 PositionX,
    IN CONST UINT64 PositionY,
    IN CONST UINT32 BackgroundColor,
    IN CONST UINT32 TextColor,
    IN CONST HII_LETTER_BITMAP *HiiLetterBitmap)
{
    STATUS Status = E_OK;
    APPLICATION_VIEW_INFO *ApplicationViewInfo = NULL_PTR;
    UINT64 DisplaysXy = 0;
    UINT64 ViewPixelBufferIndex = 0;

    if (NULL_PTR == ApplicationView)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    ApplicationViewInfo = ApplicationView->Info;
    if (NULL_PTR == ApplicationViewInfo)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    if (NULL_PTR == ApplicationViewInfo->FrameBuffer)
    {
        Status = E_NOT_OK;
        goto Cleanup;
    }

    DisplaysXy = PositionY * ApplicationViewInfo->Width + PositionX;
    for (UINT64 i = 0; i < HiiLetterBitmap->LetterHeight; ++i)
    {
        for (UINT64 j = 0; j < HiiLetterBitmap->LetterWidth; ++j)
        {
            UINT8 BitmapColor = HiiLetterBitmap->LetterBuffer[ViewPixelBufferIndex++];
            UINT32 Color = 0;
            if (0 == BitmapColor)
            {
                Color = BackgroundColor;
            }
            else
            {
                Color = TextColor;
            }
            ApplicationViewInfo->FrameBuffer[DisplaysXy + j] = Color;
        }
        DisplaysXy += ApplicationViewInfo->Width;
    }

Cleanup:
    return Status;
}
