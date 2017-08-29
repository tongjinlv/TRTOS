#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\src\\stm32l1xx_crc.c"

























 

 
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_crc.h"


























 

 







 
#line 1 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"











































 



 



 
    






  


 
  


 



    


 

    
 





 





#line 97 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"







 







 







 






















 
#line 152 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 



 




 




 
 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVC_IRQn                    = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_STAMP_IRQn           = 2,       
  RTC_WKUP_IRQn               = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      
  ADC1_IRQn                   = 18,      
  USB_HP_IRQn                 = 19,      
  USB_LP_IRQn                 = 20,      
  DAC_IRQn                    = 21,      
  COMP_IRQn                   = 22,      
  EXTI9_5_IRQn                = 23,      
  LCD_IRQn                    = 24,      
  TIM9_IRQn                   = 25,      
  TIM10_IRQn                  = 26,      
  TIM11_IRQn                  = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTC_Alarm_IRQn              = 41,      
  USB_FS_WKUP_IRQn            = 42,      
  TIM6_IRQn                   = 43,      




#line 244 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"


  TIM7_IRQn                   = 44,      
  SDIO_IRQn                   = 45,      
  TIM5_IRQn                   = 46,      
  SPI3_IRQn                   = 47,      
  UART4_IRQn                  = 48,      
  UART5_IRQn                  = 49,      
  DMA2_Channel1_IRQn          = 50,      
  DMA2_Channel2_IRQn          = 51,      
  DMA2_Channel3_IRQn          = 52,      
  DMA2_Channel4_IRQn          = 53,      
  DMA2_Channel5_IRQn          = 54,      
  AES_IRQn                    = 55,      
  COMP_ACQ_IRQn               = 56       

} IRQn_Type;



 

#line 1 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"
 




















 






















 




 


 

 













#line 89 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"


 







#line 119 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"

#line 1 "E:\\Soft\\keil472a\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"
 
 





 










#line 26 "E:\\Soft\\keil472a\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 197 "E:\\Soft\\keil472a\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"

     







     










     











#line 261 "E:\\Soft\\keil472a\\ARM\\ARMCC\\bin\\..\\include\\stdint.h"



 



#line 121 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"
#line 1 "..\\Libraries\\CMSIS\\CM3\\CoreSupport\\core_cmInstr.h"
 




















 





 




 


 




 







 







 






 








 







 







 









 









 



static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}









 



static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}











 









 









 









 











 











 











 







 














 










 









 






#line 782 "..\\Libraries\\CMSIS\\CM3\\CoreSupport\\core_cmInstr.h"

   

#line 122 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"
#line 1 "..\\Libraries\\CMSIS\\CM3\\CoreSupport\\core_cmFunc.h"
 




















 




 



 


 

 
 






 



static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}








 



static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}








 



static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}








 



static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}








 



static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}








 



static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}








 



static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}








 



static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}








 



static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}








 



static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}








 



static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}









 







 








 



static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}








 



static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}








 



static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}








 



static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}





#line 348 "..\\Libraries\\CMSIS\\CM3\\CoreSupport\\core_cmFunc.h"


#line 848 "..\\Libraries\\CMSIS\\CM3\\CoreSupport\\core_cmFunc.h"

 


#line 123 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"








 
#line 153 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"

 






 
#line 169 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"

 












 


 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[8];                  
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                  
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                  
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                  
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                  
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                  
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                     
}  NVIC_Type;

 



 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
  volatile uint32_t VTOR;                     
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
  volatile uint8_t  SHP[12];                  
  volatile uint32_t SHCSR;                    
  volatile uint32_t CFSR;                     
  volatile uint32_t HFSR;                     
  volatile uint32_t DFSR;                     
  volatile uint32_t MMFAR;                    
  volatile uint32_t BFAR;                     
  volatile uint32_t AFSR;                     
  volatile const  uint32_t PFR[2];                   
  volatile const  uint32_t DFR;                      
  volatile const  uint32_t ADR;                      
  volatile const  uint32_t MMFR[4];                  
  volatile const  uint32_t ISAR[5];                  
       uint32_t RESERVED0[5];
  volatile uint32_t CPACR;                    
} SCB_Type;

 















 






























 




#line 396 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"

 





















 









 


















 










































 









 









 















 






 


 
typedef struct
{
       uint32_t RESERVED0[1];
  volatile const  uint32_t ICTR;                     

  volatile uint32_t ACTLR;                    



} SCnSCB_Type;

 



 










 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 






 


 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                   
    volatile  uint16_t   u16;                  
    volatile  uint32_t   u32;                  
  }  PORT [32];                           
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                      
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                      
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                      
       uint32_t RESERVED3[29];                                  
  volatile  uint32_t IWR;                      
  volatile const  uint32_t IRR;                      
  volatile uint32_t IMCR;                     
       uint32_t RESERVED4[43];                                  
  volatile  uint32_t LAR;                      
  volatile const  uint32_t LSR;                      
       uint32_t RESERVED5[6];                                   
  volatile const  uint32_t PID4;                     
  volatile const  uint32_t PID5;                     
  volatile const  uint32_t PID6;                     
  volatile const  uint32_t PID7;                     
  volatile const  uint32_t PID0;                     
  volatile const  uint32_t PID1;                     
  volatile const  uint32_t PID2;                     
  volatile const  uint32_t PID3;                     
  volatile const  uint32_t CID0;                     
  volatile const  uint32_t CID1;                     
  volatile const  uint32_t CID2;                     
  volatile const  uint32_t CID3;                     
} ITM_Type;

 



 



























 



 



 



 









   






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t CYCCNT;                   
  volatile uint32_t CPICNT;                   
  volatile uint32_t EXCCNT;                   
  volatile uint32_t SLEEPCNT;                 
  volatile uint32_t LSUCNT;                   
  volatile uint32_t FOLDCNT;                  
  volatile const  uint32_t PCSR;                     
  volatile uint32_t COMP0;                    
  volatile uint32_t MASK0;                    
  volatile uint32_t FUNCTION0;                
       uint32_t RESERVED0[1];
  volatile uint32_t COMP1;                    
  volatile uint32_t MASK1;                    
  volatile uint32_t FUNCTION1;                
       uint32_t RESERVED1[1];
  volatile uint32_t COMP2;                    
  volatile uint32_t MASK2;                    
  volatile uint32_t FUNCTION2;                
       uint32_t RESERVED2[1];
  volatile uint32_t COMP3;                    
  volatile uint32_t MASK3;                    
  volatile uint32_t FUNCTION3;                
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   






 


 
typedef struct
{
  volatile uint32_t SSPSR;                    
  volatile uint32_t CSPSR;                    
       uint32_t RESERVED0[2];
  volatile uint32_t ACPR;                     
       uint32_t RESERVED1[55];
  volatile uint32_t SPPR;                     
       uint32_t RESERVED2[131];
  volatile const  uint32_t FFSR;                     
  volatile uint32_t FFCR;                     
  volatile const  uint32_t FSCR;                     
       uint32_t RESERVED3[759];
  volatile const  uint32_t TRIGGER;                  
  volatile const  uint32_t FIFO0;                    
  volatile const  uint32_t ITATBCTR2;                
       uint32_t RESERVED4[1];
  volatile const  uint32_t ITATBCTR0;                
  volatile const  uint32_t FIFO1;                    
  volatile uint32_t ITCTRL;                   
       uint32_t RESERVED5[39];
  volatile uint32_t CLAIMSET;                 
  volatile uint32_t CLAIMCLR;                 
       uint32_t RESERVED7[8];
  volatile const  uint32_t DEVID;                    
  volatile const  uint32_t DEVTYPE;                  
} TPI_Type;

 



 



 












 






 



 





















 



 





















 



 



 


















 






   







 


 
typedef struct
{
  volatile const  uint32_t TYPE;                     
  volatile uint32_t CTRL;                     
  volatile uint32_t RNR;                      
  volatile uint32_t RBAR;                     
  volatile uint32_t RASR;                     
  volatile uint32_t RBAR_A1;                  
  volatile uint32_t RASR_A1;                  
  volatile uint32_t RBAR_A2;                  
  volatile uint32_t RASR_A2;                  
  volatile uint32_t RBAR_A3;                  
  volatile uint32_t RASR_A3;                  
} MPU_Type;

 









 









 



 









 






























 







 


 
typedef struct
{
  volatile uint32_t DHCSR;                    
  volatile  uint32_t DCRSR;                    
  volatile uint32_t DCRDR;                    
  volatile uint32_t DEMCR;                    
} CoreDebug_Type;

 




































 






 







































 






 

 
#line 1227 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"

