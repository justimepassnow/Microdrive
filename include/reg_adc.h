/***********************************************************************************************************************
    @file     reg_adc.h
    @author   VV TEAM
    @brief    This flie contains all the ADC's register and its field definition.
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

#ifndef __REG_ADC_H
#define __REG_ADC_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief ADC Base Address Definition
  */
#define  ADC1_BASE                                 0x40012400 /*!<Base Address: 0x40012400*/

/**
  * @brief ADC Register Structure Definition
  */
typedef struct
{
    __IO uint32_t ADDATA;              /*!<ADC Data Register                              offset: 0x00       */
    __IO uint32_t ADCFG;               /*!<ADC Configuration Register                     offset: 0x04       */
    __IO uint32_t ADCR;                /*!<ADC Control Register                           offset: 0x08       */
    __IO uint32_t RESERVED0x0C[1];     /*!<                                               offset: 0x0C       */
    __IO uint32_t ADCMPR;              /*!<ADC Analog Watchdog Compare Register           offset: 0x10       */
    __IO uint32_t ADSTA;               /*!<ADC Status Register                            offset: 0x14       */
    __IO uint32_t ADDR0;               /*!<ADC Channel Data Register                      offset: 0x18       */
    __IO uint32_t ADDR1;               /*!<ADC Channel Data Register                      offset: 0x1C       */
    __IO uint32_t ADDR2;               /*!<ADC Channel Data Register                      offset: 0x20       */
    __IO uint32_t ADDR3;               /*!<ADC Channel Data Register                      offset: 0x24       */
    __IO uint32_t ADDR4;               /*!<ADC Channel Data Register                      offset: 0x28       */
    __IO uint32_t ADDR5;               /*!<ADC Channel Data Register                      offset: 0x2C       */
    __IO uint32_t ADDR6;               /*!<ADC Channel Data Register                      offset: 0x30       */
    __IO uint32_t ADDR7;               /*!<ADC Channel Data Register                      offset: 0x34       */
    __IO uint32_t ADDR8;               /*!<ADC Channel Data Register                      offset: 0x38       */
    __IO uint32_t RESERVED0x3C[8];     /*!<                                               offset: 0x3C~0x58  */
    __IO uint32_t CHANY0;              /*!<ADC Any Channel Selection Register 0           offset: 0x5C       */
    __IO uint32_t CHANY1;              /*!<ADC Any Channel Selection Register 1           offset: 0x60       */
    __IO uint32_t ANY_CFG;             /*!<ADC Any Channel Configuration Register         offset: 0x64       */
    __IO uint32_t ANY_CR;              /*!<ADC Any Channel Control Register               offset: 0x68       */
} ADC_TypeDef;

/**
  * @brief ADC type pointer Definition
  */
#define ADC1                                      ((ADC_TypeDef *)ADC1_BASE)

/**
  * @brief ADC_ADDATA Register Bit Definition
  */
