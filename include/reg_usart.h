/***********************************************************************************************************************
    @file     reg_usart.h
    @author   VV TEAM
    @brief    This flie contains all the USART's register and its field definition.
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

#ifndef __REG_USART_H
#define __REG_USART_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief USART Base Address Definition
  */
#define  USART2_BASE                               0x40004400 /*!<Base Address: 0x40004400*/
#define  USART1_BASE                               0x40013800 /*!<Base Address: 0x40013800*/

/**
  * @brief USART Register Structure Definition
  */
typedef struct
{
    __IO uint32_t SR;                  /*!<USART Status register                          offset: 0x00       */
    __IO uint32_t DR;                  /*!<USART Data register                            offset: 0x04       */
    __IO uint32_t BRR;                 /*!<USART Baud rate register                       offset: 0x08       */
    __IO uint32_t CR1;                 /*!<USART Control register 1                       offset: 0x0C       */
    __IO uint32_t CR2;                 /*!<USART Control register 2                       offset: 0x10       */
    __IO uint32_t CR3;                 /*!<USART Control register 3                       offset: 0x14       */
} USART_TypeDef;

/**
  * @brief USART type pointer Definition
  */
#define USART2                                    ((USART_TypeDef *)USART2_BASE)
#define USART1                                    ((USART_TypeDef *)USART1_BASE)

/**
  * @brief USART_SR Register Bit Definition
  */
#define  USART_SR_PE_Pos                          (0)
#define  USART_SR_PE_Msk                          (0x1U << USART_SR_PE_Pos)   /*!<Parity error*/
#define  USART_SR_PE                              USART_SR_PE_Msk
#define  USART_SR_FE_Pos                          (1)
#define  USART_SR_FE_Msk                          (0x1U << USART_SR_FE_Pos)   /*!<Framing error*/
#define  USART_SR_FE                              USART_SR_FE_Msk
#define  USART_SR_NF_Pos                          (2)
#define  USART_SR_NF_Msk                          (0x1U << USART_SR_NF_Pos)   /*!<Noise detected flag*/
#define  USART_SR_NF                              USART_SR_NF_Msk
#define  USART_SR_ORE_Pos                         (3)
#define  USART_SR_ORE_Msk                         (0x1U << USART_SR_ORE_Pos)  /*!<OverRun error*/
#define  USART_SR_ORE                             USART_SR_ORE_Msk
#define  USART_SR_IDLE_Pos                        (4)
#define  USART_SR_IDLE_Msk                        (0x1U << USART_SR_IDLE_Pos) /*!<IDLE frame detected*/
#define  USART_SR_IDLE                            USART_SR_IDLE_Msk
#define  USART_SR_RXNE_Pos                        (5)
#define  USART_SR_RXNE_Msk                        (0x1U << USART_SR_RXNE_Pos) /*!<Receive data register not empty*/
#define  USART_SR_RXNE                            USART_SR_RXNE_Msk
#define  USART_SR_TC_Pos                          (6)
#define  USART_SR_TC_Msk                          (0x1U << USART_SR_TC_Pos)   /*!<Transmission Complete*/
#define  USART_SR_TC                              USART_SR_TC_Msk
#define  USART_SR_TXE_Pos                         (7)
#define  USART_SR_TXE_Msk                         (0x1U << USART_SR_TXE_Pos)  /*!<Transmit data register Empty*/
#define  USART_SR_TXE                             USART_SR_TXE_Msk

/**
  * @brief USART_DR Register Bit Definition
  */
#define  USART_DR_DR_Pos                          (0)
#define  USART_DR_DR_Msk                          (0x1FFU << USART_DR_DR_Pos) /*!<Transmit /Receive data register*/
#define  USART_DR_DR                              USART_DR_DR_Msk
#define  USART_DR_DR_0                            (0x001U << USART_DR_DR_Pos)
#define  USART_DR_DR_1                            (0x002U << USART_DR_DR_Pos)
#define  USART_DR_DR_2                            (0x004U << USART_DR_DR_Pos)
#define  USART_DR_DR_3                            (0x008U << USART_DR_DR_Pos)
#define  USART_DR_DR_4                            (0x010U << USART_DR_DR_Pos)
#define  USART_DR_DR_5                            (0x020U << USART_DR_DR_Pos)
#define  USART_DR_DR_6                            (0x040U << USART_DR_DR_Pos)
#define  USART_DR_DR_7                            (0x080U << USART_DR_DR_Pos)
#define  USART_DR_DR_8                            (0x100U << USART_DR_DR_Pos)

/**
  * @brief USART_BRR Register Bit Definition
  */
