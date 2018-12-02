#ifdef WIN32
#include "stdafx.h"
#endif

#include <bp_sig_str.h>
#include <bp_custom_sig_table.h>
#include <bp_sig_table_tools.h>

BP_SigId2Val * g_CusSigId2Val;

BP_SigTable * g_CusSigTable;

BP_WORD g_CusSigNum;

BP_UINT8 ** g_CusSigNameLang;

BP_UINT8 ** g_CusSigUnitLang;

BP_UINT8 ** g_CusSigGroupLang;

BP_UINT8 ** g_CusSigEnumLang;

BP_CusLangMap * g_CusSigNameLangMap;

BP_WORD g_CusSigNameLangMapNum;

BP_CusLangMap * g_CusSigUnitLangMap;
BP_WORD g_CusSigUnitLangMapNum;

BP_CusLangMap * g_CusSigGroupLangMap;
BP_WORD g_CusSigGroupLangMapNum;

BP_CusEnumLangMap * g_CusSigEnumLangMap;
BP_WORD g_CusSigEnumLangMapNum;

/* dynamically set signal table */
void BP_SetCusSigId2ValTable(BP_SigId2Val * cus_sig_id_2_val, BP_WORD cus_sig_num)
{
	g_CusSigId2Val = cus_sig_id_2_val;
	g_CusSigNum = cus_sig_num;
}

void BP_SetCusSigTable(BP_SigTable * cus_sig_table)
{
	g_CusSigTable = cus_sig_table;
}

void BP_SetCusSigNameLang(BP_UINT8 ** cus_sig_name_lang) 
{
	g_CusSigNameLang = cus_sig_name_lang;
}

void BP_SetCusSigUnitLang(BP_UINT8 ** cus_sig_unit_lang) 
{
	g_CusSigUnitLang = cus_sig_unit_lang;
}

void BP_SetCusSigGroupLang(BP_UINT8 ** cus_sig_group_lang) 
{
	g_CusSigGroupLang = cus_sig_group_lang;
}

void BP_SetCusSigEnumLang(BP_UINT8 ** cus_sig_enum_lang) 
{
	g_CusSigEnumLang = cus_sig_enum_lang;
}

void BP_SetCusSigNameLangMap(BP_CusLangMap * cus_sig_name_lang_map, BP_WORD cus_sig_name_lang_map_num) 
{
	g_CusSigNameLangMap = cus_sig_name_lang_map;
	g_CusSigNameLangMapNum = cus_sig_name_lang_map_num;
}

void BP_SetCusSigUnitLangMap(BP_CusLangMap * cus_sig_unit_lang_map, BP_WORD cus_sig_unit_lang_map_num) 
{
	g_CusSigUnitLangMap = cus_sig_unit_lang_map;
	g_CusSigUnitLangMapNum = cus_sig_unit_lang_map_num;
}

void BP_SetCusSigGroupLangMap(BP_CusLangMap * cus_sig_group_lang_map, BP_WORD cus_sig_group_lang_map_num) 
{
	g_CusSigGroupLangMap = cus_sig_group_lang_map;
	g_CusSigGroupLangMapNum = cus_sig_group_lang_map_num;
}

void BP_SetCusSigEnumLangMap(BP_CusLangMap * cus_sig_enum_lang_map, BP_WORD cus_sig_enum_lang_map_num) 
{
	g_CusSigEnumLangMap = cus_sig_enum_lang_map;
	g_CusSigEnumLangMapNum = cus_sig_enum_lang_map_num;
}

