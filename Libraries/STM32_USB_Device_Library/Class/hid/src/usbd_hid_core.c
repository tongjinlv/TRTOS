/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
/**
  ******************************************************************************
  * @file    usbd_hid_core.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    19-March-2012
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Joystick)
  *             - Collection : Application 
  *      
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *           
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"






static uint8_t  USBD_HID_Init (void  *pdev, 
                               uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit (void  *pdev, 
                                 uint8_t cfgidx);

static uint8_t  USBD_HID_Setup (void  *pdev, 
                                USB_SETUP_REQ *req);

static uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length);

static uint8_t  USBD_HID_DataIn (void  *pdev, uint8_t epnum);

static uint8_t  USBD_HID_DataOut (void  *pdev, uint8_t epnum);
/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Variables
  * @{
  */ 

USBD_Class_cb_TypeDef  USBD_HID_cb = 
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/     // ����״̬���ʱ����
  NULL, /*EP0_RxReady*/	   // ����״̬���ʱ����
  USBD_HID_DataIn, /*DataIn*/
  USBD_HID_DataOut, /*DataOut*/
  NULL, /*SOF */
  NULL,	/* IsoINIncomplete */
  NULL, /* IsoOUTIncomplete */     
  USBD_HID_GetCfgDesc,	 // ��ȡ����������  
#ifdef USB_OTG_HS_CORE  
  USBD_HID_GetCfgDesc, /* use same config as per FS */
#endif  
};

//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
//    #pragma data_alignment=4   
//  #endif
//#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */        
__ALIGN_BEGIN static uint32_t  USBD_HID_AltSet  __ALIGN_END = 0;

//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
//    #pragma data_alignment=4   
//  #endif
//#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */      
__ALIGN_BEGIN static uint32_t  USBD_HID_Protocol  __ALIGN_END = 0;

//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
//    #pragma data_alignment=4   
//  #endif
//#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */  
__ALIGN_BEGIN static uint32_t  USBD_HID_IdleState __ALIGN_END = 0;

//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
//    #pragma data_alignment=4   
//  #endif
//#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */ 

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t USB_Rx_Buffer   [HID_OUT_PACKET] __ALIGN_END ;


/*  ���������� */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ] __ALIGN_END =
{
  // ����������
  0x09,         /* bLength: Configuration Descriptor size �ֽ��� */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,  /* bDescriptorType: Configuration ���������� */
  USB_HID_CONFIG_DESC_SIZ,    /* wTotalLength: Bytes returned ���������������� */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface ��������֧�ֵĽӿ��� */
  0x01,         /*bConfigurationValue: Configuration value �����õ�ֵ */
  0x00,         /*iConfiguration: Index of string descriptor describing
                  the configuration ���������õ��ַ���������ֵ */
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up  ���豸������ */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus �豸����ĵ���(��λ2mA) */
  
  // �ӿ�������
  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size �ֽ��� */
  USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface �ӿ�������*/
  0x00,         /*bInterfaceNumber: Number of Interface �ýӿڱ��(��0��ʼ) */
  0x00,         /*bAlternateSetting: Alternate setting �ýӿڵı��ñ�� */
  0x02,         /*bNumEndpoints �ýӿ����õĶ˵��� */
  0x03,         /*bInterfaceClass:  �ýӿ���ʹ�õ��� */
  0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot �ýӿ���ʹ�õ����� */
  0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse �ýӿ���ʹ�õ�Э�� */
  0,            /*iInterface: Index of string descriptor �����ýӿڵ��ַ���������ֵ */

  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size ������������ */
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID ���������� */
  0x11,         /*bcdHID: HID Class Spec release number HID�淶�汾�� */
  0x01,
  0x00,         /*bCountryCode: Hardware target country Ӳ������ʶ���� */
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow ֧�ֵĸ���������Ŀ */
  0x22,         /*bDescriptorType HID��������������� */
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor �����������ܳ� */
  0x00,

  /******************** Descriptor of endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size �ֽ��� */
  USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType: �˵�������*/
  
  HID_IN_EP,     /*bEndpointAddress: Endpoint Address (IN) �ö˵��ַ ���� */
  0x03,          /*bmAttributes: Interrupt endpoint �ö˵����� */
  HID_IN_PACKET, /*wMaxPacketSize: �ö˵�֧������ֽ��� */
  0x00,
  0x0A,          /*bInterval: Polling Interval (10 ms) �˵�Ĳ�ѯʱ�� */
  /* 34 */

  0x07,          /*bLength: Endpoint Descriptor size �ֽ��� */
  USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType: �˵�������*/
  
  HID_OUT_EP,     /*bEndpointAddress: Endpoint Address (OUT) �ö˵��ַ ��� */
  0x03,          /*bmAttributes: Interrupt endpoint �ö˵����� */
  HID_OUT_PACKET, /*wMaxPacketSize: �ö˵�֧������ֽ��� */
  0x00,
  0x0A,          /*bInterval: Polling Interval (10 ms) �˵�Ĳ�ѯʱ�� */
  /* 41 */
} ;