#define  USART_BRR_FFD_Pos                        (0)
#define  USART_BRR_FFD_Msk                        (0xFU << USART_BRR_FFD_Pos) /*!<Fraction frequency division of baudrate*/
#define  USART_BRR_FFD                            USART_BRR_FFD_Msk
#define  USART_BRR_FFD_0                          (0x1U << USART_BRR_FFD_Pos)
#define  USART_BRR_FFD_1                          (0x2U << USART_BRR_FFD_Pos)
#define  USART_BRR_FFD_2                          (0x4U << USART_BRR_FFD_Pos)
#define  USART_BRR_FFD_3                          (0x8U << USART_BRR_FFD_Pos)
#define  USART_BRR_MFD_Pos                        (4)
#define  USART_BRR_MFD_Msk                        (0xFFFFU << USART_BRR_MFD_Pos) /*!<Mantissa frequency division of baudrate*/
#define  USART_BRR_MFD                            USART_BRR_MFD_Msk
#define  USART_BRR_MFD_0                          (0x0001U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_1                          (0x0002U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_2                          (0x0004U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_3                          (0x0008U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_4                          (0x0010U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_5                          (0x0020U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_6                          (0x0040U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_7                          (0x0080U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_8                          (0x0100U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_9                          (0x0200U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_10                         (0x0400U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_11                         (0x0800U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_12                         (0x1000U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_13                         (0x2000U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_14                         (0x4000U << USART_BRR_MFD_Pos)
#define  USART_BRR_MFD_15                         (0x8000U << USART_BRR_MFD_Pos)

/**
  * @brief USART_CR1 Register Bit Definition
  */
#define  USART_CR1_SBK_Pos                        (0)
#define  USART_CR1_SBK_Msk                        (0x1U << USART_CR1_SBK_Pos)     /*!<Send break*/
#define  USART_CR1_SBK                            USART_CR1_SBK_Msk
#define  USART_CR1_RE_Pos                         (2)
#define  USART_CR1_RE_Msk                         (0x1U << USART_CR1_RE_Pos)      /*!<Receiver enable*/
#define  USART_CR1_RE                             USART_CR1_RE_Msk
#define  USART_CR1_TE_Pos                         (3)
#define  USART_CR1_TE_Msk                         (0x1U << USART_CR1_TE_Pos)      /*!<Transmitter enable*/
#define  USART_CR1_TE                             USART_CR1_TE_Msk
#define  USART_CR1_IDLEIEN_Pos                    (4)
#define  USART_CR1_IDLEIEN_Msk                    (0x1U << USART_CR1_IDLEIEN_Pos) /*!<IDLE interrupt enable*/
#define  USART_CR1_IDLEIEN                        USART_CR1_IDLEIEN_Msk
#define  USART_CR1_RXNEIEN_Pos                    (5)
#define  USART_CR1_RXNEIEN_Msk                    (0x1U << USART_CR1_RXNEIEN_Pos) /*!<RXNE interrupt enable*/
#define  USART_CR1_RXNEIEN                        USART_CR1_RXNEIEN_Msk
#define  USART_CR1_TCIEN_Pos                      (6)
#define  USART_CR1_TCIEN_Msk                      (0x1U << USART_CR1_TCIEN_Pos)   /*!<Transmission complete interrupt enable*/
#define  USART_CR1_TCIEN                          USART_CR1_TCIEN_Msk
#define  USART_CR1_TXEIEN_Pos                     (7)
#define  USART_CR1_TXEIEN_Msk                     (0x1U << USART_CR1_TXEIEN_Pos)  /*!<TXE interrupt enable*/
#define  USART_CR1_TXEIEN                         USART_CR1_TXEIEN_Msk
#define  USART_CR1_PEIEN_Pos                      (8)
#define  USART_CR1_PEIEN_Msk                      (0x1U << USART_CR1_PEIEN_Pos)   /*!<PE interrupt enable*/
#define  USART_CR1_PEIEN                          USART_CR1_PEIEN_Msk
#define  USART_CR1_PS_Pos                         (9)
#define  USART_CR1_PS_Msk                         (0x1U << USART_CR1_PS_Pos)      /*!<Parity selection*/
#define  USART_CR1_PS                             USART_CR1_PS_Msk
#define  USART_CR1_PCE_Pos                        (10)
#define  USART_CR1_PCE_Msk                        (0x1U << USART_CR1_PCE_Pos)     /*!<Parity control enable*/
#define  USART_CR1_PCE                            USART_CR1_PCE_Msk
#define  USART_CR1_DL_Pos                         (12)
#define  USART_CR1_DL_Msk                         (0x1U << USART_CR1_DL_Pos)      /*!<Data length*/
#define  USART_CR1_DL                             USART_CR1_DL_Msk
#define  USART_CR1_UE_Pos                         (13)
#define  USART_CR1_UE_Msk                         (0x1U << USART_CR1_UE_Pos)      /*!<USART enable*/
#define  USART_CR1_UE                             USART_CR1_UE_Msk
#define  USART_CR1_OVER8_Pos                      (15)
#define  USART_CR1_OVER8_Msk                      (0x1U << USART_CR1_OVER8_Pos)   /*!<UART oversampling mode*/
#define  USART_CR1_OVER8                          USART_CR1_OVER8_Msk
#define  USART_CR1_MLS_Pos                        (16)
#define  USART_CR1_MLS_Msk                        (0x1U << USART_CR1_MLS_Pos)     /*!<MSB/LSB mode selection*/
#define  USART_CR1_MLS                            USART_CR1_MLS_Msk
#define  USART_CR1_SAS_Pos                        (17)
#define  USART_CR1_SAS_Msk                        (0x1U << USART_CR1_SAS_Pos)     /*!<Synchronous/Asynchronous mode selection*/
#define  USART_CR1_SAS                            USART_CR1_SAS_Msk

