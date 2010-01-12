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
   void talasnica_reset(string symbol);
   void talasnica_sortOrders(string symbol);
   /**
   * po��tadlo obchod�
   *
   * po�et obchod� v packetu
   */
   int talasnica_packetCount(string symbol, int packetFilter);
   /**
   * po��tadlo obchod�
   *
   * po�et lot�  v packetu
   */
    double talasnica_packetVolume(string symbol, int packetFilter);
   /**
   * po��tadlo obchod�
   *
   * celkov� profit v packetu
   */
   double talasnica_packetProfit(string symbol, int packetFilter);
   /**
   * celkov� swap v packetu
   *
   */
   double talasnica_packetSwap(string symbol, int packetFilter);
   /**
   * profit + swap v packetu
   *
   */
   double talasnica_packetTotalProfit(string symbol, int packetFilter);
   /**
   * aproximovan� vstupn� cena v packetu
   *
   */
   double talasnica_packetOpenPrice(string symbol, int packetFilter);
   /**
   * vrac� ticket obchodu v packetu
   **/
   int talasnica_getTicket(string symbol, int packetFilter, int orderIndex);
   /**
   * vr�t� n�zev paketu
   *
   */
   string talasnica_packetName(int packetFilter);
 
   
#import

