//+------------------------------------------------------------------+
//|                                           talasnica_panClose.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property show_inputs

#include <WinUser32.mqh>
#include <talasnica.inc-1.0.mqh>

#import "talasnica.lib-1.0.ex4"
   bool tl_OrderSelect(int type, int index);
   bool tl_OrderCnt();
   int tl_OrderTicket();
   string tl_OrderName(int type);
   int tl_Log(string str, int errorLevel = 0);
   bool tl_OrderClose();
#import

extern bool zatvori_sve = false;
extern bool zatvori_buy = false;
extern bool zatvori_sell = false;
extern bool zatvori_buy_limit = false;
extern bool zatvori_sell_limit = false;
extern bool zatvori_buy_stop = false;
extern bool zatvori_sell_stop = false;

//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
  {
  
   tl_Log("STARTUJE TALASNICA PAN CLOSE SCRIPT", LOG_SCRIPT);
   
   //----
   
   tl_OrderCnt();
   
   bool toClose[6];
   toClose[0] = zatvori_buy;
   toClose[1] = zatvori_sell;
   toClose[2] = zatvori_buy_limit;
   toClose[3] = zatvori_sell_limit;
   toClose[4] = zatvori_buy_stop;
   toClose[5] = zatvori_sell_stop;
   
   for(int i = 0; i<6; i++) {
     if(toClose[i] || zatvori_sve) {
       panClose(i);
     }
   }

   tl_Log("GOTOVO TALASNICA PAN CLOSE", LOG_SCRIPT);

   //----
   return(0);
  }
//+------------------------------------------------------------------+

bool panClose(int type) {
   int i = 0;
   
   int potvrda = MessageBox("Da li èemo da izbrisamo sve " + tl_OrderName(type), "izbrisati " + tl_OrderName(type), MB_OKCANCEL);
   
   if(potvrda == IDCANCEL) {
      tl_Log("CANCEL " + tl_OrderName(type), LOG_SCRIPT);
      return(False);
   }
   
      tl_Log("CLOSE ALL " + tl_OrderName(type), LOG_SCRIPT);
   
   while(tl_OrderSelect(type, i)) {
      i++;
      if(tl_OrderClose ()) {
         tl_Log(tl_OrderTicket() + " closed", LOG_SCRIPT);
      }
      else {
         tl_Log(tl_OrderTicket() + " error", LOG_ERROR);
      } 
   }
}