#line 1236 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\core_cm3.h"






 










 

 



 




 










 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);                

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((0xFFFFUL << 16) | (7UL << 8));              
  reg_value  =  (reg_value                                 |
                ((uint32_t)0x5FA << 16) |
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}







 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) >> 8);    
}







 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}











 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}







 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}







 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}










 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}










 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 4)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] = ((priority << (8 - 4)) & 0xff);    }         
}












 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 4)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)]           >> (8 - 4)));  }  
}













 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}













 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) |
                 (1UL << 2));                    
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 




 

















 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if (ticks > (0xFFFFFFUL << 0))  return (1);             

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (ticks & (0xFFFFFFUL << 0)) - 1;       
  NVIC_SetPriority (SysTick_IRQn, (1<<4) - 1);   
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2) |
                   (1UL << 1)   |
                   (1UL << 0);                     
  return (0);                                                   
}



 



 




 

extern volatile int32_t ITM_RxBuffer;                     












 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL << 0))                  &&       
      (((ITM_Type *) (0xE0000000UL) )->TER & (1UL << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000UL) )->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}








 
static __inline int32_t ITM_ReceiveChar (void) {
  int32_t ch = -1;                            

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }

  return (ch);
}








 
static __inline int32_t ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

 





#line 267 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
#line 1 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\system_stm32l1xx.h"



















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 268 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
#line 269 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



   

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;



  









 


#line 320 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 



    



 

typedef struct
{
  volatile uint32_t SR;            
  volatile uint32_t CR1;           
  volatile uint32_t CR2;           
  volatile uint32_t SMPR1;         
  volatile uint32_t SMPR2;         
  volatile uint32_t SMPR3;         
  volatile uint32_t JOFR1;         
  volatile uint32_t JOFR2;         
  volatile uint32_t JOFR3;         
  volatile uint32_t JOFR4;         
  volatile uint32_t HTR;           
  volatile uint32_t LTR;           
  volatile uint32_t SQR1;          
  volatile uint32_t SQR2;          
  volatile uint32_t SQR3;          
  volatile uint32_t SQR4;          
  volatile uint32_t SQR5;          
  volatile uint32_t JSQR;          
  volatile uint32_t JDR1;          
  volatile uint32_t JDR2;          
  volatile uint32_t JDR3;          
  volatile uint32_t JDR4;          
  volatile uint32_t DR;            
  volatile uint32_t SMPR0;         
} ADC_TypeDef;

typedef struct
{
  volatile uint32_t CSR;           
  volatile uint32_t CCR;           
} ADC_Common_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;            
  volatile uint32_t SR;            
  volatile uint32_t DINR;          
  volatile uint32_t DOUTR;         
  volatile uint32_t KEYR0;         
  volatile uint32_t KEYR1;         
  volatile uint32_t KEYR2;         
  volatile uint32_t KEYR3;         
  volatile uint32_t IVR0;          
  volatile uint32_t IVR1;          
  volatile uint32_t IVR2;          
  volatile uint32_t IVR3;          
} AES_TypeDef;



 

typedef struct
{
  volatile uint32_t CSR;           
} COMP_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;            
  volatile uint8_t  IDR;           
  uint8_t   RESERVED0;         
  uint16_t  RESERVED1;         
  volatile uint32_t CR;             
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;            
  volatile uint32_t SWTRIGR;       
  volatile uint32_t DHR12R1;       
  volatile uint32_t DHR12L1;       
  volatile uint32_t DHR8R1;        
  volatile uint32_t DHR12R2;       
  volatile uint32_t DHR12L2;       
  volatile uint32_t DHR8R2;        
  volatile uint32_t DHR12RD;       
  volatile uint32_t DHR12LD;       
  volatile uint32_t DHR8RD;        
  volatile uint32_t DOR1;          
  volatile uint32_t DOR2;          
  volatile uint32_t SR;            
} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;        
  volatile uint32_t CR;            
  volatile uint32_t APB1FZ;        
  volatile uint32_t APB2FZ;        
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;           
  volatile uint32_t CNDTR;         
  volatile uint32_t CPAR;          
  volatile uint32_t CMAR;          
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;           
  volatile uint32_t IFCR;          
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;           
  volatile uint32_t EMR;           
  volatile uint32_t RTSR;          
  volatile uint32_t FTSR;          
  volatile uint32_t SWIER;         
  volatile uint32_t PR;            
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;           
  volatile uint32_t PECR;          
  volatile uint32_t PDKEYR;        
  volatile uint32_t PEKEYR;        
  volatile uint32_t PRGKEYR;       
  volatile uint32_t OPTKEYR;       
  volatile uint32_t SR;            
  volatile uint32_t OBR;           
  volatile uint32_t WRPR;          
  uint32_t   RESERVED[23];     
  volatile uint32_t WRPR1;         
  volatile uint32_t WRPR2;         
} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RDP;                
  volatile uint32_t USER;               
  volatile uint32_t WRP01;              
  volatile uint32_t WRP23;              
  volatile uint32_t WRP45;              
  volatile uint32_t WRP67;              
  volatile uint32_t WRP89;              
  volatile uint32_t WRP1011;            
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t CSR;           
  volatile uint32_t OTR;            
  volatile uint32_t LPOTR;         
} OPAMP_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];       
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];       
} FSMC_Bank1E_TypeDef;        



 

typedef struct
{
  volatile uint32_t MODER;         
  volatile uint16_t OTYPER;        
  uint16_t RESERVED0;          
  volatile uint32_t OSPEEDR;       
  volatile uint32_t PUPDR;         
  volatile uint16_t IDR;           
  uint16_t RESERVED1;          
  volatile uint16_t ODR;           
  uint16_t RESERVED2;          
  volatile uint16_t BSRRL;         
  volatile uint16_t BSRRH;         
  volatile uint32_t LCKR;          
  volatile uint32_t AFR[2];        
  volatile uint16_t BRR;           
  uint16_t RESERVED3;          
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t MEMRMP;        
  volatile uint32_t PMC;           
  volatile uint32_t EXTICR[4];     
} SYSCFG_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;           
  uint16_t  RESERVED0;         
  volatile uint16_t CR2;           
  uint16_t  RESERVED1;         
  volatile uint16_t OAR1;          
  uint16_t  RESERVED2;         
  volatile uint16_t OAR2;          
  uint16_t  RESERVED3;         
  volatile uint16_t DR;            
  uint16_t  RESERVED4;         
  volatile uint16_t SR1;           
  uint16_t  RESERVED5;         
  volatile uint16_t SR2;           
  uint16_t  RESERVED6;         
  volatile uint16_t CCR;           
  uint16_t  RESERVED7;         
  volatile uint16_t TRISE;         
  uint16_t  RESERVED8;         
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;            
  volatile uint32_t PR;            
  volatile uint32_t RLR;           
  volatile uint32_t SR;            
} IWDG_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;         
  volatile uint32_t FCR;        
  volatile uint32_t SR;         
  volatile uint32_t CLR;        
  uint32_t RESERVED;        
  volatile uint32_t RAM[16];    
} LCD_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CSR;   
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;             
  volatile uint32_t ICSCR;          
  volatile uint32_t CFGR;           
  volatile uint32_t CIR;            
  volatile uint32_t AHBRSTR;        
  volatile uint32_t APB2RSTR;       
  volatile uint32_t APB1RSTR;       
  volatile uint32_t AHBENR;         
  volatile uint32_t APB2ENR;        
  volatile uint32_t APB1ENR;        
  volatile uint32_t AHBLPENR;       
  volatile uint32_t APB2LPENR;      
  volatile uint32_t APB1LPENR;      
  volatile uint32_t CSR;            
} RCC_TypeDef;



 