/* ���������� */  
__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE] __ALIGN_END = 
{
  0x05,   0x01,		// USAGE_PAGE(Generic Desktop) ͨ�������豸
  0x09,   0x00,		// USAGE(0)  // �Զ���HID
  0xA1,   0x01,		// COLLECTION(Application) ��ʾӦ�ü��ϣ�����Ҫ��END_COLLECTION��������
  0x15,   0x00,		//  LOGICAL_MINIMUM(0)	ȫ����Ŀ���߼���СֵΪ0
  
  0x25,   0xFF,		// LOGICAL_MAXIMUM(255)	ȫ����Ŀ���߼����ֵΪ255
  0x19,   0x01,		// USAGE_MINIMUM(1)	 ȫ����Ŀ����;��СֵΪ1
  0x29,   0x08,		// USAGE_MAXIMUM(8)	 ȫ����Ŀ����;���ֵΪ8
  0x95,   HID_INOUT_BYTES,		// REPORT_COUNT(8)  ȫ����Ŀ�������������Ϊ8
  
  0x75,   0x08,		// REPORT_SIZE(8)  ȫ����Ŀ��ÿ�������򳤶�Ϊ8λ
  0x81,   0x02,		// INPUT(Data,Var,Abs) ����Ŀ����8������Ϊ8λ����������Ϊ����
  0x19,   0x01,		// USAGE_MINIMUM(1)	�ֲ���Ŀ����;����СֵΪ1
  0x29,   0x08,		// USAGE_MAXIMUM(8)	�ֲ���Ŀ����;�����ֵΪ8
  
  0x91,   0x02,		// OUTPUT(Data,Var,Abs)	����Ŀ�������������(8�ֽ�,ע��ǰ���ȫ����Ŀ)
  0xC0				// END_COLLECTION
}; 



