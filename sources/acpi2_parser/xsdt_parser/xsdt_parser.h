#ifndef _XSDT_PARSER_H_
#define _XSDT_PARSER_H_

#include "platform_types.h"
#include "system_configuration_table.h"

STATUS API XsdtFillSystemConfigurationTable(CONST UINT64 ExtendedSystemDescriptionTable, OUT SYSTEM_CONFIGURATION_TABLE* SystemConfiguration);

#endif /* _XSDT_PARSER_H_ */
