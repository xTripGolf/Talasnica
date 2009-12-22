//+------------------------------------------------------------------+
//|                                                talasnica_dll.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.xtrip.net"

//+------------------------------------------------------------------+
//| DLL imports                                                      |
//+------------------------------------------------------------------+
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
   
#import

