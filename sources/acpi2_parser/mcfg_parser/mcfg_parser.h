#ifndef _MCFG_H_PARSER_
#define _MCFG_H_PARSER_

#include "platform_types.h"
#include "system_configuration_table.h"

STATUS API McfgFillSystemConfigurationTable(IN CONST UINT64 RootSystemDescriptonPointer,
                                        OUT SYSTEM_CONFIGURATION_TABLE *SystemConfigurationTable);

#endif /* _MCFG_H_PARSER_ */
