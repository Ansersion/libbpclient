
#ifndef __BP_CUSTOM_SIG_TABLE_H
#define __BP_CUSTOM_SIG_TABLE_H

#include <bp_sig_str.h>

#define STD_LANGUAGE_SUPPORTED_NUM   0x06
#define STD_LANGUAGE_SUPPORTED_MASK  0xC0

#define SIG_CUS_DEVICE_NAME 		0x0000

extern BP_SigId2Val * g_CusSigId2Val;
extern BP_WORD g_CusSigNum;
extern BP_SigTable * g_CusSigTable;
extern BP_UINT8 ** g_CusSigNameLang;
extern BP_UINT8 ** g_CusSigUnitLang;
extern BP_UINT8 ** g_CusSigGroupLang;
extern BP_UINT8 ** g_CusSigEnumLang;
extern BP_CusLangMap * g_CusSigNameLangMap;
extern BP_WORD g_CusSigNameLangMapNum;
extern BP_CusLangMap * g_CusSigUnitLangMap;
extern BP_WORD g_CusSigUnitLangMapNum;
extern BP_CusLangMap * g_CusSigGroupLangMap;
extern BP_WORD g_CusSigGroupLangMapNum;
extern BP_CusEnumLangMap * g_CusSigEnumLangMap;
extern BP_WORD g_CusSigEnumLangMapNum;

EXPORT_API void BP_SetCusSigId2ValTable(BP_SigId2Val * cus_sig_id_2_val, BP_WORD cus_sig_num);
EXPORT_API void BP_SetCusSigTable(BP_SigTable * cus_sig_table);
EXPORT_API void BP_SetCusSigNameLang(BP_UINT8 ** cus_sig_name_lang);
EXPORT_API void BP_SetCusSigUnitLang(BP_UINT8 ** cus_sig_unit_lang);
EXPORT_API void BP_SetCusSigGroupLang(BP_UINT8 ** cus_sig_group_lang);
EXPORT_API void BP_SetCusSigEnumLang(BP_UINT8 ** cus_sig_enum_lang);
EXPORT_API void BP_SetCusSigNameLangMap(BP_CusLangMap * cus_sig_name_lang_map, BP_WORD cus_sig_name_lang_map_num);
EXPORT_API void BP_SetCusSigUnitLangMap(BP_CusLangMap * cus_sig_unit_lang_map, BP_WORD cus_sig_unit_lang_map_num);
EXPORT_API void BP_SetCusSigGroupLangMap(BP_CusLangMap * cus_sig_group_lang_map, BP_WORD cus_sig_group_lang_map_num);
EXPORT_API void BP_SetCusSigEnumLangMap(BP_CusLangMap * cus_sig_enum_lang_map, BP_WORD cus_sig_enum_lang_map_num);


#endif
