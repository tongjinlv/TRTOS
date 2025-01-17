/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
/**********************************************************************
* $Id$		lpc177x_8x_systick.h			2011-06-02
*//**
* @file		lpc177x_8x_systick.h
* @brief	Contains all macro definitions and function prototypes
*			support for SYSTICK firmware library on LPC177x_8x
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup SYSTICK	SysTick (System tick timer)
 * @ingroup LPC177x_8xCMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC177X_8X_SYSTICK_H_
#define __LPC177X_8X_SYSTICK_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC177x_8x.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* Private Macros ------------------------------------------------------------- */
/** @defgroup SYSTICK_Private_Macros SysTick Private Macros
 * @{
 */
/*********************************************************************//**
 * Macro defines for System Timer Control and status (STCTRL) register
 **********************************************************************/
#define ST_CTRL_ENABLE		((uint32_t)(1<<0))
#define ST_CTRL_TICKINT		((uint32_t)(1<<1))
#define ST_CTRL_CLKSOURCE	((uint32_t)(1<<2))
#define ST_CTRL_COUNTFLAG	((uint32_t)(1<<16))

/*********************************************************************//**
 * Macro defines for System Timer Reload value (STRELOAD) register
 **********************************************************************/
#define ST_RELOAD_RELOAD(n)		((uint32_t)(n & 0x00FFFFFF))

/*********************************************************************//**
 * Macro defines for System Timer Current value (STCURRENT) register
 **********************************************************************/
#define ST_RELOAD_CURRENT(n)	((uint32_t)(n & 0x00FFFFFF))

/*********************************************************************//**
 * Macro defines for System Timer Calibration value (STCALIB) register
 **********************************************************************/
#define ST_CALIB_TENMS(n)		((uint32_t)(n & 0x00FFFFFF))
#define ST_CALIB_SKEW			((uint32_t)(1<<30))
#define ST_CALIB_NOREF			((uint32_t)(1<<31))

#define CLKSOURCE_EXT			((uint32_t)(0))
#define CLKSOURCE_CPU			((uint32_t)(1))

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup SYSTICK_Public_Functions Systick Public Functions
 * @{
 */

void SYSTICK_InternalInit(uint32_t time);
void SYSTICK_ExternalInit(uint32_t freq, uint32_t time);

void SYSTICK_Cmd(FunctionalState NewState);
void SYSTICK_IntCmd(FunctionalState NewState);
uint32_t SYSTICK_GetCurrentValue(void);
void SYSTICK_ClearCounterFlag(void);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif


#endif /* __LPC177X_8X_SYSTICK_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
