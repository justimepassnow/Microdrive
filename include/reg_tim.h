/***********************************************************************************************************************
    @file     reg_tim.h
    @author   VV TEAM
    @brief    This flie contains all the TIM's register and its field definition.
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

#ifndef __REG_TIM_H
#define __REG_TIM_H


/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>




/**
  * @brief TIM Base Address Definition
  */
#define  TIM3_BASE                                 0x40000400                                       /*!<Base Address: 0x40000400*/
#define  TIM1_BASE                                 0x40012C00                                       /*!<Base Address: 0x40012C00*/
#define  TIM14_BASE                                0x40014000                                       /*!<Base Address: 0x40014000*/

/**
  * @brief TIM Register Structure Definition
  */
typedef struct
{
    __IO uint32_t CR1;                            /*!<TIM Control Register 1                         offset: 0x00       */
    __IO uint32_t CR2;                            /*!<TIM Control Register 2                         offset: 0x04       */
    __IO uint32_t SMCR;                           /*!<TIM Slave Mode Control Register                offset: 0x08       */
    __IO uint32_t DIER;                           /*!<TIM DMA/Interrupt Enable Register (DMA is      offset: 0x0C
                                                      only suitable for the chip with built in DMA)                     */
    __IO uint32_t SR;                             /*!<TIM Status Register                            offset: 0x10       */
    __IO uint32_t EGR;                            /*!<TIM Event Generation Register                  offset: 0x14       */
    __IO uint32_t CCMR1;                          /*!<TIM Capture/Compare Mode Register 1            offset: 0x18       */
    __IO uint32_t CCMR2;                          /*!<TIM Capture/Compare Mode Register 2            offset: 0x1C       */
    __IO uint32_t CCER;                           /*!<TIM Capture/Compare Enable Register            offset: 0x20       */
    __IO uint32_t CNT;                            /*!<TIM Counter                                    offset: 0x24       */
    __IO uint32_t PSC;                            /*!<TIM Prescaler                                  offset: 0x28       */
    __IO uint32_t ARR;                            /*!<TIM Auto Reload Register                       offset: 0x2C       */
    __IO uint32_t RCR;                            /*!<TIM Repeat Count Register                      offset: 0x30       */
    __IO uint32_t CCR1;                           /*!<TIM Capture/Compare Register 1                 offset: 0x34       */
    __IO uint32_t CCR2;                           /*!<TIM Capture/Compare Register 2                 offset: 0x38       */
    __IO uint32_t CCR3;                           /*!<TIM Capture/Compare Register 3                 offset: 0x3C       */
    __IO uint32_t CCR4;                           /*!<TIM Capture/Compare Register 4                 offset: 0x40       */
    __IO uint32_t BDTR;                           /*!<TIM Break And Dead-Time Register               offset: 0x44       */
    __IO uint32_t RESERVED0x48[2];                /*!<                                               offset: 0x48~0x4C  */
    __IO uint32_t OR;                             /*!<TIM Input Option Register                      offset: 0x50       */
    __IO uint32_t CCMR3;                          /*!<TIM Input Option Register                      offset: 0x54       */
    __IO uint32_t CCR5;                           /*!<TIM Compare Register 5                         offset: 0x58       */
    __IO uint32_t PDER;                           /*!<TIM PWM Phase Shift/DMA Repeat Update Request  offset: 0x5C
                                                      Enable Register                                                   */
    __IO uint32_t CCR1FALL;                       /*!<TIM PWM Phase Shift Count Down                 offset: 0x60
                                                      Capture/Compare Register                                          */
    __IO uint32_t CCR2FALL;                       /*!<TIM PWM Phase Shift Count Down                 offset: 0x64
                                                      Capture/Compare Register                                          */
    __IO uint32_t CCR3FALL;                       /*!<TIM PWM Phase Shift Count Down                 offset: 0x68
                                                      Capture/Compare Register                                          */
    __IO uint32_t CCR4FALL;                       /*!<TIM PWM Phase Shift Count Down                 offset: 0x6C
                                                      Capture/Compare Register                                          */
    __IO uint32_t CCR5FALL;                       /*!<TIM PWM Phase Shift Count Down                 offset: 0x70
                                                      Capture/Compare Register                                          */
} TIM_TypeDef;

/**
  * @brief TIM type pointer Definition
  */
#define TIM3                                      ((TIM_TypeDef *)TIM3_BASE)
#define TIM1                                      ((TIM_TypeDef *)TIM1_BASE)
#define TIM14                                     ((TIM_TypeDef *)TIM14_BASE)

/**
  * @brief TIM_CR1 Register Bit Definition
  */
#define  TIM_CR1_CEN_Pos                          (0)
#define  TIM_CR1_CEN_Msk                          (0x1U << TIM_CR1_CEN_Pos)                         /*!<Counter enable*/
#define  TIM_CR1_CEN                              TIM_CR1_CEN_Msk
#define  TIM_CR1_UDIS_Pos                         (1)
#define  TIM_CR1_UDIS_Msk                         (0x1U << TIM_CR1_UDIS_Pos)                        /*!<Update disable*/
#define  TIM_CR1_UDIS                             TIM_CR1_UDIS_Msk
#define  TIM_CR1_URS_Pos                          (2)
#define  TIM_CR1_URS_Msk                          (0x1U << TIM_CR1_URS_Pos)                         /*!<Update request source*/
#define  TIM_CR1_URS                              TIM_CR1_URS_Msk
#define  TIM_CR1_OPM_Pos                          (3)
#define  TIM_CR1_OPM_Msk                          (0x1U << TIM_CR1_OPM_Pos)                         /*!<one-pulse mode*/
#define  TIM_CR1_OPM                              TIM_CR1_OPM_Msk
#define  TIM_CR1_DIR_Pos                          (4)
#define  TIM_CR1_DIR_Msk                          (0x1U << TIM_CR1_DIR_Pos)                         /*!<Count direction*/
#define  TIM_CR1_DIR                              TIM_CR1_DIR_Msk
#define  TIM_CR1_CMS_Pos                          (5)
#define  TIM_CR1_CMS_Msk                          (0x3U << TIM_CR1_CMS_Pos)                         /*!<Center alignment mode selection*/
#define  TIM_CR1_CMS                              TIM_CR1_CMS_Msk
#define  TIM_CR1_CMS_0                            (0x1U << TIM_CR1_CMS_Pos) 
#define  TIM_CR1_CMS_1                            (0x2U << TIM_CR1_CMS_Pos) 
#define  TIM_CR1_ARPE_Pos                         (7)
#define  TIM_CR1_ARPE_Msk                         (0x1U << TIM_CR1_ARPE_Pos)                        /*!<Auto reload preload enable*/
#define  TIM_CR1_ARPE                             TIM_CR1_ARPE_Msk
#define  TIM_CR1_CKD_Pos                          (8)
#define  TIM_CR1_CKD_Msk                          (0x3U << TIM_CR1_CKD_Pos)                         /*!<Clock division*/
#define  TIM_CR1_CKD                              TIM_CR1_CKD_Msk
#define  TIM_CR1_CKD_0                            (0x1U << TIM_CR1_CKD_Pos) 
#define  TIM_CR1_CKD_1                            (0x2U << TIM_CR1_CKD_Pos) 

/**
  * @brief TIM_CR2 Register Bit Definition
  */