typedef struct
{
  volatile uint32_t ICR;        
  volatile uint32_t ASCR1;      
  volatile uint32_t ASCR2;      
  volatile uint32_t HYSCR1;      
  volatile uint32_t HYSCR2;      
  volatile uint32_t HYSCR3;      
  volatile uint32_t HYSCR4;      
} RI_TypeDef;



 

typedef struct
{
  volatile uint32_t TR;          
  volatile uint32_t DR;          
  volatile uint32_t CR;                                                                                                      
  volatile uint32_t ISR;         
  volatile uint32_t PRER;        
  volatile uint32_t WUTR;        
  volatile uint32_t CALIBR;      
  volatile uint32_t ALRMAR;      
  volatile uint32_t ALRMBR;      
  volatile uint32_t WPR;         
  volatile uint32_t SSR;         
  volatile uint32_t SHIFTR;      
  volatile uint32_t TSTR;        
  volatile uint32_t TSDR;        
  volatile uint32_t TSSSR;       
  volatile uint32_t CALR;        
  volatile uint32_t TAFCR;       
  volatile uint32_t ALRMASSR;    
  volatile uint32_t ALRMBSSR;    
  uint32_t RESERVED7;        
  volatile uint32_t BKP0R;       
  volatile uint32_t BKP1R;       
  volatile uint32_t BKP2R;       
  volatile uint32_t BKP3R;       
  volatile uint32_t BKP4R;       
  volatile uint32_t BKP5R;       
  volatile uint32_t BKP6R;       
  volatile uint32_t BKP7R;       
  volatile uint32_t BKP8R;       
  volatile uint32_t BKP9R;       
  volatile uint32_t BKP10R;      
  volatile uint32_t BKP11R;      
  volatile uint32_t BKP12R;      
  volatile uint32_t BKP13R;      
  volatile uint32_t BKP14R;      
  volatile uint32_t BKP15R;      
  volatile uint32_t BKP16R;      
  volatile uint32_t BKP17R;      
  volatile uint32_t BKP18R;      
  volatile uint32_t BKP19R;      
  volatile uint32_t BKP20R;      
  volatile uint32_t BKP21R;      
  volatile uint32_t BKP22R;      
  volatile uint32_t BKP23R;      
  volatile uint32_t BKP24R;      
  volatile uint32_t BKP25R;      
  volatile uint32_t BKP26R;      
  volatile uint32_t BKP27R;      
  volatile uint32_t BKP28R;      
  volatile uint32_t BKP29R;      
  volatile uint32_t BKP30R;      
  volatile uint32_t BKP31R;      
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;           
  volatile uint32_t CLKCR;           
  volatile uint32_t ARG;             
  volatile uint32_t CMD;             
  volatile const uint32_t  RESPCMD;         
  volatile const uint32_t  RESP1;           
  volatile const uint32_t  RESP2;           
  volatile const uint32_t  RESP3;           
  volatile const uint32_t  RESP4;           
  volatile uint32_t DTIMER;          
  volatile uint32_t DLEN;            
  volatile uint32_t DCTRL;           
  volatile const uint32_t  DCOUNT;          
  volatile const uint32_t  STA;             
  volatile uint32_t ICR;             
  volatile uint32_t MASK;            
  uint32_t      RESERVED0[2];    
  volatile const uint32_t  FIFOCNT;         
  uint32_t      RESERVED1[13];   
  volatile uint32_t FIFO;            
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;         
  uint16_t      RESERVED0;   
  volatile uint16_t CR2;         
  uint16_t      RESERVED1;   
  volatile uint16_t SR;          
  uint16_t      RESERVED2;   
  volatile uint16_t DR;          
  uint16_t      RESERVED3;   
  volatile uint16_t CRCPR;       
  uint16_t      RESERVED4;   
  volatile uint16_t RXCRCR;      
  uint16_t      RESERVED5;   
  volatile uint16_t TXCRCR;      
  uint16_t      RESERVED6;   
  volatile uint16_t I2SCFGR;     
  uint16_t      RESERVED7;   
  volatile uint16_t I2SPR;       
  uint16_t      RESERVED8;   
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;           
  uint16_t      RESERVED0;     
  volatile uint16_t CR2;           
  uint16_t      RESERVED1;     
  volatile uint16_t SMCR;          
  uint16_t      RESERVED2;     
  volatile uint16_t DIER;          
  uint16_t      RESERVED3;     
  volatile uint16_t SR;            
  uint16_t      RESERVED4;     
  volatile uint16_t EGR;           
  uint16_t      RESERVED5;     
  volatile uint16_t CCMR1;         
  uint16_t      RESERVED6;     
  volatile uint16_t CCMR2;         
  uint16_t      RESERVED7;     
  volatile uint16_t CCER;          
  uint16_t      RESERVED8;     
  volatile uint32_t CNT;           
  volatile uint16_t PSC;           
  uint16_t      RESERVED10;    
  volatile uint32_t ARR;           
  uint32_t      RESERVED12;    
  volatile uint32_t CCR1;          
  volatile uint32_t CCR2;          
  volatile uint32_t CCR3;          
  volatile uint32_t CCR4;          
  uint32_t      RESERVED17;    
  volatile uint16_t DCR;           
  uint16_t      RESERVED18;    
  volatile uint16_t DMAR;          
  uint16_t      RESERVED19;    
  volatile uint16_t OR;            
  uint16_t      RESERVED20;    
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;          
  uint16_t      RESERVED0;   
  volatile uint16_t DR;          
  uint16_t      RESERVED1;   
  volatile uint16_t BRR;         
  uint16_t      RESERVED2;   
  volatile uint16_t CR1;         
  uint16_t      RESERVED3;   
  volatile uint16_t CR2;         
  uint16_t      RESERVED4;   
  volatile uint16_t CR3;         
  uint16_t      RESERVED5;   
  volatile uint16_t GTPR;        
  uint16_t      RESERVED6;   
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CFR;   
  volatile uint32_t SR;    
} WWDG_TypeDef;



 
  


 










 




#line 909 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 920 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 931 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"





#line 944 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 951 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"










 
  


   

#line 992 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1009 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1016 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"




#line 1028 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"













 



 



 
    
 
 
 
 
 
 
 
 

 
#line 1070 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 1078 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1087 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

















  
 






































 


















































 


















































 




 













































 


 


 


 


 


 


 






#line 1328 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1335 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1342 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1349 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 1357 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1364 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1371 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1378 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1385 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1392 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 1400 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1407 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1414 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1421 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1428 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1435 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 1443 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1450 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1457 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1464 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1471 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1478 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 1486 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1493 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1500 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1507 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1514 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1521 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"


 
#line 1530 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1537 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1544 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 1551 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"





 


 


 


 


 


 




 





 
#line 1590 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 





 
 
 
 
 
 













#line 1622 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 




 


 


 


 


 


 


 


 


 


 


 
 
 
 
 

 

































 
 
 
 
 
 
#line 1736 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 





 




 
 
 
 
 

 


 


 


 
 
 
 
 

 










































 



 


 


 


 


 


 


 



 



 



 


 


 



 
 
 
 
 

 


#line 1882 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 









 

#line 1906 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 





 
 
 
 
 

 
#line 1948 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 1978 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 1988 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"















 
#line 2012 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"















 
#line 2036 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"















 
#line 2060 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"















 
#line 2084 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"















 
#line 2108 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"















 
#line 2132 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 
#line 2244 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 2270 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 2296 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 2322 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 2348 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 2374 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
 
 
 
 
 

 






 
#line 2402 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 


 


 


 





