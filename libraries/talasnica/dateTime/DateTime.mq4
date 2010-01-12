//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright © 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library


   string talasnica_dateToFileName() {
   
      int day = Day();
      string separator = "-";
      
      string fileName = Year() + separator + longFormat(Month()) + separator + longFormat(Day());
      
      return(fileName);
   }
   
   
   string talasnica_dateTimeToFileName(){
   
      string separator = "-";
      string fileName = talasnica_dateToFileName() + "___" + longFormat(Hour()) + separator + longFormat(Minute()) + separator + longFormat(Seconds());
      
      return(fileName);
   }
   
   
   string longFormat(int value) {
   
      string text = value;
   
      if(value < 10) {
         text = "0" + text;
      }
      return(text);
   }