//+------------------------------------------------------------------+
//|                                           talasnica_export.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"

#include <WinUser32.mqh>
#include <talasnica.inc-1.0.mqh>

#import "talasnica.lib-1.0.ex4"
   bool tl_OrderSelect(int type, int index);
   bool tl_OrderCnt();
   int tl_Log(string str, int errorLevel = 0);
   //int tl_OrderReverse();
   int tl_OrderTicket();
   datetime tl_OrderOpenTime();
   string tl_OrderName(int type);
   double tl_OrderLots();
   string tl_OrderSymbol();
   double tl_OrderOpenPrice();
   double tl_OrderStopLoss();
   double tl_OrderTakeProfit();
   double tl_OrderClosePrice();
   double tl_OrderSwap();
   double tl_OrderProfit();
   string tl_OrderComment();    
#import "stdlib.ex4"
   string ErrorDescription(int error_code);
#import

int handle;
//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
  {
  
   tl_Log("STARTUJE TALASNICA EXPORT SCRIPT", LOG_SCRIPT);
   tl_OrderCnt();
   
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
                     "OPEN TIME",
                     "TYPE",
                     "LOTS",
                     "SYMBOL",
                     "ENTER PRICE",
                     "STOPLOSS",
                     "TAKEPROFIT",
                     "PRICE",
                     "SWAP",
                     "PROFIT",
                     "COMMENT"
                     );
   
   for(int i = 0; i <= OP_SELLSTOP; i++) {
      export(i);
   }
   
   FileClose(handle);

   tl_Log("GOTOVO TALASNICA EXPORT", LOG_SCRIPT);

   //----
   return(0);
  }
//+------------------------------------------------------------------+

bool export(int type) {
   int i = 0;
      
   while(tl_OrderSelect(type, i)) {
      i++;
      
      FileWrite(handle, tl_OrderTicket(),
                        tl_OrderOpenTime(),
                        tl_OrderName(type),
                        tl_OrderLots(),
                        tl_OrderSymbol(),
                        tl_OrderOpenPrice(),
                        tl_OrderStopLoss(),
                        tl_OrderTakeProfit(),
                        tl_OrderClosePrice(),
                        tl_OrderSwap(),
                        tl_OrderProfit(),
                        tl_OrderComment()                        
                        );
   } 
}