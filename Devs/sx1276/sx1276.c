#include "board_cfg.h"
#include "sx1276.h"
#include "s_spi.h"
#include "rf.h"

u8 cca;
u8 gb_SF;
u8 gb_BW;
u8  CR;	//LR_RegModemConfig1 


#define CRC   0x01  //CRC Enable

#define datlen 20  

u8 gtmp;

/**********************************************************
**Parameter table define
**********************************************************/
//__root const u16 SX1276FreqTbl[3] = {0x066C, 0x0780, 0x0800}; //434MHz
//__root const u16 SX1276FreqTbl[3] = {0x0685, 0x073b, 0x0813}; //533MHz @ 26m
//__root const u16 SX1276FreqTbl[3] = {0x0634, 0x0700, 0x0800}; //169MHz @ 26m

__root const u16 SX1276Channel1[3]={0x066C,0x0740,0x0800};   //433MHz
__root const u16 SX1276Channel2[3]={0x066C,0x0780,0x0800};   //434MHz
__root const u16 SX1276Channel3[3]={0x066C,0x07C0,0x0800};   //435MHz
__root const u16 SX1276Channel4[3]={0x0660,0x0700,0x0800};   //436MHz
__root const u16 SX1276Channel5[3]={0x066D,0x0740,0x0800};   //437MHz

__root const u16 SX1276PowerTbl[4] =
{ 
  0x09FF,                   //20dbm  
  0x09FC,                   //17dbm
  0x09F9,                   //14dbm
  0x09F6,                   //11dbm 
};


__root const u8 SX1276LoRaBwTbl[10] =
{// 0        1     2       3      4       5         6      7       8      9
//7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
  0,1,2,3,4,5,6,7,8,9
};
__root const u8 SX1276SpreadFactorTbl[7] =
{
  6,7,8,9,10,11,12
};

unsigned char gb_RxData[32];         //Receive data buffer

void delayms(unsigned int t)
{
	unsigned int i;
	unsigned char j; 
	for(i=0;i<t;i++)
	for(j=0;j<120;j++);
}
void Sx1276M_GpioInt()
{
    sspi_init();
    SET_RFRST_PIN();
    SET_RFIRQ_PIN();
    SET_RFCAD_PIN();
   // SET_RFSWITCH_PIN();
}

void RF_IRQ_DS()
{
    PD_CR2_C23=0;
}

void RF_IRQ_EN()
{
   PD_CR2_C23=1;
}


void SX1276_Parameters_Select()
{
  
 //125KHz BW   SF=10;  Error coding rate=4/6
        /****BW 选择*********/
        //gb_BW=1;//10.4K  BW
        //gb_BW=2;//15.6K  BW 
        //gb_BW=3;//20.8K  BW 
        //gb_BW=4;//31.2K  BW 
        //gb_BW=5;//41.7K  BW 
        //gb_BW=6;//62.5K  BW 
        gb_BW=7;//125KHz BW 
        /****BW 选择结束*********/

        /*******SF 选择*********/
        //gb_SF=0;// SF=6;  64 chips / symbol
        //gb_SF=1;// SF=7;  128 chips / symbol
        //gb_SF=2;// SF=8;  256 chips / symbol
        //gb_SF=3;// SF=9;  9  512 chips / symbol
        gb_SF=4;////SF=10; 1024 chips / symbol
        //gb_SF=5;////SF=11; 2048 chips / symbol
        //gb_SF=6;//SF=12;  4096 chips / symbol
        /****SF 选择结束*********/

        /*******CR 选择*********/
        //CR=1;////  Error coding rate=4/5
        CR=2;////  Error coding rate=4/6
        //CR=3;////  Error coding rate=4/7
        //CR=4;////  Error coding rate=4/8
        /*******CR 选择结束*********/
      
            
}
/*
void SW_Swith_RX()
{
  
}

void SW_Swith_TX()
{

}
*/
/******************
设置射频信道
****/
void SX1276_SetChannel(u8 channel)
{
  u8 i=0;
  
  SX1276_Sleep();           //Change modem mode Must in Sleep mode 
  for(i=100;i!=0;i--)      //Delay
    asm("NOP");
  

  switch(channel)
  {
  case CHANNEL1:  //433
    {
      for(i=0;i<3;i++)          //setting frequency parameter
      {
        SPIWrite(SX1276Channel1[i]);  
      }
      rfParmeter.rfChannel=433;
    }
    break;
    
   case CHANNEL2:  //434
    {
      for(i=0;i<3;i++)          //setting frequency parameter
      {
        SPIWrite(SX1276Channel2[i]);  
      }
      rfParmeter.rfChannel=434;
    }
    break;
   case CHANNEL3:  //435
    {
      for(i=0;i<3;i++)          //setting frequency parameter
      {
        SPIWrite(SX1276Channel3[i]);  
      }
      rfParmeter.rfChannel=435;
    }
    break;
    case CHANNEL4:
    {
      for(i=0;i<3;i++)          //setting frequency parameter
      {
        SPIWrite(SX1276Channel4[i]);  
      }
      rfParmeter.rfChannel=436;
    }
    break;
    case CHANNEL5:
    {
      for(i=0;i<3;i++)          //setting frequency parameter
      {
        SPIWrite(SX1276Channel5[i]);  
      }
      rfParmeter.rfChannel=437;
    }
    break;
  }
  SX1276_LoRaEntryRx();
}

