//+------------------------------------------------------------------+
//|                                                    talasnica.mqh |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.xtrip.net"

/**
konstanty pro oznaèení prostøedí
**/
#define ENVIRONMENT_PRODUCTION 2
#define ENVIRONMENT_DEVELOPMENT 4

/**
* konstanty pro úroveò výpisu logování
* @todo dodìlat
*/

#define LOG_INIT 2
#define LOG_ERROR 4
#define LOG_INFO 8
#define LOG_SCRIPT 16
#define LOG_ 0

/**
* rozšíøení konstant typù obchodù na obchody v profitu a ve ztrátì a všechny obchody
*
*/

// 0-6 Buy - seelstop trades
// 6 - profited trades
// 7 - loss trades
// 8 - all trades
// 9 - pøevis
#define OP_PROFIT 6
#define OP_LOSS 7
#define OP_OPENED 8
#define OP_PREMOC 9
#define OP_SVETAURUS 10
#define OP_SVEMEDVED 11


#define DIMENZE_OP 12 // dimenze všech polí _C, _V, ...

