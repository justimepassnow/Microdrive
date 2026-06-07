/***********************************************************************************************************************
    @file     hal_usart.c
    @author   VV TEAM
    @brief    THIS FILE PROVIDES ALL THE USART FIRMWARE FUNCTIONS.
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

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "hal_usart.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */

/** @defgroup USART_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
  * @param usart: Select the USART peripheral.
  * @retval : None
  */
void USART_DeInit(USART_TypeDef *usart)
{
    if (usart == USART1)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART1, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART1, DISABLE);
    }

    if (usart == USART2)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART2, DISABLE);
    }
}

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *   parameters in the USART_InitStruct .
  * @param usart: Select the USART peripheral.
  * @param init_struct: pointer to a USART_InitTypeDef structure
  *   that contains the configuration information for the specified USART peripheral.
  * @retval : None
  */
void USART_Init(USART_TypeDef *usart, USART_InitTypeDef *init_struct)
{
    uint32_t apbclock = 0x00;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    MODIFY_REG(usart->CR1, USART_CR1_PS_Msk | USART_CR1_PCE_Msk, init_struct->USART_Parity);
    MODIFY_REG(usart->CR1, USART_CR1_DL_Msk, init_struct->USART_WordLength);
    MODIFY_REG(usart->CR1, USART_CR1_RE_Msk | USART_CR1_TE_Msk, init_struct->USART_Mode);

    MODIFY_REG(usart->CR2, USART_CR2_STOP_Msk, init_struct->USART_StopBits);

     /* Configure the USART Baud Rate -------------------------------------------*/
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    if ((usart == USART1) || (usart == USART2))
    {
        apbclock = RCC_ClocksStatus.PCLK1_Frequency;
    }

     /* Write to USART BRR */
    usart->BRR &= (~0x000fffff);
    usart->BRR |= (((apbclock / 16) / init_struct->USART_BaudRate) << 4);
    usart->BRR |= (((apbclock / (init_struct->USART_BaudRate)) % 16) << 0);
}

/**
  * @brief  USART_StructInit.
  * @param init_struct: pointer to a USART_InitTypeDef structure
  *   that contains the configuration information for the
  *   specified USART peripheral.
  * @retval : None
  */
void USART_StructInit(USART_InitTypeDef *init_struct)
{
     /* USART_InitStruct members default value */
    init_struct->USART_BaudRate   = 9600;
    init_struct->USART_WordLength = USART_WordLength_8b;
    init_struct->USART_StopBits   = USART_StopBits_1;
    init_struct->USART_Parity     = USART_Parity_No;
    init_struct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
}

/**
  * @brief  Half-duplex selection.
  * @param usart: Select the USART peripheral.
  * @param state: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval : None
  */
void USART_HalfDuplexCmd(USART_TypeDef *usart, FunctionalState state)
{
    (state) ?                                        \
    (usart->CR3 |= (0x01U << USART_CR3_HDSEL_Pos)) : \
    (usart->CR3 &= ~(0x01U << USART_CR3_HDSEL_Pos));
}

/**
  * @brief  Transmitter enable.
  * @param usart: Select the USART peripheral.
  * @param state: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval : None
  */
void USART_TxCmd(USART_TypeDef *usart, FunctionalState state)
{
    (state) ?                                     \
    (usart->CR1 |= (0x01U << USART_CR1_TE_Pos)) : \
    (usart->CR1 &= ~(0x01U << USART_CR1_TE_Pos));
}

/**
  * @brief  Receiver enable.
  * @param usart: Select the USART peripheral.
  * @param state: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval : None
  */
void USART_RxCmd(USART_TypeDef *usart, FunctionalState state)
{
    (state) ?                                     \
    (usart->CR1 |= (0x01U << USART_CR1_RE_Pos)) : \
    (usart->CR1 &= ~(0x01U << USART_CR1_RE_Pos));
}

/**
  * @brief  Enables or disables the specified USART peripheral.
  * @param usart: Select the USART peripheral.
  * @param state: new state of the USARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval : None
  */