#define  TIM_CR2_CCPC_Pos                         (0)
#define  TIM_CR2_CCPC_Msk                         (0x1U << TIM_CR2_CCPC_Pos)                        /*!<Compare preloaded control bit*/
#define  TIM_CR2_CCPC                             TIM_CR2_CCPC_Msk
#define  TIM_CR2_CCUS_Pos                         (2)
#define  TIM_CR2_CCUS_Msk                         (0x1U << TIM_CR2_CCUS_Pos)                        /*!<Compare control update selection*/
#define  TIM_CR2_CCUS                             TIM_CR2_CCUS_Msk
#define  TIM_CR2_MMS_Pos                          (4)
#define  TIM_CR2_MMS_Msk                          (0x7U << TIM_CR2_MMS_Pos)                         /*!<Master mode selection*/
#define  TIM_CR2_MMS                              TIM_CR2_MMS_Msk
#define  TIM_CR2_MMS_0                            (0x1U << TIM_CR2_MMS_Pos) 
#define  TIM_CR2_MMS_1                            (0x2U << TIM_CR2_MMS_Pos) 
#define  TIM_CR2_MMS_2                            (0x4U << TIM_CR2_MMS_Pos) 
#define  TIM_CR2_TI1S_Pos                         (7)
#define  TIM_CR2_TI1S_Msk                         (0x1U << TIM_CR2_TI1S_Pos)                        /*!<TI1 selection*/
#define  TIM_CR2_TI1S                             TIM_CR2_TI1S_Msk
#define  TIM_CR2_OIS1_Pos                         (8)
#define  TIM_CR2_OIS1_Msk                         (0x1U << TIM_CR2_OIS1_Pos)                        /*!<(Output idle state 1) (OC1 output)*/
#define  TIM_CR2_OIS1                             TIM_CR2_OIS1_Msk
#define  TIM_CR2_OIS1N_Pos                        (9)
#define  TIM_CR2_OIS1N_Msk                        (0x1U << TIM_CR2_OIS1N_Pos)                       /*!<(Output idle state 1) (OC1N output)*/
#define  TIM_CR2_OIS1N                            TIM_CR2_OIS1N_Msk
#define  TIM_CR2_OIS2_Pos                         (10)
#define  TIM_CR2_OIS2_Msk                         (0x1U << TIM_CR2_OIS2_Pos)                        /*!<Output idle state 2 (OC2 output). Refer to OIS1 bit.*/
#define  TIM_CR2_OIS2                             TIM_CR2_OIS2_Msk
#define  TIM_CR2_OIS2N_Pos                        (11)
#define  TIM_CR2_OIS2N_Msk                        (0x1U << TIM_CR2_OIS2N_Pos)                       /*!<Output idle state 2 (OC2N output). Refer to OIS1N bit.*/
#define  TIM_CR2_OIS2N                            TIM_CR2_OIS2N_Msk
#define  TIM_CR2_OIS3_Pos                         (12)
#define  TIM_CR2_OIS3_Msk                         (0x1U << TIM_CR2_OIS3_Pos)                        /*!<Output idle state 3 (OC3 output). Refer to OIS1 bit.*/
#define  TIM_CR2_OIS3                             TIM_CR2_OIS3_Msk
#define  TIM_CR2_OIS3N_Pos                        (13)
#define  TIM_CR2_OIS3N_Msk                        (0x1U << TIM_CR2_OIS3N_Pos)                       /*!<Output idle state 3 (OC3N output). Refer to OIS1N bit.*/
#define  TIM_CR2_OIS3N                            TIM_CR2_OIS3N_Msk
#define  TIM_CR2_OIS4_Pos                         (14)
#define  TIM_CR2_OIS4_Msk                         (0x1U << TIM_CR2_OIS4_Pos)                        /*!<Output idle state 4 (OC4 output). Refer to OIS1 bit.*/
#define  TIM_CR2_OIS4                             TIM_CR2_OIS4_Msk

/**
  * @brief TIM_SMCR Register Bit Definition
  */
#define  TIM_SMCR_SMS_Pos                         (0)
#define  TIM_SMCR_SMS_Msk                         (0x7U << TIM_SMCR_SMS_Pos)                        /*!<Slave mode selection*/
#define  TIM_SMCR_SMS                             TIM_SMCR_SMS_Msk
#define  TIM_SMCR_SMS_0                           (0x1U << TIM_SMCR_SMS_Pos) 
#define  TIM_SMCR_SMS_1                           (0x2U << TIM_SMCR_SMS_Pos) 
#define  TIM_SMCR_SMS_2                           (0x4U << TIM_SMCR_SMS_Pos) 
#define  TIM_SMCR_TS_Pos                          (4)
#define  TIM_SMCR_TS_Msk                          (0x7U << TIM_SMCR_TS_Pos)                         /*!<Trigger selection*/
#define  TIM_SMCR_TS                              TIM_SMCR_TS_Msk
#define  TIM_SMCR_TS_0                            (0x1U << TIM_SMCR_TS_Pos) 
#define  TIM_SMCR_TS_1                            (0x2U << TIM_SMCR_TS_Pos) 
#define  TIM_SMCR_TS_2                            (0x4U << TIM_SMCR_TS_Pos) 
#define  TIM_SMCR_MSM_Pos                         (7)
#define  TIM_SMCR_MSM_Msk                         (0x1U << TIM_SMCR_MSM_Pos)                        /*!<Master/slave mode*/
#define  TIM_SMCR_MSM                             TIM_SMCR_MSM_Msk

/**
  * @brief TIM_DIER Register Bit Definition
  */
#define  TIM_DIER_UIE_Pos                         (0)
#define  TIM_DIER_UIE_Msk                         (0x1U << TIM_DIER_UIE_Pos)                        /*!<Enable update interrupt*/
#define  TIM_DIER_UIE                             TIM_DIER_UIE_Msk
#define  TIM_DIER_CC1IE_Pos                       (1)
#define  TIM_DIER_CC1IE_Msk                       (0x1U << TIM_DIER_CC1IE_Pos)                      /*!<Enable capture/compare 1 interrupt*/
#define  TIM_DIER_CC1IE                           TIM_DIER_CC1IE_Msk
#define  TIM_DIER_CC2IE_Pos                       (2)
#define  TIM_DIER_CC2IE_Msk                       (0x1U << TIM_DIER_CC2IE_Pos)                      /*!<Enable capture/compare 2 interrupt*/
#define  TIM_DIER_CC2IE                           TIM_DIER_CC2IE_Msk
#define  TIM_DIER_CC3IE_Pos                       (3)
#define  TIM_DIER_CC3IE_Msk                       (0x1U << TIM_DIER_CC3IE_Pos)                      /*!<Enable capture/compare 3 interrupt*/
#define  TIM_DIER_CC3IE                           TIM_DIER_CC3IE_Msk
#define  TIM_DIER_CC4IE_Pos                       (4)
#define  TIM_DIER_CC4IE_Msk                       (0x1U << TIM_DIER_CC4IE_Pos)                      /*!<Enable capture/compare 4 interrupt*/
#define  TIM_DIER_CC4IE                           TIM_DIER_CC4IE_Msk
#define  TIM_DIER_COMIE_Pos                       (5)
#define  TIM_DIER_COMIE_Msk                       (0x1U << TIM_DIER_COMIE_Pos)                      /*!<Enable COM interrupt*/
#define  TIM_DIER_COMIE                           TIM_DIER_COMIE_Msk
#define  TIM_DIER_TIE_Pos                         (6)
#define  TIM_DIER_TIE_Msk                         (0x1U << TIM_DIER_TIE_Pos)                        /*!<Trigger interrupt enable*/
#define  TIM_DIER_TIE                             TIM_DIER_TIE_Msk
#define  TIM_DIER_BIE_Pos                         (7)
#define  TIM_DIER_BIE_Msk                         (0x1U << TIM_DIER_BIE_Pos)                        /*!<Break interrupt enable*/
#define  TIM_DIER_BIE                             TIM_DIER_BIE_Msk
#define  TIM_DIER_CC5IE_Pos                       (16)
#define  TIM_DIER_CC5IE_Msk                       (0x1U << TIM_DIER_CC5IE_Pos)                      /*!<Compare 5 interrupt enable*/
#define  TIM_DIER_CC5IE                           TIM_DIER_CC5IE_Msk

/**
  * @brief TIM_SR Register Bit Definition
  */
