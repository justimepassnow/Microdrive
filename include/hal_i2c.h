/***********************************************************************************************************************
    @file     hal_i2c.h
    @author   VV TEAM
    @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE I2C FIRMWARE LIBRARY.
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
#ifndef __HAL_I2C_H
#define __HAL_I2C_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C
  * @{
  */

/** @defgroup I2C_Exported_Types
  * @{
  */

/**
  * @brief  I2C Init structure definition
  */
typedef struct
{
    uint16_t I2C_Mode;                 /*!< Specifies the I2C mode. This parameter can be a value of I2C_mode. */
    uint16_t I2C_OwnAddress;           /*!< Specifies the first device own address. This parameter can be a 7-bit or 10-bit address. */
    uint32_t I2C_ClockSpeed;           /*!< Specifies the clock speed. */
} I2C_InitTypeDef;
/**
  * @}
  */

/** @defgroup I2C_Exported_Constants
  * @{
  */

/**
  * @brief I2C mode definition
  */
#define I2C_Own_Address                          0x55

#define I2C_Speed_Standard                       (0x01U << I2C_CR_SPEED_Pos)  /*!< I2C standard speed */
#define I2C_Speed_Fast                           (0x02U << I2C_CR_SPEED_Pos)  /*!< I2C fast speed */

#define I2C_Mode_Master                          (0x01U << I2C_CR_MASTER_Pos) /*!< I2C master mode */
#define I2C_Mode_Slave                           (0x00U << I2C_CR_MASTER_Pos) /*!< I2C slave mode */

/**
  * @brief I2C_interrupts_definition
  */
#define I2C_IT_RX_UNDER                          ((uint16_t)0x0001)
#define I2C_IT_RX_OVER                           ((uint16_t)0x0002)
#define I2C_IT_RX_FULL                           ((uint16_t)0x0004)
#define I2C_IT_TX_OVER                           ((uint16_t)0x0008)
#define I2C_IT_TX_EMPTY                          ((uint16_t)0x0010)
#define I2C_IT_RD_REQ                            ((uint16_t)0x0020)
#define I2C_IT_TX_ABRT                           ((uint16_t)0x0040)
#define I2C_IT_RX_DONE                           ((uint16_t)0x0080)
#define I2C_IT_ACTIVITY                          ((uint16_t)0x0100)
#define I2C_IT_STOP_DET                          ((uint16_t)0x0200)
#define I2C_IT_START_DET                         ((uint16_t)0x0400)
#define I2C_IT_GEN_CALL                          ((uint16_t)0x0800)

/**
  * @brief I2C_flags_definition
  */
#define I2C_FLAG_RX_UNDER                        ((uint16_t)0x0001)
#define I2C_FLAG_RX_OVER                         ((uint16_t)0x0002)
#define I2C_FLAG_RX_FULL                         ((uint16_t)0x0004)
#define I2C_FLAG_TX_OVER                         ((uint16_t)0x0008)
#define I2C_FLAG_TX_EMPTY                        ((uint16_t)0x0010)
#define I2C_FLAG_RD_REQ                          ((uint16_t)0x0020)
#define I2C_FLAG_TX_ABRT                         ((uint16_t)0x0040)
#define I2C_FLAG_RX_DONE                         ((uint16_t)0x0080)
#define I2C_FLAG_ACTIVITY                        ((uint16_t)0x0100)
#define I2C_FLAG_STOP_DET                        ((uint16_t)0x0200)
#define I2C_FLAG_START_DET                       ((uint16_t)0x0400)
#define I2C_FLAG_GEN_CALL                        ((uint16_t)0x0800)

/**
  * @brief I2C_Statusflags_definition
  */
#define I2C_STATUS_FLAG_ACTIVITY                 ((uint16_t)0x8001)
#define I2C_STATUS_FLAG_TFNF                     ((uint16_t)0x8002)
#define I2C_STATUS_FLAG_TFE                      ((uint16_t)0x8004)
#define I2C_STATUS_FLAG_RFNE                     ((uint16_t)0x8008)
#define I2C_STATUS_FLAG_RFF                      ((uint16_t)0x8010)
#define I2C_STATUS_FLAG_M_ACTIV                  ((uint16_t)0x8020)
#define I2C_STATUS_FLAG_S_ACTIV                  ((uint16_t)0x8040)

/**
  * @brief  I2C_Events
  */
#define I2C_EVENT_RX_UNDER                       ((uint16_t)0x0001)
#define I2C_EVENT_RX_OVER                        ((uint16_t)0x0002)
#define I2C_EVENT_RX_FULL                        ((uint16_t)0x0004)
#define I2C_EVENT_TX_OVER                        ((uint16_t)0x0008)
#define I2C_EVENT_TX_EMPTY                       ((uint16_t)0x0010)
#define I2C_EVENT_RD_REQ                         ((uint16_t)0x0020)
#define I2C_EVENT_TX_ABRT                        ((uint16_t)0x0040)
#define I2C_EVENT_RX_DONE                        ((uint16_t)0x0080)
#define I2C_EVENT_ACTIVITY                       ((uint16_t)0x0100)
#define I2C_EVENT_STOP_DET                       ((uint16_t)0x0200)
#define I2C_EVENT_START_DET                      ((uint16_t)0x0400)
#define I2C_EVENT_GEN_CALL                       ((uint16_t)0x0800)

#define CMD_READ                                 ((uint16_t)0x0100)
#define CMD_WRITE                                ((uint16_t)0x0000)
/**
  * @}
  */

/** @defgroup I2C_Exported_Functions
  * @{
  */
void I2C_DeInit(I2C_TypeDef *i2c);
void I2C_Init(I2C_TypeDef *i2c, I2C_InitTypeDef *init_struct);
void I2C_StructInit(I2C_InitTypeDef *init_struct);
void I2C_Cmd(I2C_TypeDef *i2c, FunctionalState state);
void I2C_GenerateSTART(I2C_TypeDef *i2c, FunctionalState state);
void I2C_GenerateSTOP(I2C_TypeDef *i2c, FunctionalState state);
void I2C_TargetAddressConfig(I2C_TypeDef *i2c, uint8_t addr);
void I2C_GeneralCallCmd(I2C_TypeDef *i2c, FunctionalState state);
void I2C_ITConfig(I2C_TypeDef *i2c, uint16_t it, FunctionalState state);
void I2C_SendData(I2C_TypeDef *i2c, uint8_t dat);
void I2C_ReadCmd(I2C_TypeDef *i2c);
uint8_t I2C_ReceiveData(I2C_TypeDef *i2c);
uint32_t I2C_GetLastEvent(I2C_TypeDef *i2c);
ErrorStatus I2C_CheckEvent(I2C_TypeDef *i2c, uint32_t event);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef *i2c, uint32_t flag);
void I2C_ClearFlag(I2C_TypeDef *i2c, uint32_t flag);
ITStatus I2C_GetITStatus(I2C_TypeDef *i2c, uint32_t it);

void I2C_ClearITPendingBit(I2C_TypeDef *i2c, uint32_t it);
void I2C_SlaveAddressConfig(I2C_TypeDef *i2c, uint8_t addr);
void I2C_SlaveModeCmd(I2C_TypeDef *i2c, FunctionalState state);
void I2C_SlaveAddressMaskConfig(I2C_TypeDef *i2c, uint16_t  mask);
uint32_t I2C_GetSlaveReceivedAddr(I2C_TypeDef *i2c);

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

