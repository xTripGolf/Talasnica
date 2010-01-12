//+------------------------------------------------------------------+
//|                                           talasnica_export.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"

#include <WinUser32.mqh>
#include <talasnica_session.mqh>
#include <talasnica_logger.mqh>
#include <talasnica_dll.mqh>
#include <stdlib.mqh>
#include <talasnica_dateTime.mqh>
#property show_inputs

extern bool export_trades = true;
extern bool export_history = false;
extern bool export_all_symbol = true;
bool development_mode = true;

int handle;
//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
  {
   string name = "talasnica export trades";

   talasnica_session_setId(name);
   if(development_mode) {
      talasnica_session_setEnv(ENVIRONMENT_DEVELOPMENT);
   }
   talasnica_logger_init(talasnica_session_getEnv(), talasnica_session_getId());
   //Print("volamo talasnica_session_getId() z main " + talasnica_session_getId());
  
   talasnica_logger_log("STARTUJE TALASNICA EXPORT SCRIPT", LOG_SCRIPT);
   
   //----
   handle = FileOpen(getFileName(), FILE_CSV|FILE_WRITE|FILE_READ, ';');

   if(handle < 1)
   {
     Print("can\'t open export file. Error-" + ErrorDescription(GetLastError()));
     return (false);
   }
   
   //FileSeek(handle,0,SEEK_END);
   
   FileWrite(handle, "TICKET",
                     "SYMBOL",
                     "OPEN TIME",
                     "TYPE",
                     "LOTS",
                     "OPEN PRICE",
                     "STOPLOSS",
                     "TAKEPROFIT",
                     "EXPIRATION",
                     "CLOSE TIME",
                     "CLOSE PRICE",
                     "COMMISSION",
                     "PROFIT",
                     "SWAP",  
                     "COMMENT",
                     "MAGIC NUMBER"
                     );
 
   
   if(export_trades){
    export_trades();
   }
   
   if(export_history){
    export_history();
   }
   
   FileClose(handle);

   talasnica_logger_log("GOTOVO TALASNICA EXPORT", LOG_SCRIPT);

   //----
   return(0);
  }
//+------------------------------------------------------------------+

string getFileName() {

   string pool;
   string symbol;
   string separator = "-";

   if(export_all_symbol) {
      symbol = "ALL";
   }
   else {
      symbol = Symbol();
   }

   if(export_trades && export_history) {
      pool = "trades-and-history";
   }
   else {
      if(export_trades) {
         pool = "trades";
      }
   
      if(export_history) {
         pool = "history";
      }   
   }
     

   
   string file = talasnica_logger_getPath() + symbol + separator + pool + separator + talasnica_dateTimeToFileName() + ".csv";
 
   return(file);
}

void export_trades() {
  export(MODE_TRADES, OrdersTotal());
}

void export_history() {
  export(MODE_HISTORY, OrdersHistoryTotal());
}

void export(int pool, int total) {

   for(int i = 0; i<total; i++){
        if(OrderSelect(i,SELECT_BY_POS,pool)){
           FileWrite(handle, OrderTicket(),
                               OrderSymbol(),
                               talasnica_formatTime(OrderOpenTime(), "%A %d.%B %Y %H:%M:%S"),
                               talasnica_orderName(OrderType()),
                               OrderLots(),
                               OrderOpenPrice(),
                               OrderStopLoss(),
                               OrderTakeProfit(),
                               talasnica_formatTime(OrderExpiration(), "%A %d.%B %Y %H:%M:%S"),
                               talasnica_formatTime(OrderCloseTime(), "%A %d.%B %Y %H:%M:%S"),
                               OrderClosePrice(),
                               OrderCommission(),
                               OrderProfit(),
                               OrderSwap(),
                               OrderComment(),
                               OrderMagicNumber()
                               );
        }
      }
}


