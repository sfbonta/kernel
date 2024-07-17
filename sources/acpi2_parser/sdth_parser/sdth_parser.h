#ifndef _STDH_PARSER_H_
#define _STDH_PARSER_H_

#include "platform_types.h"
#include "system_configuration_table.h"

typedef struct _SYSTEM_DESCRIPTION_TABLE_HEADER
{
    CHAR8 Signature[4];
    UINT32 Length;
    UINT8 Revision;
    UINT8 Checksum;
    CHAR8 OemId[6];
    CHAR8 OemTabelId[8];
    UINT32 OemRevision;
    UINT32 CreatorId;
    UINT32 CreatorRevision;
} PACKED SYSTEM_DESCRIPTION_TABLE_HEADER;

STATUS API SdthFillSystemConfigurationTable(CONST UINT64 SystemDescriptionTableHeader, OUT SYSTEM_CONFIGURATION_TABLE* SystemConfiguration);

#endif /* _STDH_PARSER_H_ */
