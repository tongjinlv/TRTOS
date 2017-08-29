/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <..\USER\Prj_Lora\sx1276_7_8.h>
/************************Description************************
/************************************************	
									 ---------------
	   key2 ----    |PD4         PD3|	 ----key1
 GREEN_LED----    |PD5         PD2|	 ----NIRQ
   RED_LED----    |PD6         PD1|	 ----
	    	  ----    |NRST        PC7|   ----SDO
	        ----    |PA1         PC6|   ----SDI
 	        ----    |PA2         PC5|	 ----SCK
	    	  ----    |Vss         PC4|   ----
		      ----    |Vcap        PC3|   ----SDN
		      ----    |Vdd         PB4|	 ----
		  NSEL----    |PA3         PB5|	 ----
									---------------
										stm8s103f3p
************************************************/
/************************************************
//  RF module:           sx1276_7_8
//  FSK:
//  Carry Frequency:     434MHz
//  Bit Rate:            1.2Kbps/2.4Kbps/4.8Kbps/9.6Kbps
//  Tx Power Output:     20dbm/17dbm/14dbm/11dbm
//  Frequency Deviation: +/-35KHz
//  Receive Bandwidth:   83KHz
//  Coding:              NRZ
//  Packet Format:       0x5555555555+0xAA2DD4+"HR_WT Lora sx1276_7_8" (total: 29 bytes)
//  LoRa:
//  Carry Frequency:     434MHz
//  Spreading Factor:    6/7/8/9/10/11/12
//  Tx Power Output:     20dbm/17dbm/14dbm/11dbm
//  Receive Bandwidth:   7.8KHz/10.4KHz/15.6KHz/20.8KHz/31.2KHz/41.7KHz/62.5KHz/125KHz/250KHz/500KHz
//  Coding:              NRZ
//  Packet Format:       "HR_WT Lora sx1276_7_8" (total: 21 bytes)
//  Tx Current:          about 120mA  (RFOP=+20dBm,typ.)
//  Rx Current:          about 11.5mA  (typ.)       
**********************************************************/

/**********************************************************
**Parameter table define
**********************************************************/


u16 SysTime;
u16 time2_count;
u16 key1_time_count;
u16 key2_time_count;
u8 rf_rx_packet_length;

u8 mode;//lora--1/FSK--0
u8 Freq_Sel;//
u8 Power_Sel;//
u8 Lora_Rate_Sel;//
u8 BandWide_Sel;//

u8 Fsk_Rate_Sel;//


 u8 sx1276_7_8FreqTbl[1][3] = 
{ 
  {0x6C, 0x80, 0x00}, //434MHz
};

 u8 sx1276_7_8PowerTbl[4] =
{ 
  0xFF,                   //20dbm  
  0xFC,                   //17dbm
  0xF9,                   //14dbm
  0xF6,                   //11dbm 
};

 u8 sx1276_7_8SpreadFactorTbl[7] =
{
  6,7,8,9,10,11,12
};

 u8 sx1276_7_8LoRaBwTbl[10] =
{
//7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
  0,1,2,3,4,5,6,7,8,9
};

 u8  sx1276_7_8Data[] = {"HR_WT Lora sx1276_7_8"};

u8 RxData[64];

/**********************************************************
**Variable define
**********************************************************/

void SPI_Write(uint8 addr,uint8 cmd)
{
	SPIWrite(((uint16)addr)<<8+cmd);
}
void sx1276_7_8_Config(void);

