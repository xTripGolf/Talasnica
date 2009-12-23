//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

//#include "./../../../include/stdlib.mqh"
#include "./../../../include/talasnica_dll.mqh"
//#include "./../../../include/talasnica_logger.mqh"
//#include "./../../../include/talasnica_session.mqh"

/****************************************************************
funkce pro poèítání obchodù
****************************************************************/

bool talasnica_recalculate(){
   
      //Print("Pøed resetem " + talasnica_getTradepacketInfo());
      talasnica_reset();
      //Print("Po resetu " + talasnica_getTradepacketInfo());
   
      for(int i = 0; i<OrdersTotal(); i++){
        if(OrderSelect(i,SELECT_BY_POS,MODE_TRADES) && OrderSymbol()==Symbol() /*&& OrderComment() == tl_Comment()*/){
        /*Print(OrderTicket()+ ", " +
                               OrderSymbol()+ ", " +
                               OrderOpenTime()+ ", " +
                               Talasnica::Type::Order()+ ", " +
                               OrderLots()+ ", " +
                               OrderOpenPrice()+ ", " +
                               OrderStopLoss()+ ", " +
                               OrderTakeProfit()+ ", " +
                               OrderExpiration()+ ", " +
                               OrderCloseTime()+ ", " +
                               OrderClosePrice()+ ", " +
                               OrderCommission()+ ", " +
                               OrderProfit()+ ", " +
                               OrderSwap()+ ", " +
                               OrderComment()+ ", " +
                               OrderMagicNumber()
                               );*/
           talasnica_addOrder(OrderTicket(),
                               OrderSymbol(),
                               OrderOpenTime(),
                               Talasnica::Type::Order(),
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
        
        talasnica_sortOrders();
   }
    return(true);
}