#define  TIM_SR_UIF_Pos                           (0)
#define  TIM_SR_UIF_Msk                           (0x1U << TIM_SR_UIF_Pos)                          /*!<Update interrupt flag*/
#define  TIM_SR_UIF                               TIM_SR_UIF_Msk
#define  TIM_SR_CC1IF_Pos                         (1)
#define  TIM_SR_CC1IF_Msk                         (0x1U << TIM_SR_CC1IF_Pos)                        /*!<Capture/compare 1 interrupt flag*/
#define  TIM_SR_CC1IF                             TIM_SR_CC1IF_Msk
#define  TIM_SR_CC2IF_Pos                         (2)
#define  TIM_SR_CC2IF_Msk                         (0x1U << TIM_SR_CC2IF_Pos)                        /*!<Capture/compare 2 interrupt flag*/
#define  TIM_SR_CC2IF                             TIM_SR_CC2IF_Msk
#define  TIM_SR_CC3IF_Pos                         (3)
#define  TIM_SR_CC3IF_Msk                         (0x1U << TIM_SR_CC3IF_Pos)                        /*!<Capture/compare 3 interrupt flag*/
#define  TIM_SR_CC3IF                             TIM_SR_CC3IF_Msk
#define  TIM_SR_CC4IF_Pos                         (4)
#define  TIM_SR_CC4IF_Msk                         (0x1U << TIM_SR_CC4IF_Pos)                        /*!<Capture/compare 4 interrupt flag*/
#define  TIM_SR_CC4IF                             TIM_SR_CC4IF_Msk
#define  TIM_SR_COMIF_Pos                         (5)
#define  TIM_SR_COMIF_Msk                         (0x1U << TIM_SR_COMIF_Pos)                        /*!<COM interrupt flag*/
#define  TIM_SR_COMIF                             TIM_SR_COMIF_Msk
#define  TIM_SR_TIF_Pos                           (6)
#define  TIM_SR_TIF_Msk                           (0x1U << TIM_SR_TIF_Pos)                          /*!<Trigger interrupt flag*/
#define  TIM_SR_TIF                               TIM_SR_TIF_Msk
#define  TIM_SR_BIF_Pos                           (7)
#define  TIM_SR_BIF_Msk                           (0x1U << TIM_SR_BIF_Pos)                          /*!<Break interrupt flag*/
#define  TIM_SR_BIF                               TIM_SR_BIF_Msk
#define  TIM_SR_CC1OF_Pos                         (9)
#define  TIM_SR_CC1OF_Msk                         (0x1U << TIM_SR_CC1OF_Pos)                        /*!<Capture/compare 1 over capture flag*/
#define  TIM_SR_CC1OF                             TIM_SR_CC1OF_Msk
#define  TIM_SR_CC2OF_Pos                         (10)
#define  TIM_SR_CC2OF_Msk                         (0x1U << TIM_SR_CC2OF_Pos)                        /*!<Capture/compare 2 over capture flag*/
#define  TIM_SR_CC2OF                             TIM_SR_CC2OF_Msk
#define  TIM_SR_CC3OF_Pos                         (11)
#define  TIM_SR_CC3OF_Msk                         (0x1U << TIM_SR_CC3OF_Pos)                        /*!<Capture/compare 3 over capture flag*/
#define  TIM_SR_CC3OF                             TIM_SR_CC3OF_Msk
#define  TIM_SR_CC4OF_Pos                         (12)
#define  TIM_SR_CC4OF_Msk                         (0x1U << TIM_SR_CC4OF_Pos)                        /*!<Capture/compare 4 over capture flag*/
#define  TIM_SR_CC4OF                             TIM_SR_CC4OF_Msk
#define  TIM_SR_CC5IF_Pos                         (16)
#define  TIM_SR_CC5IF_Msk                         (0x1U << TIM_SR_CC5IF_Pos)                        /*!<Compare 5 interrupt flag*/
#define  TIM_SR_CC5IF                             TIM_SR_CC5IF_Msk

/**
  * @brief TIM_EGR Register Bit Definition
  */
#define  TIM_EGR_UG_Pos                           (0)
#define  TIM_EGR_UG_Msk                           (0x1U << TIM_EGR_UG_Pos)                          /*!<Update event generation*/
#define  TIM_EGR_UG                               TIM_EGR_UG_Msk
#define  TIM_EGR_CC1G_Pos                         (1)
#define  TIM_EGR_CC1G_Msk                         (0x1U << TIM_EGR_CC1G_Pos)                        /*!<Capture/compare 1 generation*/
#define  TIM_EGR_CC1G                             TIM_EGR_CC1G_Msk
#define  TIM_EGR_CC2G_Pos                         (2)
#define  TIM_EGR_CC2G_Msk                         (0x1U << TIM_EGR_CC2G_Pos)                        /*!<Capture/compare 2 generation*/
#define  TIM_EGR_CC2G                             TIM_EGR_CC2G_Msk
#define  TIM_EGR_CC3G_Pos                         (3)
#define  TIM_EGR_CC3G_Msk                         (0x1U << TIM_EGR_CC3G_Pos)                        /*!<Capture/compare 3 generation*/
#define  TIM_EGR_CC3G                             TIM_EGR_CC3G_Msk
#define  TIM_EGR_CC4G_Pos                         (4)
#define  TIM_EGR_CC4G_Msk                         (0x1U << TIM_EGR_CC4G_Pos)                        /*!<Capture/compare 4 generation*/
#define  TIM_EGR_CC4G                             TIM_EGR_CC4G_Msk
#define  TIM_EGR_COMG_Pos                         (5)
#define  TIM_EGR_COMG_Msk                         (0x1U << TIM_EGR_COMG_Pos)                        /*!<Compare control update generation*/
#define  TIM_EGR_COMG                             TIM_EGR_COMG_Msk
#define  TIM_EGR_TG_Pos                           (6)
#define  TIM_EGR_TG_Msk                           (0x1U << TIM_EGR_TG_Pos)                          /*!<Trigger generation*/
#define  TIM_EGR_TG                               TIM_EGR_TG_Msk
#define  TIM_EGR_BG_Pos                           (7)
#define  TIM_EGR_BG_Msk                           (0x1U << TIM_EGR_BG_Pos)                          /*!<Break generation*/
#define  TIM_EGR_BG                               TIM_EGR_BG_Msk
#define  TIM_EGR_CC5G_Pos                         (16)
#define  TIM_EGR_CC5G_Msk                         (0x1U << TIM_EGR_CC5G_Pos)                        /*!<Compare 5 generation*/
#define  TIM_EGR_CC5G                             TIM_EGR_CC5G_Msk

/**
  * @brief TIM_CCMR1 Register Bit Definition
  */