/**********************************************************
**Name:     sx1276_7_8_Standby
**Function: Entry standby mode
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_Standby(void)
{
  SPI_Write(LR_RegOpMode,0x09);                              		//Standby//Low Frequency Mode
	//SPI_Write(LR_RegOpMode,0x01);                              	 //Standby//High Frequency Mode
}

/**********************************************************
**Name:     sx1276_7_8_Sleep
**Function: Entry sleep mode
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_Sleep(void)
{
  SPI_Write(LR_RegOpMode,0x08);                              		//Sleep//Low Frequency Mode
	//SPI_Write(LR_RegOpMode,0x00);                            		 //Sleep//High Frequency Mode
}

/*********************************************************/
//LoRa mode
/*********************************************************/
/**********************************************************
**Name:     sx1276_7_8_EntryLoRa
**Function: Set RFM69 entry LoRa(LongRange) mode
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_EntryLoRa(void)
{
  SPI_Write(LR_RegOpMode,0x88);//Low Frequency Mode
	//SPI_Write(LR_RegOpMode,0x80);//High Frequency Mode
}

/**********************************************************
**Name:     sx1276_7_8_LoRaClearIrq
**Function: Clear all irq
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_LoRaClearIrq(void)
{
  SPI_Write(LR_RegIrqFlags,0xFF);
}

/**********************************************************
**Name:     sx1276_7_8_LoRaEntryRx
**Function: Entry Rx mode
**Input:    None
**Output:   None
**********************************************************/
u8 sx1276_7_8_LoRaEntryRx(void)
{
  u8 addr; 
        
  sx1276_7_8_Config();                                         //setting base parameter
  
  SPI_Write(REG_LR_PADAC,0x84);                              //Normal and Rx
  SPI_Write(LR_RegHopPeriod,0xFF);                          //RegHopPeriod NO FHSS
  SPI_Write(REG_LR_DIOMAPPING1,0x01);                       //DIO0=00, DIO1=00, DIO2=00, DIO3=01
      
  SPI_Write(LR_RegIrqFlagsMask,0x3F);                       //Open RxDone interrupt & Timeout
  sx1276_7_8_LoRaClearIrq();   
  
  SPI_Write(LR_RegPayloadLength,21);                       //RegPayloadLength  21byte(this register must difine when the data long of one byte in SF is 6)
    
  addr = SPIRead(LR_RegFifoRxBaseAddr);           				//Read RxBaseAddr
  SPI_Write(LR_RegFifoAddrPtr,addr);                        //RxBaseAddr -> FiFoAddrPtr　 
  SPI_Write(LR_RegOpMode,0x8d);                        		//Continuous Rx Mode//Low Frequency Mode
	//SPI_Write(LR_RegOpMode,0x05);                        		//Continuous Rx Mode//High Frequency Mode
	SysTime = 0;
	while(1)
	{
		if((SPIRead(LR_RegModemStat)&0x04)==0x04)   //Rx-on going RegModemStat
			break;
		if(SysTime>=3)	
			return 0;                                              //over time for error
	}
}
/**********************************************************
**Name:     sx1276_7_8_LoRaReadRSSI
**Function: Read the RSSI value
**Input:    none
**Output:   temp, RSSI value
**********************************************************/
u8 sx1276_7_8_LoRaReadRSSI(void)
{
  u16 temp=10;
  temp=SPIRead(LR_RegRssiValue);                  //Read RegRssiValue，Rssi value
  temp=temp+127-137;                                       //127:Max RSSI, 137:RSSI offset
  return (u8)temp;
}

/**********************************************************
**Name:     sx1276_7_8_LoRaRxPacket
**Function: Receive data in LoRa mode
**Input:    None
**Output:   1- Success
            0- Fail
**********************************************************/
u8 sx1276_7_8_LoRaRxPacket(void)
{
  u8 i; 
  u8 addr;
  u8 packet_size;
 
  if(GPIO_ReadInputDataBit(Pin_Maps[6].GPIOx,Pin_Maps[6].GPIO_Pin))
  {
    for(i=0;i<32;i++) 
      RxData[i] = 0x00;
    
    addr = SPIRead(LR_RegFifoRxCurrentaddr);      //last packet addr
    SPI_Write(LR_RegFifoAddrPtr,addr);                      //RxBaseAddr -> FiFoAddrPtr    
    if(sx1276_7_8SpreadFactorTbl[Lora_Rate_Sel]==6)           //When SpreadFactor is six，will used Implicit Header mode(Excluding internal packet length)
      packet_size=21;
    else
      packet_size = SPIRead(LR_RegRxNbBytes);     //Number for received bytes    
    SPIBurstRead(0x00, RxData, packet_size);
    
    sx1276_7_8_LoRaClearIrq();
    for(i=0;i<17;i++)
    {
      if(RxData[i]!=sx1276_7_8Data[i])
        break;  
    }    
    if(i>=17)                                              //Rx success
      return(1);
    else
      return(0);
  }
  else
    return(0);
}

/**********************************************************
**Name:     sx1276_7_8_LoRaEntryTx
**Function: Entry Tx mode
**Input:    None
**Output:   None
**********************************************************/
u8 sx1276_7_8_LoRaEntryTx(void)
{
  u8 addr,temp;
    
  sx1276_7_8_Config();                                         //setting base parameter
    
  SPI_Write(REG_LR_PADAC,0x87);                                   //Tx for 20dBm
  SPI_Write(LR_RegHopPeriod,0x00);                               //RegHopPeriod NO FHSS
  SPI_Write(REG_LR_DIOMAPPING1,0x41);                       //DIO0=01, DIO1=00, DIO2=00, DIO3=01
  
  sx1276_7_8_LoRaClearIrq();
  SPI_Write(LR_RegIrqFlagsMask,0xF7);                       //Open TxDone interrupt
  SPI_Write(LR_RegPayloadLength,21);                       //RegPayloadLength  21byte
  
  addr = SPIRead(LR_RegFifoTxBaseAddr);           //RegFiFoTxBaseAddr
  SPI_Write(LR_RegFifoAddrPtr,addr);                        //RegFifoAddrPtr
	SysTime = 0;
	while(1)
	{
		temp=SPIRead(LR_RegPayloadLength);
		if(temp==21)
		{
			break; 
		}
		if(SysTime>=3)	
			return 0;
	}
}
/**********************************************************
**Name:     sx1276_7_8_LoRaTxPacket
**Function: Send data in LoRa mode
**Input:    None
**Output:   1- Send over
**********************************************************/
u8 sx1276_7_8_LoRaTxPacket(void)
{ 
  u8 TxFlag=0;
  u8 addr;
  
	BurstWrite(0x00, (u8 *)sx1276_7_8Data, 21);
	SPI_Write(LR_RegOpMode,0x8b);                    //Tx Mode           
	while(1)
	{
		if(GPIO_ReadInputDataBit(Pin_Maps[6].GPIOx,Pin_Maps[6].GPIO_Pin))                      //Packet send over
		{      
			SPIRead(LR_RegIrqFlags);
			sx1276_7_8_LoRaClearIrq();                                //Clear irq
				
			sx1276_7_8_Standby();                                     //Entry Standby mode      
			
			break;
		}
	} 
}

