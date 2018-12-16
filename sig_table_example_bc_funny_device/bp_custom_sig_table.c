
#include <bp_sig_str.h>
#include <bp_custom_sig_table.h>
#include <bp_sig_table_tools.h>

const SigTypeU SIG_CUS_ENERGY_MIN = {.t_u16 = 0}, SIG_CUS_ENERGY_MAX = {.t_u16 = 100}, SIG_CUS_ENERGY_DEF = {.t_u16 = 0};
const SigTypeU SIG_CUS_MODE_MIN = {.t_enm = 0}, SIG_CUS_MODE_MAX = {.t_enm = 2}, SIG_CUS_MODE_DEF = {.t_enm = 0};

BP_SigId2Val g_CusSigId2Val[] = 
{
	{SIG_CUS_DEVICE_NAME, 0}, 
	{SIG_CUS_ENERGY, 0}, 
	{SIG_CUS_MODE, 0}, 
};

BP_SigTable g_CusSigTable[] = 
{
	{SIG_CUS_DEVICE_NAME, SIG_TYPE_STR, DISABLE_STATISTICS, DISABLE_DISPLAY, 0, DISABLE_ALARM, SIG_PERM_RO, ALARM_CLASS_NONE, NO_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&STRING_DEFAULT_VALUE, (SigTypeU *)&STRING_DEFAULT_VALUE, (SigTypeU *)&STRING_DEFAULT_VALUE, ALARM_DELAY_DEFAULT, ALARM_DELAY_DEFAULT},
	{SIG_CUS_ENERGY, SIG_TYPE_U16, ENABLE_STATISTICS, ENABLE_DISPLAY, 0, DISABLE_ALARM, SIG_PERM_RO, ALARM_CLASS_NONE, NO_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&SIG_CUS_ENERGY_MIN, (SigTypeU *)&SIG_CUS_ENERGY_MAX, (SigTypeU *)&SIG_CUS_ENERGY_DEF, ALARM_DELAY_DEFAULT, ALARM_DELAY_DEFAULT},
	{SIG_CUS_MODE, SIG_TYPE_ENM, ENABLE_STATISTICS, ENABLE_DISPLAY, 0, DISABLE_ALARM, SIG_PERM_RW, ALARM_CLASS_NONE, NO_CUSTOM_INFO, RESERVED_FIELD, (SigTypeU *)&SIG_CUS_MODE_MIN, (SigTypeU *)&SIG_CUS_MODE_MAX, (SigTypeU *)&SIG_CUS_MODE_DEF, ALARM_DELAY_DEFAULT, ALARM_DELAY_DEFAULT},
};

BP_WORD g_CusSigNum = sizeof(g_CusSigId2Val) / sizeof(BP_SigId2Val);

BP_UINT8 * g_CusSigNameLang[] = 
{
	/* signal 0x0000 */
    "Juguete",
    "عروسه لعبه",
    "игрушечный",
    "Jouet",
    "BC Funny Device",
    "BC玩具",

	/* signal 0x0001 */
    "energía",
    "طاقة",
    "энергия",
    "énergie",
    "Energy",
    "能量",

	/* signal 0x0002 */
    "Modo",
    "الوضع",
    "Режим",
    "Mode",
    "Mode",
    "形态",
};

BP_UINT8 * g_CusSigUnitLang[] = 
{
	/* ULR 1 */
    "%",
    "%",
    "%",
    "%",
    "%",
    "%",
};

BP_UINT8 * g_CusSigGroupLang[] = 
{
	/* GLR 1 */
    "BASIC",
    "الأساسية",
	"основной",
    "De base",
    "Basic",
    "基本",
};

BP_UINT8 * g_CusSigEnumLang[] = 
{
	/* ELR 1 */
    "Circulo",
    "دائرة",
	"Круг",
    "Cercle",
    "Circle",
    "圆形",

	/* ELR 2 */
    "Rectángulo",
    "مستطيل",
	"Прямоугольник",
    "Rectangle",
    "Rectangle",
    "正方形",

	/* ELR 3 */
    "Triángulo",
    "مثلث",
	"Треугольник",
    "Triangle",
    "Triangle",
    "三角形",
};

BP_CusLangMap g_CusSigNameLangMap[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    {SIG_CUS_DEVICE_NAME, 1},
    {SIG_CUS_ENERGY, 2},
    {SIG_CUS_MODE, 3},
};

BP_WORD g_CusSigNameLangMapNum = sizeof(g_CusSigNameLangMap) / sizeof(BP_CusLangMap);

BP_CusLangMap g_CusSigUnitLangMap[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    {SIG_CUS_ENERGY, 1},
};
BP_WORD g_CusSigUnitLangMapNum = sizeof(g_CusSigUnitLangMap) / sizeof(BP_CusLangMap);

BP_CusLangMap g_CusSigGroupLangMap[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    {SIG_CUS_ENERGY, 1},
    {SIG_CUS_MODE, 1},
};
BP_WORD g_CusSigGroupLangMapNum = sizeof(g_CusSigGroupLangMap) / sizeof(BP_CusLangMap);

/* cycle n */
BP_EnumSignalMap SIG_CUS_MODE_ENUM_MAP[] = 
{
    /* 1 mean first language resource, 0 means no language resource */
    // {SIG_CUS_DEVICE_NAME, 0},
	{0, 1},
	{1, 2},
	{2, 3},
};
/* cycle n end*/

BP_SigId2EnumSignalMap g_CusSigId2EnumSigMap[] = 
{
	{SIG_CUS_MODE, SIG_CUS_MODE_ENUM_MAP, sizeof(SIG_CUS_MODE_ENUM_MAP) / sizeof(BP_EnumSignalMap)},
};

BP_WORD g_CusSigId2EnumSignalMapNum = sizeof(g_CusSigId2EnumSigMap) / sizeof(BP_SigId2EnumSignalMap);

