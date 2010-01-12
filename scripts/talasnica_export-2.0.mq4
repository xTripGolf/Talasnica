//+------------------------------------------------------------------+
//|                                           talasnica_export.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"

#include <WinUser32.mqh>
#include <talasnica_logger.mqh>
#include <stdlib.mqh>
#property show_inputs

extern bool export_trades = true;
extern bool export_history = false;

int handle;
//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
  {
  
   talasnica_logger_log("STARTUJE TALASNICA EXPORT SCRIPT", LOG_SCRIPT);
   
   //----
   handle = FileOpen(Symbol() + "-" + 
             Year()+ "-" + 
             Month() + "-" + 
             Day() + "-" +
             Hour() + "-" +
             Minute() + "-" +
             Seconds() + ".txt", FILE_CSV|FILE_WRITE|FILE_READ, ';');

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
                               OrderOpenTime(),
                               OrderType(),
                               OrderLots(),
                               OrderOpenPrice(),
                               OrderStopLoss(),
                               OrderTakeProfit(),
                               OrderExpiration(),
                               OrderCloseTime(),
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