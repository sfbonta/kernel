#ifndef _MADT_PARSER_H_
#define _MADT_PARSER_H_

#include "platform_types.h"
#include "system_configuration_table.h"

STATUS API MadtFillSystemConfigurationTable(CONST UINT64 MultipleApicDescriptorTable, OUT SYSTEM_CONFIGURATION_TABLE* SystemConfiguration);

#endif /* _XSDT_PARSER_H_ */