#define  ADC_ADDATA_DATA_Pos                      (0)
#define  ADC_ADDATA_DATA_Msk                      (0xFFFFU << ADC_ADDATA_DATA_Pos) /*!<12-bit A/D conversion result (Transfer data)*/
#define  ADC_ADDATA_DATA                          ADC_ADDATA_DATA_Msk
#define  ADC_ADDATA_DATA_0                        (0x0001U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_1                        (0x0002U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_2                        (0x0004U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_3                        (0x0008U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_4                        (0x0010U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_5                        (0x0020U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_6                        (0x0040U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_7                        (0x0080U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_8                        (0x0100U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_9                        (0x0200U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_10                       (0x0400U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_11                       (0x0800U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_12                       (0x1000U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_13                       (0x2000U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_14                       (0x4000U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_DATA_15                       (0x8000U << ADC_ADDATA_DATA_Pos)
#define  ADC_ADDATA_CHANNELSEL_Pos                (16)
#define  ADC_ADDATA_CHANNELSEL_Msk                (0xFU << ADC_ADDATA_CHANNELSEL_Pos) /*!<4 bits show the channel corresponding to the current data (Channel selection)*/
#define  ADC_ADDATA_CHANNELSEL                    ADC_ADDATA_CHANNELSEL_Msk
#define  ADC_ADDATA_CHANNELSEL_0                  (0x1U << ADC_ADDATA_CHANNELSEL_Pos)
#define  ADC_ADDATA_CHANNELSEL_1                  (0x2U << ADC_ADDATA_CHANNELSEL_Pos)
#define  ADC_ADDATA_CHANNELSEL_2                  (0x4U << ADC_ADDATA_CHANNELSEL_Pos)
#define  ADC_ADDATA_CHANNELSEL_3                  (0x8U << ADC_ADDATA_CHANNELSEL_Pos)
#define  ADC_ADDATA_OVERRUN_Pos                   (20)
#define  ADC_ADDATA_OVERRUN_Msk                   (0x1U << ADC_ADDATA_OVERRUN_Pos) /*!<Data overrun flag (read-only)*/
#define  ADC_ADDATA_OVERRUN                       ADC_ADDATA_OVERRUN_Msk
#define  ADC_ADDATA_VALID_Pos                     (21)
#define  ADC_ADDATA_VALID_Msk                     (0x1U << ADC_ADDATA_VALID_Pos)   /*!<Valid flag for data (read-only)*/
#define  ADC_ADDATA_VALID                         ADC_ADDATA_VALID_Msk

/**
  * @brief ADC_ADCFG Register Bit Definition
  */
#define  ADC_ADCFG_ADEN_Pos                       (0)
#define  ADC_ADCFG_ADEN_Msk                       (0x1U << ADC_ADCFG_ADEN_Pos)    /*!<A/D conversion enable (ADC enable)*/
#define  ADC_ADCFG_ADEN                           ADC_ADCFG_ADEN_Msk
#define  ADC_ADCFG_ADWEN_Pos                      (1)
#define  ADC_ADCFG_ADWEN_Msk                      (0x1U << ADC_ADCFG_ADWEN_Pos)   /*!<ADC window comparison enable*/
#define  ADC_ADCFG_ADWEN                          ADC_ADCFG_ADWEN_Msk
#define  ADC_ADCFG_VSEN_Pos                       (3)
#define  ADC_ADCFG_VSEN_Msk                       (0x1U << ADC_ADCFG_VSEN_Pos)    /*!<Internal reference voltage and temperature sensor enable (Voltage Sensor and Temperature Sensor Enable)*/
#define  ADC_ADCFG_VSEN                           ADC_ADCFG_VSEN_Msk
#define  ADC_ADCFG_ADCPREH_Pos                    (4)
#define  ADC_ADCFG_ADCPREH_Msk                    (0x7U << ADC_ADCFG_ADCPREH_Pos) /*!<ADC Prescaler High Bits*/
#define  ADC_ADCFG_ADCPREH                        ADC_ADCFG_ADCPREH_Msk
#define  ADC_ADCFG_ADCPREH_0                      (0x1U << ADC_ADCFG_ADCPREH_Pos)
#define  ADC_ADCFG_ADCPREH_1                      (0x2U << ADC_ADCFG_ADCPREH_Pos)
#define  ADC_ADCFG_ADCPREH_2                      (0x4U << ADC_ADCFG_ADCPREH_Pos)
#define  ADC_ADCFG_RSLTCTL_Pos                    (7)
#define  ADC_ADCFG_RSLTCTL_Msk                    (0x7U << ADC_ADCFG_RSLTCTL_Pos) /*!<ADC conversion data resolution selection*/
#define  ADC_ADCFG_RSLTCTL                        ADC_ADCFG_RSLTCTL_Msk
#define  ADC_ADCFG_RSLTCTL_0                      (0x1U << ADC_ADCFG_RSLTCTL_Pos)
#define  ADC_ADCFG_RSLTCTL_1                      (0x2U << ADC_ADCFG_RSLTCTL_Pos)
#define  ADC_ADCFG_RSLTCTL_2                      (0x4U << ADC_ADCFG_RSLTCTL_Pos)
#define  ADC_ADCFG_SAMCTL_Pos                     (10)
#define  ADC_ADCFG_SAMCTL_Msk                     (0xFU << ADC_ADCFG_SAMCTL_Pos) /*!<Channel x Sample time selection*/
#define  ADC_ADCFG_SAMCTL                         ADC_ADCFG_SAMCTL_Msk
#define  ADC_ADCFG_SAMCTL_0                       (0x1U << ADC_ADCFG_SAMCTL_Pos)
#define  ADC_ADCFG_SAMCTL_1                       (0x2U << ADC_ADCFG_SAMCTL_Pos)
#define  ADC_ADCFG_SAMCTL_2                       (0x4U << ADC_ADCFG_SAMCTL_Pos)
#define  ADC_ADCFG_SAMCTL_3                       (0x8U << ADC_ADCFG_SAMCTL_Pos)
#define  ADC_ADCFG_ADCPREL_Pos                    (14)
#define  ADC_ADCFG_ADCPREL_Msk                    (0x1U << ADC_ADCFG_ADCPREL_Pos) /*!<ADC Prescaler Low Bits*/
#define  ADC_ADCFG_ADCPREL                        ADC_ADCFG_ADCPREL_Msk

