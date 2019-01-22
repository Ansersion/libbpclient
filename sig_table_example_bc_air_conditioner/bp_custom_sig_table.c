
#include <bp_sig_str.h>
#include <bp_custom_sig_table.h>
#include <bp_sig_table_tools.h>

BP_SigId2Val g_CusSigId2Val[] = 
{
	{SIG_CUS_DEVICE_NAME, 0}, 
};

const BP_SigTable g_CusSigTable[] = 
{
	{SIG_CUS_DEVICE_NAME, SIG_TYPE_STR, DISABLE_STATISTICS, DISABLE_DISPLAY, 0, DISABLE_ALARM, SIG_PERM_RO, ALARM_CLASS_NONE, NO_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&STRING_DEFAULT_VALUE, (SigTypeU *)&STRING_DEFAULT_VALUE, (SigTypeU *)&STRING_DEFAULT_VALUE, ALARM_DELAY_DEFAULT, ALARM_DELAY_DEFAULT},
};

const BP_WORD g_CusSigNum = sizeof(g_CusSigId2Val) / sizeof(BP_SigId2Val);

const BP_UINT8 * g_CusSigNameLang[] = 
{
    STRING_NONE,
    STRING_NONE,
    STRING_NONE,
    STRING_NONE,
    "BC Air Conditioner",
    "BC空调",
};

const BP_UINT8 * g_CusSigUnitLang[] = 
{
};

const BP_UINT8 * g_CusSigGroupLang[] = 
{
};

const BP_UINT8 * g_CusSigEnumLang[] = 
{
    /* must be ordered */
};

const BP_CusLangMap g_CusSigNameLangMap[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    {SIG_CUS_DEVICE_NAME, 1},
};

const BP_WORD g_CusSigNameLangMapNum = sizeof(g_CusSigNameLangMap) / sizeof(BP_CusLangMap);

const BP_CusLangMap g_CusSigUnitLangMap[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    // {SIG_CUS_DEVICE_NAME, 0},
};
const BP_WORD g_CusSigUnitLangMapNum = sizeof(g_CusSigUnitLangMap) / sizeof(BP_CusLangMap);

const BP_CusLangMap g_CusSigGroupLangMap[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    // {SIG_CUS_DEVICE_NAME, 0},
};
const BP_WORD g_CusSigGroupLangMapNum = sizeof(g_CusSigGroupLangMap) / sizeof(BP_CusLangMap);

const BP_SigId2EnumSignalMap g_CusSigId2EnumSigMap[] = 
{
};

const BP_WORD g_CusSigId2EnumSignalMapNum = sizeof(g_CusSigId2EnumSigMap) / sizeof(BP_SigId2EnumSignalMap);
