//+------------------------------------------------------------------+
//|                                           talasnica_dateTime.mq4 |
//|                                 Copyright � 2005, MITHRADES a.s. |
//|                                        http://www.mithrades.com  |
//+------------------------------------------------------------------+
#property copyright "Copyright � 2006, MITHRADES a.s."
#property link      "http://www.xtrip.net"

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
#import "talasnica/dateTime/DateTime.ex4"
   string talasnica_dateToFileName();
   string talasnica_dateTimeToFileName();
#import

//+------------------------------------------------------------------+