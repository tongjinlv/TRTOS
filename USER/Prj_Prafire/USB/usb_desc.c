/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_desc.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Descriptors for Joystick Mouse Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const u8 Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
  {	 //�豸������
    0x12,                       /*bLength �������ĳ��ȣ��豸�������ĳ���Ϊ18���ֽ�*/
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType�����������ͣ��豸������������Ϊ0x01*/
    0x00,                      
    0x02,                       /*bcdUSB USB�豸����ѭ��Э��汾�ţ�����2.0Э��Ϊ0x0200*/
    0x00,                       /*bDeviceClassUSB�豸����룬��USB-IF���䣬������ֶ�Ϊ0x00����ʾ�ɽӿ���������ָ�����п��ܸ�USB�豸��һ�������豸��USB�豸�ĸ����ӿ��໥�������ֱ����ڲ�ͬ���豸�ࣩ�������0x01~0xfe����ʾΪUSB-IF������豸�࣬����0x03ΪHID�豸��0x09ΪHUB�豸�������0xff����ʾ�ɳ����Զ����豸���͡�*/
    0x00,                       /*bDeviceSubClass USB������룬��USB-IF���䣬���bDeviceClassΪ0x00����ô���ֶ�Ҳ����Ϊ 0x00������������Բο�USB���ڶ���USB Device Class�Ķ���*/
    0x00,                       /*bDeviceProtocol Э����룬��USB-IF���䣬���bDeviceClass��bDeviceSubClass����Ϊ0x00����ô���ֶ�Ҳ����Ϊ0x00��*/
    0x40,                       /*bMaxPacketSize40�˵�0������ݰ����ȣ�����Ϊ8��16��32��64*/
    0x34,                       /*idVendor (0x0483)*///Ϊ�˷ɳ��Ҹ�Ϊ0x1234
    0x12,                       //����ID����USB-IF���䣬��Ҫ��USB-IF��֯����
    0x21,                       /*idProduct = 0x5710Ϊ�˷ɳ���Ϊ0x4321
    0x49,                       ��ƷID���ɳ���ָ��*/
    0x00,                       
    0x02,                       /*bcdDevice rel. 2.00�豸���кţ��ɳ�����������*/
    1,                          /*Index of string descriptor describing
                                                  manufacturer  �����������̵��ַ�������������*/
    2,                          /*Index of string descriptor describing
                                                 product����������Ʒ���ַ�������������*/
    3,                          /*Index of string descriptor describing the
                                                 device serial number����������Ʒ���кŵ��ַ���������������ע�⣬���е��ַ����������ǿ�ѡ�ģ����û���ַ�����������ָ����Щ����Ϊ0x00�� */
    0x01                        /*bNumConfigurations ��������������*/
  }
  ; /* Joystick_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const u8 Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuation Descriptor size�������������ȣ���������������Ϊ9�ֽڴ�С *///����������
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration ���������ͣ���������������Ϊ0x02*/
    JOYSTICK_SIZ_CONFIG_DESC,/* wTotalLength: Bytes returned ������������Ϣ�ܵĴ�С�������ӿ����������˵��������ȵȡ�*/
    0x00,
    0x01,         /*bNumInterfaces: 1 interface USB�ӿ�����*/
    0x01,         /*bConfigurationValue: Configuration value��ʹ��SetConfiguration��GetConfiguration����ʱ��ָ������������ֵ*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                     the configuration�������õ��ַ�������������*/
    0x80,         /*bmAttributes: bus powered �������ã�λ��ϸ�������£�

                          D7              ������������1

                          D6              �Թ���ģʽ

                          D5              Զ�̻���

                          D4��D0      ����
                         */ //��߱��Ĺ�
    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus  ��󹦺ģ���2mAΪ��λ������0x32Ϊ50*2=100mA��*/

    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size���������ȣ��ӿ�����������Ϊ9���ֽڡ�*///�ӿ�������
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type���������ͣ��ӿ�������������Ϊ0x04*/
    0x00,         /*bInterfaceNumber: Number of Interface�ýӿڱ�ţ��ӿڱ�Ŵ�0��ʼ���䣬��һ�������ж���ӿ�ʱ�����ø��ֶ������ֲ�ͬ�Ľӿڡ�*/
    0x00,         /*bAlternateSetting: Alternate setting*/
    0x02,         /*bNumEndpoints�˵��������������˵�0*/	//Ϊ�˷ɳ�����������һ��
    0x03,         /*bInterfaceClass:0x03Ϊhid�豸 �̶�HID*/
    0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no bootϵͳ����ǰʹ��*/
    0x01,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse�����̻�������������*/
    0,            /*iInterface: Index of string descriptor�����ýӿڵ��ַ���������������*/
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,         /*bLength: HID Descriptor size*/ //HID��������
    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID���������ͣ��˵�����������Ϊ0x05��*/
    0x00,         /*bcdHID: HID Class Spec release number*/
    0x01,         //�˵��ַ����ϸ�������� D7 �˵㷽�� 0 OUT�˵�1 IN D6��D4       ���� D3��D0       �˵���
    0x00,         /*bCountryCode: Hardware target country*/
    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
    0x22,         /*bDescriptorType*/
    JOYSTICK_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
    0x00,
    /******************** Descriptor of Joystick Mouse endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size*///�˵�������
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x81,          /*bEndpointAddress: Endpoint Address (IN)*/
    0x03,          /*bmAttributes: Interrupt endpoint*/
    0x08,          /*wMaxPacketSize: 4 Byte max *///Ϊ�˷ɳ��������ӵ�8
    0x00,
    0x20,          /*bInterval: Polling Interval (32 ms)*/
    /* 34 */
		//������Ϊ�˷ɳ������ӵ�һ���˵㡣
	0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x01,          /*bEndpointAddress: Endpoint Address (OUT)*/
    0x03,          /*bmAttributes: Interrupt endpoint*/
    0x08,          /*wMaxPacketSize: 8 Byte max */
    0x00,
    0x20,          /*bInterval: Polling Interval (32 ms)*/
  }; /* MOUSE_ConfigDescriptor */

