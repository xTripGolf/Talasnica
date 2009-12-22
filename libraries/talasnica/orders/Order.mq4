//+------------------------------------------------------------------+
//|                                                        Order.mq4 |
//|                                 Copyright © 2006, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

#include "./../../../include/stdlib.mqh"
#include "./../../../include/talasnica_dll.mqh"
#include "./../../../include/talasnica_logger.mqh"
//#include "./../../../include/talasnica_session.mqh"

/****************************************************************
funkce pro obchodování
****************************************************************/

/*
vybere obchod ze seynamu obchodù
param type - typ obchodu
param index - poøadí v poli
*/

bool tl_OrderSelect(int type, int index) {
   
   int ticket = talasnica_getTicket(type, index);
   
   bool ret = OrderSelect(ticket, SELECT_BY_TICKET);
   
   if(!ret) {
      talasnica_logger_log ("Error in _OrderSelect() ticket = " + ticket + " : " + ErrorDescription(GetLastError()), LOG_ERROR);
   }
   
   return (ret);
   
}