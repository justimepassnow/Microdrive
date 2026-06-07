/***********************************************************************************************************************
    @file     reg_iwdg.h
    @author   VV TEAM
    @brief    This flie contains all the IWDG's register and its field definition.
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

#ifndef __REG_IWDG_H
#define __REG_IWDG_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief IWDG Base Address Definition
  */
#define  IWDG_BASE                                 0x40003000 /*!<Base Address: 0x40003000*/

/**
  * @brief IWDG Register Structure Definition
  */
typedef struct
{
    __IO uint32_t KR;                  /*!<IWDG Key register                              offset: 0x00       */
    __IO uint32_t PR;                  /*!<IWDG Prescaler register                        offset: 0x04       */
    __IO uint32_t RLR;                 /*!<IWDG Reload register                           offset: 0x08       */
    __IO uint32_t SR;                  /*!<IWDG Status register                           offset: 0x0C       */
    __IO uint32_t CR;                  /*!<IWDG Control register                          offset: 0x10       */
    __IO uint32_t IGEN;                /*!<IWDG Interrupt generate register               offset: 0x14       */
    __IO uint32_t CNT;                 /*!<IWDG Counter register                          offset: 0x18       */
} IWDG_TypeDef;

/**
  * @brief IWDG type pointer Definition
  */
#define IWDG                                      ((IWDG_TypeDef *)IWDG_BASE)

/**
  * @brief IWDG_KR Register Bit Definition
  */
#define  IWDG_KR_KEY_Pos                          (0)
#define  IWDG_KR_KEY_Msk                          (0xFFFFU << IWDG_KR_KEY_Pos) /*!<Key value (write-only register)*/
#define  IWDG_KR_KEY                              IWDG_KR_KEY_Msk
#define  IWDG_KR_KEY_0                            (0x0001U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_1                            (0x0002U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_2                            (0x0004U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_3                            (0x0008U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_4                            (0x0010U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_5                            (0x0020U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_6                            (0x0040U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_7                            (0x0080U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_8                            (0x0100U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_9                            (0x0200U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_10                           (0x0400U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_11                           (0x0800U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_12                           (0x1000U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_13                           (0x2000U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_14                           (0x4000U << IWDG_KR_KEY_Pos)
#define  IWDG_KR_KEY_15                           (0x8000U << IWDG_KR_KEY_Pos)

/**
  * @brief IWDG_PR Register Bit Definition
  */
#define  IWDG_PR_PR_Pos                           (0)
#define  IWDG_PR_PR_Msk                           (0x7U << IWDG_PR_PR_Pos) /*!<Prescaler divider*/
#define  IWDG_PR_PR                               IWDG_PR_PR_Msk
#define  IWDG_PR_PR_0                             (0x1U << IWDG_PR_PR_Pos)
#define  IWDG_PR_PR_1                             (0x2U << IWDG_PR_PR_Pos)
#define  IWDG_PR_PR_2                             (0x4U << IWDG_PR_PR_Pos)

/**
  * @brief IWDG_RLR Register Bit Definition
  */
#define  IWDG_RLR_RL_Pos                          (0)
#define  IWDG_RLR_RL_Msk                          (0xFFFU << IWDG_RLR_RL_Pos) /*!<Watchdog counter reload value*/
#define  IWDG_RLR_RL                              IWDG_RLR_RL_Msk
#define  IWDG_RLR_RL_0                            (0x001U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_1                            (0x002U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_2                            (0x004U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_3                            (0x008U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_4                            (0x010U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_5                            (0x020U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_6                            (0x040U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_7                            (0x080U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_8                            (0x100U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_9                            (0x200U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_10                           (0x400U << IWDG_RLR_RL_Pos)
#define  IWDG_RLR_RL_11                           (0x800U << IWDG_RLR_RL_Pos)

/**
  * @brief IWDG_SR Register Bit Definition
  */
