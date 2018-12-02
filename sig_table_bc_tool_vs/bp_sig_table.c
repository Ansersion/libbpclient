#include <bp_sig_table.h>
#include <bp_public.h>
#include <bp_strlen.h>
#include <bp_sig_table_tools.h>

/* system signal min, max, default value */
// BP_UINT16 SIG_SYS_COMM_STATE_MIN = 0, SIG_SYS_COMM_STATE_MAX = 2, SIG_SYS_COMM_STATE_DEF = 2;
SigTypeU SIG_SYS_COMM_STATE_MIN = {.t_enm = 0}, SIG_SYS_COMM_STATE_MAX = {.t_enm = 2}, SIG_SYS_COMM_STATE_DEF = {.t_enm = 2};
// SIG_SYS_SERIAL_NUMBER_DEF = SYS_STRING_DEFAULT_VALUE;
SigTypeU SIG_SYS_POWER_MIN = {.t_enm = 0}, SIG_SYS_POWER_MAX = {.t_enm = 1}, SIG_SYS_POWER_DEF = {.t_enm = 0};
SigTypeU SIG_SYS_STRENGTH_MIN = {.t_enm = 0}, SIG_SYS_STRENGTH_MAX = {.t_enm = 2}, SIG_SYS_STRENGTH_DEF = {.t_enm = 1};

/* system signal id to value array index*/
BP_SigId2Val * g_SysSigId2Val;

/* system signal id to signal table */
BP_SigTable * g_SysSigTable;

/* system signal number */
BP_WORD g_SysSigNum;

/* system signal custom value */
BP_UINT8 SIG_SYS_SERIAL_NUMBER_CUSTOM_DEF_VAL[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1";
BP_EnumSignalMap SIG_SYS_STRENGTH_CUSTOM_ENUM_MAP[] = 
{
    {0,9},
    {1,11},
};
BP_SysCusEnumUnit SIG_SYS_STRENGTH_CUSTOM_ENUM_LANG = {sizeof(SIG_SYS_STRENGTH_CUSTOM_ENUM_MAP) / sizeof(BP_EnumSignalMap), SIG_SYS_STRENGTH_CUSTOM_ENUM_MAP};

/* system signal custom value unit array */
BP_SysCustomUnit * g_SysCustomUnitTable;

/* system signal custom unit number */
BP_WORD g_SysCustomUnitNum;


/* system signal enable map */
BP_UINT8 g_SysMapDis_0[1] = {0x20 | 0x04 | 0x02 | 0x01};

BP_SysSigMap * g_SysSigMap;

BP_WORD g_SysSigMapSize;


void BP_SetSysSigId2ValTable(BP_SigId2Val * sys_sig_id_2_val, BP_WORD sys_sig_num)
{
	g_SysSigId2Val = sys_sig_id_2_val;
	g_SysSigNum = sys_sig_num;
}

void BP_SetSysSigTable(BP_SigTable * sys_sig_table)
{
	g_SysSigTable = sys_sig_table;
}

void BP_SetSysCustomUnitTable(BP_SysCustomUnit * sys_custom_unit_table, BP_WORD sys_custom_unit_num)
{
	g_SysCustomUnitTable = sys_custom_unit_table;
	g_SysCustomUnitNum = sys_custom_unit_num;
}

void BP_SetSysSigMap(BP_SysSigMap * sys_sig_map, BP_WORD sys_sig_map_size)
{
	g_SysSigMap = sys_sig_map;
	g_SysSigMapSize = sys_sig_map_size;
}