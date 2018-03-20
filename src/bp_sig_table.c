#include <bp_sig_table.h>
// #include <stdio.h>

const BP_UINT16 SIG_SYS_COMM_STATE_MIN = 0, SIG_SYS_COMM_STATE_MAX = 2, SIG_SYS_COMM_STATE_DEF = 2;
const BP_UINT16 SIG_SYS_POWER_MIN = 0, SIG_SYS_POWER_MAX = 1, SIG_SYS_POWER_DEF = 0;

BP_SigId2Val g_SysSigId2Val[] = 
{
	{SIG_SYS_COMM_STATE, 0}, 
	{SIG_SYS_POWER, 1}, 
};

const BP_SigTable g_SysSigTable[] = 
{
	{SIG_SYS_COMM_STATE, SIG_TYPE_ENM, 1, 0, SIG_PERM_RO, 0, (SigTypeU *)&SIG_SYS_COMM_STATE_MIN, (SigTypeU *)&SIG_SYS_COMM_STATE_MAX, (SigTypeU *)&SIG_SYS_COMM_STATE_DEF},
	{SIG_SYS_POWER, SIG_TYPE_ENM, 1, 0, SIG_PERM_RW, 0, (SigTypeU *)&SIG_SYS_POWER_MIN, (SigTypeU *)&SIG_SYS_POWER_MAX, (SigTypeU *)&SIG_SYS_POWER_DEF},
};

const BP_UINT16 g_SysSigNum = sizeof(g_SysSigId2Val) / sizeof(BP_SigId2Val);

BP_UINT16 BP_GetSigIdx(const BP_UINT16 sig_id)
{
	BP_UINT16 i;
	for(i = 0; i < g_SysSigNum; i++) {
		if(sig_id == g_SysSigId2Val[i].SigId) {
			return i;
		}
	}
	return SIG_INDEX_INVALID;
}

BP_INT16 BP_SetSigVal(BP_UINT8 sig_num, BP_SigId2Val * sig_array)
{
	BP_UINT16 i, j, idx;
	if(BP_NULL == sig_array) {
		return -0x1;
	}
	for(i = 0; i < sig_num; i++) {
		if(SIG_INDEX_INVALID != (idx = BP_GetSigIdx(sig_array[i].SigId))) {
			g_SysSigId2Val[idx].SigVal = sig_array[i].SigVal;
			continue;
		}
		return -0x2;

	}
	return 0;
}

void BP_SigDump(void)
{
	BP_UINT16 i = 0;
	for(i = 0; i < g_SysSigNum; i++) {
		switch(g_SysSigTable[i].SigType) {
			case SIG_TYPE_U32:
				// printf("U32: %04x=>%d\n", g_SysSigId2Val[i].SigId, g_SysSigId2Val[i].SigVal.t_u32);
				break;
			case SIG_TYPE_I32:
				// printf("I32: %04x=>%d\n", g_SysSigId2Val[i].SigId, g_SysSigId2Val[i].SigVal.t_i32);
				break;
			case SIG_TYPE_U16:
				// printf("U16: %04x=>%d\n", g_SysSigId2Val[i].SigId, g_SysSigId2Val[i].SigVal.t_u16);
				break;
			case SIG_TYPE_I16:
				// printf("I16: %04x=>%d\n", g_SysSigId2Val[i].SigId, g_SysSigId2Val[i].SigVal.t_i16);
				break;
			case SIG_TYPE_ENM:
				// printf("ENM: %04x=>%d\n", g_SysSigId2Val[i].SigId, g_SysSigId2Val[i].SigVal.t_enm);
				break;
			case SIG_TYPE_FLT:
				// printf("FLT: %04x=>%f\n", g_SysSigId2Val[i].SigId, g_SysSigId2Val[i].SigVal.t_flt);
				break;
			case SIG_TYPE_STR:
				// printf("str: %04x=>%s\n", g_SysSigId2Val[i].SigId, g_SysSigId2Val[i].SigVal.t_str);
				break;
		}
	}
}

