#include <bp_sig_table.h>
#include <bp_public.h>
#include <bp_strlen.h>

/* system default value */
const BP_UINT8 * const STRING_NONE = "";
const SigTypeU SYS_STRING_DEFAULT_VALUE = {.t_str = STRING_NONE};

/* system signal min, max, default value */
// const BP_UINT16 SIG_SYS_COMM_STATE_MIN = 0, SIG_SYS_COMM_STATE_MAX = 2, SIG_SYS_COMM_STATE_DEF = 2;
const SigTypeU SIG_SYS_COMM_STATE_MIN = {.t_enm = 0}, SIG_SYS_COMM_STATE_MAX = {.t_enm = 2}, SIG_SYS_COMM_STATE_DEF = {.t_enm = 2};
// SIG_SYS_SERIAL_NUMBER_DEF = SYS_STRING_DEFAULT_VALUE;
const SigTypeU SIG_SYS_POWER_MIN = {.t_enm = 0}, SIG_SYS_POWER_MAX = {.t_enm = 1}, SIG_SYS_POWER_DEF = {.t_enm = 0};

/* system signal id to value array index*/
BP_SigId2Val g_SysSigId2Val[] = 
{
	{SIG_SYS_COMM_STATE, 0}, 
	{SIG_SYS_SERIAL_NUMBER, 0}, 
	{SIG_SYS_POWER, 0}, 
};

/* system signal id to signal table */
const BP_SigTable g_SysSigTable[] = 
{
	{SIG_SYS_COMM_STATE, SIG_TYPE_ENM, ENABLE_STATISTICS, ENABLE_DISPLAY, 0, ENABLE_ALARM, SIG_PERM_RO, ALARM_CLASS_SERIOUS, NO_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&SIG_SYS_COMM_STATE_MIN, (SigTypeU *)&SIG_SYS_COMM_STATE_MAX, (SigTypeU *)&SIG_SYS_COMM_STATE_DEF, 5, 5},
	{SIG_SYS_SERIAL_NUMBER, SIG_TYPE_STR, ENABLE_STATISTICS, DISABLE_DISPLAY, 0, DISABLE_ALARM, SIG_PERM_RO, ALARM_CLASS_NONE, HAS_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&SYS_STRING_DEFAULT_VALUE, (SigTypeU *)&SYS_STRING_DEFAULT_VALUE, (SigTypeU *)&SYS_STRING_DEFAULT_VALUE, 5, 5},
	{SIG_SYS_POWER, SIG_TYPE_ENM, ENABLE_STATISTICS, ENABLE_DISPLAY, 0, DISABLE_ALARM, SIG_PERM_RW, ALARM_CLASS_NONE, NO_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&SIG_SYS_POWER_MIN, (SigTypeU *)&SIG_SYS_POWER_MAX, (SigTypeU *)&SIG_SYS_POWER_DEF, 5, 5},
};

/* system signal number */
const BP_UINT16 g_SysSigNum = sizeof(g_SysSigId2Val) / sizeof(BP_SigId2Val);

/* system signal custom value */
const BP_UINT8 * const SIG_SYS_SERIAL_NUMBER_CUSTOM_DEF_VALUE = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1";

/* system signal custom value unit array */
const BP_SysCustomUnit g_SysCustomUnitTable[] = {
    {SIG_SYS_SERIAL_NUMBER, SYS_SIG_CUSTOM_TYPE_DEF_VAL, (void *)SIG_SYS_SERIAL_NUMBER_CUSTOM_DEF_VALUE}
};

/* system signal custom unit number */
const BP_UINT16 g_SysCustomUnitNum = sizeof(g_SysCustomUnitTable) / sizeof(BP_SysCustomUnit);


const BP_UINT8 g_SysMapDis_0[1] = {0x04 | 0x02 | 0x01};

const BP_SysSigMap g_SysSigMap[] = 
{
	{0x0 | DIST_CLASS_1_MSK | DIST_END_FLAG_MSK, sizeof(g_SysMapDis_0) / sizeof(BP_UINT8), g_SysMapDis_0}, 
};

const BP_UINT16 g_SysSigMapSize = sizeof(g_SysSigMap) / sizeof(BP_SysSigMap);


