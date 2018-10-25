
#ifndef __BP_CUSTOM_SIG_TABLE_H
#define __BP_CUSTOM_SIG_TABLE_H

#include <bp_sig_str.h>

#define STD_LANGUAGE_SUPPORTED_NUM   0x06
#define STD_LANGUAGE_SUPPORTED_MASK  0xC0

#define SIG_CUS_DEVICE_NAME 		0x0000

extern BP_SigId2Val g_CusSigId2Val[];
extern BP_WORD g_CusSigNum;
extern BP_SigTable g_CusSigTable[];
extern BP_UINT8 * g_CusSigNameLang[];
extern BP_UINT8 * g_CusSigUnitLang[];
extern BP_UINT8 * g_CusSigGroupLang[];
extern BP_UINT8 * g_CusSigEnumLang[];
extern BP_CusLangMap g_CusSigNameLangMap[];
extern BP_WORD g_CusSigNameLangMapNum;
extern BP_CusLangMap g_CusSigUnitLangMap[];
extern BP_WORD g_CusSigUnitLangMapNum;
extern BP_CusLangMap g_CusSigGroupLangMap[];
extern BP_WORD g_CusSigGroupLangMapNum;
extern BP_CusEnumLangMap g_CusSigEnumLangMap[];
extern BP_WORD g_CusSigEnumLangMapNum;



#endif
