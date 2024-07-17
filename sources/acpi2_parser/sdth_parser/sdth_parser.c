#include "sdth_parser.h"

#include "system_log.h"
#include "utils.h"

#define MODULE_TAG u"SDTH"

STATUS API SdthFillSystemConfigurationTable(CONST UINT64 SystemDescriptionTableHeader, OUT SYSTEM_CONFIGURATION_TABLE *SystemConfiguration)
{
    CHAR16 Signature[5];
    CHAR16 OemId[7];
    CHAR16 OemTableId[9];
    SYSTEM_DESCRIPTION_TABLE_HEADER *Sdth = (SYSTEM_DESCRIPTION_TABLE_HEADER *)SystemDescriptionTableHeader;

    Char8ToChar16(Sdth->Signature, Signature, 4);
    Char8ToChar16(Sdth->OemId, OemId, 6);
    Char8ToChar16(Sdth->OemTabelId, OemTableId, 8);

    LOG_DEBUG(u"Signature %s", Signature);
    LOG_DEBUG(u"Length 0x%x", Sdth->Length);
    LOG_DEBUG(u"Revision 0x%x", Sdth->Revision);
    LOG_DEBUG(u"Checksum 0x%x", Sdth->Checksum);
    LOG_DEBUG(u"Oem Id %s", OemId);
    LOG_DEBUG(u"Oem Table Id %s", OemTableId);
    LOG_DEBUG(u"OemRevision 0x%x", Sdth->OemRevision);
    LOG_DEBUG(u"CreatorId 0x%x", Sdth->CreatorId);
    LOG_DEBUG(u"CreatorRevision 0x%x", Sdth->CreatorRevision);

    (VOID) SystemConfiguration;
    return E_OK;
}
