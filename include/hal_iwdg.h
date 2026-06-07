/***********************************************************************************************************************
    @file     hal_iwdg.h
    @author   VV TEAM
    @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE IWDG FIRMWARE LIBRARY.
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
#ifndef __HAL_IWDG_H
#define __HAL_IWDG_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG
  * @{
  */

/** @defgroup IWDG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/**
  * @brief  Write access to IWDG_PR and IWDG_RLR registers
  */
#define IWDG_WriteAccess_Enable         0x5555 /* Enable write */
#define IWDG_WriteAccess_Disable        0x0000 /* Disable write */

/**
  * @brief  IWDG prescaler
  */
#define IWDG_Prescaler_4                (0x00U << IWDG_PR_PR_Pos)
#define IWDG_Prescaler_8                (0x01U << IWDG_PR_PR_Pos)
#define IWDG_Prescaler_16               (0x02U << IWDG_PR_PR_Pos)
#define IWDG_Prescaler_32               (0x03U << IWDG_PR_PR_Pos)
#define IWDG_Prescaler_64               (0x04U << IWDG_PR_PR_Pos)
#define IWDG_Prescaler_128              (0x05U << IWDG_PR_PR_Pos)
#define IWDG_Prescaler_256              (0x06U << IWDG_PR_PR_Pos)

/**
  * @brief  IWDG flag
  */
#define IWDG_FLAG_PVU                   (0x01U << IWDG_SR_PVU_Pos) /* IWDG prescaler value update flag */
#define IWDG_FLAG_RVU                   (0x01U << IWDG_SR_RVU_Pos) /* IWDG counter reload value update flag */
#define IWDG_FLAG_IVU                   (0x01U << IWDG_SR_IVU_Pos) /* IWDG Interrupt Generate value update flag */

/**
  * @brief  IWDG Key Reload
  */
#define KR_KEY_Reload                   0xAAAA                     /* Reload value */
#define KR_KEY_Enable                   0xCCCC                     /* Start IWDG */

/**
  * @brief  IWDG Overflow Configration
  */
#define IWDG_Overflow_Reset             (0x00U << IWDG_CR_IRQ_SEL_Pos)
#define IWDG_Overflow_Interrupt         (0x01U << IWDG_CR_IRQ_SEL_Pos)
/**
  * @}
  */

/** @defgroup IWDG_Exported_Functions
  * @{
  */
void IWDG_WriteAccessCmd(uint16_t write_access);
FlagStatus IWDG_GetFlagStatus(uint32_t flag);
void PVU_CheckStatus(void);
void RVU_CheckStatus(void);
void IVU_CheckStatus(void);
void IWDG_SetPrescaler(uint32_t prescaler);
void IWDG_SetReload(uint16_t reload);
uint32_t IWDG_GetReload(void);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
void IWDG_OverflowConfig(uint32_t overflow_action);
void IWDG_ClearITPendingBit(void);

void IWDG_SetIGen(uint16_t GenValue);
uint16_t IWDG_GetCnt(void);

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

