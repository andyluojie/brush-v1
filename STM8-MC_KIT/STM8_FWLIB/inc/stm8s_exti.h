/**
  ******************************************************************************
  * @file stm8s_exti.h
  * @brief This file contains all functions prototype and macros for the EXTI peripheral.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.0.1
  * @date 09/22/2008
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2008 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_EXTI_H__
#define __STM8S_EXTI_H__

/* Includes ------------------------------------------------------------------*/
#include "stm8s_map.h"

/* Exported types ------------------------------------------------------------*/

/** @addtogroup EXTI_Exported_Types
  * @{
  */

/**
  * @brief EXTI Sensitivity values for PORTA to PORTE
  */
typedef enum {
  EXTI_SENSITIVITY_FALL_LOW  = (u8)0x00, /*!< Interrupt on Falling edge and Low level */
  EXTI_SENSITIVITY_RISE_ONLY = (u8)0x01, /*!< Interrupt on Rising edge only */
  EXTI_SENSITIVITY_FALL_ONLY = (u8)0x02, /*!< Interrupt on Falling edge only */
  EXTI_SENSITIVITY_RISE_FALL = (u8)0x03  /*!< Interrupt on Rising and Falling edges */
} EXTI_Sensitivity_TypeDef;

/**
  * @brief EXTI Sensitivity values for TLI
  */
typedef enum {
  EXTI_TLISENSITIVITY_FALL_ONLY = (u8)0x00, /*!< Top Level Interrupt on Falling edge only */
  EXTI_TLISENSITIVITY_RISE_ONLY = (u8)0x04  /*!< Top Level Interrupt on Rising edge only */
} EXTI_TLISensitivity_TypeDef;

/**
  * @brief EXTI PortNum possible values
  */
typedef enum {
  EXTI_PORT_GPIOA = (u8)0x00, /*!< GPIO Port A */
  EXTI_PORT_GPIOB = (u8)0x01, /*!< GPIO Port B */
  EXTI_PORT_GPIOC = (u8)0x02, /*!< GPIO Port C */
  EXTI_PORT_GPIOD = (u8)0x03, /*!< GPIO Port D */
  EXTI_PORT_GPIOE = (u8)0x04  /*!< GPIO Port E */
} EXTI_Port_TypeDef;

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @addtogroup EXTI_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for PORTA to PORTE.
  */
#define IS_EXTI_SENSITIVITY_OK(SensitivityValue) \
  (((SensitivityValue) == EXTI_SENSITIVITY_FALL_LOW) || \
   ((SensitivityValue) == EXTI_SENSITIVITY_RISE_ONLY) || \
   ((SensitivityValue) == EXTI_SENSITIVITY_FALL_ONLY) || \
   ((SensitivityValue) == EXTI_SENSITIVITY_RISE_FALL))

/**
  * @brief Macro used by the assert function in order to check the different sensitivity values for TLI.
  */
#define IS_EXTI_TLISENSITIVITY_OK(SensitivityValue) \
  (((SensitivityValue) == EXTI_TLISENSITIVITY_FALL_ONLY) || \
   ((SensitivityValue) == EXTI_TLISENSITIVITY_RISE_ONLY))

/**
  * @brief Macro used by the assert function in order to check the different Port values
  */
#define IS_EXTI_PORT_OK(PORT) \
  (((PORT) == EXTI_PORT_GPIOA) ||\
   ((PORT) == EXTI_PORT_GPIOB) ||\
   ((PORT) == EXTI_PORT_GPIOC) ||\
   ((PORT) == EXTI_PORT_GPIOD) ||\
   ((PORT) == EXTI_PORT_GPIOE))

/**
  * @brief Macro used by the assert function in order to check the different values of the EXTI PinMask
  */
#define IS_EXTI_PINMASK_OK(PinMask) ((((PinMask) & (u8)0x00) == (u8)0x00) && ((PinMask) != (u8)0x00))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup EXTI_Exported_Functions
  * @{
  */

void EXTI_DeInit(void);
void EXTI_SetExtIntSensitivity(EXTI_Port_TypeDef Port, EXTI_Sensitivity_TypeDef SensitivityValue);
void EXTI_SetTLISensitivity(EXTI_TLISensitivity_TypeDef SensitivityValue);
EXTI_Sensitivity_TypeDef EXTI_GetExtIntSensitivity(EXTI_Port_TypeDef Port);
EXTI_TLISensitivity_TypeDef EXTI_GetTLISensitivity(void);

/**
  * @}
  */

#endif /* __STM8S_EXTI_H__ */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
