/***********************************************************************************************************************
    @file     hal_usart.h
    @author   VV TEAM
    @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE USART FIRMWARE LIBRARY.
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
#ifndef __HAL_USART_H
#define __HAL_USART_H


/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @defgroup USART
  * @{
  */

/** @defgroup USART_Exported_Types
  * @{
  */

/**
* @brief  USART Init Structure definition
*/
typedef struct
{
    uint32_t USART_BaudRate;
    uint32_t USART_WordLength;
    uint32_t USART_StopBits;
    uint32_t USART_Parity;
    uint32_t USART_Mode;
} USART_InitTypeDef;
/**
  * @}
  */

/** @defgroup USART_Exported_Constants
  * @{
  */

/** 
  * @brief  USART_Word_Length
  */
#define USART_WordLength_8b                     (0x00U << USART_CR1_DL_Pos)
#define USART_WordLength_9b                     (0x01U << USART_CR1_DL_Pos)

/**
  * @brief   USART_Stop_Bits
  */
#define USART_StopBits_1                        (0x00U << USART_CR2_STOP_Pos) /*!< 1 STOP bit */
#define USART_StopBits_2                        (0x02U << USART_CR2_STOP_Pos) /*!< 2 STOP bit */

/** 
  * @brief  USART_Parity
  */
#define USART_Parity_No                         (0x00U << USART_CR1_PCE_Pos)
#define USART_Parity_Even                       ((0x00U << USART_CR1_PS_Pos) | (0x01U << USART_CR1_PCE_Pos))
#define USART_Parity_Odd                        ((0x01U << USART_CR1_PS_Pos) | (0x01U << USART_CR1_PCE_Pos))

/** 
  * @brief  USART_Mode
  */
#define USART_Mode_Rx                           (0x01U << USART_CR1_RE_Pos) /*!< Receiver enable */
#define USART_Mode_Tx                           (0x01U << USART_CR1_TE_Pos) /*!< Transmitter enable */

/** 
  * @brief  USART_Interrupt_definition
  */
#define USART_IT_IDLE           (0x01U << USART_CR1_IDLEIEN_Pos)   /*!< IDLE interrupt enable */
#define USART_IT_RXNE           (0x01U << USART_CR1_RXNEIEN_Pos)   /*!< RXNE interrupt enable */
#define USART_IT_TC             (0x01U << USART_CR1_TCIEN_Pos)     /*!< Transmission complete Interrupt enable */
#define USART_IT_TXE            (0x01U << USART_CR1_TXEIEN_Pos)    /*!< TXE interrupt enable */
#define USART_IT_PE             (0x01U << USART_CR1_PEIEN_Pos)     /*!< PE interrupt enable */
#define USART_IT_ERR            (0x01U << USART_CR3_ERRIEN_Pos)    /*!< Error interrupt enable */

/** 
  * @brief  USART_Flags
  */
#define USART_FLAG_PE               (0x01U << USART_SR_PE_Pos)    /*!< Parity error */
#define USART_FLAG_FE               (0x01U << USART_SR_FE_Pos)    /*!< Framing error*/
#define USART_FLAG_NF               (0x01U << USART_SR_NF_Pos)    /*!< Noise detected flag */
#define USART_FLAG_ORE              (0x01U << USART_SR_ORE_Pos)   /*!< Overrun error */
#define USART_FLAG_IDLE             (0x01U << USART_SR_IDLE_Pos)  /*!< IDLE frame detected */
#define USART_FLAG_RXNE             (0x01U << USART_SR_RXNE_Pos)  /*!< Read data register not empty */
#define USART_FLAG_TC               (0x01U << USART_SR_TC_Pos)    /*!< Transmission complete */
#define USART_FLAG_TXE              (0x01U << USART_SR_TXE_Pos)   /*!< Transmit data register Empty */

/**
  * @brief  USART SYNC MODE
  */ 
#define USART_Clock_Idle_High                   (0x01U << USART_CR2_CPOL_Pos)
#define USART_Clock_Idle_Low                    (0x00U << USART_CR2_CPOL_Pos)
#define USART_Clock_Phase_1Edge                 (0x00U << USART_CR2_CPHA_Pos)
#define USART_Clock_Phase_2Edge                 (0x01U << USART_CR2_CPHA_Pos)
/**
  * @}
  */

/** @defgroup USART_Exported_Functions
  * @{
  */
void USART_DeInit(USART_TypeDef *usart);
void USART_Init(USART_TypeDef *usart, USART_InitTypeDef* init_struct);
void USART_StructInit(USART_InitTypeDef* init_struct);
void USART_HalfDuplexCmd(USART_TypeDef *usart, FunctionalState state);
void USART_TxCmd(USART_TypeDef *usart, FunctionalState state);
void USART_RxCmd(USART_TypeDef *usart, FunctionalState state);
void USART_Cmd(USART_TypeDef *usart, FunctionalState state);
void USART_ITConfig(USART_TypeDef *usart, uint32_t usart_it, FunctionalState state);
void USART_SendData(USART_TypeDef *usart, uint16_t data);
uint16_t USART_ReceiveData(USART_TypeDef *usart);
FlagStatus USART_GetFlagStatus(USART_TypeDef *usart, uint32_t usart_flag);
void USART_ClearFlag(USART_TypeDef *usart, uint32_t usart_flag);
ITStatus USART_GetITStatus(USART_TypeDef *usart, uint32_t usart_it);
void USART_ClearITPendingBit(USART_TypeDef *usart, uint32_t usart_it);
void USART_SyncMasterConfig(USART_TypeDef *usart, uint32_t clock_polarity, uint32_t clock_phase, uint32_t usart_bound);
void USART_SyncSlaveConfig(USART_TypeDef *usart, uint32_t clock_polarity, uint32_t clock_phase);

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
