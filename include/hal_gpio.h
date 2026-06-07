/***********************************************************************************************************************
    @file     hal_gpio.h
    @author   VV TEAM
    @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE GPIO FIRMWARE LIBRARY.
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
#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types
  * @{
  */

/**
  * @brief  Output Maximum frequency selection
  */
typedef enum
{
    GPIO_Speed_Low                    = 1, /*!< Maximum speed is low */
    GPIO_Speed_Middle                 = 2, /*!< Maximum speed is middle */
    GPIO_Speed_High                   = 3  /*!< Maximum speed is high */
} GPIOSpeed_TypeDef;

/**
  * @brief  Configuration Mode enumeration
  */
typedef enum
{
    GPIO_Mode_AIN       = 0x00,        /*!< Analog input */
    GPIO_Mode_FLOATING  = 0x04,        /*!< Floating input */
    GPIO_Mode_IPD       = 0x28,        /*!< Pull down input */
    GPIO_Mode_IPU       = 0x48,        /*!< Pull up input */
    GPIO_Mode_Out_OD    = 0x14,        /*!< Universal open drain output */
    GPIO_Mode_Out_PP    = 0x10,        /*!< Universal push-pull output */
    GPIO_Mode_AF_OD     = 0x1C,        /*!< Multiplex open drain output */
    GPIO_Mode_AF_PP     = 0x18         /*!< Multiplexed push-pull output */
} GPIOMode_TypeDef;

/**
  * @brief  Bit_SET and Bit_RESET enumeration
  */
typedef enum
{
    Bit_RESET = 0,                     /*!< bit reset */
    Bit_SET                            /*!< bit set */
} BitAction;

/**
  * @brief  GPIO Init structure definition
  */
typedef struct
{
    uint16_t               GPIO_Pin;   /*!< GPIO_Pin */
    GPIOSpeed_TypeDef      GPIO_Speed; /*!< GPIO_Speed */
    GPIOMode_TypeDef       GPIO_Mode;  /*!< GPIO_Mode */
} GPIO_InitTypeDef;
/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */
#define GPIO_Pin_0                  (0x0001U) /*!< Pin 0 selected */
#define GPIO_Pin_1                  (0x0002U) /*!< Pin 1 selected */
#define GPIO_Pin_2                  (0x0004U) /*!< Pin 2 selected */
#define GPIO_Pin_3                  (0x0008U) /*!< Pin 3 selected */
#define GPIO_Pin_4                  (0x0010U) /*!< Pin 4 selected */
#define GPIO_Pin_5                  (0x0020U) /*!< Pin 5 selected */
#define GPIO_Pin_6                  (0x0040U) /*!< Pin 6 selected */
#define GPIO_Pin_7                  (0x0080U) /*!< Pin 7 selected */
#define GPIO_Pin_8                  (0x0100U) /*!< Pin 8 selected */
#define GPIO_Pin_9                  (0x0200U) /*!< Pin 9 selected */
#define GPIO_Pin_10                 (0x0400U) /*!< Pin 10 selected */
#define GPIO_Pin_11                 (0x0800U) /*!< Pin 11 selected */
#define GPIO_Pin_12                 (0x1000U) /*!< Pin 12 selected */
#define GPIO_Pin_13                 (0x2000U) /*!< Pin 13 selected */
#define GPIO_Pin_14                 (0x4000U) /*!< Pin 14 selected */
#define GPIO_Pin_15                 (0x8000U) /*!< Pin 15 selected */
#define GPIO_Pin_All                (0xFFFFU) /*!< All pins selected */

#define GPIO_AF_0                   (0x00U)   /*!< Alternative function 0 */
#define GPIO_AF_1                   (0x01U)   /*!< Alternative function 1 */
#define GPIO_AF_2                   (0x02U)   /*!< Alternative function 2 */
#define GPIO_AF_3                   (0x03U)   /*!< Alternative function 3 */
#define GPIO_AF_4                   (0x04U)   /*!< Alternative function 4 */
#define GPIO_AF_5                   (0x05U)   /*!< Alternative function 5 */
#define GPIO_AF_6                   (0x06U)   /*!< Alternative function 6 */
#define GPIO_AF_7                   (0x07U)   /*!< Alternative function 7 */

#define GPIO_PinSource0             (0x00U)
#define GPIO_PinSource1             (0x01U)
#define GPIO_PinSource2             (0x02U)
#define GPIO_PinSource3             (0x03U)
#define GPIO_PinSource4             (0x04U)
#define GPIO_PinSource5             (0x05U)
#define GPIO_PinSource6             (0x06U)
#define GPIO_PinSource7             (0x07U)
#define GPIO_PinSource8             (0x08U)
#define GPIO_PinSource9             (0x09U)
#define GPIO_PinSource10            (0x0AU)
#define GPIO_PinSource11            (0x0BU)
#define GPIO_PinSource12            (0x0CU)
#define GPIO_PinSource13            (0x0DU)
#define GPIO_PinSource14            (0x0EU)
#define GPIO_PinSource15            (0x0FU)
/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions
  * @{
  */
void GPIO_DeInit(GPIO_TypeDef *gpio);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef *gpio, GPIO_InitTypeDef *init_struct);
void GPIO_StructInit(GPIO_InitTypeDef *init_struct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *gpio, uint16_t pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef *gpio);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *gpio, uint16_t pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *gpio);
void GPIO_SetBits(GPIO_TypeDef *gpio, uint16_t pin);
void GPIO_ResetBits(GPIO_TypeDef *gpio, uint16_t pin);
void GPIO_WriteBit(GPIO_TypeDef *gpio, uint16_t pin, BitAction value);
void GPIO_Write(GPIO_TypeDef *gpio, uint16_t value);
void GPIO_PinLockConfig(GPIO_TypeDef *gpio, uint16_t pin, uint16_t lock);
void GPIO_PinAFConfig(GPIO_TypeDef *gpio, uint8_t pin, uint8_t alternate_function);

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