/******************
设置射频功率
*****************/
void SX1276_SetPower(u8 power)
{
  u8 i=0;
  SX1276_Sleep();           //Change modem mode Must in Sleep mode 
  for(i=100;i!=0;i--)      //Delay
    asm("NOP");
  switch(power)
  {
   case POWER1:
     rfParmeter.rfPower=20;
      break;
   case POWER2:
     rfParmeter.rfPower=17;
    break;
   case POWER3:
     rfParmeter.rfPower=14;
    break;
   case POWER4:
     rfParmeter.rfPower=11;
     break;
  }
 SPIWrite(SX1276PowerTbl[power]);    //20dbm         //Setting output power parameter
}




/**********************************************************
**Name:     SX1276_Standby
**Function: Entry standby mode
**Input:    None
**Output:   None
**********************************************************/
void SX1276_Standby(void)
{
  SPIWrite(LR_RegOpMode+0x01+0x08);                              //Standby
}

/**********************************************************
**Name:     SX1276_Sleep
**Function: Entry sleep mode
**Input:    None
**Output:   None
**********************************************************/
void SX1276_Sleep(void)
{
  SPIWrite(LR_RegOpMode+0x00+0x08);                              //Sleep
}

/*********************************************************/
//LoRa mode
/*********************************************************/
/**********************************************************
**Name:     SX1276_EntryLoRa
**Function: Set RFM69 entry LoRa(LongRange) mode
**Input:    None
**Output:   None
**********************************************************/
void SX1276_EntryLoRa(void)
{
  SPIWrite(LR_RegOpMode+0x80+0x08);
}

/**********************************************************
**Name:     SX1276_LoRaClearIrq
**Function: Clear all irq
**Input:    None
**Output:   None
**********************************************************/
void SX1276_LoRaClearIrq(void)
{
  SPIWrite(LR_RegIrqFlags+0xFF);
}

/**********************************************************
**Name:     SX1276_Config
**Function: SX1276 base config
**Input:    mode
**Output:   None
**********************************************************/
void SX1276_baseConfig()
{
  u8 i;
  
  //复位 
  RF_RST=0;
  for(i=150;i!=0;i--)                                      //Delay
    asm("NOP"); 
  
  RF_RST=1;
  
  for(i=100;i!=0;i--)                                      //Delay
    asm("NOP");  
    
  SX1276_Sleep();                                           //Change modem mode Must in Sleep mode 
  for(i=100;i!=0;i--)                                      //Delay
    asm("NOP");  

    SPIWrite(REG_LR_TCXO+0x09);                              //USE TCXO
    SX1276_EntryLoRa();  
  
     //设置频段
    for(i=0;i<3;i++)                                       //setting frequency parameter
    {
      SPIWrite(SX1276Channel1[i]);   //433MHz
    }
    rfParmeter.rfChannel=433;
     
    
    //setting base parameter 
    //设置功率
    SPIWrite(SX1276PowerTbl[0]);    //20dbm         //Setting output power parameter
    rfParmeter.rfPower=20;
    
    
    SPIWrite(LR_RegOcp+0x0B);                              //RegOcp,Close Ocp
    SPIWrite(LR_RegLna+0x23);                              //RegLNA,High & LNA Enable

	
    
    if(SX1276SpreadFactorTbl[gb_SF]==6)           //SFactor=6
    {
      u8 tmp;
      SPIWrite(LR_RegModemConfig1+(SX1276LoRaBwTbl[gb_BW]<<4)+(CR<<1)+0x01);//Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
      SPIWrite(LR_RegModemConfig2+(SX1276SpreadFactorTbl[gb_SF]<<4)+(CRC<<2)+0x03);
      
      tmp = SPIRead(0x31);
      tmp &= 0xF8;
      tmp |= 0x05;
      SPIWrite(0x3100+tmp);
      SPIWrite(0x3700+0x0C);
    } 
    else
    {
      SPIWrite(LR_RegModemConfig1+(SX1276LoRaBwTbl[gb_BW]<<4)+(CR<<1)+0x00);//Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
      SPIWrite(LR_RegModemConfig2+(SX1276SpreadFactorTbl[gb_SF]<<4)+(CRC<<2)+0x03);  //SFactor &  LNA gain set by the internal AGC loop 
      SPIWrite(LR_RegModemConfig3+0x08);//LowDataRateOptimize en
    }
    SPIWrite(LR_RegSymbTimeoutLsb+0xFF);                   //RegSymbTimeoutLsb Timeout = 0x3FF(Max) 
    
    SPIWrite(LR_RegPreambleMsb + 0);                       //RegPreambleMsb 
    SPIWrite(LR_RegPreambleLsb + 16);                      //RegPreambleLsb 8+4=12byte Preamble  16+4=20
    
    SPIWrite(REG_LR_DIOMAPPING2+0x01);                     //RegDioMapping2 DIO5=00, DIO4=01
    SX1276_Standby();                                         //Entry standby mode
   
}

