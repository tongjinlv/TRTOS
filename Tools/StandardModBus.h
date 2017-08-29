/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _STANDARDMODBUS_H_
#define _STANDARDMODBUS_H_
#include <Include.h>
#include <Tools_Include.h>
/*
127~~~~~~~110~~~~~~~~~100~~~~~~~~72~~~~~~~~~65~~~~~~~~~~1
  公共功能码   用户码      公共码    用户码				公共码
*/

typedef enum
{
	MBCC_ReadBits=0x01,//读输入离散值
	MBCC_ReadDisValue=0x02,//读输入离散值
	MBCC_ReadHoldReg=0x03,//读取保持寄存器值
	MBCC_ReadInPutReg=0x04,//读输入寄存器
	MBCC_WriteBit=0x05,//写单个线圈 0XFF00=1  0X0000=0
	MBCC_WriteByte=0x06,//写单个寄存器
	MBCC_WriteBytes=0x10,//写多个寄存器
	MBCC_WRBytes=0x17,//读写多个寄存器
	MBCC_WriteShield=0x16,//屏蔽写寄存器
	MBCC_ReadFileRcord=0x14,//读文件记录
	MBCC_WriteFileRcord=0x15,//写文件记录
	MBCC_ReadDevIDInfor=0x2B,//读设备识别码
}ModBusCmdCode;

typedef enum
{
	MBEC_NotError=0x00,
	MBEC_CmdCodeError=0x01,
	MBEC_DataLenthError=0x02,
	MBEC_CrcCheckError =0x03,
	MBEC_RegRangeError=0x04,
}ModBusErrorCode;


typedef enum
{
	MBWM_BroadCastEN=S0,//允许广播
	
}ModBusWorkMode;

typedef struct
{
	uint8 LoclAddr;//本地地址
	uint8 WorkMode;//工作模式
	uint8 *RxBuf;
	uint16 RxBuf_Length;
	uint8 *TxBuf;
	uint16 TxBuf_Length;
	void *RunValue;//缓存区地址
	uint16 RunValue_Length;
	void *CfgValue;//缓存区地址
	uint16 CfgValue_Length;
	
}ModBus_Base;

typedef struct
{
	ModBus_Base *BaseInfor;//协议配置信息
	uint8 CmdCode;//命令码
	
}ModBus_Infor;

#define MB_BroadCast 0xff





uint16 MB_AppendCrc(uint8 *Buf,uint16 Length);
BOOL MB_CheckCrc(uint8 *Buf,uint16 Length);



#endif
