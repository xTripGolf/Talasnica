//+------------------------------------------------------------------+
//|                                                talasnica_dll.mq4 |
//|                                 Copyright � 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright � 2006, MITHRADES a.s."
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
   * po��tadlo obchod�
   *
   * po�et obchod� dle druhu
   */
   int talasnica_count(int type);
   /**
   * po��tadlo obchod�
   *
   * po�et lot�
   */
    double talasnica_volume(int type);
   /**
   * po��tadlo obchod�
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
   * aproximovan� vstupn� cena
   *
   */
   double talasnica_averageOpenPrice(int type);
   /**
   * vybere obchod
   **/
   int talasnica_getTicket(int type, int index);
   
#import