/**
  * @brief ADC_ADCR Register Bit Definition
  */
#define  ADC_ADCR_ADIE_Pos                        (0)
#define  ADC_ADCR_ADIE_Msk                        (0x1U << ADC_ADCR_ADIE_Pos)    /*!<ADC Interrupt Enable*/
#define  ADC_ADCR_ADIE                            ADC_ADCR_ADIE_Msk
#define  ADC_ADCR_AWDIE_Pos                       (1)
#define  ADC_ADCR_AWDIE_Msk                       (0x1U << ADC_ADCR_AWDIE_Pos)   /*!<ADC Window Comparator Interrupt Enable*/
#define  ADC_ADCR_AWDIE                           ADC_ADCR_AWDIE_Msk
#define  ADC_ADCR_TRGEN_Pos                       (2)
#define  ADC_ADCR_TRGEN_Msk                       (0x1U << ADC_ADCR_TRGEN_Pos)   /*!<External Hardware Trigger Sources Enable*/
#define  ADC_ADCR_TRGEN                           ADC_ADCR_TRGEN_Msk
#define  ADC_ADCR_DMAEN_Pos                       (3)
#define  ADC_ADCR_DMAEN_Msk                       (0x1U << ADC_ADCR_DMAEN_Pos)   /*!<Direct Memory Access Enable*/
#define  ADC_ADCR_DMAEN                           ADC_ADCR_DMAEN_Msk
#define  ADC_ADCR_TRGSELL_Pos                     (4)
#define  ADC_ADCR_TRGSELL_Msk                     (0x7U << ADC_ADCR_TRGSELL_Pos) /*!<External trigger selection, bits [18:17,6:4]*/
#define  ADC_ADCR_TRGSELL                         ADC_ADCR_TRGSELL_Msk
#define  ADC_ADCR_TRGSELL_0                       (0x1U << ADC_ADCR_TRGSELL_Pos)
#define  ADC_ADCR_TRGSELL_1                       (0x2U << ADC_ADCR_TRGSELL_Pos)
#define  ADC_ADCR_TRGSELL_2                       (0x4U << ADC_ADCR_TRGSELL_Pos)
#define  ADC_ADCR_ADST_Pos                        (8)
#define  ADC_ADCR_ADST_Msk                        (0x1U << ADC_ADCR_ADST_Pos) /*!<A/D conversion start*/
#define  ADC_ADCR_ADST                            ADC_ADCR_ADST_Msk
#define  ADC_ADCR_ADMD_Pos                        (9)
#define  ADC_ADCR_ADMD_Msk                        (0x3U << ADC_ADCR_ADMD_Pos) /*!<A/D conversion mode (ADC Mode)*/
#define  ADC_ADCR_ADMD                            ADC_ADCR_ADMD_Msk
#define  ADC_ADCR_ADMD_0                          (0x1U << ADC_ADCR_ADMD_Pos)
#define  ADC_ADCR_ADMD_1                          (0x2U << ADC_ADCR_ADMD_Pos)
#define  ADC_ADCR_ALIGN_Pos                       (11)
#define  ADC_ADCR_ALIGN_Msk                       (0x1U << ADC_ADCR_ALIGN_Pos) /*!<Data Alignment*/
#define  ADC_ADCR_ALIGN                           ADC_ADCR_ALIGN_Msk
#define  ADC_ADCR_CMPCH_Pos                       (12)
#define  ADC_ADCR_CMPCH_Msk                       (0xFU << ADC_ADCR_CMPCH_Pos) /*!<Window comparison channel selection*/
#define  ADC_ADCR_CMPCH                           ADC_ADCR_CMPCH_Msk
#define  ADC_ADCR_CMPCH_0                         (0x1U << ADC_ADCR_CMPCH_Pos)
#define  ADC_ADCR_CMPCH_1                         (0x2U << ADC_ADCR_CMPCH_Pos)
#define  ADC_ADCR_CMPCH_2                         (0x4U << ADC_ADCR_CMPCH_Pos)
#define  ADC_ADCR_CMPCH_3                         (0x8U << ADC_ADCR_CMPCH_Pos)
#define  ADC_ADCR_TRGSELH_Pos                     (17)
#define  ADC_ADCR_TRGSELH_Msk                     (0x3U << ADC_ADCR_TRGSELH_Pos) /*!<External Trigger Sources Select For High Bits*/
#define  ADC_ADCR_TRGSELH                         ADC_ADCR_TRGSELH_Msk
#define  ADC_ADCR_TRGSELH_0                       (0x1U << ADC_ADCR_TRGSELH_Pos)
#define  ADC_ADCR_TRGSELH_1                       (0x2U << ADC_ADCR_TRGSELH_Pos)
#define  ADC_ADCR_TRGSHIFT_Pos                    (19)
#define  ADC_ADCR_TRGSHIFT_Msk                    (0x7U << ADC_ADCR_TRGSHIFT_Pos) /*!<External trigger shift sample*/
#define  ADC_ADCR_TRGSHIFT                        ADC_ADCR_TRGSHIFT_Msk
#define  ADC_ADCR_TRGSHIFT_0                      (0x1U << ADC_ADCR_TRGSHIFT_Pos)
#define  ADC_ADCR_TRGSHIFT_1                      (0x2U << ADC_ADCR_TRGSHIFT_Pos)
#define  ADC_ADCR_TRGSHIFT_2                      (0x4U << ADC_ADCR_TRGSHIFT_Pos)
#define  ADC_ADCR_TRG_EDGE_Pos                    (24)
#define  ADC_ADCR_TRG_EDGE_Msk                    (0x3U << ADC_ADCR_TRG_EDGE_Pos) /*!<Trigger Sources Edge Selection*/
#define  ADC_ADCR_TRG_EDGE                        ADC_ADCR_TRG_EDGE_Msk
#define  ADC_ADCR_TRG_EDGE_0                      (0x1U << ADC_ADCR_TRG_EDGE_Pos)
#define  ADC_ADCR_TRG_EDGE_1                      (0x2U << ADC_ADCR_TRG_EDGE_Pos)

