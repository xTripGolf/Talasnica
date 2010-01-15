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

#define VYSKA_RADKU_TEXT 20

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
   string rows[];

  ArrayResize(rows, PACKET_TABLE_ROWS);
  string err = talasnica_loadPacketsTable(rows, PACKET_TABLE_ROWS, Symbol());
  
  int vyskaRadku = VYSKA_RADKU_TEXT;
  int posun = 5;
  int fontSize = 10;
  color barva = DarkOliveGreen;
  
   for(int i = 0; i < PACKET_TABLE_ROWS; i++) {
      switch(i){
         // oddìlovaèe øádkù
         case 0:
         case 2:
         case 5:
         case 7:
         case 10:
         case 16:
         case 19:
            barva = LawnGreen;
            vyskaRadku = 10;
            break;        
         // hlavièka
         case 1:
            barva = LawnGreen;
            break;
         // buy
         case 3:
            barva = colorByProfit(OP_BUY);
            break;
         // sell
         case 4:
            barva = colorByProfit(OP_SELL);
            break;
         // buy limit
          case 12:
            barva = colorByCount(PACKET_BUY_LIMIT);
            break;
         // sell limit
          case 13:
            barva = colorByCount(PACKET_SELL_LIMIT);
            break;
         // buy stop
          case 14:
            barva = colorByCount(PACKET_BUY_STOP);
            break;
         // sell stop
          case 15:
            barva = colorByCount(PACKET_SELL_STOP);
            break;
         // ztrátové
          case 9:
            barva = colorByProfit(PACKET_LOSSED);
            break;
         // profitabilní
          case 8:
            barva = colorByProfit(PACKET_PROFITED);
            break;
         // all opened
          case 6:
            barva = colorByProfit(PACKET_ALL_OPENED);
            break;
         // all
          case 11:
            barva = colorByCount(PACKET_ALL);
            break;
         // premoc min
          case 17:
            barva = colorByProfit(PACKET_PREMOC_MIN);
            break;
         // premoc max
          case 18:
            barva = colorByProfit(PACKET_PREMOC_MAX);
            break;
         default:
            fontSize = 10;
            barva = DarkOliveGreen;
      }
      posun += vyskaRadku;
      LabelCreate("packet_row_" + i, 5, posun, ROH_HORE_PRAVO, rows[i], fontSize, barva);
      // výchozí hodnota
      vyskaRadku = VYSKA_RADKU_TEXT;
   }
   
   errorLabel(err, "packet_row_error_");
   
}


color colorByProfit(int packet) {
   color barva;
   double profit = talasnica_packetTotalProfit(Symbol(), packet);
   if(profit > -1 && profit < 1)
   {
      barva = Teal;
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

color colorByVolume(int packet) {
   color barva;
   double volume = talasnica_packetVolume(Symbol(), packet);
   if(volume > -0.01 && volume < 0.01)
   {
      barva = Teal;
   }
   else if (volume > 0)
   {
      barva = Chartreuse;//MediumSpringGreen;
   }
   else
   {
      barva = OrangeRed;
   }
   return(barva);
}

color colorByCount(int packet) {
   color barva;
   double count = talasnica_packetCount(Symbol(), packet);
   if(count > 0)
   {
      barva = Gold;
   }
   else
   {
      barva = Teal;
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
* naformátuje text do tabulky
*
* nepoužívá se, dll si to formátuje samo
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