/* CCMR1 */
#define  TIM_CCMR1_CC1S_Pos                       (0)
#define  TIM_CCMR1_CC1S_Msk                       (0x3U << TIM_CCMR1_CC1S_Pos)                      /*!<Channel 1 capture/compare selection*/
#define  TIM_CCMR1_CC1S                           TIM_CCMR1_CC1S_Msk
#define  TIM_CCMR1_CC1S_0                         (0x1U << TIM_CCMR1_CC1S_Pos) 
#define  TIM_CCMR1_CC1S_1                         (0x2U << TIM_CCMR1_CC1S_Pos) 
#define  TIM_CCMR1_OC1FE_Pos                      (2)
#define  TIM_CCMR1_OC1FE_Msk                      (0x1U << TIM_CCMR1_OC1FE_Pos)                     /*!<Channel 1 output compare quick enable*/
#define  TIM_CCMR1_OC1FE                          TIM_CCMR1_OC1FE_Msk
#define  TIM_CCMR1_IC1PSC_Pos                     (2)
#define  TIM_CCMR1_IC1PSC_Msk                     (0x3U << TIM_CCMR1_IC1PSC_Pos)                    /*!<Channel 1 input/capture prescaler*/
#define  TIM_CCMR1_IC1PSC                         TIM_CCMR1_IC1PSC_Msk
#define  TIM_CCMR1_IC1PSC_0                       (0x1U << TIM_CCMR1_IC1PSC_Pos) 
#define  TIM_CCMR1_IC1PSC_1                       (0x2U << TIM_CCMR1_IC1PSC_Pos) 
#define  TIM_CCMR1_OC1PE_Pos                      (3)
#define  TIM_CCMR1_OC1PE_Msk                      (0x1U << TIM_CCMR1_OC1PE_Pos)                     /*!<Channel 1 output compare preload enable*/
#define  TIM_CCMR1_OC1PE                          TIM_CCMR1_OC1PE_Msk
#define  TIM_CCMR1_OC1M_Pos                       (4)
#define  TIM_CCMR1_OC1M_Msk                       (0x7U << TIM_CCMR1_OC1M_Pos)                      /*!<Channel 1 output compare mode*/
#define  TIM_CCMR1_OC1M                           TIM_CCMR1_OC1M_Msk
#define  TIM_CCMR1_OC1M_0                         (0x1U << TIM_CCMR1_OC1M_Pos) 
#define  TIM_CCMR1_OC1M_1                         (0x2U << TIM_CCMR1_OC1M_Pos) 
#define  TIM_CCMR1_OC1M_2                         (0x4U << TIM_CCMR1_OC1M_Pos) 
#define  TIM_CCMR1_IC1F_Pos                       (4)
#define  TIM_CCMR1_IC1F_Msk                       (0xFU << TIM_CCMR1_IC1F_Pos)                      /*!<Channel 1 input capture filter*/
#define  TIM_CCMR1_IC1F                           TIM_CCMR1_IC1F_Msk
#define  TIM_CCMR1_IC1F_0                         (0x1U << TIM_CCMR1_IC1F_Pos) 
#define  TIM_CCMR1_IC1F_1                         (0x2U << TIM_CCMR1_IC1F_Pos) 
#define  TIM_CCMR1_IC1F_2                         (0x4U << TIM_CCMR1_IC1F_Pos) 
#define  TIM_CCMR1_IC1F_3                         (0x8U << TIM_CCMR1_IC1F_Pos) 
#define  TIM_CCMR1_CC2S_Pos                       (8)
#define  TIM_CCMR1_CC2S_Msk                       (0x3U << TIM_CCMR1_CC2S_Pos)                      /*!<Channel 2 capture/compare 2 selection*/
#define  TIM_CCMR1_CC2S                           TIM_CCMR1_CC2S_Msk
#define  TIM_CCMR1_CC2S_0                         (0x1U << TIM_CCMR1_CC2S_Pos) 
#define  TIM_CCMR1_CC2S_1                         (0x2U << TIM_CCMR1_CC2S_Pos) 
#define  TIM_CCMR1_OC2FE_Pos                      (10)
#define  TIM_CCMR1_OC2FE_Msk                      (0x1U << TIM_CCMR1_OC2FE_Pos)                     /*!<Channel 2 output and compare quick enable*/
#define  TIM_CCMR1_OC2FE                          TIM_CCMR1_OC2FE_Msk
#define  TIM_CCMR1_IC2PSC_Pos                     (10)
#define  TIM_CCMR1_IC2PSC_Msk                     (0x3U << TIM_CCMR1_IC2PSC_Pos)                    /*!<Input/capture 2 prescaler*/
#define  TIM_CCMR1_IC2PSC                         TIM_CCMR1_IC2PSC_Msk
#define  TIM_CCMR1_IC2PSC_0                       (0x1U << TIM_CCMR1_IC2PSC_Pos) 
#define  TIM_CCMR1_IC2PSC_1                       (0x2U << TIM_CCMR1_IC2PSC_Pos) 
#define  TIM_CCMR1_OC2PE_Pos                      (11)
#define  TIM_CCMR1_OC2PE_Msk                      (0x1U << TIM_CCMR1_OC2PE_Pos)                     /*!<Channel 2 output and compare preload enable*/
#define  TIM_CCMR1_OC2PE                          TIM_CCMR1_OC2PE_Msk
#define  TIM_CCMR1_OC2M_Pos                       (12)
#define  TIM_CCMR1_OC2M_Msk                       (0x7U << TIM_CCMR1_OC2M_Pos)                      /*!<Channel 2 output and compare mode*/
#define  TIM_CCMR1_OC2M                           TIM_CCMR1_OC2M_Msk
#define  TIM_CCMR1_OC2M_0                         (0x1U << TIM_CCMR1_OC2M_Pos) 
#define  TIM_CCMR1_OC2M_1                         (0x2U << TIM_CCMR1_OC2M_Pos) 
#define  TIM_CCMR1_OC2M_2                         (0x4U << TIM_CCMR1_OC2M_Pos) 
#define  TIM_CCMR1_IC2F_Pos                       (12)
#define  TIM_CCMR1_IC2F_Msk                       (0xFU << TIM_CCMR1_IC2F_Pos)                      /*!<Input capture 2 filter*/
#define  TIM_CCMR1_IC2F                           TIM_CCMR1_IC2F_Msk
#define  TIM_CCMR1_IC2F_0                         (0x1U << TIM_CCMR1_IC2F_Pos) 
#define  TIM_CCMR1_IC2F_1                         (0x2U << TIM_CCMR1_IC2F_Pos) 
#define  TIM_CCMR1_IC2F_2                         (0x4U << TIM_CCMR1_IC2F_Pos) 
#define  TIM_CCMR1_IC2F_3                         (0x8U << TIM_CCMR1_IC2F_Pos) 

/**
  * @brief TIM_CCMR2 Register Bit Definition
  */