/**
  * @brief ADC_ADCMPR Register Bit Definition
  */
#define  ADC_ADCMPR_CMPLDATA_Pos                  (0)
#define  ADC_ADCMPR_CMPLDATA_Msk                  (0xFFFU << ADC_ADCMPR_CMPLDATA_Pos) /*!<Compare data low limit*/
#define  ADC_ADCMPR_CMPLDATA                      ADC_ADCMPR_CMPLDATA_Msk
#define  ADC_ADCMPR_CMPLDATA_0                    (0x001U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_1                    (0x002U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_2                    (0x004U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_3                    (0x008U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_4                    (0x010U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_5                    (0x020U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_6                    (0x040U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_7                    (0x080U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_8                    (0x100U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_9                    (0x200U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_10                   (0x400U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPLDATA_11                   (0x800U << ADC_ADCMPR_CMPLDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_Pos                  (16)
#define  ADC_ADCMPR_CMPHDATA_Msk                  (0xFFFU << ADC_ADCMPR_CMPHDATA_Pos) /*!<Compare data high limit*/
#define  ADC_ADCMPR_CMPHDATA                      ADC_ADCMPR_CMPHDATA_Msk
#define  ADC_ADCMPR_CMPHDATA_0                    (0x001U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_1                    (0x002U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_2                    (0x004U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_3                    (0x008U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_4                    (0x010U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_5                    (0x020U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_6                    (0x040U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_7                    (0x080U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_8                    (0x100U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_9                    (0x200U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_10                   (0x400U << ADC_ADCMPR_CMPHDATA_Pos)
#define  ADC_ADCMPR_CMPHDATA_11                   (0x800U << ADC_ADCMPR_CMPHDATA_Pos)

