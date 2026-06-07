/***********************************************************************************************************************
    @file     hal_syscfg.h
    @author   VV TEAM
    @brief    THIS FILE PROVIDES ALL THE FLASH FIRMWARE FUNCTIONS.
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

/*!< Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SYSCFG_H
#define __HAL_SYSCFG_H

/*!< Files includes ------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSCFG
  * @{
  */

/** @defgroup SYSCFG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Constants
  * @{
  */

/**
  * @brief SYSCFG_EXTI_Port_Sources
  */
#define EXTI_PortSourceGPIOA                    ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB                    ((uint8_t)0x01)

/**
  * @brief SYSCFG_EXTI_Pin_sources
  */
#define EXTI_PinSource0                         ((uint8_t)0x00)
#define EXTI_PinSource1                         ((uint8_t)0x01)
#define EXTI_PinSource2                         ((uint8_t)0x02)
#define EXTI_PinSource3                         ((uint8_t)0x03)
#define EXTI_PinSource4                         ((uint8_t)0x04)
#define EXTI_PinSource5                         ((uint8_t)0x05)
#define EXTI_PinSource6                         ((uint8_t)0x06)
#define EXTI_PinSource7                         ((uint8_t)0x07)
#define EXTI_PinSource8                         ((uint8_t)0x08)
#define EXTI_PinSource9                         ((uint8_t)0x09)
#define EXTI_PinSource10                        ((uint8_t)0x0A)
#define EXTI_PinSource11                        ((uint8_t)0x0B)
#define EXTI_PinSource12                        ((uint8_t)0x0C)
#define EXTI_PinSource13                        ((uint8_t)0x0D)
#define EXTI_PinSource14                        ((uint8_t)0x0E)
#define EXTI_PinSource15                        ((uint8_t)0x0F)

/**
  * @brief SYSCFG_Memory_Remap_Config
  */
#define SYSCFG_MemoryRemap_Flash                ((uint8_t)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((uint8_t)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((uint8_t)0x03)

#define SYSCFG_I2CPort_OD                       (0x00U << SYSCFG_PADHYS_I2C1_MODE_SEL_Pos) /*!< open-drain */
#define SYSCFG_I2CPort_PP                       (0x01U << SYSCFG_PADHYS_I2C1_MODE_SEL_Pos) /*!< Push-pull  */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Functions
  * @{
  */

void SYSCFG_DeInit(void);
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap);
void SYSCFG_I2CPortModeConfig(uint32_t port_mode);
void SYSCFG_EXTILineConfig(uint8_t port_source_gpio, uint8_t pin_source);

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

