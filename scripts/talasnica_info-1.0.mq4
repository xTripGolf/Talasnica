//+------------------------------------------------------------------+
//|                                                         Info.mq4 |
//|                                      Copyright � 2008, EvgeTrofi |
//+------------------------------------------------------------------+
#property copyright "Copyright � 2008, EvgeTrofi"
 
#include <WinUser32.mqh>
 
int start()
{
 if (!IsConnected())
 {
  MessageBox("Spojen� se serverem nebylo nav�z�no, nebo bylo p�eru�eno\t","Pozor!",MB_OK|MB_ICONERROR);
  return(-1);
 }
 string str2;
 string str="jm�no\t\t\tkonstanta\t\t\thodnota\t\tjednotka.\t\n\n";
 str=StringConcatenate(str,"spred\t\t\tSPREAD\t\t\t",MarketInfo(Symbol(),MODE_SPREAD),"\t\tbod�\t\n\n");
 str=StringConcatenate(str,"min. stop\t\t\tSTOPLEVEL\t\t",MarketInfo(Symbol(),MODE_STOPLEVEL),"\t\tbod�\t\n\n");
 str=StringConcatenate(str,"1 lot * 1 bod =\t\tTICKVALUE\t\t",MarketInfo(Symbol(),MODE_TICKVALUE),"\t\t",AccountCurrency(),"\t\n\n");
 switch(MarketInfo(Symbol(),MODE_SWAPTYPE))
 {
  case 0:
   str2="bod�";
   break;
  case 1:
   str2=Symbol();
   break;
  case 2:
   str2="%";
   break;
  case 3:
   str2=AccountCurrency();
   break;
 }
 str=StringConcatenate(str,"swap n�kupu\t\tSWAPLONG\t\t",MarketInfo(Symbol(),MODE_SWAPLONG),"\t\t",str2,"\t\n\n");
 str=StringConcatenate(str,"swap prodeje\t\tSWAPSHORT\t\t",MarketInfo(Symbol(),MODE_SWAPSHORT),"\t\t",str2,"\t\n\n");
 str=StringConcatenate(str,"minim�ln� lot\t\tMINLOT\t\t\t",MarketInfo(Symbol(),MODE_MINLOT),"\n\n");
 str=StringConcatenate(str,"krok lotu\t\t\tLOTSTEP\t\t\t",MarketInfo(Symbol(),MODE_LOTSTEP),"\n\n");
 double MaxLot = MarketInfo(Symbol(),MODE_MAXLOT);
 if(MaxLot>AccountFreeMargin()*0.99/MarketInfo(Symbol(),MODE_MARGINREQUIRED))//kde 0.99 - koeficient zapasa
    MaxLot=AccountFreeMargin()*0.99/MarketInfo(Symbol(),MODE_MARGINREQUIRED);
 str=StringConcatenate(str,"maxim�ln� lot = AccountFreeMargin() / MARGINREQUIRED = ",MaxLot,"\n\n");
 str=StringConcatenate(str,"Lot na ztr�tu 100 bod� = AccountFreeMargin() / 100 / TICKVALUE = ",AccountFreeMargin()/100/MarketInfo(Symbol(),MODE_TICKVALUE),"\n\n");
 
 if(MarketInfo(Symbol(),MODE_TRADEALLOWED)==0)
  str2="zak�z�no";
 else
  str2="povoleno";
 str=StringConcatenate(str,"\nObchodov�n� na trhu ",Symbol()," ",str2,"\n\n");
 MessageBox(str,"Informace o trhu "+Symbol(),MB_OK|MB_ICONINFORMATION);
 
 return(0);
}