#line 2427 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 2437 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 



 


 
 
 
 
 
 











#line 2475 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 











#line 2498 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 











#line 2521 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 











#line 2544 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 








































 








































 








































 








































 


































 


































 


































 


































 
 
 
 
 
   
#line 2903 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

    
#line 2921 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

   
#line 2971 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

   
#line 3021 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3039 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
 
#line 3056 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3074 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
 
#line 3091 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

   
#line 3125 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3144 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3154 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3164 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
 
 
 
 

 
#line 3186 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3195 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"







 



#line 3216 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 



 


 
#line 3241 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3251 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 




 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 














 































 
#line 3342 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 



 


 
 
 
 
 

 











 
#line 3377 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"










 
#line 3394 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"





 
 
 
 
 
 


















 



#line 3437 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 




 









 











 
#line 3475 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"






 











 






 












 
#line 3523 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 





 











 
#line 3551 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"






 






 
#line 3573 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 3581 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 3590 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"


 
#line 3607 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
 
 
#line 3617 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3639 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3656 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"


 
#line 3667 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"


 
#line 3690 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3709 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3719 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3741 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 













 







 
#line 3773 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"


 
 
 
 
 
 
#line 3808 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3838 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3866 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3885 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 



 


 



 
#line 3938 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 3980 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 


 



 
#line 4019 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4039 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 
#line 4057 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4079 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4087 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4095 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 
 
 
 
 

 




 












 


 






#line 4233 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 4303 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4318 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4344 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 


 
 
 
 
 

 









#line 4377 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4386 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4396 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 


 


 


 





















 




 
 
 
 
 
 
#line 4448 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 







  
#line 4469 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4481 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4493 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4504 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 







  
#line 4521 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4532 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4543 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4554 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 







  
#line 4571 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4582 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4593 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4604 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 







  
#line 4621 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4632 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4643 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



  
#line 4654 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
 
 
 
 
 
 

 

































 
#line 4728 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4757 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4776 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 4794 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4813 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 4831 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4850 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 4868 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4887 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
 
 
 
 

 
















 









 



























 
#line 4962 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4974 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 4982 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
                   
 




























 





















 




























 





















 
#line 5098 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 


 

           
 


 


 


 


 
#line 5127 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

#line 5134 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 




 
 
 
 
 

 
#line 5160 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 


 



 
#line 5184 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 5193 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"







 
#line 5213 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 5224 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 5441 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 5453 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 






 
#line 5470 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5614 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5626 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5638 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5650 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5662 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5674 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5686 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5698 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 

 


#line 5712 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5724 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5736 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5748 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5760 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5772 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5784 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5796 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5808 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5820 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5832 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5844 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5856 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5868 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5880 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 


#line 5892 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 
 
 
 
 

 
#line 5910 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 
#line 5922 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"







 


 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 5995 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 6030 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 6065 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 6100 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
#line 6135 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 





 





 





 





 





 





 





 





 






 
#line 6202 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 



 









 
#line 6226 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"




 




 
#line 6242 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 





 
#line 6264 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 
 





 
#line 6279 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"
 
#line 6286 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"

 




 






 


 


 



 

 

  

#line 1 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"

























 

 



 
 
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"


























 

 







 
#line 1 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"











































 



 



 
    
#line 6346 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"



 

  

 

 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"



 



 

 



 
  
typedef struct
{
  uint32_t ADC_Resolution;                
 
  
  FunctionalState ADC_ScanConvMode;       

 
  
  FunctionalState ADC_ContinuousConvMode; 

 
  
  uint32_t ADC_ExternalTrigConvEdge;      

 
  
  uint32_t ADC_ExternalTrigConv;          

 
  
  uint32_t ADC_DataAlign;                 
 
  
  uint8_t  ADC_NbrOfConversion;           

 
}ADC_InitTypeDef;

typedef struct 
{                                              
  uint32_t ADC_Prescaler;                 

 
}ADC_CommonInitTypeDef;

 



  





  









  




  









  





  












  



  











  



  

 




 




 



 


 



 


#line 202 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"


  



  
  







  



  
   





#line 235 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"


   





#line 250 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"

 



#line 268 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"










#line 294 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"


  



  

#line 310 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"

#line 319 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"


  



  

#line 335 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"

#line 344 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"



 



  











  




  


 



 


 





 


 



 


 


#line 409 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"


  



  











  



  
  
#line 440 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"

#line 448 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"


  



  
  




 




  



  
  
#line 480 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_adc.h"
  

   







  



  
  




  



 
   




  



 
   




  



  
  




  



 
   




  



  
  




  



 
   




  



  






  



  

 
  

    
void ADC_DeInit(ADC_TypeDef* ADCx); 

  
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_CommonInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_BankSelection(ADC_TypeDef* ADCx, uint8_t ADC_Bank);

 
void ADC_PowerDownCmd(ADC_TypeDef* ADCx, uint32_t ADC_PowerDown, FunctionalState NewState);
void ADC_DelaySelectionConfig(ADC_TypeDef* ADCx, uint8_t ADC_DelayLength);

 
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);

 
void ADC_TempSensorVrefintCmd(FunctionalState NewState);

 
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_EOCOnEachRegularChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);

 
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMARequestAfterLastTransferCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

 
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length);
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvEdgeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConvEdge);
void ADC_SoftwareStartInjectedConv(ADC_TypeDef* ADCx);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel);

 
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint16_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint16_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT);









  



  

 
#line 35 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_aes.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_aes.h"



 



 

 



 
typedef struct
{
  uint32_t AES_Operation; 
 
  uint32_t AES_Chaining;  
 
  uint32_t AES_DataType;  
 
}AES_InitTypeDef;



  
typedef struct
{
  uint32_t AES_Key0;   
  uint32_t AES_Key1;   
  uint32_t AES_Key2;   
  uint32_t AES_Key3;   
}AES_KeyInitTypeDef;



  
typedef struct
{
  uint32_t AES_IV0;   
  uint32_t AES_IV1;   
  uint32_t AES_IV2;   
  uint32_t AES_IV3;   
}AES_IVInitTypeDef;

 



  



   












  



  









 



  











 



  









  



  








 



  









 



 

 
 

 
void AES_DeInit(void);
void AES_Init(AES_InitTypeDef* AES_InitStruct);
void AES_KeyInit(AES_KeyInitTypeDef* AES_KeyInitStruct);
void AES_IVInit(AES_IVInitTypeDef* AES_IVInitStruct);
void AES_Cmd(FunctionalState NewState);

 
void AES_StructInit(AES_InitTypeDef* AES_InitStruct);
void AES_KeyStructInit(AES_KeyInitTypeDef* AES_KeyInitStruct);
void AES_IVStructInit(AES_IVInitTypeDef* AES_IVInitStruct);

   
void AES_WriteSubData(uint32_t Data);
uint32_t AES_ReadSubData(void);
void AES_ReadKey(AES_KeyInitTypeDef* AES_KeyInitStruct);
void AES_ReadIV(AES_IVInitTypeDef* AES_IVInitStruct);

 
void AES_DMAConfig(uint32_t AES_DMATransfer, FunctionalState NewState);

 
void AES_ITConfig(uint32_t AES_IT, FunctionalState NewState);
FlagStatus AES_GetFlagStatus(uint32_t AES_FLAG);
void AES_ClearFlag(uint32_t AES_FLAG);
ITStatus AES_GetITStatus(uint32_t AES_IT);
void AES_ClearITPendingBit(uint32_t AES_IT);

 
ErrorStatus AES_ECB_Encrypt(uint8_t* Key, uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_ECB_Decrypt(uint8_t* Key, uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CBC_Encrypt(uint8_t* Key, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CBC_Decrypt(uint8_t* Key, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CTR_Encrypt(uint8_t* Key, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);
ErrorStatus AES_CTR_Decrypt(uint8_t* Key, uint8_t InitVectors[16], uint8_t* Input, uint32_t Ilength, uint8_t* Output);









  



 

 
#line 36 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_comp.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_comp.h"



 



 

 



 
  
typedef struct
{
  uint32_t COMP_Speed;               
 
  uint32_t COMP_InvertingInput;      
 
  uint32_t COMP_OutputSelect;        
 
   
}COMP_InitTypeDef;

 
   


  






 






 


  



 

#line 100 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_comp.h"

#line 109 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_comp.h"


  



 

#line 125 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_comp.h"

#line 134 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_comp.h"


  
  


 








 
  


  

 
 

 
void COMP_DeInit(void);

 
void COMP_Init(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(FunctionalState NewState);
uint8_t COMP_GetOutputLevel(uint32_t COMP_Selection);
void COMP_SW1SwitchConfig(FunctionalState NewState);

 
void COMP_WindowCmd(FunctionalState NewState);

 
void COMP_VrefintOutputCmd(FunctionalState NewState);









  



 

 
#line 37 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_crc.h"


























 

 
#line 74 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_crc.h"



 



 

 
#line 38 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"
 


 



 

 



 
  
typedef struct
{
  uint32_t DAC_Trigger;                      
 

  uint32_t DAC_WaveGeneration;               

 

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; 

 

  uint32_t DAC_OutputBuffer;                 
 
}DAC_InitTypeDef;

 



 



 
  
#line 90 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"

#line 99 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"
                                 


 
  


 

#line 114 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"


 
  


 

#line 146 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"

#line 171 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"


 



 







 
  


 







 



 

#line 209 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dac.h"


 



 







 



 





 



  
  





  




  
  

  




  



  

 
  

   
void DAC_DeInit(void);

 
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);

 
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);

 
void DAC_ITConfig(uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState);
FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG);
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG);
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT);
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT);









  



  

 
#line 39 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dbgmcu.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dbgmcu.h"



 



 

 
 



 