void USART_Cmd(USART_TypeDef *usart, FunctionalState state)
{
    (state) ?                                     \
    (usart->CR1 |= (0x01U << USART_CR1_UE_Pos)) : \
    (usart->CR1 &= ~(0x01U << USART_CR1_UE_Pos));
}

/**
  * @brief  Enables or disables the specified USART CR1 interrupts.
  * @param usart: Select the USART or the USART peripheral.
  * @param usart_it: specifies the USART interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  * @arg   USART_IT_IDLE
  * @arg   USART_IT_RXNE
  * @arg   USART_IT_TC
  * @arg   USART_IT_TXE
  * @arg   USART_IT_PE
  * @arg   USART_IT_ERR
  * @param NewState: new state of the specified USARTx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval : None
  */
void USART_ITConfig(USART_TypeDef *usart, uint32_t usart_it, FunctionalState state)
{
    if (usart_it == USART_IT_ERR)
    {
        (state) ?                  \
        (usart->CR3 |= usart_it) : \
        (usart->CR3 &= ~usart_it);
    }
    else
    {
        (state) ?                  \
        (usart->CR1 |= usart_it) : \
        (usart->CR1 &= ~usart_it);
    }
}

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param usart: Select the USART or the USART peripheral.
  * @param data: the data to transmit.
  * @retval : None
  */
void USART_SendData(USART_TypeDef *usart, uint16_t data)
{
     /* Transmit Data */
    usart->DR = data & 0x1FFU;
}

/**
  * @brief  Returns the most recent received data by the USARTx peripheral.
  * @param usart: Select the USART or the USART peripheral.
  * @retval : The received data.
  */
