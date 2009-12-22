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

#define INFOBOX_TABLEHEADER "header"

#define INFOBOX_STOPS "koliko èaka stopu" // poèet odložených obchodù
#define INFOBOX_LIMITS "koliko èaka limitek" // poèet odložených obchodù

#define INFOBOX_CELLSIZE_NAME 6
#define INFOBOX_CELLSIZE_COUNT 5
#define INFOBOX_CELLSIZE_VOLUME 6
#define INFOBOX_CELLSIZE_PRICE 8
#define INFOBOX_CELLSIZE_PROFIT 10

#define INFOBOX_CELLSIZE_TICKET 8

// Posunu do rohu
// 0 - Levy nahore
// 1 - Pravy nahore
// 2 - Levy dole
// 3 - Pravy dole
#define ROH_HORE_LEVO 0
#define ROH_HORE_PRAVO 1
#define ROH_DULE_LEVO 2
#define ROH_DULE_PRAVO 3

int InfoboxFontSize = 10;
string InfoboxFontName = "Courier";

int InfoboxRows[]; // øádky, které se zobrazí v infoboxu

/**********************************************************************
funkce pro práci s infoBoxem
**********************************************************************/
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
* vytvoøí informaèní box
*
*/

void talasnica_createTradeList() {

   string tableHeader = formatText2Cell("type", INFOBOX_CELLSIZE_NAME)
                        + formatText2Cell("count", INFOBOX_CELLSIZE_COUNT)
                        + formatText2Cell("volume", INFOBOX_CELLSIZE_VOLUME)
                        + formatText2Cell("price", INFOBOX_CELLSIZE_PRICE)
                        + formatText2Cell("profit", INFOBOX_CELLSIZE_PROFIT);
   
   int move = 16;

   int i, index;
   LabelCreate(INFOBOX_TABLEHEADER, 5, 20, ROH_HORE_PRAVO, tableHeader, InfoboxFontSize, Yellow);

   for(i = 0; i < ArraySize(InfoboxRows); i++) {
      index = InfoboxRows[i];
      LabelCreate(talasnica_getPacketName(index), 5, 40 + i * move, ROH_HORE_PRAVO, talasnica_getPacketName(index), InfoboxFontSize, DarkGray);
   }
   
   LabelCreate(INFOBOX_STOPS, 5, 40 + i * move, ROH_HORE_PRAVO, INFOBOX_STOPS, InfoboxFontSize, DarkGray);
   i++;
   LabelCreate(INFOBOX_LIMITS, 5, 40 + i * move, ROH_HORE_PRAVO, INFOBOX_LIMITS, InfoboxFontSize, DarkGray);
   
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
   
   label = "STOPS - još èaka " + talasnica_count(OP_BUYSTOP) + " gore " + talasnica_count(OP_SELLSTOP) + " dole ";
   ObjectSetText(INFOBOX_STOPS, label, InfoboxFontSize, InfoboxFontName, White);
   
   label = "LIMITS - još èaka " + talasnica_count(OP_BUYLIMIT) + " gore " + talasnica_count(OP_SELLLIMIT) + " dole ";
   ObjectSetText(INFOBOX_LIMITS, label, InfoboxFontSize, InfoboxFontName, White);

   double tickValue = MarketInfo(Symbol(), MODE_TICKVALUE);
   
   int index;
   
   color barva;
   
   for(int i = 0; i < ArraySize(InfoboxRows); i++) {
      index = InfoboxRows[i];
      label = formatText2Cell(talasnica_getPacketName(index), INFOBOX_CELLSIZE_NAME) +
              formatText2Cell(talasnica_count(index), INFOBOX_CELLSIZE_COUNT) +
              formatText2Cell(DoubleToStr(talasnica_volume(index), 2), INFOBOX_CELLSIZE_VOLUME) +
              formatText2Cell(DoubleToStr(talasnica_averageOpenPrice(index), Digits), INFOBOX_CELLSIZE_PRICE) +
              formatText2Cell(DoubleToStr(talasnica_totalProfit(index), 2), INFOBOX_CELLSIZE_PROFIT);
      if (talasnica_count(index) == 0) {
         barva = DarkGray;
      }
      else {              
         if (talasnica_totalProfit(index) < 0) {
            barva = Magenta;
         }
         /*else if (talasnica_totalProfit(index) < BerProfitPips * tickValue * StartLots) {
            barva = Aqua;
         }*/
         else {
            barva = LawnGreen;
         }
      }
      ObjectSetText(talasnica_getPacketName(index), label, InfoboxFontSize, InfoboxFontName, barva);
   }
  
   // hedged
   CreateInfoBoxHedged();
   /*i = 0;
   int bulls = talasnica_count(OP_BUY);
   int bears = talasnica_count(OP_SELL);
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