/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_Init (void  *pdev, 
                               uint8_t cfgidx)
{
  
  /* Open EP IN */
  DCD_EP_Open(pdev,
              HID_IN_EP,
              HID_IN_PACKET,
              USB_OTG_EP_INT);
  
  /* Open EP OUT */
  DCD_EP_Open(pdev,
              HID_OUT_EP,
              HID_OUT_PACKET,
              USB_OTG_EP_INT);

  /* Prepare Out endpoint to receive next packet */
  DCD_EP_PrepareRx(pdev,
                   HID_OUT_EP,
                   (uint8_t*)(USB_Rx_Buffer),
                   HID_OUT_PACKET);
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit (void  *pdev, 
                                 uint8_t cfgidx)
{
  /* Close HID EPs */
  DCD_EP_Close (pdev , HID_IN_EP);
  DCD_EP_Close (pdev , HID_OUT_EP);
  
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup (void  *pdev, 
                                USB_SETUP_REQ *req)
{
  uint16_t len = 0;
  uint8_t  *pbuf = NULL;
  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)	// bmRequest D5~D6 ��������
  {
  case USB_REQ_TYPE_CLASS :     //======= ������
    switch (req->bRequest)
    {
      
      
    case HID_REQ_SET_PROTOCOL:	  // ����PROTOCOL
      USBD_HID_Protocol = (uint8_t)(req->wValue);
      break;
      
    case HID_REQ_GET_PROTOCOL:	 // ��ȡPROTOCOL
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&USBD_HID_Protocol,
                        1);    
      break;
      
    case HID_REQ_SET_IDLE:		// ����IDLE State
      USBD_HID_IdleState = (uint8_t)(req->wValue >> 8);
      break;
      
    case HID_REQ_GET_IDLE:		// ��ȡIDLE State
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&USBD_HID_IdleState,
                        1);        
      break;      
      
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:	  //======= ��׼����
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR: 		// ��ȡ������
      if( req->wValue >> 8 == HID_REPORT_DESC)	   // ����������
      {
        len = MIN(HID_MOUSE_REPORT_DESC_SIZE , req->wLength);
        pbuf = HID_MOUSE_ReportDesc;
      }
      else if( req->wValue >> 8 == HID_DESCRIPTOR_TYPE)	 // ����������
      {
        
//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//        pbuf = USBD_HID_Desc;   
//#else
        pbuf = USBD_HID_CfgDesc + 0x12;
//#endif 
        len = MIN(USB_HID_DESC_SIZ , req->wLength);
      }
      
      USBD_CtlSendData (pdev, 
                        pbuf,
                        len);
      
      break;
      
    case USB_REQ_GET_INTERFACE :	  // Get Interface
      USBD_CtlSendData (pdev,
                        (uint8_t *)&USBD_HID_AltSet,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :	 // Set Interface
      USBD_HID_AltSet = (uint8_t)(req->wValue);
      break;
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_SendReport 
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport     (USB_OTG_CORE_HANDLE  *pdev, 
                                 uint8_t *report,
                                 uint16_t len)
{
  if (pdev->dev.device_status == USB_OTG_CONFIGURED )
  {
    DCD_EP_Tx (pdev, HID_IN_EP, report, len);
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgDesc);
  return USBD_HID_CfgDesc;
}

/**
  * @brief  USBD_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataIn (void  *pdev, 
                              uint8_t epnum)
{
  
  /* Ensure that the FIFO is empty before a new transfer, this condition could 
  be caused by  a new transfer before the end of the previous transfer */
  DCD_EP_Flush(pdev, HID_IN_EP);
  return USBD_OK;
}

/*
  Dataout ���ݴ�������PC��������
*/
extern uint32_t count;
static uint8_t  USBD_HID_DataOut (void  *pdev, uint8_t epnum)
{
	uint8_t i;
	/* ������USB_Rx_Buffer�� */
    if(USB_Rx_Buffer[0]&0x01)	  // LED1
       STM_EVAL_LEDOn(LED1);
	else
		STM_EVAL_LEDOff(LED1);

	if(USB_Rx_Buffer[0]&0x02)	  // LED2
       STM_EVAL_LEDOn(LED2);
	else
		STM_EVAL_LEDOff(LED2);

	if(USB_Rx_Buffer[0]&0x04)	  // LED3
       STM_EVAL_LEDOn(LED3);
	else
		STM_EVAL_LEDOff(LED3);

	if(USB_Rx_Buffer[1]!=0)		  // ��ռ���
	    count=0;
	
	for(i=0;i<HID_OUT_PACKET;i++)	// ��ջ��� 
	    USB_Rx_Buffer[i]=0;



	/* Prepare Out endpoint to receive next packet */
	  DCD_EP_PrepareRx(pdev,
	                   HID_OUT_EP,
	                   (uint8_t*)(USB_Rx_Buffer),
	                   HID_OUT_PACKET);

    return USBD_OK;
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
