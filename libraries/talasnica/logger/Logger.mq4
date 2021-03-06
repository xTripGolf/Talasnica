//+------------------------------------------------------------------+
//|                                                   talasnica.mq4 |
//|                                 Copyright � 2005, MITHRADES a.s. |
//|                                         http://www.mithrades.com |
//+------------------------------------------------------------------+
#property copyright "Copyright � 2005, MITHRADES a.s."
#property link      "http://www.mithrades.com"
#property library

#include "./../../../include/stdlib.mqh"
//#include "./../../../include/talasnica_dll.mqh"
//#include "./../../../include/talasnica_logger.mqh"
#include "./../../../include/talasnica_session.mqh"
#include "./../../../include/talasnica_dateTime.mqh"

/*****************************************
loging
******************************************/
// p�en�� nastaven� session z hlavn�ho scriptu
bool talasnica_logger_init(string environment, string id){
   talasnica_session_setId(id);
   talasnica_session_setEnv(environment);
}

/**
* zap�e �et�zec do logovac�ho souboru
*/
 
 int talasnica_logger_log(string str, int level = 0)
{
   
   if(talasnica_session_getEnv() == ENVIRONMENT_DEVELOPMENT){
      Print(str);
      //return(0);
   }

   int handle;
 
   handle = FileOpen(talasnica_logger_getFileName(), FILE_CSV|FILE_WRITE|FILE_READ, ';');
   if(handle < 1)
   {
     Print("can't open journal file. Error-" + ErrorDescription(GetLastError()));
   }
   else {
      FileSeek(handle,0,SEEK_END);
      str = tl_Vcil() + "\t" + str;
      FileWrite(handle, str);
   } 
   FileClose(handle);
   //Print("LOG level " + level);
   //Print(">> " + str);
}

/**
* vrac� cestu k log souboru
*
*/

string talasnica_logger_getFileName () {
   string filename = talasnica_logger_getPath() + Symbol() + "_" + talasnica_dateToFileName() + ".log";
   //Print("talasnica_logger_getFileName > " + filename);
   return (filename);
}

string talasnica_logger_getPath () {
   string filename = AccountName() + "/" + talasnica_session_getId() + "." + talasnica_session_getEnvName() + "/";
   //Print("talasnica_logger_getPath () > " + filename);
   return (filename);
}

/**
* aktu�ln� �as jako �et�zec
*/

string tl_Vcil() {
   return (Symbol() + " at " + TimeToStr(TimeCurrent(),TIME_DATE|TIME_SECONDS));
}

void talasnica_logger_err(string err)
{
   string name = "error_log";
   ObjectCreate(name, OBJ_LABEL, 0, 0, 0);
   ObjectSet(name, OBJPROP_CORNER, 0);
   //Posun dle osy X
   ObjectSet(name, OBJPROP_XDISTANCE, 40 );
   //Posun dle osy Y
   //ObjectSet(name, OBJPROP_YDISTANCE, 0 );
   //Nastavim Text a Barvu textu
   ObjectSetText (name, err , 36, "Courier", Red);
}

