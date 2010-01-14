//+------------------------------------------------------------------+
//|                                            talasnica_infoBox.mq4 |
//|                                 Copyright © 2006, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2006, MITHRADES a.s."
#property link      "http://www.mithrades.com"

//+------------------------------------------------------------------+
//| defines                                                          |
//+------------------------------------------------------------------+
// #define MacrosHello   "Hello, world!"
// #define MacrosYear    2005

//+------------------------------------------------------------------+
//| DLL imports                                                      |
//+------------------------------------------------------------------+
// #import "user32.dll"
//   int      SendMessageA(int hWnd,int Msg,int wParam,int lParam);

// #import "my_expert.dll"
//   int      ExpertRecalculate(int wParam,int lParam);
// #import

//+------------------------------------------------------------------+
//| EX4 imports                                                      |
//+------------------------------------------------------------------+
 #import "talasnica/infoBox/InfoBox.ex4"
   void talasnica_refreshTradeList();
   bool talasnica_drawPacketNamesTable();  
   bool talasnica_drawPacketsTable();
 #import
//+------------------------------------------------------------------+