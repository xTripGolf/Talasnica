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
                             datetime openTime,
                             int orderType,
                             double lots,
                             double openPrice,
                             double stopLoss,
                             double takeProfit,
                             datetime expiration,
                             datetime closeTime,
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
   * poèítadlo obchodù
   *
   * poèet obchodù v packetu
   */
   int talasnica_packetCount(string symbol, int packetFilter);
   /**
   * poèítadlo obchodù
   *
   * poèet lotù  v packetu
   */
    double talasnica_packetVolume(string symbol, int packetFilter);
   /**
   * poèítadlo obchodù
   *
   * celkový profit v packetu
   */
   double talasnica_packetProfit(string symbol, int packetFilter);
   /**
   * celkový swap v packetu
   *
   */
   double talasnica_packetSwap(string symbol, int packetFilter);
   /**
   * profit + swap v packetu
   *
   */
   double talasnica_packetTotalProfit(string symbol, int packetFilter);
   /**
   * aproximovaná vstupní cena v packetu
   *
   */
   double talasnica_packetOpenPrice(string symbol, int packetFilter);
   /**
   * vrací ticket obchodu v packetu
   **/
   int talasnica_getTicket(string symbol, int packetFilter, int orderIndex);
   /**
   * vrátí název paketu
   *
   */
   string talasnica_packetName(int packetFilter);
   /**
   * vrátí název typu obchodu
   *
   */
   string talasnica_orderName(int orderType);
   /**
   * formátuje èas
         specifier	Replaced by	Example
      %a	Abbreviated weekday name *	Thu
      %A	Full weekday name * 	Thursday
      %b	Abbreviated month name *	Aug
      %B	Full month name *	August
      %c	Date and time representation *	Thu Aug 23 14:55:02 2001
      %d	Day of the month (01-31)	23
      %H	Hour in 24h format (00-23)	14
      %I	Hour in 12h format (01-12)	02
      %j	Day of the year (001-366)	235
      %m	Month as a decimal number (01-12)	08
      %M	Minute (00-59)	55
      %p	AM or PM designation	PM
      %S	Second (00-61)	02
      %U	Week number with the first Sunday as the first day of week one (00-53)	33
      %w	Weekday as a decimal number with Sunday as 0 (0-6)	4
      %W	Week number with the first Monday as the first day of week one (00-53)	34
      %x	Date representation *	08/23/01
      %X	Time representation *	14:55:02
      %y	Year, last two digits (00-99)	01
      %Y	Year	2001
      %Z	Timezone name or abbreviation	CDT
      %%	A % sign	%

         **/
   string talasnica_formatTime(datetime unixFormat, string format);
   
   /**
   * vrací velikost pole packetù

   **/
   int talasnica_getPacketSize();
   
   /**
   * nastaví jména packetù do pole
   *
   * používat takto
     string packetNames[];
     packetSize = talasnica_getPacketSize();
     ArrayResize(packetNames, packetSize);
     string err = talasnica_loadPacketNamesTable(packetNames, packetSize)
     if(err > ""){
      Print(err);
     }
   **/
   string talasnica_loadPacketNamesTable(string& arr[], int arraySize);  
   string talasnica_loadPacketsTable(string& arr[], int arraySize, string symbol);
   

 
   
#import