#line 72 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dbgmcu.h"








  

 
 

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);









 



 

 
#line 40 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"



 



 

 



 

typedef struct
{
  uint32_t DMA_PeripheralBaseAddr;  

  uint32_t DMA_MemoryBaseAddr;      

  uint32_t DMA_DIR;                
 

  uint32_t DMA_BufferSize;         

 

  uint32_t DMA_PeripheralInc;      
 

  uint32_t DMA_MemoryInc;          
 

  uint32_t DMA_PeripheralDataSize; 
 

  uint32_t DMA_MemoryDataSize;     
 

  uint32_t DMA_Mode;               


 

  uint32_t DMA_Priority;           
 

  uint32_t DMA_M2M;                
 
}DMA_InitTypeDef;

 



 

#line 109 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"



 







 



 







 



 







 



 

#line 156 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"


 



 

#line 170 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"


 



 






 



 

#line 197 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"


 



 







 



 






#line 250 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"

#line 271 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"



#line 298 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"


 



 
#line 333 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"

#line 354 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"



#line 381 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_dma.h"


 



 





 



 

 
 

  
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

 
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);

 
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);

 
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
void DMA_ClearFlag(uint32_t DMAy_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);









 



 

 
#line 41 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_exti.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_exti.h"



 



 

 



 

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;





 

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;






 

typedef struct
{
  uint32_t EXTI_Line;               
 
   
  EXTIMode_TypeDef EXTI_Mode;       
 

  EXTITrigger_TypeDef EXTI_Trigger; 
 

  FunctionalState EXTI_LineCmd;     
  
}EXTI_InitTypeDef;

 



 



 

#line 138 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_exti.h"










#line 160 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_exti.h"



 



 

 
 
 
void EXTI_DeInit(void);

 
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);

 
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);









 



 

 
#line 42 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"



 



 

 



  
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;

 
  


  
  


  







  



 
   





  



 
  





  



 
  
#line 138 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"



#line 173 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"



#line 208 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"







 




 





 




  



  


  
 






  



 







 



 







 



 







 



 

#line 294 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"



 



 

#line 310 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"

#line 317 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"



 
  


  

#line 337 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_flash.h"
    









  



  



















 
  


  




  



 





  


  

 
 
  


   
   
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);
void FLASH_ReadAccess64Cmd(FunctionalState NewState);
void FLASH_SLEEPPowerDownCmd(FunctionalState NewState);

    
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_FastProgramWord(uint32_t Address, uint32_t Data);

   
void DATA_EEPROM_Unlock(void);
void DATA_EEPROM_Lock(void);
void DATA_EEPROM_FixedTimeProgramCmd(FunctionalState NewState);
FLASH_Status DATA_EEPROM_EraseByte(uint32_t Address);
FLASH_Status DATA_EEPROM_EraseHalfWord(uint32_t Address);
FLASH_Status DATA_EEPROM_EraseWord(uint32_t Address);
FLASH_Status DATA_EEPROM_FastProgramByte(uint32_t Address, uint8_t Data);
FLASH_Status DATA_EEPROM_FastProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status DATA_EEPROM_FastProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status DATA_EEPROM_ProgramByte(uint32_t Address, uint8_t Data);
FLASH_Status DATA_EEPROM_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status DATA_EEPROM_ProgramWord(uint32_t Address, uint32_t Data);

 
void FLASH_OB_Unlock(void);
void FLASH_OB_Lock(void);
void FLASH_OB_Launch(void);
FLASH_Status FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState);
FLASH_Status FLASH_OB_WRP1Config(uint32_t OB_WRP1, FunctionalState NewState);
FLASH_Status FLASH_OB_WRP2Config(uint32_t OB_WRP2, FunctionalState NewState);
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
FLASH_Status FLASH_OB_PCROPConfig(uint32_t OB_WRP, FunctionalState NewState);
FLASH_Status FLASH_OB_PCROP1Config(uint32_t OB_WRP1, FunctionalState NewState);
FLASH_Status FLASH_OB_PCROPSelectionConfig(uint16_t OB_PcROP);
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
FLASH_Status FLASH_OB_BORConfig(uint8_t OB_BOR);
FLASH_Status FLASH_OB_BootConfig(uint8_t OB_BOOT);
uint8_t FLASH_OB_GetUser(void);
uint32_t FLASH_OB_GetWRP(void);
uint32_t FLASH_OB_GetWRP1(void);
uint32_t FLASH_OB_GetWRP2(void);
FlagStatus FLASH_OB_GetRDP(void);
FlagStatus FLASH_OB_GetSPRMOD(void);
uint8_t FLASH_OB_GetBOR(void);

   
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);





  
FLASH_Status FLASH_RUNPowerDownCmd(FunctionalState NewState);
FLASH_Status FLASH_EraseParallelPage(uint32_t Page_Address1, uint32_t Page_Address2);
FLASH_Status FLASH_ProgramHalfPage(uint32_t Address, uint32_t* pBuffer);
FLASH_Status FLASH_ProgramParallelHalfPage(uint32_t Address1, uint32_t* pBuffer1, uint32_t Address2, uint32_t* pBuffer2);
FLASH_Status DATA_EEPROM_EraseDoubleWord(uint32_t Address);
FLASH_Status DATA_EEPROM_ProgramDoubleWord(uint32_t Address, uint64_t Data);
  








 



  

 
#line 43 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_fsmc.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_fsmc.h"



 



 

 



 

