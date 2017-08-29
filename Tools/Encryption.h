/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _ENCRYPTION_H_
#define _ENCRYPTION_H_
#include <Include.h>


//********************************************************
//声明unsigned long char 数据类型的数据
typedef union
{
   unsigned char  UcType[4];
   unsigned int   UiType[2];
   unsigned long  UlType;
}UILONG; 


//********************************************************
//宏定义
#define     M_DEFAULT_YW       6      //默认移位为6位
#define PASSWORD_GLOBALS


extern uint8  PasswordSum[8];            //密码存放
extern uint8  PasswordTemp[8];           //密码暂存

//********************************************************
//
extern void EncryptP(uint8  *ptr);  //对64位数据加密
extern void DecryptP(uint8  *ptr);  //对64位数据解密 uint8  PasswordSum[8];            //密码存放
extern uint8  PasswordTemp[8];           //密码暂存

//********************************************************
//
extern void EncryptP(uint8  *ptr);  //对64位数据加密
extern void DecryptP(uint8  *ptr);  //对64位数据解密

#endif

