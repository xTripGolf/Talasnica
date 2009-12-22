//+------------------------------------------------------------------+
//|                                              ExportFunctions.mq4 |
//|                      Copyright © 2005, MetaQuotes Software Corp. |
//|                                       http://www.metaquotes.net/ |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MetaQuotes Software Corp."
#property link      "http://www.metaquotes.net/"
#include <talasnica.inc-2.0.mqh>

//int environment = ENVIRONMENT_PRODUCTION;
string environment = ENVIRONMENT_DEVELOPMENT;

/*#define TIME_INDEX   0
#define OPEN_INDEX   1
#define LOW_INDEX    2
#define HIGH_INDEX   3
#define CLOSE_INDEX  4
#define VOLUME_INDEX 5*/
//+------------------------------------------------------------------+
//| expert initialization function                                   |
//+------------------------------------------------------------------+
int init()
  {
    
//---- 
   Print("******************************");
   Print("*** TALASNICA STARTUJE ***");
   Print("******************************");
   
   talasnica_log("talasnica::init()", LOG_INIT);
   
   talasnica_setEnvironment(environment);
   
   // nastavíme velikost lotù pro nové obchody
   
   //tl_setLots(StartLots);
   
   ObjectsDeleteAll(-1, OBJ_LABEL);
   
   //CreateInfoBox();
   
   Print("Obchodovaná mìna: Order Symbol = ", Symbol());
   
  /* if (Period() != xronos)
    {
    Print("Nastavena nesprávná perioda pracovního grafu.");
    Print("Perioda aktuálního grafu je ", Period(), ", požadovaná perioda je ", xronos);
    return (-1);
    }
   else {
   Print("Èasová perioda grafu: Period = ", Period());
   }*/
 
   // nezùstal zaseknutý globální InTrade ?
   // Jednou se mi to stalo, nešly obchody a já nevìdìl co s tím
   // Tohle to øeší
 
   if (GlobalVariableCheck("InTrade")) {
      GlobalVariableDel("InTrade");   // clear lock indicator
   }

//----
   
   return(1);
  }
//+------------------------------------------------------------------+
//| expert deinitialization function                                 |
//+------------------------------------------------------------------+
int deinit()
  {
//---- 

   Print("*** FUNCTION DEINIT ***");

//----
   Print("******************************");
   Print("*** TALASNICA GOTOVO ***");
   Print("******************************");
   talasnica_log("*** TALASNICA GOTOVO ***", LOG_INIT);
   return(0);
  }
//+------------------------------------------------------------------+
//| example - dll expert initialization function                                   |
//+------------------------------------------------------------------+
/*int init()
  {
   double ret,some_value=10.5;
   string sret;
   int    cnt;
   string strarray[6]={ "first", "second", "third", "fourth", "fifth" };
//---- simple dll-functions call
   cnt=GetIntValue(some_value);
   Print("Returned value is ",cnt);
   ret=GetDoubleValue(some_value);
   Print("Returned value is ",ret);
   sret=GetStringValue("some string");
   Print("Returned value is ",sret);
//----
   cnt=SortStringArray(strarray,ArraySize(strarray));
   for(int i=0; i<cnt; i++) Print(i," - ",strarray[i]);
   cnt=ProcessStringArray(strarray,ArraySize(strarray));
   for(i=0; i<cnt; i++) Print(i," - ",strarray[i]);
//----
   return(0);
  }*/
//+------------------------------------------------------------------+
//| array functions call                                             |
//+------------------------------------------------------------------+
int start()
  {
   
   talasnica_recalculate();
  
  //Print("Po naètení " + talasnica_getTradepacketInfo());
  
  /*******************************/
   /*double price;
   double arr[5]={1.5, 2.6, 3.7, 4.8, 5.9 };
   double rates[][6];
//---- get first item from passed array
   price=GetArrayItemValue(arr,5,0);
   Print("Returned from arr[0] ",price);
//---- change second item in the passed array
   if(SetArrayItemValue(arr,5,1,1234.5)==true)
      Print("Changed to ",arr[1]);
//---- get current close
   ArrayCopyRates(rates);
   price=GetRatesItemValue(rates,Bars,0,CLOSE_INDEX);
   Print("Returned from Close ",price);*/
//----
   return(0);
  }
//+------------------------------------------------------------------+