typedef struct
{
  uint32_t FSMC_AddressSetupTime;       


 

  uint32_t FSMC_AddressHoldTime;        


 

  uint32_t FSMC_DataSetupTime;          


 

  uint32_t FSMC_BusTurnAroundDuration;  


 

  uint32_t FSMC_CLKDivision;            

 

  uint32_t FSMC_DataLatency;            





 

  uint32_t FSMC_AccessMode;             
 
}FSMC_NORSRAMTimingInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Bank;                
 

  uint32_t FSMC_DataAddressMux;      

 

  uint32_t FSMC_MemoryType;          

 

  uint32_t FSMC_MemoryDataWidth;     
 

  uint32_t FSMC_BurstAccessMode;     

 
                                       
  uint32_t FSMC_AsynchronousWait;     

 

  uint32_t FSMC_WaitSignalPolarity;  

 

  uint32_t FSMC_WrapMode;            

 

  uint32_t FSMC_WaitSignalActive;    


 

  uint32_t FSMC_WriteOperation;      
 

  uint32_t FSMC_WaitSignal;          

 

  uint32_t FSMC_ExtendedMode;        
 

  uint32_t FSMC_WriteBurst;          
  

  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;    

  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;            
}FSMC_NORSRAMInitTypeDef;

 



 



 











 



 



 








 



 

#line 200 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_fsmc.h"



 



 








 



 







 
  


 







 
  


 








 



 








 



 








 



 





                              


 



 







 



 









 



 







 



 





 



 





 



 





 



 





 



 





 



 





 



 

#line 404 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_fsmc.h"



 



 



 

 
  
 
void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState);








 



  

 
#line 44 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"



 



 

 

#line 58 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"



  
typedef enum
{ 
  GPIO_Mode_IN   = 0x00,  
  GPIO_Mode_OUT  = 0x01,  
  GPIO_Mode_AF   = 0x02,  
  GPIO_Mode_AN   = 0x03   
}GPIOMode_TypeDef;




 



  
typedef enum
{ GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;




 



  
typedef enum
{ 
  GPIO_Speed_400KHz = 0x00,  
  GPIO_Speed_2MHz   = 0x01,  
  GPIO_Speed_10MHz  = 0x02,  
  GPIO_Speed_40MHz  = 0x03   
}GPIOSpeed_TypeDef;




 



  
typedef enum
{ GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
}GPIOPuPd_TypeDef;




 



 
typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;




 



  
typedef struct
{
  uint32_t GPIO_Pin;              
 

  GPIOMode_TypeDef GPIO_Mode;     
 

  GPIOSpeed_TypeDef GPIO_Speed;   
 

  GPIOOType_TypeDef GPIO_OType;   
 

  GPIOPuPd_TypeDef GPIO_PuPd;     
 
}GPIO_InitTypeDef;

 



 
  


 
#line 178 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"

#line 196 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"


 



  
#line 219 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"

#line 236 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"


 



 



  
#line 253 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"



  



  





  





  




  




  



  





  




  



  



  




  




  


#line 333 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_gpio.h"



 



 
    




 



   
  
 
 

 
void GPIO_DeInit(GPIO_TypeDef* GPIOx);

 
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

 
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

 
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);









 



 

 
#line 45 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"



 



 

 



 

typedef struct
{
  uint32_t I2C_ClockSpeed;          
 

  uint16_t I2C_Mode;                
 

  uint16_t I2C_DutyCycle;           
 

  uint16_t I2C_OwnAddress1;         
 

  uint16_t I2C_Ack;                 
 

  uint16_t I2C_AcknowledgedAddress; 
 
}I2C_InitTypeDef;

 




 





 

#line 94 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"


 



 







  



 







 



 







 



 







  



 

#line 168 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"


 



 







 



 







  



 







  



 







  



 

#line 238 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"



#line 248 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"


 



 



 

#line 267 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"



 

#line 286 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"



#line 300 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"


 



 





 








 
 

























 

 


 





























 

  
 


 
 

 







 

























 

    
 



 



 



























 

  
 

 


 
 


 






 

#line 506 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_i2c.h"


 



 




 



 




 



 

 
 

 
void I2C_DeInit(I2C_TypeDef* I2Cx);

 
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert);
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);

  
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition);

  
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx);

 
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);


 
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);

























































































 





 
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);




 
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);




 
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);


void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);









  



  

 
#line 46 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_iwdg.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_iwdg.h"



 



 

 
 



 



 







 



 

#line 85 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_iwdg.h"


 



 







 



 

 
 

 
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);

 
void IWDG_Enable(void);

 
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);









 



 

 
#line 47 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"



 



  

 
 


 

typedef struct
{
  uint32_t LCD_Prescaler;     
 
  uint32_t LCD_Divider;       
 
  uint32_t LCD_Duty;          
 
  uint32_t LCD_Bias;          
  
  uint32_t LCD_VoltageSource; 
 
}LCD_InitTypeDef;


 



 



 

#line 95 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"

#line 112 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"



 
  


 

#line 137 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"

#line 154 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"



 




 
  














  
  



 
  









  
    


 
  





                           


   



 






 


 



 

#line 236 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"

#line 245 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"


 




 

#line 262 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"

#line 271 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"


 



 













     



 

#line 305 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"

#line 314 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"


 



 

#line 330 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"

#line 339 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"


 
      


 

#line 353 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"








    



 

#line 383 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"

#line 400 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_lcd.h"



   
   


 

 
 

 
void LCD_DeInit(void);

 
void LCD_Init(LCD_InitTypeDef* LCD_InitStruct);
void LCD_StructInit(LCD_InitTypeDef* LCD_InitStruct);
void LCD_Cmd(FunctionalState NewState);
void LCD_WaitForSynchro(void);
void LCD_HighDriveCmd(FunctionalState NewState);
void LCD_MuxSegmentCmd(FunctionalState NewState);
void LCD_PulseOnDurationConfig(uint32_t LCD_PulseOnDuration);
void LCD_DeadTimeConfig(uint32_t LCD_DeadTime);
void LCD_BlinkConfig(uint32_t LCD_BlinkMode, uint32_t LCD_BlinkFrequency);
void LCD_ContrastConfig(uint32_t LCD_Contrast);

 
void LCD_Write(uint32_t LCD_RAMRegister, uint32_t LCD_Data);
void LCD_UpdateDisplayRequest(void);

 
void LCD_ITConfig(uint32_t LCD_IT, FunctionalState NewState);
FlagStatus LCD_GetFlagStatus(uint32_t LCD_FLAG);
void LCD_ClearFlag(uint32_t LCD_FLAG);
ITStatus LCD_GetITStatus(uint32_t LCD_IT);
void LCD_ClearITPendingBit(uint32_t LCD_IT);









 



 

 
#line 48 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_opamp.h"


























  

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_opamp.h"



 



 

 
 



  



 











  



 

 






 
#line 89 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_opamp.h"

 










  



 









  



 









  



 





 



 









  


 

 
 
 
void OPAMP_DeInit(void);
void OPAMP_SwitchCmd(uint32_t OPAMP_OPAMPxSwitchy, FunctionalState NewState);
void OPAMP_Cmd(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_LowPowerCmd(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_PowerRangeSelect(uint32_t OPAMP_PowerRange);

 
void OPAMP_OffsetTrimmingModeSelect(uint32_t OPAMP_Trimming);
void OPAMP_OffsetTrimConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue);
void OPAMP_OffsetTrimLowPowerConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue);
FlagStatus OPAMP_GetFlagStatus(uint32_t OPAMP_Selection);









  



 

 
#line 49 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_pwr.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_pwr.h"



 



  

 
 



  



  

#line 72 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_pwr.h"


 



 

#line 86 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_pwr.h"


 

  


 










     
  


 







 



 




 


 
  


 




 


 



 

#line 152 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_pwr.h"








 



 

 
 

  
void PWR_DeInit(void);

  
void PWR_RTCAccessCmd(FunctionalState NewState);

  
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_PVDCmd(FunctionalState NewState);

  
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);

  
void PWR_FastWakeUpCmd(FunctionalState NewState);
void PWR_UltraLowPowerCmd(FunctionalState NewState);

  
void PWR_VoltageScalingConfig(uint32_t PWR_VoltageScaling);

  
void PWR_EnterLowPowerRunMode(FunctionalState NewState);
void PWR_EnterSleepMode(uint32_t PWR_Regulator, uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);

  
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);









 



 

 
#line 50 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"



 



 

 