/**
  * @brief ADC_ADSTA Register Bit Definition
  */
#define  ADC_ADSTA_ADIF_Pos                       (0)
#define  ADC_ADSTA_ADIF_Msk                       (0x1U << ADC_ADSTA_ADIF_Pos)    /*!<ADC interrupt flag*/
#define  ADC_ADSTA_ADIF                           ADC_ADSTA_ADIF_Msk
#define  ADC_ADSTA_AWDIF_Pos                      (1)
#define  ADC_ADSTA_AWDIF_Msk                      (0x1U << ADC_ADSTA_AWDIF_Pos)   /*!<ADC window comparator interrupt flag*/
#define  ADC_ADSTA_AWDIF                          ADC_ADSTA_AWDIF_Msk
#define  ADC_ADSTA_BUSY_Pos                       (2)
#define  ADC_ADSTA_BUSY_Msk                       (0x1U << ADC_ADSTA_BUSY_Pos)    /*!<Non-Injected Conversion Busy/Idle*/
#define  ADC_ADSTA_BUSY                           ADC_ADSTA_BUSY_Msk
#define  ADC_ADSTA_CHANNEL_Pos                    (4)
#define  ADC_ADSTA_CHANNEL_Msk                    (0xFU << ADC_ADSTA_CHANNEL_Pos) /*!<Read-only.*/
#define  ADC_ADSTA_CHANNEL                        ADC_ADSTA_CHANNEL_Msk
#define  ADC_ADSTA_CHANNEL_0                      (0x1U << ADC_ADSTA_CHANNEL_Pos)
#define  ADC_ADSTA_CHANNEL_1                      (0x2U << ADC_ADSTA_CHANNEL_Pos)
#define  ADC_ADSTA_CHANNEL_2                      (0x4U << ADC_ADSTA_CHANNEL_Pos)
#define  ADC_ADSTA_CHANNEL_3                      (0x8U << ADC_ADSTA_CHANNEL_Pos)
#define  ADC_ADSTA_VALID_Pos                      (8)
#define  ADC_ADSTA_VALID_Msk                      (0x1FFU << ADC_ADSTA_VALID_Pos) /*!<Reserved, always read as 0.*/
#define  ADC_ADSTA_VALID                          ADC_ADSTA_VALID_Msk
#define  ADC_ADSTA_VALID_0                        (0x001U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_1                        (0x002U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_2                        (0x004U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_3                        (0x008U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_4                        (0x010U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_5                        (0x020U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_6                        (0x040U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_7                        (0x080U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_VALID_8                        (0x100U << ADC_ADSTA_VALID_Pos)
#define  ADC_ADSTA_OVERRUN_Pos                    (20)
#define  ADC_ADSTA_OVERRUN_Msk                    (0x1FFU << ADC_ADSTA_OVERRUN_Pos) /*!<Data overrun flag for channel 0 ~ 8 (Overrun flag)*/
#define  ADC_ADSTA_OVERRUN                        ADC_ADSTA_OVERRUN_Msk
#define  ADC_ADSTA_OVERRUN_0                      (0x001U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_1                      (0x002U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_2                      (0x004U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_3                      (0x008U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_4                      (0x010U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_5                      (0x020U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_6                      (0x040U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_7                      (0x080U << ADC_ADSTA_OVERRUN_Pos)
#define  ADC_ADSTA_OVERRUN_8                      (0x100U << ADC_ADSTA_OVERRUN_Pos)