/**********************************************************
**Name:     sx1276_7_8_ReadRSSI
**Function: Read the RSSI value
**Input:    none
**Output:   temp, RSSI value
**********************************************************/
u8 sx1276_7_8_ReadRSSI(void)
{
  u8 temp=0xff;
	
  temp=SPIRead(0x11);
  temp>>=1;
  temp=127-temp;                                           //127:Max RSSI
  return temp;
}
void delay_ms(uint32 a)
{
	a*1000;
	while(a--);
}
/**********************************************************
**Name:     sx1276_7_8_Config
**Function: sx1276_7_8 base config
**Input:    mode
**Output:   None
**********************************************************/
void sx1276_7_8_Config(void)
{
  u8 i; 

	mode = 0x01;//lora mode
	Freq_Sel = 0x00;//433M
	Power_Sel = 0x00;//
	Lora_Rate_Sel = 0x06;//
	BandWide_Sel = 0x07;
	Fsk_Rate_Sel = 0x00;
	
	
  sx1276_7_8_Sleep();                                      //Change modem mode Must in Sleep mode 
  for(i=250;i!=0;i--)                                      //Delay
	delay_ms(15);

  //lora mode
	sx1276_7_8_EntryLoRa();  
	//SPI_Write(0x5904);   //?? Change digital regulator form 1.6V to 1.47V: see errata note
    
	BurstWrite(LR_RegFrMsb,sx1276_7_8FreqTbl[Freq_Sel],3);  //setting frequency parameter

	//setting base parameter 
	SPI_Write(LR_RegPaConfig,sx1276_7_8PowerTbl[Power_Sel]);             //Setting output power parameter  
    
	SPI_Write(LR_RegOcp,0x0B);                              //RegOcp,Close Ocp
	SPI_Write(LR_RegLna,0x23);                              //RegLNA,High & LNA Enable
    
	if(sx1276_7_8SpreadFactorTbl[Lora_Rate_Sel]==6)           //SFactor=6
	{
		u8 tmp;
		SPI_Write(LR_RegModemConfig1,((sx1276_7_8LoRaBwTbl[BandWide_Sel]<<4)+(1<<1)+0x01));//Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
		SPI_Write(LR_RegModemConfig2,((sx1276_7_8SpreadFactorTbl[Lora_Rate_Sel]<<4)+(1<<2)+0x03));
      
		tmp = SPIRead(0x31);
		tmp &= 0xF8;
		tmp |= 0x05;
		SPI_Write(0x31,tmp);
		SPI_Write(0x37,0x0C);
	} 
	else
	{
		SPI_Write(LR_RegModemConfig1,((sx1276_7_8LoRaBwTbl[BandWide_Sel]<<4)+(1<<1)+0x00));//Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
		SPI_Write(LR_RegModemConfig2,((sx1276_7_8SpreadFactorTbl[Lora_Rate_Sel]<<4)+(1<<2)+0x03));  //SFactor &  LNA gain set by the internal AGC loop 
	}
	SPI_Write(LR_RegSymbTimeoutLsb,0xFF);                   //RegSymbTimeoutLsb Timeout = 0x3FF(Max) 
    
	SPI_Write(LR_RegPreambleMsb,0x00);                       //RegPreambleMsb 
	SPI_Write(LR_RegPreambleLsb,12);                      //RegPreambleLsb 8+4=12byte Preamble
    
	SPI_Write(REG_LR_DIOMAPPING2,0x01);                     //RegDioMapping2 DIO5=00, DIO4=01
	
  sx1276_7_8_Standby();                                         //Entry standby mode
}

void Task_LoraS(void *Tags)
{
	uint8 i;
	sx1276_7_8_LoRaEntryRx();
	while(1)
	{
		
 sx1276_7_8_LoRaEntryTx();
					sx1276_7_8_LoRaTxPacket();
		Tos_TaskDelay(1000);

	}
}
