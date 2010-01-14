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
#include "./../../../include/talasnica_logger.mqh"
//#include "./../../../include/talasnica_session.mqh"

// Posunu do rohu
// 0 - Levy nahore
// 1 - Pravy nahore
// 2 - Levy dole
// 3 - Pravy dole
#define ROH_HORE_LEVO 0
#define ROH_HORE_PRAVO 1
#define ROH_DULE_LEVO 2
#define ROH_DULE_PRAVO 3

string InfoboxFontName = "Courier";

/**********************************************************************
funkce pro práci s infoBoxem
**********************************************************************/

bool talasnica_drawPacketNamesTable()
{

   // tyto hodnoty naèteme z dll knihovny
   int arraySize;
   string packetNames[];

  arraySize = talasnica_getPacketSize();
  ArrayResize(packetNames, arraySize);
  string err = talasnica_loadPacketNamesTable(packetNames, arraySize);
  
  int move = 16;
  int fontSize = 10;
  
  for(int i = 0; i < arraySize; i++) {
     LabelCreate("packet_name_" + i, 5, 40 + i * move, ROH_HORE_PRAVO, packetNames[i], fontSize, DarkGray);
  }
  
  errorLabel(err, "packet_name_error_");


}
bool talasnica_drawPacketsTable()
{

   // tyto hodnoty naèteme z dll knihovny
   int arraySize;
   string rows[];

  arraySize = talasnica_getPacketSize();
  arraySize++;
  ArrayResize(rows, arraySize);
  string err = talasnica_loadPacketsTable(rows, arraySize, Symbol());
  
  int sirkaRadku = 20;
  int fontSize = 10;
  color barva = DarkOliveGreen;
  
   for(int i = 0; i < arraySize; i++) {
      switch(i){
         // hlavièka
         case 0:
            barva = DarkOrange;
            break;
         // buy
         case 1:
            barva = colorByProfit(OP_BUY);
            break;
         // sell
         case 2:
            barva = colorByProfit(OP_SELL);
            break;
         // buy limit
          case 3:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // sell limit
          case 4:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // buy stop
          case 5:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // sell stop
          case 6:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // ztrátové
          case 7:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // profitabilní
          case 8:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // all opened
          case 9:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // all
          case 10:
            barva = colorByProfit(PACKET_ALL);
            break;
         // premoc min
          case 11:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // premoc max
          case 12:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         default:
            fontSize = 10;
            barva = DarkOliveGreen;
      }
      LabelCreate("packet_row_" + i, 5, 15 + i * sirkaRadku, ROH_HORE_PRAVO, rows[i], fontSize, barva);
   }
   
   errorLabel(err, "packet_row_error_");
   
}


color colorByProfit(int packet) {
   color barva;
   double profit = talasnica_packetTotalProfit(Symbol(), packet);
   if(profit == 0)
   {
      barva = Red;
   }
   else if (profit > 0)
   {
      barva = Chartreuse;//MediumSpringGreen;
   }
   else
   {
      barva = OrangeRed;
   }
   return(barva);
}

void errorLabel(string err, string labelName)
{
  if(err > ""){
      Print(err);
      int strlen =  StringLen(err);
      int subLen = 32;
      int start = 0;
      int i = 0;
      int move = 25;
      while(start < strlen){
         LabelCreate(labelName + i, 12, 40 + i * move, ROH_HORE_PRAVO, StringSubstr(err, start, subLen), 16, Red);
         start += subLen;
         i++;
   }
  }
}



/**
* Funkce na vytvareni popisku na grafu
*/