/**
  * @brief ADC_ADDR Register Bit Definition
  */
#define  ADC_ADDR_DATA_Pos                        (0)
#define  ADC_ADDR_DATA_Msk                        (0xFFFFU << ADC_ADDR_DATA_Pos) /*!<12-bit A/D conversion result in the channel (Transfer data) Data can be left or right aligned as configured.*/
#define  ADC_ADDR_DATA                            ADC_ADDR_DATA_Msk
#define  ADC_ADDR_DATA_0                          (0x0001U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_1                          (0x0002U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_2                          (0x0004U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_3                          (0x0008U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_4                          (0x0010U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_5                          (0x0020U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_6                          (0x0040U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_7                          (0x0080U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_8                          (0x0100U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_9                          (0x0200U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_10                         (0x0400U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_11                         (0x0800U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_12                         (0x1000U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_13                         (0x2000U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_14                         (0x4000U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_DATA_15                         (0x8000U << ADC_ADDR_DATA_Pos)
#define  ADC_ADDR_OVERRUN_Pos                     (20)
#define  ADC_ADDR_OVERRUN_Msk                     (0x1U << ADC_ADDR_OVERRUN_Pos) /*!<Data overrun flag (read-only)*/
#define  ADC_ADDR_OVERRUN                         ADC_ADDR_OVERRUN_Msk
#define  ADC_ADDR_VALID_Pos                       (21)
#define  ADC_ADDR_VALID_Msk                       (0x1U << ADC_ADDR_VALID_Pos)   /*!<Valid flag (read-only)*/
#define  ADC_ADDR_VALID                           ADC_ADDR_VALID_Msk

/**
  * @brief ADC_CHANY0 Register Bit Definition
  */
