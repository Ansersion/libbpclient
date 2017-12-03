#include <bp_public.h>
#include <bp_sig_str.h>

const BP_UINT8 g_SysMapDis_0[1] = {0x80 | 0x40};

const BP_SysSigMap g_SysSigMap[] = 
{
	{0x0 | DIST_CLASS_6_MSK | DIST_END_FLAG_MSK, sizeof(g_SysMapDis_0) / sizeof(BP_UINT8), g_SysMapDis_0}, 
};

const BP_UINT16 g_SysSigMapSize = sizeof(g_SysSigMap) / sizeof(BP_SysSigMap);

// const BP_UINT8 * g_SysSigMap[SYS_SIG_DIST_NUM]
// {
// }


// const BP_UINT8 BP_SysSigEnableMap[] = {
// 	1,
// };
// 
// const BP_SysSigTable BP_SysSigMap[] = {
// 	{4, 1, 0, 0, 0, 2, 0}, 
// };
// 
// const BP_UINT16 BP_SysSigEnableMapSize = sizeof(BP_SysSigEnableMap) / sizeof(BP_UINT8);