typedef struct
{
  uint32_t SYSCLK_Frequency;
  uint32_t HCLK_Frequency;
  uint32_t PCLK1_Frequency;
  uint32_t PCLK2_Frequency;
}RCC_ClocksTypeDef;

 



 



 









  



 

#line 89 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"

#line 97 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"



  
  


 








  



 

#line 128 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"









 



 










 
  


 

#line 166 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"


 



 

#line 188 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"


  



 

#line 204 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"


 
  



 

#line 221 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"












 
  


 








 



 

#line 264 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"


 



 

#line 287 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"






 



 

#line 307 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"




  



 

#line 337 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"





 



 

#line 356 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"







 



 












   



 

#line 400 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"

#line 408 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rcc.h"






 



 

 
 

 
void RCC_DeInit(void);

 
void RCC_HSEConfig(uint8_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_MSIRangeConfig(uint32_t RCC_MSIRange);
void RCC_AdjustMSICalibrationValue(uint8_t MSICalibrationValue);
void RCC_MSICmd(FunctionalState NewState);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint8_t RCC_PLLSource, uint8_t RCC_PLLMul, uint8_t RCC_PLLDiv);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_LSEClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCOSource, uint8_t RCC_MCODiv);

 
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

 
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_RTCResetCmd(FunctionalState NewState);

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

void RCC_AHBPeriphClockLPModeCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockLPModeCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockLPModeCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

 
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);









 



  

 
#line 51 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



 



  

 



  
typedef struct
{
  uint32_t RTC_HourFormat;   
 
  
  uint32_t RTC_AsynchPrediv; 
 
  
  uint32_t RTC_SynchPrediv;  
  
}RTC_InitTypeDef;



 
typedef struct
{
  uint8_t RTC_Hours;    


 

  uint8_t RTC_Minutes;  
 
  
  uint8_t RTC_Seconds;  
 

  uint8_t RTC_H12;      
 
}RTC_TimeTypeDef; 



 
typedef struct
{
  uint8_t RTC_WeekDay; 
 
  
  uint8_t RTC_Month;   
 

  uint8_t RTC_Date;     
 
  
  uint8_t RTC_Year;     
 
}RTC_DateTypeDef;



 
typedef struct
{
  RTC_TimeTypeDef RTC_AlarmTime;      

  uint32_t RTC_AlarmMask;            
 

  uint32_t RTC_AlarmDateWeekDaySel;  
 
  
  uint8_t RTC_AlarmDateWeekDay;      



 
}RTC_AlarmTypeDef;

 



  




  






  



  

 


  




  




  



  







  



  






  



  




  



  

 
#line 211 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



  



  
  
#line 234 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"


  




  
#line 250 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



  




  








  




  
#line 280 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



  



  







  



  
#line 349 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"


  



  





  



 
#line 379 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"


  



  






  



  




 







  



  






  



  








  

 

  






  



  
#line 458 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"
                                          


  



  
#line 473 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



  



  




 



  











  



  
#line 514 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



  



  


#line 534 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"


  



  
#line 565 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



 

  

  
#line 581 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"







 



  
#line 599 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"






 



  







 



  






  



  




 
  


 

#line 707 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"


  



  






  



  
#line 750 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



  



  
#line 766 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"


#line 774 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_rtc.h"



  



  





 



  


 
  

  
ErrorStatus RTC_DeInit(void);


  
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct);
void RTC_WriteProtectionCmd(FunctionalState NewState);
ErrorStatus RTC_EnterInitMode(void);
void RTC_ExitInitMode(void);
ErrorStatus RTC_WaitForSynchro(void);
ErrorStatus RTC_RefClockCmd(FunctionalState NewState);
void RTC_BypassShadowCmd(FunctionalState NewState);

  
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
uint32_t RTC_GetSubSecond(void);
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct);
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct);

  
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct);
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState);
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask);
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm);

  
void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock);
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter);
uint32_t RTC_GetWakeUpCounter(void);
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState);

  
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation);
uint32_t RTC_GetStoreOperation(void);

  
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity);

 
ErrorStatus RTC_CoarseCalibConfig(uint32_t RTC_CalibSign, uint32_t Value);
ErrorStatus RTC_CoarseCalibCmd(FunctionalState NewState);
void RTC_CalibOutputCmd(FunctionalState NewState);
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput);
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod, 
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue);

  
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState);
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct, 
                                      RTC_DateTypeDef* RTC_StampDateStruct);
uint32_t RTC_GetTimeStampSubSecond(void);

  
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger);
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState);
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter);
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq);
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration);
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState);
void RTC_TamperPullUpCmd(FunctionalState NewState);

  
void RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data);
uint32_t RTC_ReadBackupRegister(uint32_t RTC_BKP_DR);

  
void RTC_OutputTypeConfig(uint32_t RTC_OutputType);

 
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS);

  
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG);
void RTC_ClearFlag(uint32_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint32_t RTC_IT);
void RTC_ClearITPendingBit(uint32_t RTC_IT);









  



  

 
#line 52 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"



 



 

 

typedef struct
{
  uint32_t SDIO_ClockEdge;            
 

  uint32_t SDIO_ClockBypass;          

 

  uint32_t SDIO_ClockPowerSave;       

 

  uint32_t SDIO_BusWide;              
 

  uint32_t SDIO_HardwareFlowControl;  
 

  uint8_t SDIO_ClockDiv;              
 

} SDIO_InitTypeDef;

typedef struct
{
  uint32_t SDIO_Argument;  


 

  uint32_t SDIO_CmdIndex;   

  uint32_t SDIO_Response;  
 

  uint32_t SDIO_Wait;      
 

  uint32_t SDIO_CPSM;      

 
} SDIO_CmdInitTypeDef;

typedef struct
{
  uint32_t SDIO_DataTimeOut;     

  uint32_t SDIO_DataLength;      
 
  uint32_t SDIO_DataBlockSize;  
 
 
  uint32_t SDIO_TransferDir;    

 
 
  uint32_t SDIO_TransferMode;   
 
 
  uint32_t SDIO_DPSM;           

 
} SDIO_DataInitTypeDef;

 



 



 







 



 







  



 







 



 









 



 







 



 






  




 

#line 224 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"


  



 




 



 

#line 247 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"


 



 








 



 






  



 

#line 285 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"


 



 




 



 

#line 332 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"


 



 







 



 







 



 






 



 

#line 423 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"



#line 450 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_sdio.h"





 



 







 



 

 
  
 
void SDIO_DeInit(void);

 
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(uint32_t SDIO_PowerState);
uint32_t SDIO_GetPowerState(void);

 
void SDIO_DMACmd(FunctionalState NewState);

 
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
uint8_t SDIO_GetCommandResponse(void);
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP);

 
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
uint32_t SDIO_GetDataCounter(void);
uint32_t SDIO_ReadData(void);
void SDIO_WriteData(uint32_t Data);
uint32_t SDIO_GetFIFOCount(void);

 
void SDIO_StartSDIOReadWait(FunctionalState NewState);
void SDIO_StopSDIOReadWait(FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);

 
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
void SDIO_SendCEATACmd(FunctionalState NewState);

 
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG);
void SDIO_ClearFlag(uint32_t SDIO_FLAG);
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT);
void SDIO_ClearITPendingBit(uint32_t SDIO_IT);









 



 

 
#line 53 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"



 



  

 



 

typedef struct
{
  uint16_t SPI_Direction;           
 

  uint16_t SPI_Mode;                
 

  uint16_t SPI_DataSize;            
 

  uint16_t SPI_CPOL;                
 

  uint16_t SPI_CPHA;                
 

  uint16_t SPI_NSS;                 

 
 
  uint16_t SPI_BaudRatePrescaler;   



 

  uint16_t SPI_FirstBit;            
 

  uint16_t SPI_CRCPolynomial;        
}SPI_InitTypeDef;



 

