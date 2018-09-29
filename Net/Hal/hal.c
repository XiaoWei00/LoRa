#include "hal.h"
#include "rf.h"
#include "app.h"

#include "IotOS.h"


unsigned char sendnum=0;
static void ATInstruct(void);


unsigned short hal_process_events(unsigned char tasksId,unsigned short events)
{
    (void)tasksId;  //未使用参数    
    if(events & AT_INSTRUCT)
    {
       ATInstruct();
       return (events ^ AT_INSTRUCT);
    }
  return events;
}



/*************AT指令集*********/
static void ATInstruct()
{
char ATcommand1[]="LoRa";
char ATcommand2[]="softversion";
char ATcommand3[]="channel";
char ATcommand4[]="power";
////////setchannel/////////////////
char ATccommand1[]="setchannel1";
char ATccommand2[]="setchannel2";
char ATccommand3[]="setchannel3";
char ATccommand4[]="setchannel4";
char ATccommand5[]="setchannel5";
/////////setpower/////////

char ATpcommand1[]="setpower1";
char ATpcommand2[]="setpower2";
char ATpcommand3[]="setpower3";
char ATpcommand4[]="setpower4";

///////////////send///////////
char ATscommand[]="send";


  if(strcmp((const char *)ATcommand1,(const char *)uRxDate)==0)  //LoRa
  {
    printf("ATInstruct ok\r\n");
    printf("AT+softversion    Query the software version number\r\n");
    printf("AT+channel        Query rf channel\r\n");
    printf("AT+power          Query rf power\r\n");
    printf("AT+setchannel[x]  Set rf channel\r\n");
    printf("channel1:433M,channel2:434M,channel3:435M,channel4:436M,channel5:437M\r\n");
    printf("AT+setpower[x]  Set rf power\r\n");
    printf("power1:20dbm,power2:17dbm,power3:14dbm,power4:11dbm\r\n");
  }
  
 else if(strcmp((const char *)ATcommand2,(const char *)uRxDate)==0)  //softversion
 {
     printf("Softversion=%d\r\n",rfParmeter.softVersion);
 }
   
  else if(strcmp((const char *)ATcommand3,(const char *)uRxDate)==0)  //channel
  {
    printf("Channel=%d MHz\r\n",rfParmeter.rfChannel);
  }
  
  else if(strcmp((const char *)ATcommand4,(const char *)uRxDate)==0) //power
  {
    printf("Power=%d dbm\r\n",rfParmeter.rfPower);
  }
  
  else if(strcmp((const char *)ATccommand1,(const char *)uRxDate)==0) //setchannel1
  {
      rf_setChannel(CHANNEL1);
      printf("Setup channel success,Channel=%d MHz\r\n",rfParmeter.rfChannel);
  }
  else if(strcmp((const char *)ATccommand2,(const char *)uRxDate)==0) //setchannel2
  {
      rf_setChannel(CHANNEL2);
      printf("Setup channel success,Channel=%d MHz\r\n",rfParmeter.rfChannel);
  }
  else if(strcmp((const char *)ATccommand3,(const char *)uRxDate)==0) //setchannel3
  {
      rf_setChannel(CHANNEL3);
      printf("Setup channel success,Channel=%d MHz\r\n",rfParmeter.rfChannel);
  }
  else if(strcmp((const char *)ATccommand4,(const char *)uRxDate)==0) //setchannel4
  {
      rf_setChannel(CHANNEL4);
      printf("Setup channel success,Channel=%d MHz\r\n",rfParmeter.rfChannel);
  }  
  else if(strcmp((const char *)ATccommand5,(const char *)uRxDate)==0) //setchannel5
  {
      rf_setChannel(CHANNEL5);
      printf("Setup channel success,Channel=%d MHz\r\n",rfParmeter.rfChannel);
  }
  
   else if(strcmp((const char *)ATpcommand1,(const char *)uRxDate)==0) //setpower1
  {
      rf_setPower(POWER1);
      printf("Setup power success,Power=%d dbm\r\n",rfParmeter.rfPower);
  }
  else if(strcmp((const char *)ATpcommand2,(const char *)uRxDate)==0) //setpower2
  {
      rf_setPower(POWER2);
      printf("Setup power success,Power=%d dbm\r\n",rfParmeter.rfPower);
  }
  else if(strcmp((const char *)ATpcommand3,(const char *)uRxDate)==0) //setpower3
  {
      rf_setPower(POWER3);
      printf("Setup power success,Power=%d dbm\r\n",rfParmeter.rfPower);
  }
  else if(strcmp((const char *)ATpcommand4,(const char *)uRxDate)==0) //setpower4
  {
      rf_setPower(POWER4);
      printf("Setup power success,Power=%d dbm\r\n",rfParmeter.rfPower);
  }
  
  else if(strncmp((const char *)ATscommand,(const char *)uRxDate,4)==0)
 {

    sendnum=sizeof(uRxDate)-4;
    tasksEvents[APP] |=SEND_URAT_MESSAGE; //
 }
 
  else
  {
   printf("ATInstruct error\r\n");
  }
    
}
