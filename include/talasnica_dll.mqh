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
                             int orderType,
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
   void talasnica_sortOrders();
   string talasnica_printOrdersManager();
   /**
   * poèítadlo obchodù
   *
   * poèet obchodù v packetu
   */
   int talasnica_packetCount(int packetFilter);
   /**
   * poèítadlo obchodù
   *
   * poèet lotù  v packetu
   */
    double talasnica_packetVolume(int packetFilter);
   /**
   * poèítadlo obchodù
   *
   * celkový profit v packetu
   */
   double talasnica_packetProfit(int packetFilter);
   /**
   * celkový swap v packetu
   *
   */
   double talasnica_packetSwap(int packetFilter);
   /**
   * profit + swap v packetu
   *
   */
   double talasnica_packetTotalProfit(int packetFilter);
   /**
   * aproximovaná vstupní cena v packetu
   *
   */
   double talasnica_packetOpenPrice(int packetFilter);
   /**
   * vrací ticket obchodu v packetu
   **/
   int talasnica_getTicket(int packetFilter, int orderIndex);
   /**
   * vrátí název paketu
   *
   */
   string talasnica_packetName(int packetFilter);
   /**
   * vrátí popis paketu
   *
   */
   string talasnica_packetDescription(int packetFilter);
   
#import