typedef struct
{

  uint16_t I2S_Mode;         
 

  uint16_t I2S_Standard;     
 

  uint16_t I2S_DataFormat;   
 

  uint16_t I2S_MCLKOutput;   
 

  uint32_t I2S_AudioFreq;    
 

  uint16_t I2S_CPOL;         
 
}I2S_InitTypeDef;

 



 









 
  
#line 137 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


 



 







 



 







  



 







 



 







 



 







  



 

#line 221 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


  



 







 



 

#line 249 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


 
  



 

#line 268 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


 
  


 

#line 284 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


 



 







 



 

#line 314 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"






 
            


 







 



 






 



 







 



 






 



 







 



 























 



 

#line 421 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"

#line 428 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


 



 




 



 

#line 464 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_spi.h"


 
  


 

 
 

  
void SPI_I2S_DeInit(SPI_TypeDef* SPIx);

 
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

  
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);

 
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);

 
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);

 
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);









 



 

 
#line 54 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"



 



  
  
 
 



  
  


  
#line 66 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"
                                      
#line 75 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"


 



  
#line 114 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"


 



  




   







 
  


 










 


  



 











  



 









  



  
  








  
  


  
  












  
  


  
                                                             
#line 235 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"

#line 252 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"



  



  
  
 
#line 293 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"

   
#line 322 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"


#line 381 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"



 



 

#line 397 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"

#line 405 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"


 



 
#line 429 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_syscfg.h"





 



 

 
 

 
void SYSCFG_DeInit(void);
void SYSCFG_RIDeInit(void);

  
void SYSCFG_MemoryRemapConfig(uint8_t SYSCFG_MemoryRemap);
uint32_t SYSCFG_GetBootMode(void);
void SYSCFG_USBPuCmd(FunctionalState NewState);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);

  
void SYSCFG_RITIMSelect(uint32_t TIM_Select);
void SYSCFG_RITIMInputCaptureConfig(uint32_t RI_InputCapture, uint32_t RI_InputCaptureRouting);
void SYSCFG_RIResistorConfig(uint32_t RI_Resistor, FunctionalState NewState);
void SYSCFG_RIChannelSpeedConfig(uint32_t RI_Channel, uint32_t RI_ChannelSpeed);
void SYSCFG_RISwitchControlModeCmd(FunctionalState NewState);
void SYSCFG_RIIOSwitchConfig(uint32_t RI_IOSwitch, FunctionalState NewState);
void SYSCFG_RIHysteresisConfig(uint8_t RI_Port, uint16_t RI_Pin, FunctionalState NewState);









  



  

 
#line 55 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"



 



  

 




 

typedef struct
{
  uint16_t TIM_Prescaler;         
 

  uint16_t TIM_CounterMode;       
 

  uint32_t TIM_Period;            

  

  uint16_t TIM_ClockDivision;     
 

} TIM_TimeBaseInitTypeDef;       



 

typedef struct
{
  uint16_t TIM_OCMode;        
 

  uint16_t TIM_OutputState;   
 

  uint32_t TIM_Pulse;         
 

  uint16_t TIM_OCPolarity;    
 

} TIM_OCInitTypeDef;



 

typedef struct
{

  uint16_t TIM_Channel;      
 

  uint16_t TIM_ICPolarity;   
 

  uint16_t TIM_ICSelection;  
 

  uint16_t TIM_ICPrescaler;  
 

  uint16_t TIM_ICFilter;     
 
} TIM_ICInitTypeDef;

 

  


 

#line 131 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"

 
#line 140 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"

 





 






 
#line 162 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"

 
#line 170 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"

 










 

#line 204 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


 



 







  



 










                                 





  



 

#line 251 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


 



 

#line 269 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 







 




 







  




 







  



 

#line 321 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 337 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 353 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 368 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"

#line 375 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 419 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 463 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 478 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"



  



 

#line 495 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 523 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 







  



  






 



 







  



 







  



 

#line 584 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  




 

#line 600 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"
   


  



 

#line 615 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 







  



 





                                     


  



 







  



 

#line 676 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 

#line 692 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


  



 







  
  


 

#line 733 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"



  



 




  



 




 



 







 



 






























#line 822 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"



 



 

#line 849 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_tim.h"


 



 
  
 
  

 
void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload);
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

 
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_SelectOCREFClear(TIM_TypeDef* TIMx, uint16_t TIM_OCReferenceClear);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);

 
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);

 
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);

 
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);


 
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);

                    
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);

 
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_Remap);










  



 

 
#line 56 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"



 



  

  



  
  
typedef struct
{
  uint32_t USART_BaudRate;            



 

  uint16_t USART_WordLength;          
 

  uint16_t USART_StopBits;            
 

  uint16_t USART_Parity;              




 
 
  uint16_t USART_Mode;                
 

  uint16_t USART_HardwareFlowControl; 

 
} USART_InitTypeDef;



  
  
typedef struct
{

  uint16_t USART_Clock;   
 

  uint16_t USART_CPOL;    
 

  uint16_t USART_CPHA;    
 

  uint16_t USART_LastBit; 

 
} USART_ClockInitTypeDef;

 



  
  












  
  


                                    




  



  
  
#line 145 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"


  



  
  
#line 159 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"


  



  
  





  



  
#line 186 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"


  



  






  



 
  






  



 







 



 







  



 
  
#line 253 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"



 



 

#line 274 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"


 



 







  



 







 



 
  







 



 







  



 

#line 346 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_usart.h"
                              








  



  

 
  

  
void USART_DeInit(USART_TypeDef* USARTx);

 
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);

  
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);

 
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp);
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);

 
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendBreak(USART_TypeDef* USARTx);

 
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);

 
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);

 
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);

 
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);

 
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);









  



  

 
#line 57 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_wwdg.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_wwdg.h"



 



  

 
 



  
  


  
  
#line 69 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_wwdg.h"



  



  

 
 
   
void WWDG_DeInit(void);

 
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint8_t Counter);

 
void WWDG_Enable(uint8_t Counter);

 
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);









  



  

 
#line 58 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"
#line 1 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\misc.h"


























 

 







 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\misc.h"



 



 

 



 

typedef struct
{
  uint8_t NVIC_IRQChannel;                    


 

  uint8_t NVIC_IRQChannelPreemptionPriority;  

 

  uint8_t NVIC_IRQChannelSubPriority;         

 

  FunctionalState NVIC_IRQChannelCmd;         

    
} NVIC_InitTypeDef;

























 

 



 



 







 



 

#line 128 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\misc.h"


 



 

#line 146 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\misc.h"















 



 







 



 

 
  

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);









 



 

 
#line 59 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"

 
 

 
 

 
#line 82 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx_conf.h"



 
#line 6317 "..\\Libraries\\CMSIS\\CM3\\DeviceSupport\\ST\\STM32L1xx\\stm32l1xx.h"




 

















 









 

  

 

 
#line 39 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\inc\\stm32l1xx_crc.h"



 



 

 
 



 



 

 
  

void CRC_ResetDR(void);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);









 



 

 
#line 30 "..\\Libraries\\STM32L1xx_StdPeriph_Driver\\src\\stm32l1xx_crc.c"



 




 

 
 
 
 
 
 



 





 
void CRC_ResetDR(void)
{
   
  ((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->CR = ((uint32_t)0x00000001);
}





 
uint32_t CRC_CalcCRC(uint32_t Data)
{
  ((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->DR = Data;
  
  return (((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->DR);
}






 
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;
  
  for(index = 0; index < BufferLength; index++)
  {
    ((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->DR = pBuffer[index];
  }
  return (((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->DR);
}





 
uint32_t CRC_GetCRC(void)
{
  return (((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->DR);
}





 
void CRC_SetIDRegister(uint8_t IDValue)
{
  ((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->IDR = IDValue;
}





 
uint8_t CRC_GetIDRegister(void)
{
  return (((CRC_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x3000))->IDR);
}



 



 



 

 
