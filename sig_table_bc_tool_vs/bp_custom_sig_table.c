#ifdef WIN32
#include "stdafx.h"
#endif

#include <bp_sig_str.h>
#include <bp_custom_sig_table.h>
#include <bp_sig_table_tools.h>

BP_SigId2Val g_CusSigId2Val[] = 
{
	{SIG_CUS_DEVICE_NAME, 0}, 
};

BP_SigTable g_CusSigTable[] = 
{
	{SIG_CUS_DEVICE_NAME, SIG_TYPE_STR, DISABLE_STATISTICS, DISABLE_DISPLAY, 0, DISABLE_ALARM, SIG_PERM_RO, ALARM_CLASS_NONE, NO_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&STRING_DEFAULT_VALUE, (SigTypeU *)&STRING_DEFAULT_VALUE, (SigTypeU *)&STRING_DEFAULT_VALUE, 5, 5},
};

BP_WORD g_CusSigNum = sizeof(g_CusSigId2Val) / sizeof(BP_SigId2Val);

BP_UINT8 * g_CusSigNameLang[] = 
{
    STRING_NONE,
    STRING_NONE,
    STRING_NONE,
    STRING_NONE,
    "BC Light",
    "BC Light",
};

BP_UINT8 * g_CusSigUnitLang[] = 
{
	BP_NULL
};

BP_UINT8 * g_CusSigGroupLang[] =
{
	BP_NULL
};

BP_UINT8 * g_CusSigEnumLang[] = 
{
	BP_NULL
};

BP_CusLangMap g_CusSigNameLangMap[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    {SIG_CUS_DEVICE_NAME, 1},
};

BP_WORD g_CusSigNameLangMapNum = sizeof(g_CusSigNameLangMap) / sizeof(BP_CusLangMap);

BP_CusLangMap g_CusSigUnitLangMap[] =
{
	BP_NULL
};
BP_WORD g_CusSigUnitLangMapNum = sizeof(g_CusSigUnitLangMap) / sizeof(BP_CusLangMap);

BP_CusLangMap g_CusSigGroupLangMap[] =
{
	BP_NULL
};
BP_WORD g_CusSigGroupLangMapNum = sizeof(g_CusSigGroupLangMap) / sizeof(BP_CusLangMap);

BP_CusEnumLangMap g_CusSigEnumLangMap[] =
{
	BP_NULL
};
BP_WORD g_CusSigEnumLangMapNum = sizeof(g_CusSigEnumLangMap) / sizeof(BP_CusEnumLangMap);