#define  ADC_CHANY0_CHANY_SEL0_Pos                (0)
#define  ADC_CHANY0_CHANY_SEL0_Msk                (0xFU << ADC_CHANY0_CHANY_SEL0_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL0                    ADC_CHANY0_CHANY_SEL0_Msk
#define  ADC_CHANY0_CHANY_SEL0_0                  (0x1U << ADC_CHANY0_CHANY_SEL0_Pos)
#define  ADC_CHANY0_CHANY_SEL0_1                  (0x2U << ADC_CHANY0_CHANY_SEL0_Pos)
#define  ADC_CHANY0_CHANY_SEL0_2                  (0x4U << ADC_CHANY0_CHANY_SEL0_Pos)
#define  ADC_CHANY0_CHANY_SEL0_3                  (0x8U << ADC_CHANY0_CHANY_SEL0_Pos)
#define  ADC_CHANY0_CHANY_SEL1_Pos                (4)
#define  ADC_CHANY0_CHANY_SEL1_Msk                (0xFU << ADC_CHANY0_CHANY_SEL1_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL1                    ADC_CHANY0_CHANY_SEL1_Msk
#define  ADC_CHANY0_CHANY_SEL1_0                  (0x1U << ADC_CHANY0_CHANY_SEL1_Pos)
#define  ADC_CHANY0_CHANY_SEL1_1                  (0x2U << ADC_CHANY0_CHANY_SEL1_Pos)
#define  ADC_CHANY0_CHANY_SEL1_2                  (0x4U << ADC_CHANY0_CHANY_SEL1_Pos)
#define  ADC_CHANY0_CHANY_SEL1_3                  (0x8U << ADC_CHANY0_CHANY_SEL1_Pos)
#define  ADC_CHANY0_CHANY_SEL2_Pos                (8)
#define  ADC_CHANY0_CHANY_SEL2_Msk                (0xFU << ADC_CHANY0_CHANY_SEL2_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL2                    ADC_CHANY0_CHANY_SEL2_Msk
#define  ADC_CHANY0_CHANY_SEL2_0                  (0x1U << ADC_CHANY0_CHANY_SEL2_Pos)
#define  ADC_CHANY0_CHANY_SEL2_1                  (0x2U << ADC_CHANY0_CHANY_SEL2_Pos)
#define  ADC_CHANY0_CHANY_SEL2_2                  (0x4U << ADC_CHANY0_CHANY_SEL2_Pos)
#define  ADC_CHANY0_CHANY_SEL2_3                  (0x8U << ADC_CHANY0_CHANY_SEL2_Pos)
#define  ADC_CHANY0_CHANY_SEL3_Pos                (12)
#define  ADC_CHANY0_CHANY_SEL3_Msk                (0xFU << ADC_CHANY0_CHANY_SEL3_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL3                    ADC_CHANY0_CHANY_SEL3_Msk
#define  ADC_CHANY0_CHANY_SEL3_0                  (0x1U << ADC_CHANY0_CHANY_SEL3_Pos)
#define  ADC_CHANY0_CHANY_SEL3_1                  (0x2U << ADC_CHANY0_CHANY_SEL3_Pos)
#define  ADC_CHANY0_CHANY_SEL3_2                  (0x4U << ADC_CHANY0_CHANY_SEL3_Pos)
#define  ADC_CHANY0_CHANY_SEL3_3                  (0x8U << ADC_CHANY0_CHANY_SEL3_Pos)
#define  ADC_CHANY0_CHANY_SEL4_Pos                (16)
#define  ADC_CHANY0_CHANY_SEL4_Msk                (0xFU << ADC_CHANY0_CHANY_SEL4_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL4                    ADC_CHANY0_CHANY_SEL4_Msk
#define  ADC_CHANY0_CHANY_SEL4_0                  (0x1U << ADC_CHANY0_CHANY_SEL4_Pos)
#define  ADC_CHANY0_CHANY_SEL4_1                  (0x2U << ADC_CHANY0_CHANY_SEL4_Pos)
#define  ADC_CHANY0_CHANY_SEL4_2                  (0x4U << ADC_CHANY0_CHANY_SEL4_Pos)
#define  ADC_CHANY0_CHANY_SEL4_3                  (0x8U << ADC_CHANY0_CHANY_SEL4_Pos)
#define  ADC_CHANY0_CHANY_SEL5_Pos                (20)
#define  ADC_CHANY0_CHANY_SEL5_Msk                (0xFU << ADC_CHANY0_CHANY_SEL5_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL5                    ADC_CHANY0_CHANY_SEL5_Msk
#define  ADC_CHANY0_CHANY_SEL5_0                  (0x1U << ADC_CHANY0_CHANY_SEL5_Pos)
#define  ADC_CHANY0_CHANY_SEL5_1                  (0x2U << ADC_CHANY0_CHANY_SEL5_Pos)
#define  ADC_CHANY0_CHANY_SEL5_2                  (0x4U << ADC_CHANY0_CHANY_SEL5_Pos)
#define  ADC_CHANY0_CHANY_SEL5_3                  (0x8U << ADC_CHANY0_CHANY_SEL5_Pos)
#define  ADC_CHANY0_CHANY_SEL6_Pos                (24)
#define  ADC_CHANY0_CHANY_SEL6_Msk                (0xFU << ADC_CHANY0_CHANY_SEL6_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL6                    ADC_CHANY0_CHANY_SEL6_Msk
#define  ADC_CHANY0_CHANY_SEL6_0                  (0x1U << ADC_CHANY0_CHANY_SEL6_Pos)
#define  ADC_CHANY0_CHANY_SEL6_1                  (0x2U << ADC_CHANY0_CHANY_SEL6_Pos)
#define  ADC_CHANY0_CHANY_SEL6_2                  (0x4U << ADC_CHANY0_CHANY_SEL6_Pos)
#define  ADC_CHANY0_CHANY_SEL6_3                  (0x8U << ADC_CHANY0_CHANY_SEL6_Pos)
#define  ADC_CHANY0_CHANY_SEL7_Pos                (28)
#define  ADC_CHANY0_CHANY_SEL7_Msk                (0xFU << ADC_CHANY0_CHANY_SEL7_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY0_CHANY_SEL7                    ADC_CHANY0_CHANY_SEL7_Msk
#define  ADC_CHANY0_CHANY_SEL7_0                  (0x1U << ADC_CHANY0_CHANY_SEL7_Pos)
#define  ADC_CHANY0_CHANY_SEL7_1                  (0x2U << ADC_CHANY0_CHANY_SEL7_Pos)
#define  ADC_CHANY0_CHANY_SEL7_2                  (0x4U << ADC_CHANY0_CHANY_SEL7_Pos)
#define  ADC_CHANY0_CHANY_SEL7_3                  (0x8U << ADC_CHANY0_CHANY_SEL7_Pos)