/**
  * @brief USART_CR2 Register Bit Definition
  */
#define  USART_CR2_CPHA_Pos                       (9)
#define  USART_CR2_CPHA_Msk                       (0x1U << USART_CR2_CPHA_Pos) /*!<Clock phase*/
#define  USART_CR2_CPHA                           USART_CR2_CPHA_Msk
#define  USART_CR2_CPOL_Pos                       (10)
#define  USART_CR2_CPOL_Msk                       (0x1U << USART_CR2_CPOL_Pos) /*!<Clock polarity*/
#define  USART_CR2_CPOL                           USART_CR2_CPOL_Msk
#define  USART_CR2_STOP_Pos                       (12)
#define  USART_CR2_STOP_Msk                       (0x3U << USART_CR2_STOP_Pos) /*!<STOP bit*/
#define  USART_CR2_STOP                           USART_CR2_STOP_Msk
#define  USART_CR2_STOP_0                         (0x1U << USART_CR2_STOP_Pos)
#define  USART_CR2_STOP_1                         (0x2U << USART_CR2_STOP_Pos)
#define  USART_CR2_SWAP_Pos                       (15)
#define  USART_CR2_SWAP_Msk                       (0x1U << USART_CR2_SWAP_Pos) /*!<Swap pin between input and output*/
#define  USART_CR2_SWAP                           USART_CR2_SWAP_Msk

/**
  * @brief USART_CR3 Register Bit Definition
  */
#define  USART_CR3_ERRIEN_Pos                     (0)
#define  USART_CR3_ERRIEN_Msk                     (0x1U << USART_CR3_ERRIEN_Pos)  /*!<Error interrupt enable*/
#define  USART_CR3_ERRIEN                         USART_CR3_ERRIEN_Msk
#define  USART_CR3_HDSEL_Pos                      (3)
#define  USART_CR3_HDSEL_Msk                      (0x1U << USART_CR3_HDSEL_Pos)   /*!<Single wire Half-duplex selection*/
#define  USART_CR3_HDSEL                          USART_CR3_HDSEL_Msk
#define  USART_CR3_DMAMODE_Pos                    (6)
#define  USART_CR3_DMAMODE_Msk                    (0x1U << USART_CR3_DMAMODE_Pos) /*!<DMA mode enable bit*/
#define  USART_CR3_DMAMODE                        USART_CR3_DMAMODE_Msk
#define  USART_CR3_RTSE_Pos                       (8)
#define  USART_CR3_RTSE_Msk                       (0x1U << USART_CR3_RTSE_Pos)    /*!<RTS enable*/
#define  USART_CR3_RTSE                           USART_CR3_RTSE_Msk
#define  USART_CR3_CTSE_Pos                       (9)
#define  USART_CR3_CTSE_Msk                       (0x1U << USART_CR3_CTSE_Pos)    /*!<CTS enable*/
#define  USART_CR3_CTSE                           USART_CR3_CTSE_Msk
#define  USART_CR3_CTSIEN_Pos                     (10)
#define  USART_CR3_CTSIEN_Msk                     (0x1U << USART_CR3_CTSIEN_Pos)  /*!<CTS interrupt enable*/
#define  USART_CR3_CTSIEN                         USART_CR3_CTSIEN_Msk
#define  USART_CR3_ONEBIT_Pos                     (11)
#define  USART_CR3_ONEBIT_Msk                     (0x1U << USART_CR3_ONEBIT_Pos)  /*!<UART one sample bit method enable*/
#define  USART_CR3_ONEBIT                         USART_CR3_ONEBIT_Msk
#define  USART_CR3_CKINE_Pos                      (16)
#define  USART_CR3_CKINE_Msk                      (0x1U << USART_CR3_CKINE_Pos)   /*!<Clock input permission in synchronous mode*/
#define  USART_CR3_CKINE                          USART_CR3_CKINE_Msk
#define  USART_CR3_RXTOG_Pos                      (28)
#define  USART_CR3_RXTOG_Msk                      (0x1U << USART_CR3_RXTOG_Pos)   /*!<Receive toggle bit*/
#define  USART_CR3_RXTOG                          USART_CR3_RXTOG_Msk
#define  USART_CR3_TXTOG_Pos                      (29)
#define  USART_CR3_TXTOG_Msk                      (0x1U << USART_CR3_TXTOG_Pos)   /*!<Transmit toggle bit*/
#define  USART_CR3_TXTOG                          USART_CR3_TXTOG_Msk

#endif

