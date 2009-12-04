//+------------------------------------------------------------------+
//|                                                  draw_trades.mq4 |
//|                      Copyright © 2008, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2008, MetaQuotes Software Corp."
#property link      "http://www.metaquotes.net"
#property show_inputs

//+------------------------------------------------------------------+
//| script program start function                                    |
//+------------------------------------------------------------------+
int start()
  {
//----

   Print("STARTUJE TALASNICA DRAW TRADES");

   // retrieving info from trade history
  int i,hstTotal=OrdersHistoryTotal();
  
  Print("Vykreslím z historie " + hstTotal + " obchodù.");
   
  datetime time1, time2, time3;
  double price1, price2;
  string name;
  color color1 = DarkOrange, color2 = DarkTurquoise, color3 = DarkViolet;
  
  ObjectsDeleteAll(0, OBJ_TRIANGLE);
  ObjectsDeleteAll(0, OBJ_TREND);
  
  for(i=0;i<hstTotal;i++)
    {
     //---- check selection result
     if(OrderSelect(i,SELECT_BY_POS,MODE_HISTORY)==false)
       {
        Print("Access to history failed with error (",GetLastError(),")");
        break;
       }
     // some work with order
     time1 = OrderOpenTime();
     time2 = OrderCloseTime();
     time3 = TimeCurrent();
     price1 = OrderOpenPrice();
     price2 = OrderClosePrice();
     
     name = "openTriangle_" + i;
     //Print(name, " ", time1, " - ", time2, " :: ", price1, " - ", price2);
     ObjectCreate(name, OBJ_TRIANGLE, 0, time1, price1, time2, price2, time2, price1);
     ObjectSet(name, OBJPROP_COLOR, color1);
     
     name = "inputLine_" + i;
     ObjectCreate(name, OBJ_TREND, 0, time2, price1, time3, price1);
     ObjectSet(name, OBJPROP_COLOR, color2); 
     
     name = "outputLine_" + i;
     ObjectCreate(name, OBJ_TREND, 0, time2, price2, time3, price2);
     ObjectSet(name, OBJPROP_COLOR, color3);
     
     
    }

//----
   return(0);
  }
//+------------------------------------------------------------------+