/* CCMR2 */
#define  TIM_CCMR2_CC3S_Pos                       (0)
#define  TIM_CCMR2_CC3S_Msk                       (0x3U << TIM_CCMR2_CC3S_Pos)                      /*!<Channel 3 capture/compare selection*/
#define  TIM_CCMR2_CC3S                           TIM_CCMR2_CC3S_Msk
#define  TIM_CCMR2_CC3S_0                         (0x1U << TIM_CCMR2_CC3S_Pos) 
#define  TIM_CCMR2_CC3S_1                         (0x2U << TIM_CCMR2_CC3S_Pos) 
#define  TIM_CCMR2_OC3FE_Pos                      (2)
#define  TIM_CCMR2_OC3FE_Msk                      (0x1U << TIM_CCMR2_OC3FE_Pos)                     /*!<Channel 3 output compare quick enable*/
#define  TIM_CCMR2_OC3FE                          TIM_CCMR2_OC3FE_Msk
#define  TIM_CCMR2_IC3PSC_Pos                     (2)
#define  TIM_CCMR2_IC3PSC_Msk                     (0x3U << TIM_CCMR2_IC3PSC_Pos)                    /*!<Channel 3 input/capture prescaler*/
#define  TIM_CCMR2_IC3PSC                         TIM_CCMR2_IC3PSC_Msk
#define  TIM_CCMR2_IC3PSC_0                       (0x1U << TIM_CCMR2_IC3PSC_Pos) 
#define  TIM_CCMR2_IC3PSC_1                       (0x2U << TIM_CCMR2_IC3PSC_Pos) 
#define  TIM_CCMR2_OC3PE_Pos                      (3)
#define  TIM_CCMR2_OC3PE_Msk                      (0x1U << TIM_CCMR2_OC3PE_Pos)                     /*!<Channel 3 output compare preload enable*/
#define  TIM_CCMR2_OC3PE                          TIM_CCMR2_OC3PE_Msk
#define  TIM_CCMR2_OC3M_Pos                       (4)
#define  TIM_CCMR2_OC3M_Msk                       (0x7U << TIM_CCMR2_OC3M_Pos)                      /*!<Channel 3 output compare mode*/
#define  TIM_CCMR2_OC3M                           TIM_CCMR2_OC3M_Msk
#define  TIM_CCMR2_OC3M_0                         (0x1U << TIM_CCMR2_OC3M_Pos) 
#define  TIM_CCMR2_OC3M_1                         (0x2U << TIM_CCMR2_OC3M_Pos) 
#define  TIM_CCMR2_OC3M_2                         (0x4U << TIM_CCMR2_OC3M_Pos) 
#define  TIM_CCMR2_IC3F_Pos                       (4)
#define  TIM_CCMR2_IC3F_Msk                       (0xFU << TIM_CCMR2_IC3F_Pos)                      /*!<Channel 3 input capture filter*/
#define  TIM_CCMR2_IC3F                           TIM_CCMR2_IC3F_Msk
#define  TIM_CCMR2_IC3F_0                         (0x1U << TIM_CCMR2_IC3F_Pos) 
#define  TIM_CCMR2_IC3F_1                         (0x2U << TIM_CCMR2_IC3F_Pos) 
#define  TIM_CCMR2_IC3F_2                         (0x4U << TIM_CCMR2_IC3F_Pos) 
#define  TIM_CCMR2_IC3F_3                         (0x8U << TIM_CCMR2_IC3F_Pos) 
#define  TIM_CCMR2_CC4S_Pos                       (8)
#define  TIM_CCMR2_CC4S_Msk                       (0x3U << TIM_CCMR2_CC4S_Pos)                      /*!<Channel 4 capture/compare selection*/
#define  TIM_CCMR2_CC4S                           TIM_CCMR2_CC4S_Msk
#define  TIM_CCMR2_CC4S_0                         (0x1U << TIM_CCMR2_CC4S_Pos) 
#define  TIM_CCMR2_CC4S_1                         (0x2U << TIM_CCMR2_CC4S_Pos) 
#define  TIM_CCMR2_OC4FE_Pos                      (10)
#define  TIM_CCMR2_OC4FE_Msk                      (0x1U << TIM_CCMR2_OC4FE_Pos)                     /*!<Refer to OC3PE description*/
#define  TIM_CCMR2_OC4FE                          TIM_CCMR2_OC4FE_Msk
#define  TIM_CCMR2_IC4PSC_Pos                     (10)
#define  TIM_CCMR2_IC4PSC_Msk                     (0x3U << TIM_CCMR2_IC4PSC_Pos)                    /*!<Input/capture 4 prescaler*/
#define  TIM_CCMR2_IC4PSC                         TIM_CCMR2_IC4PSC_Msk
#define  TIM_CCMR2_IC4PSC_0                       (0x1U << TIM_CCMR2_IC4PSC_Pos) 
#define  TIM_CCMR2_IC4PSC_1                       (0x2U << TIM_CCMR2_IC4PSC_Pos) 
#define  TIM_CCMR2_OC4PE_Pos                      (11)
#define  TIM_CCMR2_OC4PE_Msk                      (0x1U << TIM_CCMR2_OC4PE_Pos)                     /*!<Channel 4 output compare preload enable*/
#define  TIM_CCMR2_OC4PE                          TIM_CCMR2_OC4PE_Msk
#define  TIM_CCMR2_OC4M_Pos                       (12)
#define  TIM_CCMR2_OC4M_Msk                       (0x7U << TIM_CCMR2_OC4M_Pos)                      /*!<Channel 4 output compare mode*/
#define  TIM_CCMR2_OC4M                           TIM_CCMR2_OC4M_Msk
#define  TIM_CCMR2_OC4M_0                         (0x1U << TIM_CCMR2_OC4M_Pos) 
#define  TIM_CCMR2_OC4M_1                         (0x2U << TIM_CCMR2_OC4M_Pos) 
#define  TIM_CCMR2_OC4M_2                         (0x4U << TIM_CCMR2_OC4M_Pos) 
#define  TIM_CCMR2_IC4F_Pos                       (12)
#define  TIM_CCMR2_IC4F_Msk                       (0xFU << TIM_CCMR2_IC4F_Pos)                      /*!<Input capture 4 filter*/
#define  TIM_CCMR2_IC4F                           TIM_CCMR2_IC4F_Msk
#define  TIM_CCMR2_IC4F_0                         (0x1U << TIM_CCMR2_IC4F_Pos) 
#define  TIM_CCMR2_IC4F_1                         (0x2U << TIM_CCMR2_IC4F_Pos) 
#define  TIM_CCMR2_IC4F_2                         (0x4U << TIM_CCMR2_IC4F_Pos) 
#define  TIM_CCMR2_IC4F_3                         (0x8U << TIM_CCMR2_IC4F_Pos) 

/**
  * @brief TIM_CCER Register Bit Definition
  */
#define  TIM_CCER_CC1E_Pos                        (0)
#define  TIM_CCER_CC1E_Msk                        (0x1U << TIM_CCER_CC1E_Pos)                       /*!<Channel 1 input/capture output enable*/
#define  TIM_CCER_CC1E                            TIM_CCER_CC1E_Msk
#define  TIM_CCER_CC1P_Pos                        (1)
#define  TIM_CCER_CC1P_Msk                        (0x1U << TIM_CCER_CC1P_Pos)                       /*!<Channel 1 input/capture output polarity*/
#define  TIM_CCER_CC1P                            TIM_CCER_CC1P_Msk
#define  TIM_CCER_CC1NE_Pos                       (2)
#define  TIM_CCER_CC1NE_Msk                       (0x1U << TIM_CCER_CC1NE_Pos)                      /*!<Channel 1 complementary output enable*/
#define  TIM_CCER_CC1NE                           TIM_CCER_CC1NE_Msk
#define  TIM_CCER_CC1NP_Pos                       (3)
#define  TIM_CCER_CC1NP_Msk                       (0x1U << TIM_CCER_CC1NP_Pos)                      /*!<Channel 1 input/capture complementary output polarity*/
#define  TIM_CCER_CC1NP                           TIM_CCER_CC1NP_Msk
#define  TIM_CCER_CC2E_Pos                        (4)
#define  TIM_CCER_CC2E_Msk                        (0x1U << TIM_CCER_CC2E_Pos)                       /*!<Channel 2 input/capture output enable*/
#define  TIM_CCER_CC2E                            TIM_CCER_CC2E_Msk
#define  TIM_CCER_CC2P_Pos                        (5)
#define  TIM_CCER_CC2P_Msk                        (0x1U << TIM_CCER_CC2P_Pos)                       /*!<Channel 2 input capture output polarity*/
#define  TIM_CCER_CC2P                            TIM_CCER_CC2P_Msk
#define  TIM_CCER_CC2NE_Pos                       (6)
#define  TIM_CCER_CC2NE_Msk                       (0x1U << TIM_CCER_CC2NE_Pos)                      /*!<Channel 2 complementary output enable*/
#define  TIM_CCER_CC2NE                           TIM_CCER_CC2NE_Msk
#define  TIM_CCER_CC2NP_Pos                       (7)
#define  TIM_CCER_CC2NP_Msk                       (0x1U << TIM_CCER_CC2NP_Pos)                      /*!<Channel 2 input/capture complementary output polarity*/
#define  TIM_CCER_CC2NP                           TIM_CCER_CC2NP_Msk
#define  TIM_CCER_CC3E_Pos                        (8)
#define  TIM_CCER_CC3E_Msk                        (0x1U << TIM_CCER_CC3E_Pos)                       /*!<Channel 3 input/capture output enable*/
#define  TIM_CCER_CC3E                            TIM_CCER_CC3E_Msk
#define  TIM_CCER_CC3P_Pos                        (9)
#define  TIM_CCER_CC3P_Msk                        (0x1U << TIM_CCER_CC3P_Pos)                       /*!<Channel 3 input capture output polarity*/
#define  TIM_CCER_CC3P                            TIM_CCER_CC3P_Msk
#define  TIM_CCER_CC3NE_Pos                       (10)
#define  TIM_CCER_CC3NE_Msk                       (0x1U << TIM_CCER_CC3NE_Pos)                      /*!<Channel 3 complementary output enable*/
#define  TIM_CCER_CC3NE                           TIM_CCER_CC3NE_Msk
#define  TIM_CCER_CC3NP_Pos                       (11)
#define  TIM_CCER_CC3NP_Msk                       (0x1U << TIM_CCER_CC3NP_Pos)                      /*!<Channel 3 input/capture complementary output polarity*/
#define  TIM_CCER_CC3NP                           TIM_CCER_CC3NP_Msk
#define  TIM_CCER_CC4E_Pos                        (12)
#define  TIM_CCER_CC4E_Msk                        (0x1U << TIM_CCER_CC4E_Pos)                       /*!<Channel 4 capture/compare enable*/
#define  TIM_CCER_CC4E                            TIM_CCER_CC4E_Msk
#define  TIM_CCER_CC4P_Pos                        (13)
#define  TIM_CCER_CC4P_Msk                        (0x1U << TIM_CCER_CC4P_Pos)                       /*!<Channel 4 capture/compare output polarity*/
#define  TIM_CCER_CC4P                            TIM_CCER_CC4P_Msk
#define  TIM_CCER_CC4NP_Pos                       (15)
#define  TIM_CCER_CC4NP_Msk                       (0x1U << TIM_CCER_CC4NP_Pos)                      /*!<Channel 4 input/capture complementary output polarity*/
#define  TIM_CCER_CC4NP                           TIM_CCER_CC4NP_Msk