/**
  * @brief ADC_CHANY1 Register Bit Definition
  */
#define  ADC_CHANY1_CHANY_SEL8_Pos                (0)
#define  ADC_CHANY1_CHANY_SEL8_Msk                (0xFU << ADC_CHANY1_CHANY_SEL8_Pos) /*!<can be configured to any channel from channel 0 ~ 8.*/
#define  ADC_CHANY1_CHANY_SEL8                    ADC_CHANY1_CHANY_SEL8_Msk
#define  ADC_CHANY1_CHANY_SEL8_0                  (0x1U << ADC_CHANY1_CHANY_SEL8_Pos)
#define  ADC_CHANY1_CHANY_SEL8_1                  (0x2U << ADC_CHANY1_CHANY_SEL8_Pos)
#define  ADC_CHANY1_CHANY_SEL8_2                  (0x4U << ADC_CHANY1_CHANY_SEL8_Pos)
#define  ADC_CHANY1_CHANY_SEL8_3                  (0x8U << ADC_CHANY1_CHANY_SEL8_Pos)

/**
  * @brief ADC_ANY_CFG Register Bit Definition
  */
#define  ADC_ANY_CFG_CHANY_NUM_Pos                (0)
#define  ADC_ANY_CFG_CHANY_NUM_Msk                (0xFU << ADC_ANY_CFG_CHANY_NUM_Pos) /*!<Number of Any Channel Mode*/
#define  ADC_ANY_CFG_CHANY_NUM                    ADC_ANY_CFG_CHANY_NUM_Msk
#define  ADC_ANY_CFG_CHANY_NUM_0                  (0x1U << ADC_ANY_CFG_CHANY_NUM_Pos)
#define  ADC_ANY_CFG_CHANY_NUM_1                  (0x2U << ADC_ANY_CFG_CHANY_NUM_Pos)
#define  ADC_ANY_CFG_CHANY_NUM_2                  (0x4U << ADC_ANY_CFG_CHANY_NUM_Pos)
#define  ADC_ANY_CFG_CHANY_NUM_3                  (0x8U << ADC_ANY_CFG_CHANY_NUM_Pos)

/**
  * @brief ADC_ANY_CR Register Bit Definition
  */
#define  ADC_ANY_CR_CHANY_MDEN_Pos                (0)
#define  ADC_ANY_CR_CHANY_MDEN_Msk                (0x1U << ADC_ANY_CR_CHANY_MDEN_Pos) /*!<Arbitrary channel configuration mode enable bit*/
#define  ADC_ANY_CR_CHANY_MDEN                    ADC_ANY_CR_CHANY_MDEN_Msk

#endif