uint16_t USART_ReceiveData(USART_TypeDef *usart)
{
     /* Receive Data */
    return ((uint16_t)(usart->DR & (uint16_t)0x01FF));
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param usart: Select the USART or the USART peripheral.
  * @param usart_flag: specifies the flag to check.
  *   This parameter can be one of the following values:
  * @arg   USART_FLAG_PE
  * @arg   USART_FLAG_FE
  * @arg   USART_FLAG_NF
  * @arg   USART_FLAG_ORE
  * @arg   USART_FLAG_IDLE
  * @arg   USART_FLAG_RXNE
  * @arg   USART_FLAG_TC
  * @arg   USART_FLAG_TXE
  * @retval : The new state of USART_FLAG (SET or RE
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef *usart, uint32_t usart_flag)
{
    return ((usart->SR & usart_flag) ? SET : RESET);
}

/**
  * @brief  Clears the USARTx's pending flags.
  * @param usart: Select the USART or the USART peripheral.
  * @param usart_flag: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  * @arg   USART_FLAG_RXNE
  * @retval : None
  */
void USART_ClearFlag(USART_TypeDef *usart, uint32_t usart_flag)
{
    usart->SR = ~(usart_flag);
}

/**
  * @brief  Checks whether the specified USART  interrupt has occurred or not.
  * @param usart: Select the USART or the USART peripheral..
  * @param usart_it: specifies the flag to check.
  *   This parameter can be any combination of the following values:
  * @arg   USART_IT_IDLE
  * @arg   USART_IT_RXNE
  * @arg   USART_IT_TC
  * @arg   USART_IT_TXE
  * @arg   USART_IT_PE
  * @arg   USART_IT_ERR
  * @retval : The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef *usart, uint32_t usart_it)
{
    ITStatus ret = RESET;

    if (usart_it == USART_IT_IDLE)
    {
        ret = ((usart->SR & USART_SR_IDLE_Msk) ? SET : RESET);
    }
    else if (usart_it == USART_IT_RXNE)
    {
        ret = ((usart->SR & USART_SR_RXNE_Msk) ? SET : RESET);
    }
    else if (usart_it == USART_IT_TC)
    {
        ret = ((usart->SR & USART_SR_TC_Msk) ? SET : RESET);
    }
    else if (usart_it == USART_IT_TXE)
    {
        ret = ((usart->SR & USART_SR_TXE_Msk) ? SET : RESET);
    }
    else if (usart_it == USART_IT_PE)
    {
        ret = ((usart->SR & USART_SR_PE_Msk) ? SET : RESET);
    }
    else if (usart_it == USART_IT_ERR)
    {
        ret = ((usart->SR & (USART_SR_FE_Msk | USART_SR_ORE_Msk | USART_SR_NF_Msk)) ? SET : RESET);
    }

    return (ret);
}

/**
  * @brief  Clears the USARTx interrupt pending bits.
  * @param usart: Select the USART or the USART peripheral.
  *   This parameter can be one of the following values:
  *   USART1.
  * @param usart_it: specifies the interrupt pending bit to clear.
  *   This parameter can be one of the following values:
  * @arg  USART_IT_RXNE
  * @retval : None
  */
void USART_ClearITPendingBit(USART_TypeDef *usart, uint32_t usart_it)
{
    usart->SR = ~(usart_it);
}

/**
  * @brief  Initializes the SYNC MASTER USARTx peripheral according to the specified
  *   parameters in the USART_InitStruct .
  * @param usart: Select the USART or the USART peripheral.
  * @param clock_polarity
  * @arg  USART_Clock_Idle_High
  * @arg  USART_Clock_Idle_Low
  * @param clock_phase
  * @arg  USART_Clock_Phase_1Edge
  * @arg  USART_Clock_Phase_2Edge
  * @param usart_bound: speed.
  * @retval : None
  */
void USART_SyncMasterConfig(USART_TypeDef *usart, uint32_t clock_polarity, uint32_t clock_phase, uint32_t usart_bound)
{
    uint32_t apbclock = 0x00;
    RCC_ClocksTypeDef RCC_ClocksStatus;

     /* Configure the USART Baud Rate -------------------------------------------*/
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    if ((usart == USART1) || (usart == USART2))
    {
        apbclock = RCC_ClocksStatus.PCLK1_Frequency;
    }

     /* Write to USART BRR */
    usart->BRR &= (~0x000fffff);
    usart->BRR |= (((apbclock / 4) / usart_bound) << 4);

    usart->CR1 |= (0x01U << USART_CR1_SAS_Pos);
    usart->CR1 |= (0x01U << USART_CR1_MLS_Pos);
    usart->CR3 &= ~(0x01U << USART_CR3_HDSEL_Pos);

    MODIFY_REG(usart->CR2, USART_CR2_CPHA_Msk, clock_phase);
    MODIFY_REG(usart->CR2, USART_CR2_CPOL_Msk, clock_polarity);

    usart->CR1 |= ((0x01U << USART_CR1_TE_Pos) | (0x01U << USART_CR1_RE_Pos));
}

/**
  * @brief  Initializes the SYNC SLAVE USARTx peripheral according to the specified
  *   parameters in the USART_InitStruct .
  * @param usart: Select the USART or the USART peripheral.
  * @param clock_polarity
  * @arg  USART_Clock_Idle_High
  * @arg  USART_Clock_Idle_Low
  * @param clock_phase
  * @arg  USART_Clock_Phase_1Edge
  * @arg  USART_Clock_Phase_2Edge
  * @retval None
  */
void USART_SyncSlaveConfig(USART_TypeDef *usart, uint32_t clock_polarity, uint32_t clock_phase)
{
    usart->CR1 |= (0x01U << USART_CR1_SAS_Pos);
    usart->CR1 |= (0x01U << USART_CR1_MLS_Pos);
    usart->CR3 &= ~(0x01U << USART_CR3_HDSEL_Pos);

    MODIFY_REG(usart->CR2, USART_CR2_CPHA_Msk, clock_phase);
    MODIFY_REG(usart->CR2, USART_CR2_CPOL_Msk, clock_polarity);

    usart->CR1 |= ((0x01U << USART_CR1_TE_Pos) | (0x01U << USART_CR1_RE_Pos));
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