/**
  * @brief TIM_CNT Register Bit Definition
  */
#define  TIM_CNT_CNT_Pos                          (0)
#define  TIM_CNT_CNT_Msk                          (0xFFFFU << TIM_CNT_CNT_Pos)                      /*!<Counter value*/
#define  TIM_CNT_CNT                              TIM_CNT_CNT_Msk
#define  TIM_CNT_CNT_0                            (0x0001U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_1                            (0x0002U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_2                            (0x0004U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_3                            (0x0008U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_4                            (0x0010U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_5                            (0x0020U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_6                            (0x0040U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_7                            (0x0080U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_8                            (0x0100U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_9                            (0x0200U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_10                           (0x0400U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_11                           (0x0800U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_12                           (0x1000U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_13                           (0x2000U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_14                           (0x4000U << TIM_CNT_CNT_Pos) 
#define  TIM_CNT_CNT_15                           (0x8000U << TIM_CNT_CNT_Pos) 

/**
  * @brief TIM_PSC Register Bit Definition
  */
#define  TIM_PSC_PSC_Pos                          (0)
#define  TIM_PSC_PSC_Msk                          (0xFFFFU << TIM_PSC_PSC_Pos)                      /*!<Prescaler value*/
#define  TIM_PSC_PSC                              TIM_PSC_PSC_Msk
#define  TIM_PSC_PSC_0                            (0x0001U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_1                            (0x0002U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_2                            (0x0004U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_3                            (0x0008U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_4                            (0x0010U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_5                            (0x0020U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_6                            (0x0040U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_7                            (0x0080U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_8                            (0x0100U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_9                            (0x0200U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_10                           (0x0400U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_11                           (0x0800U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_12                           (0x1000U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_13                           (0x2000U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_14                           (0x4000U << TIM_PSC_PSC_Pos) 
#define  TIM_PSC_PSC_15                           (0x8000U << TIM_PSC_PSC_Pos) 

/**
  * @brief TIM_ARR Register Bit Definition
  */
#define  TIM_ARR_ARR_Pos                          (0)
#define  TIM_ARR_ARR_Msk                          (0xFFFFU << TIM_ARR_ARR_Pos)                      /*!<Auto reload value*/
#define  TIM_ARR_ARR                              TIM_ARR_ARR_Msk
#define  TIM_ARR_ARR_0                            (0x0001U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_1                            (0x0002U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_2                            (0x0004U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_3                            (0x0008U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_4                            (0x0010U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_5                            (0x0020U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_6                            (0x0040U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_7                            (0x0080U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_8                            (0x0100U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_9                            (0x0200U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_10                           (0x0400U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_11                           (0x0800U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_12                           (0x1000U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_13                           (0x2000U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_14                           (0x4000U << TIM_ARR_ARR_Pos) 
#define  TIM_ARR_ARR_15                           (0x8000U << TIM_ARR_ARR_Pos) 

/**
  * @brief TIM_RCR Register Bit Definition
  */
#define  TIM_RCR_REP_Pos                          (0)
#define  TIM_RCR_REP_Msk                          (0xFFU << TIM_RCR_REP_Pos)                        /*!<Repeat counter value*/
#define  TIM_RCR_REP                              TIM_RCR_REP_Msk
#define  TIM_RCR_REP_0                            (0x01U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_1                            (0x02U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_2                            (0x04U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_3                            (0x08U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_4                            (0x10U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_5                            (0x20U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_6                            (0x40U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_7                            (0x80U << TIM_RCR_REP_Pos) 
#define  TIM_RCR_REP_CNT_Pos                      (8)
#define  TIM_RCR_REP_CNT_Msk                      (0xFFU << TIM_RCR_REP_CNT_Pos)                    /*!<Real-time value written by the repeat counter*/
#define  TIM_RCR_REP_CNT                          TIM_RCR_REP_CNT_Msk
#define  TIM_RCR_REP_CNT_0                        (0x01U << TIM_RCR_REP_CNT_Pos) 
#define  TIM_RCR_REP_CNT_1                        (0x02U << TIM_RCR_REP_CNT_Pos) 
#define  TIM_RCR_REP_CNT_2                        (0x04U << TIM_RCR_REP_CNT_Pos) 
#define  TIM_RCR_REP_CNT_3                        (0x08U << TIM_RCR_REP_CNT_Pos) 
#define  TIM_RCR_REP_CNT_4                        (0x10U << TIM_RCR_REP_CNT_Pos) 
#define  TIM_RCR_REP_CNT_5                        (0x20U << TIM_RCR_REP_CNT_Pos) 
#define  TIM_RCR_REP_CNT_6                        (0x40U << TIM_RCR_REP_CNT_Pos) 
#define  TIM_RCR_REP_CNT_7                        (0x80U << TIM_RCR_REP_CNT_Pos) 

/**
  * @brief TIM_CCR1 Register Bit Definition
  */
#define  TIM_CCR1_CCR1_Pos                        (0)
#define  TIM_CCR1_CCR1_Msk                        (0xFFFFU << TIM_CCR1_CCR1_Pos)                    /*!<Channel 1 capture/compare value*/
#define  TIM_CCR1_CCR1                            TIM_CCR1_CCR1_Msk
#define  TIM_CCR1_CCR1_0                          (0x0001U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_1                          (0x0002U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_2                          (0x0004U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_3                          (0x0008U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_4                          (0x0010U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_5                          (0x0020U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_6                          (0x0040U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_7                          (0x0080U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_8                          (0x0100U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_9                          (0x0200U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_10                         (0x0400U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_11                         (0x0800U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_12                         (0x1000U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_13                         (0x2000U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_14                         (0x4000U << TIM_CCR1_CCR1_Pos) 
#define  TIM_CCR1_CCR1_15                         (0x8000U << TIM_CCR1_CCR1_Pos) 

/**
  * @brief TIM_CCR2 Register Bit Definition
  */
#define  TIM_CCR2_CCR2_Pos                        (0)
#define  TIM_CCR2_CCR2_Msk                        (0xFFFFU << TIM_CCR2_CCR2_Pos)                    /*!<Channel 2 capture/compare value*/
#define  TIM_CCR2_CCR2                            TIM_CCR2_CCR2_Msk
#define  TIM_CCR2_CCR2_0                          (0x0001U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_1                          (0x0002U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_2                          (0x0004U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_3                          (0x0008U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_4                          (0x0010U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_5                          (0x0020U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_6                          (0x0040U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_7                          (0x0080U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_8                          (0x0100U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_9                          (0x0200U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_10                         (0x0400U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_11                         (0x0800U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_12                         (0x1000U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_13                         (0x2000U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_14                         (0x4000U << TIM_CCR2_CCR2_Pos) 
#define  TIM_CCR2_CCR2_15                         (0x8000U << TIM_CCR2_CCR2_Pos) 

