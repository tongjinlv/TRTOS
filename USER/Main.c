/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
#include <Include.h>

//ʵ�þͺã����ܷǲ��Ǳ�
#if	  defined(BOARD_LCD4_3)//ˮλ��4.3�紥����
  #include <..\USER\Prj_4.3LCD\4.3LCD_Main.c>
#elif  defined(BOARD_CORE1_0)//���İ�
  #include <..\USER\Prj_CanBus\CanBus_main.c>
#elif defined(SENSOR_TYPE_ANGLE)//�Ƕȴ�����
	#include <..\USER\Prj_Sensor\Sensor_main.c>
#elif defined(SENSOR_TYPE_COMPASS)//��������
	#include <..\USER\Prj_Sensor\Sensor_main.c>
#elif defined(SENSOR_TYPE_0_20MV_TO_CAN)//0~20mvתCAN����
	#include <..\USER\Prj_Sensor\Sensor_main.c>
#elif defined(SENSOR_TYPE_CXHEFT)//��������can������
	#include <..\USER\Prj_CXHeftSensor\CXHeftSensor_main.c>
#elif defined(SENSOR_TYPE_SCHEFT)//ʢ��������can������
	#include <..\USER\Prj_SCATHeftSensor\SCATHeft_main.c>
#elif defined(SENSOR_TYPE_CXRANGE)//���Ƿ���can���ߴ�����
	#include <..\USER\Prj_CXRangeSensor\CXRangeSe nsor_main.c>
#elif defined(BOARD_TANK_Hand)//���ɹ��Ϲܳ�ң�ز���
	#include <..\USER\Prj_TankHand\TankHand_main.c>
#elif defined(BOARD_NJSIGDOT)//�Ͼ��������ݲɼ�
	#include <..\USER\Prj_NJSigDot\NjSigDot_main.c>
#elif defined(BOARD_TS_Collect)//��ɽ�޳����ݲɼ� 
	#include <..\USER\Prj_TSCollect\TSCollect_main.c>
#elif defined(BOARD_TANK_Ctr)//���ɹ��Ϲܳ�����ϵͳ�����Ʋ���
	#include <..\USER\Prj_TankCtr\TankCtr_main.c>
#elif defined(BOARD_TANK_Ctr1)//���ɹ��Ϲܳ�����ϵͳ�޿��Ʋ���
	#include <..\USER\Prj_TankCtr\TankCtr1_main.c>
#elif defined(BOARD_CENCTR)//���壨����İ�)
	#include <..\USER\Prj_CenCtr\CenCtr_main.c>
#elif defined(BOARD_REALLY)//����������
	#include <..\USER\Prj_Really\Really_main.c>
#elif defined(BOARD_PRAFIRE)//���Ե�Ұ�𿪷���
  #include <..\USER\Prj_Prafire\Prafire_main.c>
	//#include <..\USER\Prj_Prafire\Geek-CC.c>
#elif defined(BOARD_PDATRAN)//PDAת�Ӱ�
	#include <..\USER\Prj_PdaTran\Pdatran_main.c>
#elif defined(BOARD_TWOCAN)//˫CAN����
	#include <..\USER\Prj_TwoCan\TwoCan_main.c> 
#elif defined(BOARD_LCD7SJJ)//����������
	#include <..\USER\Prj_7LCDSJJ\7LCDSJJ_main.c> 
#elif defined(TOS_BOOTLOADER)//��������
	#include <..\USER\Prj_Boot\BootLoader_main.c>
#elif defined(BOARD_WJ4_3)//�ڻ�4.3��
	#include <..\USER\Prj_WJ4_3\WJ4_3_main.c>
#elif defined(BOARD_CAMERACTR)//�๤����ͷ����
	#include <..\USER\Prj_CAMERACTR\CAMERACTR_main.c>
#elif defined(BOARD_CAMERAMOTR)//����ͷ����
	#include <..\USER\Prj_CAMERAMotr\CAMERAMotr_main.c>
#elif defined(BOARD_RS485ANGLE)//�๤�Ƕ�485
	#include <..\USER\Prj_RS485ANGLE\RS485ANGLE_main.c>
#elif defined(BOARD_BLACKBOX)//��ϻ��
	#include <..\USER\Prj_BlackBox\BlackBox_main.c>
#elif defined(BOARD_CAMERAMRC)//����ͷ����ң��
	#include <..\USER\Prj_CameraMRC\CameraMRC_main.c>
#elif defined(BOARD_REMOTECONTROL)//���߲���ң�ض�
#include <..\USER\Prj_RemoteControl\RemoteControl_main.c>
#elif defined(BOARD_TELECONTROL)//���߲������ƶ�
#include <..\USER\Prj_TeleControl\TeleControl_main.c>
#elif defined(BOARD_TANK_CtrNew)//���壨����İ�)
	#include <..\USER\Prj_TankCtrNew\TankCtr_main.c>
#elif defined(BOARD_SKYBUS)//���壨����İ�)
#include <..\USER\Prj_TankCtrNew\SkyBus_main.c>
#elif defined(BOARD_TP500)//������Զ����ʪ��
#include <..\USER\Prj_TP500\TP500_main.c>
#elif defined(BOARD_TP500_New)//������Զ����ʪ��
#include <..\USER\Prj_TP500New\TP500_main.c>
#elif defined(BOARD_TP502T)//����TP502
#include <..\USER\Prj_TP502T\TP500_main.c>
#elif defined(IAP_Addr0x5000)
#include <..\USER\Prj_IAP_Addr0x5000\IAP_main.c>
#elif defined(BOARD_GEEK_Bast)//��ɫС��
#include <..\USER\Prj_Geek_Bast\Geek_main.c>
#elif defined(BOARD_BastJson)//����jsonЭ��
#include <..\USER\Prj_BastJson\Json_main.c>
#elif defined(BOARD_HAOYU)
#include <..\USER\Prj_Haoyu\Haoyu_main.c>
#elif defined(BOARD_Lora)
#include <..\USER\Prj_Lora\Lora_main.c>
#elif defined(BOARD_Insect)
#include <..\USER\Prj_Insect\Insect_main.c>
#elif defined(BOARD_InsectV2)
#include <..\USER\Prj_InsectV2\Insect_main.c>
#elif defined(BOARD_TP401)
#include <..\USER\Prj_TP401\TP401_main.c>
#elif defined(BOARD_MiniDTU)
#include <..\USER\Prj_MiniDTU\MiniDTU_main.c>
#elif defined(BOARD_USBLora)
#include <..\USER\Prj_USBLora\Lora_main.c>
#elif defined(BOARD_AirCleaner)
#include <..\USER\Prj_AirCleaner\AirCleaner_main.c>
#else  
	#error "Missing define: Check Your Project Main.c!"
#endif

int tos_main()
{
	main();//goto main file
	return Tos_TaskTotal;	//goto config ini file
}
