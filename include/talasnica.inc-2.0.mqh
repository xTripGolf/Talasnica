//+------------------------------------------------------------------+
//|                                                    talasnica.mqh |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.xtrip.net"

#import "talasnica/talasnica.dll"
   // register order in talasnica

   int    talasnica_addOrder(int ticket,
                             string symbol,
                             int openTime,
                             int type,
                             double lots,
                             double openPrice,
                             double stopLoss,
                             double takeProfit,
                             int expiration,
                             int closeTime,
                             double closePrice,
                             double commission,
                             double profit,
                             double swap,
                             string comment,
                             int magicNumber
                             );
   void talasnica_reset();
   string talasnica_getTradepacketInfo();
   /**
   * poèítadlo obchodù
   *
   * poèet obchodù dle druhu
   */
   int talasnica_count(int type);
   /**
   * poèítadlo obchodù
   *
   * poèet lotù
   */
    double talasnica_volume(int type);
   /**
   * poèítadlo obchodù
   *
   * profit
   */
   double talasnica_profit(int type);
   /**
   * swap
   *
   */
   double talasnica_swap(int type);
   /**
   * profit + swap
   *
   */
   double talasnica_totalProfit(int type);
   /**
   * aproximovaná vstupní cena
   *
   */
   double talasnica_averageOpenPrice(int type);
   /**
   * vybere obchod
   **/
   int talasnica_getTicket(int type, int index);
   
   
   // sample
   int    GetIntValue(int);
   double GetDoubleValue(double);
   string GetStringValue(string);
   double GetArrayItemValue(double arr[],int,int);
   bool   SetArrayItemValue(double& arr[],int,int,double);
   double GetRatesItemValue(double rates[][6],int,int,int);
   int    SortStringArray(string& arr[],int);
   int    ProcessStringArray(string& arr[],int);
#import "talasnica/talasnica.lib-2.0.ex4"
   bool talasnica_recalculate();
   bool talasnica_OrderSelect(int type, int index);
#import

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