const u8 Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] =
{
 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
 0x09, 0x06, // USAGE (Keyboard)
 0xa1, 0x01, // COLLECTION (Application)
 0x05, 0x07, //     USAGE_PAGE (Keyboard/Keypad)
 0x19, 0xe0, //     USAGE_MINIMUM (Keyboard LeftControl)
 0x29, 0xe7, //     USAGE_MAXIMUM (Keyboard Right GUI)
 0x15, 0x00, //     LOGICAL_MINIMUM (0)
 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
 0x95, 0x08, //     REPORT_COUNT (8)
 0x75, 0x01, //     REPORT_SIZE (1)
 0x81, 0x02, //     INPUT (Data,Var,Abs)
 0x95, 0x01, //     REPORT_COUNT (1)
 0x75, 0x08, //     REPORT_SIZE (8)
 0x81, 0x03, //     INPUT (Cnst,Var,Abs)
 0x95, 0x06, //   REPORT_COUNT (6)
 0x75, 0x08, //   REPORT_SIZE (8)
 0x25, 0xFF, //   LOGICAL_MAXIMUM (255)
 0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
 0x29, 0x65, //   USAGE_MAXIMUM (Keyboard Application)
 0x81, 0x00, //     INPUT (Data,Ary,Abs)
 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
 0x95, 0x02, //   REPORT_COUNT (2)
 0x75, 0x01, //   REPORT_SIZE (1)
 0x05, 0x08, //   USAGE_PAGE (LEDs)
 0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
 0x29, 0x02, //   USAGE_MAXIMUM (Caps Lock)
 0x91, 0x02, //   OUTPUT (Data,Var,Abs)
 0x95, 0x01, //   REPORT_COUNT (1)
 0x75, 0x06, //   REPORT_SIZE (6)
 0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)
 0xc0        // END_COLLECTION
}; /* Joystick_ReportDescriptor */


/* USB String Descriptors (optional) */
const u8 Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
  {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const u8 Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
  {
    JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
   0x81,0x67, 
   0xc1,0x54,  
   0xde,0x98,   		
   0x66,0x8f,		
  };

//ʹ��UNICODE����
const u8 Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
  {
    JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
	0x81,0x67, 
    0xc1,0x54,  
    0xde,0x98,   	
    0x66,0x8f,
  };

u8 Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
  {
    JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
		'T',0,'R',0,'T',0,'O',0,'S',0,' ',0,'H',0,'I',0,'D',0,
	  0x1a,0x90,  
    0xe1,0x4f,   
    0x9e,0x5b, 	
    0x8c,0x9a,
  };

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

