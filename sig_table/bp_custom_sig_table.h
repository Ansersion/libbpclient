
#ifndef __BP_CUSTOM_SIG_TABLE_H
#define __BP_CUSTOM_SIG_TABLE_H

#include <bp_sig_str.h>

#define STD_LANGUAGE_SUPPORTED_NUM   0x06
#define STD_LANGUAGE_SUPPORTED_MASK  0xC0

#define SIG_CUS_DEVICE_NAME 		0x0000

extern BP_SigId2Val g_CusSigId2Val[];
extern const BP_WORD g_CusSigNum;
extern const BP_SigTable g_CusSigTable[];
extern const BP_UINT8 * g_CusSigNameLang[];
extern const BP_UINT8 * g_CusSigUnitLang[];
extern const BP_UINT8 * g_CusSigGroupLang[];
extern const BP_UINT8 * g_CusSigEnumLang[];
extern const BP_CusLangMap g_CusSigNameLangMap[];
extern const BP_WORD g_CusSigNameLangMapNum;
extern const BP_CusLangMap g_CusSigUnitLangMap[];
extern const BP_WORD g_CusSigUnitLangMapNum;
extern const BP_CusLangMap g_CusSigGroupLangMap[];
extern const BP_WORD g_CusSigGroupLangMapNum;
extern const BP_SigId2EnumSignalMap g_CusSigId2EnumSigMap[];
extern const BP_WORD g_CusSigId2EnumSignalMapNum;



#endif
