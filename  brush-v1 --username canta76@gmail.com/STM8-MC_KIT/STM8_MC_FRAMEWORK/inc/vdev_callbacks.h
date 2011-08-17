/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : vdev_callbacks.h
* Author             : IMS Systems Lab 
* Date First Issued  : mm/dd/yyy
* Description        : virtual callbacks header file
********************************************************************************
* History:
* mm/dd/yyyy ver. x.y.z
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/******************************************************************************/
#ifndef __VDEV_CALLBACKS_H__
#define __VDEV_CALLBACKS_H__

/******************************************************************************/
#include "dev_type.h"
#include "vdev.h"

/******************************************************************************/
#define VDEV_CALLBACK				/* Uncomment if define callbacks */
#define VDEV_CALLBACK_DIVBY0_IDX	0
#define VDEV_CALLBACK_NUMBER		1

/******************************************************************************/
errorcode fncallback_divby0(pvdev_regs_t pregs, pvdev_mems_t pmems);

#endif /* __VDEV_CALLBACKS_H__ */
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