/**
  * @brief TIM_CCR3 Register Bit Definition
  */
#define  TIM_CCR3_CCR3_Pos                        (0)
#define  TIM_CCR3_CCR3_Msk                        (0xFFFFU << TIM_CCR3_CCR3_Pos)                    /*!<Channel 3 capture/compare value*/
#define  TIM_CCR3_CCR3                            TIM_CCR3_CCR3_Msk
#define  TIM_CCR3_CCR3_0                          (0x0001U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_1                          (0x0002U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_2                          (0x0004U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_3                          (0x0008U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_4                          (0x0010U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_5                          (0x0020U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_6                          (0x0040U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_7                          (0x0080U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_8                          (0x0100U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_9                          (0x0200U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_10                         (0x0400U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_11                         (0x0800U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_12                         (0x1000U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_13                         (0x2000U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_14                         (0x4000U << TIM_CCR3_CCR3_Pos) 
#define  TIM_CCR3_CCR3_15                         (0x8000U << TIM_CCR3_CCR3_Pos) 

/**
  * @brief TIM_CCR4 Register Bit Definition
  */
#define  TIM_CCR4_CCR4_Pos                        (0)
#define  TIM_CCR4_CCR4_Msk                        (0xFFFFU << TIM_CCR4_CCR4_Pos)                    /*!<Channel 4 capture/compare value*/
#define  TIM_CCR4_CCR4                            TIM_CCR4_CCR4_Msk
#define  TIM_CCR4_CCR4_0                          (0x0001U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_1                          (0x0002U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_2                          (0x0004U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_3                          (0x0008U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_4                          (0x0010U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_5                          (0x0020U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_6                          (0x0040U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_7                          (0x0080U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_8                          (0x0100U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_9                          (0x0200U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_10                         (0x0400U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_11                         (0x0800U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_12                         (0x1000U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_13                         (0x2000U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_14                         (0x4000U << TIM_CCR4_CCR4_Pos) 
#define  TIM_CCR4_CCR4_15                         (0x8000U << TIM_CCR4_CCR4_Pos) 

/**
  * @brief TIM_BDTR Register Bit Definition
  */
#define  TIM_BDTR_DTG_Pos                         (0)
#define  TIM_BDTR_DTG_Msk                         (0xFFU << TIM_BDTR_DTG_Pos)                       /*!<Dead-time generator setup adjustment*/
#define  TIM_BDTR_DTG                             TIM_BDTR_DTG_Msk
#define  TIM_BDTR_DTG_0                           (0x01U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_DTG_1                           (0x02U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_DTG_2                           (0x04U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_DTG_3                           (0x08U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_DTG_4                           (0x10U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_DTG_5                           (0x20U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_DTG_6                           (0x40U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_DTG_7                           (0x80U << TIM_BDTR_DTG_Pos) 
#define  TIM_BDTR_LOCK_Pos                        (8)
#define  TIM_BDTR_LOCK_Msk                        (0x3U << TIM_BDTR_LOCK_Pos)                       /*!<Lock configuration*/
#define  TIM_BDTR_LOCK                            TIM_BDTR_LOCK_Msk
#define  TIM_BDTR_LOCK_0                          (0x1U << TIM_BDTR_LOCK_Pos) 
#define  TIM_BDTR_LOCK_1                          (0x2U << TIM_BDTR_LOCK_Pos) 
#define  TIM_BDTR_OSSI_Pos                        (10)
#define  TIM_BDTR_OSSI_Msk                        (0x1U << TIM_BDTR_OSSI_Pos)                       /*!<Off state selection in the idle mode*/
#define  TIM_BDTR_OSSI                            TIM_BDTR_OSSI_Msk
#define  TIM_BDTR_OSSR_Pos                        (11)
#define  TIM_BDTR_OSSR_Msk                        (0x1U << TIM_BDTR_OSSR_Pos)                       /*!<Off state selection in the run mode*/
#define  TIM_BDTR_OSSR                            TIM_BDTR_OSSR_Msk
#define  TIM_BDTR_BKE_Pos                         (12)
#define  TIM_BDTR_BKE_Msk                         (0x1U << TIM_BDTR_BKE_Pos)                        /*!<Break function enable*/
#define  TIM_BDTR_BKE                             TIM_BDTR_BKE_Msk
#define  TIM_BDTR_BKP_Pos                         (13)
#define  TIM_BDTR_BKP_Msk                         (0x1U << TIM_BDTR_BKP_Pos)                        /*!<Break input polarity*/
#define  TIM_BDTR_BKP                             TIM_BDTR_BKP_Msk
#define  TIM_BDTR_AOE_Pos                         (14)
#define  TIM_BDTR_AOE_Msk                         (0x1U << TIM_BDTR_AOE_Pos)                        /*!<Auto output enable*/
#define  TIM_BDTR_AOE                             TIM_BDTR_AOE_Msk
#define  TIM_BDTR_MOE_Pos                         (15)
#define  TIM_BDTR_MOE_Msk                         (0x1U << TIM_BDTR_MOE_Pos)                        /*!<Main output enable*/
#define  TIM_BDTR_MOE                             TIM_BDTR_MOE_Msk
#define  TIM_BDTR_DOE_Pos                         (16)
#define  TIM_BDTR_DOE_Msk                         (0x1U << TIM_BDTR_DOE_Pos)                        /*!<Direct output enable*/
#define  TIM_BDTR_DOE                             TIM_BDTR_DOE_Msk

/**
  * @brief TIM_OR Register Bit Definition
  */
#define  TIM_OR_ETR_RMP_Pos                       (0)
#define  TIM_OR_ETR_RMP_Msk                       (0x3U << TIM_OR_ETR_RMP_Pos)                      /*!<ETR multiplex*/
#define  TIM_OR_ETR_RMP                           TIM_OR_ETR_RMP_Msk
#define  TIM_OR_ETR_RMP_0                         (0x1U << TIM_OR_ETR_RMP_Pos) 
#define  TIM_OR_ETR_RMP_1                         (0x2U << TIM_OR_ETR_RMP_Pos) 

/**
  * @brief TIM_CCMR3 Register Bit Definition
  */
#define  TIM_CCMR3_OC5PE_Pos                      (3)
#define  TIM_CCMR3_OC5PE_Msk                      (0x1U << TIM_CCMR3_OC5PE_Pos)                     /*!<Output compare 5 preload enable*/
#define  TIM_CCMR3_OC5PE                          TIM_CCMR3_OC5PE_Msk

/**
  * @brief TIM_CCR5 Register Bit Definition
  */
#define  TIM_CCR5_CCR5_Pos                        (0)
#define  TIM_CCR5_CCR5_Msk                        (0xFFFFU << TIM_CCR5_CCR5_Pos)                    /*!<Compare 5 value*/
#define  TIM_CCR5_CCR5                            TIM_CCR5_CCR5_Msk
#define  TIM_CCR5_CCR5_0                          (0x0001U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_1                          (0x0002U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_2                          (0x0004U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_3                          (0x0008U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_4                          (0x0010U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_5                          (0x0020U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_6                          (0x0040U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_7                          (0x0080U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_8                          (0x0100U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_9                          (0x0200U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_10                         (0x0400U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_11                         (0x0800U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_12                         (0x1000U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_13                         (0x2000U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_14                         (0x4000U << TIM_CCR5_CCR5_Pos) 
#define  TIM_CCR5_CCR5_15                         (0x8000U << TIM_CCR5_CCR5_Pos) 

