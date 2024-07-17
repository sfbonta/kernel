#ifndef _SYSTEM_VIDEO_H_
#define _SYSTEM_VIDEO_H_

#include "platform_types.h"
#include "video_adapter_types.h"
#include "application_view.h"

STATUS API SystemVideoInit(IN CONST VIDEO_ADAPTER* VideoAdapter);

STATUS API SystemVideoRegisterApplicationView(IN CONST APPLICATION_VIEW* ApplicationView);

STATUS API SystemVideoRedraw(VOID);

#endif /* _SYSTEM_VIDEO_H_ */
