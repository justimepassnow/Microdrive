/***********************************************************************************************************************
    @file     hal_exti.h
    @author   VV TEAM
    @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE EXTI FIRMWARE LIBRARY.
  **********************************************************************************************************************
    @attention

    <h2><center>&copy; Copyright(c) <2023> <MindMotion></center></h2>

      Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
    following conditions are met:
    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
       the following disclaimer in the documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or
       promote products derived from this software without specific prior written permission.

      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *********************************************************************************************************************/

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef __HAL_EXTI_H
#define __HAL_EXTI_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI
  * @{
  */

/** @defgroup EXTI_Exported_Types
  * @{
  */

/**
  * @brief  EXTI mode enumeration
  */
typedef enum
{
    EXTI_Mode_Interrupt = 0x00,        /*!< EXTI interrupt mode */
    EXTI_Mode_Event     = 0x04         /*!< EXTI event mode */
} EXTIMode_TypeDef;

/**
  * @brief  EXTI Trigger enumeration
  */
typedef enum
{
    EXTI_Trigger_Rising  = 0x08,       /*!< EXTI rising edge triggering */
    EXTI_Trigger_Falling = 0x0C,       /*!< EXTI falling edge triggering */
    EXTI_Trigger_Rising_Falling = 0x10 /*!< EXTI rising and falling edge triggers */
} EXTITrigger_TypeDef;

/**
  * @brief  EXTI Init Structure definition
  */
typedef struct
{
    uint32_t            EXTI_Line;     /*!< Specifies the EXTI lines to be enabled or disabled. */
     /*!< This parameter can be any combination of @ref EXTI_Lines */
    EXTIMode_TypeDef    EXTI_Mode;     /*!< Specifies the mode for the EXTI lines. */

     /*!< This parameter can be a value of @ref EXTIMode_TypeDef */
    EXTITrigger_TypeDef EXTI_Trigger;  /*!< Specifies the trigger signal active edge for the EXTI lines. */
     /*!< This parameter can be a value of @ref EXTITrigger_TypeDef */
    FunctionalState     EXTI_LineCmd;  /*!< Specifies the new state of the selected EXTI lines. */
    /*!< This parameter can be set either to ENABLE or DISABLE */
} EXTI_InitTypeDef;
/**
  * @}
  */

/** @defgroup EXTI_Exported_Constants
  * @{
  */
#define EXTI_LineNone             ((uint32_t)0x0000000) /*!< No interrupt selected */
#define EXTI_Line0                ((uint32_t)0x0000001) /*!< External interrupt line 0 */
#define EXTI_Line1                ((uint32_t)0x0000002) /*!< External interrupt line 1 */
#define EXTI_Line2                ((uint32_t)0x0000004) /*!< External interrupt line 2 */
#define EXTI_Line3                ((uint32_t)0x0000008) /*!< External interrupt line 3 */
#define EXTI_Line4                ((uint32_t)0x0000010) /*!< External interrupt line 4 */
#define EXTI_Line5                ((uint32_t)0x0000020) /*!< External interrupt line 5 */
#define EXTI_Line6                ((uint32_t)0x0000040) /*!< External interrupt line 6 */
#define EXTI_Line7                ((uint32_t)0x0000080) /*!< External interrupt line 7 */
#define EXTI_Line8                ((uint32_t)0x0000100) /*!< External interrupt line 8 */
#define EXTI_Line9                ((uint32_t)0x0000200) /*!< External interrupt line 9 */
#define EXTI_Line10               ((uint32_t)0x0000400) /*!< External interrupt line 10 */
#define EXTI_Line11               ((uint32_t)0x0000800) /*!< External interrupt line 11 */
#define EXTI_Line12               ((uint32_t)0x0001000) /*!< External interrupt line 12 */
#define EXTI_Line13               ((uint32_t)0x0002000) /*!< External interrupt line 13 */
#define EXTI_Line14               ((uint32_t)0x0004000) /*!< External interrupt line 14 */
#define EXTI_Line15               ((uint32_t)0x0008000) /*!< External interrupt line 15 */
#define EXTI_Line16               ((uint32_t)0x0010000) /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_Line17               ((uint32_t)0x0020000) /*!< External interrupt line 17 Connected to the IWDG Output */
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions
  * @{
  */
FlagStatus EXTI_GetFlagStatus(uint32_t line);
ITStatus EXTI_GetITStatus(uint32_t line);

void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef *init_struct);
void EXTI_StructInit(EXTI_InitTypeDef *init_struct);
void EXTI_GenerateSWInterrupt(uint32_t line);
void EXTI_ClearFlag(uint32_t line);
void EXTI_ClearITPendingBit(uint32_t line);

#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