/**
  * @brief TIM_PDER Register Bit Definition
  */
#define  TIM_PDER_CCDREPE_Pos                     (0)
#define  TIM_PDER_CCDREPE_Msk                     (0x1U << TIM_PDER_CCDREPE_Pos)                    /*!<Enable DMA will generate the update request at each underflow or overflow*/
#define  TIM_PDER_CCDREPE                         TIM_PDER_CCDREPE_Msk
#define  TIM_PDER_CCR1_SHIFT_EN_Pos               (1)
#define  TIM_PDER_CCR1_SHIFT_EN_Msk               (0x1U << TIM_PDER_CCR1_SHIFT_EN_Pos)              /*!<Enable channel 1 output PWM phase shift bit*/
#define  TIM_PDER_CCR1_SHIFT_EN                   TIM_PDER_CCR1_SHIFT_EN_Msk
#define  TIM_PDER_CCR2_SHIFT_EN_Pos               (2)
#define  TIM_PDER_CCR2_SHIFT_EN_Msk               (0x1U << TIM_PDER_CCR2_SHIFT_EN_Pos)              /*!<Enable channel 2 output PWM phase shift bit*/
#define  TIM_PDER_CCR2_SHIFT_EN                   TIM_PDER_CCR2_SHIFT_EN_Msk
#define  TIM_PDER_CCR3_SHIFT_EN_Pos               (3)
#define  TIM_PDER_CCR3_SHIFT_EN_Msk               (0x1U << TIM_PDER_CCR3_SHIFT_EN_Pos)              /*!<Enable channel 3 output PWM phase shift bit*/
#define  TIM_PDER_CCR3_SHIFT_EN                   TIM_PDER_CCR3_SHIFT_EN_Msk
#define  TIM_PDER_CCR4_SHIFT_EN_Pos               (4)
#define  TIM_PDER_CCR4_SHIFT_EN_Msk               (0x1U << TIM_PDER_CCR4_SHIFT_EN_Pos)              /*!<Enable channel 4 output PWM phase shift bit*/
#define  TIM_PDER_CCR4_SHIFT_EN                   TIM_PDER_CCR4_SHIFT_EN_Msk
#define  TIM_PDER_CCR5_SHIFT_EN_Pos               (5)
#define  TIM_PDER_CCR5_SHIFT_EN_Msk               (0x1U << TIM_PDER_CCR5_SHIFT_EN_Pos)              /*!<Enable channel 5 output PWM phase shift bit*/
#define  TIM_PDER_CCR5_SHIFT_EN                   TIM_PDER_CCR5_SHIFT_EN_Msk

/**
  * @brief TIM_CCRFALL Register Bit Definition
  */
#define  TIM_CCR1FALL_CCR1FALL_Pos                (0)
#define  TIM_CCR1FALL_CCR1FALL_Msk                (0xFFFFU << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL                    TIM_CCR1FALL_CCR1FALL_Msk                         /*!<Channel x compare value during count down in PWM central alignment mode.PWM phase shift function: Enable PDER register PWM phase shift. According to the required phase shift, configure CCR1FALL and CCRx, PWM exports programmable phase shift waveform, and can shift left or right.*/
#define  TIM_CCR1FALL_CCR1FALL_0                  (0x0001U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_1                  (0x0002U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_2                  (0x0004U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_3                  (0x0008U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_4                  (0x0010U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_5                  (0x0020U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_6                  (0x0040U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_7                  (0x0080U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_8                  (0x0100U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_9                  (0x0200U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_10                 (0x0400U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_11                 (0x0800U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_12                 (0x1000U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_13                 (0x2000U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_14                 (0x4000U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR1FALL_CCR1FALL_15                 (0x8000U << TIM_CCR1FALL_CCR1FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_Pos                (0)
#define  TIM_CCR2FALL_CCR2FALL_Msk                (0xFFFFU << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL                    TIM_CCR2FALL_CCR2FALL_Msk                         /*!<Channel x compare value during count down in PWM central alignment mode.PWM phase shift function: Enable PDER register PWM phase shift. According to the required phase shift, configure CCR2FALL and CCRx, PWM exports programmable phase shift waveform, and can shift left or right.*/
#define  TIM_CCR2FALL_CCR2FALL_0                  (0x0001U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_1                  (0x0002U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_2                  (0x0004U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_3                  (0x0008U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_4                  (0x0010U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_5                  (0x0020U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_6                  (0x0040U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_7                  (0x0080U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_8                  (0x0100U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_9                  (0x0200U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_10                 (0x0400U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_11                 (0x0800U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_12                 (0x1000U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_13                 (0x2000U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_14                 (0x4000U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR2FALL_CCR2FALL_15                 (0x8000U << TIM_CCR2FALL_CCR2FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_Pos                (0)
#define  TIM_CCR3FALL_CCR3FALL_Msk                (0xFFFFU << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL                    TIM_CCR3FALL_CCR3FALL_Msk                         /*!<Channel x compare value during count down in PWM central alignment mode.PWM phase shift function: Enable PDER register PWM phase shift. According to the required phase shift, configure CCR3FALL and CCRx, PWM exports programmable phase shift waveform, and can shift left or right.*/
#define  TIM_CCR3FALL_CCR3FALL_0                  (0x0001U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_1                  (0x0002U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_2                  (0x0004U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_3                  (0x0008U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_4                  (0x0010U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_5                  (0x0020U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_6                  (0x0040U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_7                  (0x0080U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_8                  (0x0100U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_9                  (0x0200U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_10                 (0x0400U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_11                 (0x0800U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_12                 (0x1000U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_13                 (0x2000U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_14                 (0x4000U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR3FALL_CCR3FALL_15                 (0x8000U << TIM_CCR3FALL_CCR3FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_Pos                (0)
#define  TIM_CCR4FALL_CCR4FALL_Msk                (0xFFFFU << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL                    TIM_CCR4FALL_CCR4FALL_Msk                         /*!<Channel x compare value during count down in PWM central alignment mode.PWM phase shift function: Enable PDER register PWM phase shift. According to the required phase shift, configure CCR4FALL and CCRx, PWM exports programmable phase shift waveform, and can shift left or right.*/
#define  TIM_CCR4FALL_CCR4FALL_0                  (0x0001U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_1                  (0x0002U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_2                  (0x0004U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_3                  (0x0008U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_4                  (0x0010U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_5                  (0x0020U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_6                  (0x0040U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_7                  (0x0080U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_8                  (0x0100U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_9                  (0x0200U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_10                 (0x0400U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_11                 (0x0800U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_12                 (0x1000U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_13                 (0x2000U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_14                 (0x4000U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR4FALL_CCR4FALL_15                 (0x8000U << TIM_CCR4FALL_CCR4FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_Pos                (0)
#define  TIM_CCR5FALL_CCR5FALL_Msk                (0xFFFFU << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL                    TIM_CCR5FALL_CCR5FALL_Msk                         /*!<Channel x compare value during count down in PWM central alignment mode.PWM phase shift function: Enable PDER register PWM phase shift. According to the required phase shift, configure CCR5FALL and CCRx, PWM exports programmable phase shift waveform, and can shift left or right.*/
#define  TIM_CCR5FALL_CCR5FALL_0                  (0x0001U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_1                  (0x0002U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_2                  (0x0004U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_3                  (0x0008U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_4                  (0x0010U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_5                  (0x0020U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_6                  (0x0040U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_7                  (0x0080U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_8                  (0x0100U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_9                  (0x0200U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_10                 (0x0400U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_11                 (0x0800U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_12                 (0x1000U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_13                 (0x2000U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_14                 (0x4000U << TIM_CCR5FALL_CCR5FALL_Pos) 
#define  TIM_CCR5FALL_CCR5FALL_15                 (0x8000U << TIM_CCR5FALL_CCR5FALL_Pos) 


#endif