void LabelCreate(string _LabelName, int _OsaX, int _OsaY, int _Roh = 2, string _Text = "", int _FontSize = 12, color _Color = Yellow)
{
   int _GetLastError;

   //Vytvorim objekt
   if ( !ObjectCreate( _LabelName, OBJ_LABEL, 0, 0,  0) ){
      _GetLastError = GetLastError();
      if ( _GetLastError != 4200 )
      {
         talasnica_logger_log( "LabelCreate() - ObjectCreate( \"" +  _LabelName + "\") - Error #" +  _GetLastError + " )", LOG_ERROR);
         return(-1);
      }
}

   // Posunu do rohu
   // 0 - Levy nahore
   // 1 - Pravy nahore
   // 2 - Levy dole
   // 3 - Pravy dole

   ObjectSet( _LabelName, OBJPROP_CORNER, _Roh );
   //Posun dle osy X
   ObjectSet( _LabelName, OBJPROP_XDISTANCE, _OsaX );
   //Posun dle osy Y
   ObjectSet( _LabelName, OBJPROP_YDISTANCE, _OsaY );
   //Nastavim Text a Barvu textu
   ObjectSetText (_LabelName, _Text , _FontSize, InfoboxFontName, _Color);
}


/**
* vytvoøí textová pole pro seznam zámkù
*
*/

void CreateInfoBoxHedged() {
   //string tableHeader = formatText2Cell("bull") + formatText2Cell("bear") + formatText2Cell("price");
  /* int move = 18;
   
   // smazeme ty navic
   
   int i = tl_Zamceno();
   string name = "hedged_" + i;
   
   while (ObjectFind(name) >= 0) {
      ObjectDelete(name);
      i++;
      name = "hedged_" + i;
   }  
   
   // vytvorime ty potrebne
   
   for(i = 0; i < tl_Zamceno(); i++) {
      name = "hedged_" + i;
      if(ObjectFind(name) < 0) {
         LabelCreate(name, 5, 5 + i * move, ROH_DULE_LEVO, "#" + i, InfoboxFontSize, Yellow);
      } 
   }*/
}

/**
*
*
*
*
*
*/

void talasnica_refreshTradeList() {

   string label;

   double tickValue = MarketInfo(Symbol(), MODE_TICKVALUE);
   
   //int index;
   
   color barva;
    // tyto hodnoty naèteme z dll knihovny
   int arraySize;
   string packetNames[];

   for(int i = 0; i < arraySize; i++) {
      
      if (talasnica_packetCount(Symbol(), i) == 0) {
         barva = DarkGray;
      }
      else {              
         if (talasnica_packetTotalProfit(Symbol(), i) < 0) {
            barva = Magenta;
         }
         /*else if (talasnica_packetTotalProfit(index) < BerProfitPips * tickValue * StartLots) {
            barva = Aqua;
         }*/
         else {
            barva = LawnGreen;
         }
      }
      ObjectSetText(talasnica_packetName(i), label, 10, InfoboxFontName, barva);
   }
  
   // hedged
   CreateInfoBoxHedged();
   /*i = 0;
   int bulls = talasnica_packetCount(OP_BUY);
   int bears = talasnica_packetCount(OP_SELL);
   int iBears, iBulls;
   string name = "hedged_" + i;
   double profitZamku;
   while (ObjectFind(name) >= 0) {
      iBears = bears - i - 1;
      iBulls = bulls - i - 1;
      profitZamku = tl_getProfit(OP_BUY, iBulls) + tl_getProfit(OP_SELL, iBears);
      label = formatText2Cell(DoubleToStr(tl_getTicket(OP_BUY, iBulls), 0), INFOBOX_CELLSIZE_TICKET) +
              formatText2Cell(DoubleToStr(tl_getTicket(OP_SELL, iBears), 0), INFOBOX_CELLSIZE_TICKET) +
              formatText2Cell(DoubleToStr(profitZamku, 2), INFOBOX_CELLSIZE_PROFIT);
      if(profitZamku > 0) {
         barva = LawnGreen;
      }
      else {
         barva = Yellow;
      }
      ObjectSetText(name, label, InfoboxFontSize, InfoboxFontName, barva);
      i++;
      name = "hedged_" + i;
   }*/
 }

/**
* naformátuje text do tabulky
*
*/

string formatText2Cell(string text, int cellSize = 12) {
   
   int strLen = StringLen(text);
   
   if(strLen > cellSize) {
      text = StringSubstr(text, 0, cellSize);
      return(text);
   }
   else {
      string space;
      for(int i = 0; i < cellSize - strLen; i++) {
         space = space + " ";
      }
      return("|" + space + text );
   }
   
}


