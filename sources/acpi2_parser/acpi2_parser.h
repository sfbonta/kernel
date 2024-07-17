#ifndef _ACPI2_H_PARSER_
#define _ACPI2_H_PARSER_

#include "platform_types.h"
#include "system_configuration_table.h"

STATUS API Acpi2FillSystemConfigurationTable(IN CONST UINT64 RootSystemDescriptonPointer,
                                        OUT SYSTEM_CONFIGURATION_TABLE *SystemConfigurationTable);

#endif /* _ACPI2_H_PARSER_ */
