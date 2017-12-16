#include <bp_sig_table.h>

const BP_UINT16 SIG_SYS_COMM_STATE_MIN = 0, SIG_SYS_COMM_STATE_MAX = 2, SIG_SYS_COMM_STATE_DEF = 2;
const BP_UINT16 SIG_SYS_POWER_MIN = 0, SIG_SYS_POWER_MAX = 1, SIG_SYS_POWER_DEF = 0;

BP_SigId2Val g_SysSigId2Val[] = 
{
	{SIG_SYS_COMM_STATE, 123}, 
	{SIG_SYS_POWER, 456}, 
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