/**********************************************************
**Name:     SX1276_LoRaEntryRx
**Function: Entry Rx mode
**Input:    None
**Output:   None
**********************************************************/
void SX1276_LoRaEntryRx(void)
{
  u8 addr; 
        
  SPIWrite(0x4D00+0x84);                                   //Normal and Rx
  SPIWrite(LR_RegHopPeriod+0xFF);                          //RegHopPeriod NO FHSS
  SPIWrite(REG_LR_DIOMAPPING1+0x01);                       //DIO0=00, DIO1=00, DIO2=00, DIO3=01  DIO0=00--RXDONE
      
  SPIWrite(LR_RegIrqFlagsMask+0x3F);                       //Open RxDone interrupt & Timeout
  SX1276_LoRaClearIrq();   
  
  SPIWrite(LR_RegPayloadLength+datlen);                       //RegPayloadLength  21byte(this register must difine when the data long of one byte in SF is 6)
    
  addr = SPIRead((u8)(LR_RegFifoRxBaseAddr>>8));           //Read RxBaseAddr
  SPIWrite(LR_RegFifoAddrPtr+addr);                        //RxBaseAddr -> FiFoAddrPtr　 
  SPIWrite(LR_RegOpMode+0x0D);                        //Continuous Rx Mode

  delayms(10);
}

/**********************************************************
**Name:     SX1276_LoRaRxWaitStable
**Function: Determine whether the state of stable Rx 查询RX 状态
**Input:    none
**Output:   none
**********************************************************/
/*
u8 SX1276_LoRaRxWaitStable(void)
{ 
	uint8 tmp;
	tmp=SPIRead((u8)(LR_RegModemStat>>8));
	return tmp;
}
*/
/**********************************************************
**Name:     SX1276_LoRaRxPacket
**Function: Receive data in LoRa mode
**Input:    None
**Output:   None
**********************************************************/
void SX1276_LoRaRxPacket(void)
{
    u8 addr;
    u8 packet_size;
    addr = SPIRead((u8)(LR_RegFifoRxCurrentaddr>>8));//last packet addr 数据包的最后地址(数据的尾地址)
    SPIWrite(LR_RegFifoAddrPtr+addr);//RxBaseAddr -> FiFoAddrPtr   

    if(SX1276SpreadFactorTbl[gb_SF]==6)//When SpreadFactor is six，will used Implicit Header mode(Excluding internal packet length)
            packet_size=21;
    else
            packet_size = SPIRead((u8)(LR_RegRxNbBytes>>8));//Number for received bytes    

    gtmp= packet_size;
    
    SPIBurstRead(0x00, (u8 *)gb_RxData, packet_size);
    
    SX1276_LoRaClearIrq();
}


/**********************************************************
**Name:     SX1276_LoRaEntryTx
**Function: Entry Tx mode
**Input:    None
**Output:   None
**********************************************************/
void SX1276_LoRaEntryTx(void)
{
    u8 addr;

                                //setting base parameter

    SPIWrite(0x4D00+0x87);                                   //Tx for 20dBm
    SPIWrite(LR_RegHopPeriod);                               //RegHopPeriod NO FHSS
    SPIWrite(REG_LR_DIOMAPPING1+0x41);                       //DIO0=01, DIO1=00, DIO2=00, DIO3=01

    SX1276_LoRaClearIrq();
    SPIWrite(LR_RegIrqFlagsMask+0xF7);                       //Open TxDone interrupt
    SPIWrite(LR_RegPayloadLength+ datlen);                       //RegPayloadLength  21byte

    addr = SPIRead((u8)(LR_RegFifoTxBaseAddr>>8));           //RegFiFoTxBaseAddr
    SPIWrite(LR_RegFifoAddrPtr+addr);                        //RegFifoAddrPtr
}

/**********************************************************
**Name:     SX1276_LoRaTxPacket
**Function: Send data in LoRa mode
**Input:    None
**Output:   1- Send over
**********************************************************/
void SX1276_LoRaTxPacket(unsigned char *data,uint32 length)
{ 	
    delayms(10);
    BurstWrite(0x00, (u8 *)data,(u8)length);
    SPIWrite(LR_RegOpMode+0x03+0x08);                    //Tx Mode       
}

/**********/
void SX1276_LoRaEntryCAD(void)
{
  
  SPIWrite(REG_LR_DIOMAPPING1+0x00); //
  SPIWrite(REG_LR_DIOMAPPING2+0x01);// PreambleDetect interrupt DIO4  00
  SPIWrite(LR_RegIrqFlagsMask+0xFE);  //1111 1110  CadDetectedMask 
  SX1276_LoRaClearIrq(); 
}

/**********/
uint8 SX1276_LoRaCCA()
{
    SPIWrite(LR_RegOpMode+0x0F);                        //CAD mode 
    delayms(1);
    cca=SPIRead(0x12);
    if(cca & 0x01)
    {
      SX1276_LoRaClearIrq(); 
      return  _BUSY;
    }
    else
    {
      return _IDLE;
    }
}