#define  IWDG_SR_PVU_Pos                          (0)
#define  IWDG_SR_PVU_Msk                          (0x1U << IWDG_SR_PVU_Pos)    /*!<Watchdog prescaler value update*/
#define  IWDG_SR_PVU                              IWDG_SR_PVU_Msk
#define  IWDG_SR_RVU_Pos                          (1)
#define  IWDG_SR_RVU_Msk                          (0x1U << IWDG_SR_RVU_Pos)    /*!<Watchdog counter reload value update*/
#define  IWDG_SR_RVU                              IWDG_SR_RVU_Msk
#define  IWDG_SR_IVU_Pos                          (2)
#define  IWDG_SR_IVU_Msk                          (0x1U << IWDG_SR_IVU_Pos)    /*!<Watchdog Interrupt Generate value update*/
#define  IWDG_SR_IVU                              IWDG_SR_IVU_Msk
#define  IWDG_SR_UPDATE_Pos                       (3)
#define  IWDG_SR_UPDATE_Msk                       (0x1U << IWDG_SR_UPDATE_Pos) /*!<Watchdog reload value update flag*/
#define  IWDG_SR_UPDATE                           IWDG_SR_UPDATE_Msk

/**
  * @brief IWDG_CR Register Bit Definition
  */
#define  IWDG_CR_IRQ_SEL_Pos                      (0)
#define  IWDG_CR_IRQ_SEL_Msk                      (0x1U << IWDG_CR_IRQ_SEL_Pos) /*!<IWDG overflow operation select*/
#define  IWDG_CR_IRQ_SEL                          IWDG_CR_IRQ_SEL_Msk
#define  IWDG_CR_IRQ_CLR_Pos                      (1)
#define  IWDG_CR_IRQ_CLR_Msk                      (0x1U << IWDG_CR_IRQ_CLR_Pos) /*!<IWDG interrupt clear*/
#define  IWDG_CR_IRQ_CLR                          IWDG_CR_IRQ_CLR_Msk

/**
  * @brief IWDG_IGEN Register Bit Definition
  */
#define  IWDG_IGEN_IGEN_Pos                       (0)
#define  IWDG_IGEN_IGEN_Msk                       (0xFFFU << IWDG_IGEN_IGEN_Pos) /*!<IWDG Interrupt Generate value*/
#define  IWDG_IGEN_IGEN                           IWDG_IGEN_IGEN_Msk
#define  IWDG_IGEN_IGEN_0                         (0x001U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_1                         (0x002U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_2                         (0x004U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_3                         (0x008U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_4                         (0x010U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_5                         (0x020U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_6                         (0x040U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_7                         (0x080U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_8                         (0x100U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_9                         (0x200U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_10                        (0x400U << IWDG_IGEN_IGEN_Pos)
#define  IWDG_IGEN_IGEN_11                        (0x800U << IWDG_IGEN_IGEN_Pos)

/**
  * @brief IWDG_CNT Register Bit Definition
  */
#define  IWDG_CNT_IWDG_PS_Pos                     (0)
#define  IWDG_CNT_IWDG_PS_Msk                     (0xFFU << IWDG_CNT_IWDG_PS_Pos) /*!<Value of the prescaler counter of the IWDG clock*/
#define  IWDG_CNT_IWDG_PS                         IWDG_CNT_IWDG_PS_Msk
#define  IWDG_CNT_IWDG_PS_0                       (0x01U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_PS_1                       (0x02U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_PS_2                       (0x04U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_PS_3                       (0x08U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_PS_4                       (0x10U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_PS_5                       (0x20U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_PS_6                       (0x40U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_PS_7                       (0x80U << IWDG_CNT_IWDG_PS_Pos)
#define  IWDG_CNT_IWDG_CNT_Pos                    (8)
#define  IWDG_CNT_IWDG_CNT_Msk                    (0x7FFU << IWDG_CNT_IWDG_CNT_Pos) /*!<IWDG counter value*/
#define  IWDG_CNT_IWDG_CNT                        IWDG_CNT_IWDG_CNT_Msk
#define  IWDG_CNT_IWDG_CNT_0                      (0x001U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_1                      (0x002U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_2                      (0x004U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_3                      (0x008U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_4                      (0x010U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_5                      (0x020U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_6                      (0x040U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_7                      (0x080U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_8                      (0x100U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_9                      (0x200U << IWDG_CNT_IWDG_CNT_Pos)
#define  IWDG_CNT_IWDG_CNT_10                     (0x400U << IWDG_CNT_IWDG_CNT_Pos)

#endif

