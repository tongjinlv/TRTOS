/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
**************************************************************************************/

#ifndef _TTS_TOUCH_DRIVER_H_
#define _TTS_TOUCH_DRIVER_H_

#include <Include.h>

typedef struct 
{
	Func UpIng_Event;
	Func DownIng_Event;
	Func Up_Event;
	Func Down_Event;
	uint8 UpDelay_Count;
	uint8 DownDelay_Count;
}_Touch_Event;


#define TOUCH_UP          0
#define TOUCH_UPING       1
#define TOUCH_DOWN        2
#define TOUCH_DOWNING     3

#define TOUCH_CROSS_SIZE  5			//����У������С
#define TOUCH_CROSS_GAUGE 40    //У׼����߽����
#define TOUCH_FONT_SIZE  16

#define  TOUCH_ADC_CHN      2    
#define  TOUCH_ADC_BUFSize  10   
extern volatile uint16  TOUCH_ADC_Value[TOUCH_ADC_BUFSize][TOUCH_ADC_CHN]; 
extern uint16 TOUCH_ADC_XValue,TOUCH_ADC_YValue;
extern uint16 TOUCH_XValue,TOUCH_YValue;
extern uint8  Touch_Update;
extern uint8 Touch_Screen_UserTaskID;
extern uint8 DeviceId_TOUCH;
extern _Touch_Event Touch_Event;
void  ADC_Touch_Init(void);
void Task_GetTouch(void *Tags);
void DeviceMount_Touch(void);
void TouchScreen_Correct(void);
void Load_Touch_Configs(void);
void Save_Touch_Configs(void);
void Tos_TaskGetTouch(void);
#endif
