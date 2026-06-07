/***********************************************************************************************************************
    @file     reg_rcc.h
    @author   VV TEAM
    @brief    This flie contains all the RCC's register and its field definition.
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

#ifndef __REG_RCC_H
#define __REG_RCC_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief RCC Base Address Definition
  */
#define  RCC_BASE                                  0x40021000 /*!<Base Address: 0x40021000*/

/**
  * @brief RCC Register Structure Definition
  */
typedef struct
{
    __IO uint32_t CR;                  /*!<RCC Clock Control Register                     offset: 0x00       */
    __IO uint32_t CFGR;                /*!<RCC Clock Configuration Register               offset: 0x04       */
    __IO uint32_t CIR;                 /*!<RCC Clock Interrupt Register                   offset: 0x08       */
    __IO uint32_t RESERVED0x0C[1];     /*!<                                               offset: 0x0C       */
    __IO uint32_t APB1RSTR;            /*!<RCC APB1 Peripheral Reset Register             offset: 0x10       */
    __IO uint32_t AHBENR;              /*!<RCC AHB Peripheral Clock Enable Register       offset: 0x14       */
    __IO uint32_t RESERVED0x18[1];     /*!<                                               offset: 0x18       */
    __IO uint32_t APB1ENR;             /*!<RCC APB1Peripheral Clock Enable Register       offset: 0x1C       */
    __IO uint32_t RESERVED0x20[1];     /*!<                                               offset: 0x20       */
    __IO uint32_t CSR;                 /*!<RCC Control Status Register                    offset: 0x24       */
    __IO uint32_t AHBRSTR;             /*!<RCC AHB Peripheral Reset Register              offset: 0x28       */
    __IO uint32_t RESERVED0x2C[5];     /*!<                                               offset: 0x2C~0x3C  */
    __IO uint32_t SYSCFGR;             /*!<RCC System Configuration Register              offset: 0x40       */
} RCC_TypeDef;

/**
  * @brief RCC type pointer Definition
  */
#define RCC                                       ((RCC_TypeDef *)RCC_BASE)

/**
  * @brief RCC_CR Register Bit Definition
  */
#define  RCC_CR_HSION_Pos                         (0)
#define  RCC_CR_HSION_Msk                         (0x1U << RCC_CR_HSION_Pos)  /*!<Internal High-speed Clock Enable*/
#define  RCC_CR_HSION                             RCC_CR_HSION_Msk
#define  RCC_CR_HSIRDY_Pos                        (1)
#define  RCC_CR_HSIRDY_Msk                        (0x1U << RCC_CR_HSIRDY_Pos) /*!<Internal High-speed Clock Ready Flag*/
#define  RCC_CR_HSIRDY                            RCC_CR_HSIRDY_Msk
#define  RCC_CR_HSEON_Pos                         (16)
#define  RCC_CR_HSEON_Msk                         (0x1U << RCC_CR_HSEON_Pos)  /*!<External High-speed Clock Enable*/
#define  RCC_CR_HSEON                             RCC_CR_HSEON_Msk
#define  RCC_CR_HSERDY_Pos                        (17)
#define  RCC_CR_HSERDY_Msk                        (0x1U << RCC_CR_HSERDY_Pos) /*!<External High-speed Clock Ready Flag*/
#define  RCC_CR_HSERDY                            RCC_CR_HSERDY_Msk

/**
  * @brief RCC_CFGR Register Bit Definition
  */
#define  RCC_CFGR_SW_Pos                          (0)
#define  RCC_CFGR_SW_Msk                          (0x3U << RCC_CFGR_SW_Pos) /*!<System Clock Switch*/
#define  RCC_CFGR_SW                              RCC_CFGR_SW_Msk
#define  RCC_CFGR_SW_0                            (0x1U << RCC_CFGR_SW_Pos)
#define  RCC_CFGR_SW_1                            (0x2U << RCC_CFGR_SW_Pos)
#define  RCC_CFGR_SWS_Pos                         (2)
#define  RCC_CFGR_SWS_Msk                         (0x3U << RCC_CFGR_SWS_Pos) /*!<System Clock Switch Status*/
#define  RCC_CFGR_SWS                             RCC_CFGR_SWS_Msk
#define  RCC_CFGR_SWS_0                           (0x1U << RCC_CFGR_SWS_Pos)
#define  RCC_CFGR_SWS_1                           (0x2U << RCC_CFGR_SWS_Pos)
#define  RCC_CFGR_HPRE_Pos                        (4)
#define  RCC_CFGR_HPRE_Msk                        (0xFU << RCC_CFGR_HPRE_Pos) /*!<AHB prescaler coefficient*/
#define  RCC_CFGR_HPRE                            RCC_CFGR_HPRE_Msk
#define  RCC_CFGR_HPRE_0                          (0x1U << RCC_CFGR_HPRE_Pos)
#define  RCC_CFGR_HPRE_1                          (0x2U << RCC_CFGR_HPRE_Pos)
#define  RCC_CFGR_HPRE_2                          (0x4U << RCC_CFGR_HPRE_Pos)
#define  RCC_CFGR_HPRE_3                          (0x8U << RCC_CFGR_HPRE_Pos)
#define  RCC_CFGR_PPRE1_Pos                       (8)
#define  RCC_CFGR_PPRE1_Msk                       (0x7U << RCC_CFGR_PPRE1_Pos) /*!<APB1 prescaler coefficient*/
#define  RCC_CFGR_PPRE1                           RCC_CFGR_PPRE1_Msk
#define  RCC_CFGR_PPRE1_0                         (0x1U << RCC_CFGR_PPRE1_Pos)
#define  RCC_CFGR_PPRE1_1                         (0x2U << RCC_CFGR_PPRE1_Pos)
#define  RCC_CFGR_PPRE1_2                         (0x4U << RCC_CFGR_PPRE1_Pos)
#define  RCC_CFGR_MCO_Pos                         (24)
#define  RCC_CFGR_MCO_Msk                         (0x7U << RCC_CFGR_MCO_Pos) /*!<Micro Controller Clock Output*/
#define  RCC_CFGR_MCO                             RCC_CFGR_MCO_Msk
#define  RCC_CFGR_MCO_0                           (0x1U << RCC_CFGR_MCO_Pos)
#define  RCC_CFGR_MCO_1                           (0x2U << RCC_CFGR_MCO_Pos)
#define  RCC_CFGR_MCO_2                           (0x4U << RCC_CFGR_MCO_Pos)

/**
  * @brief RCC_CIR Register Bit Definition
  */
#define  RCC_CIR_LSIRDYF_Pos                      (0)
#define  RCC_CIR_LSIRDYF_Msk                      (0x1U << RCC_CIR_LSIRDYF_Pos)  /*!<LSI Ready Interrupt Flag*/
#define  RCC_CIR_LSIRDYF                          RCC_CIR_LSIRDYF_Msk
#define  RCC_CIR_HSIRDYF_Pos                      (2)
#define  RCC_CIR_HSIRDYF_Msk                      (0x1U << RCC_CIR_HSIRDYF_Pos)  /*!<HSI Ready Interrupt Flag*/
#define  RCC_CIR_HSIRDYF                          RCC_CIR_HSIRDYF_Msk
#define  RCC_CIR_HSERDYF_Pos                      (3)
#define  RCC_CIR_HSERDYF_Msk                      (0x1U << RCC_CIR_HSERDYF_Pos)  /*!<HSE Ready Interrupt Flag*/
#define  RCC_CIR_HSERDYF                          RCC_CIR_HSERDYF_Msk
#define  RCC_CIR_LSIRDYIE_Pos                     (8)
#define  RCC_CIR_LSIRDYIE_Msk                     (0x1U << RCC_CIR_LSIRDYIE_Pos) /*!<LSI Ready Interrupt Enable*/
#define  RCC_CIR_LSIRDYIE                         RCC_CIR_LSIRDYIE_Msk
#define  RCC_CIR_HSIRDYIE_Pos                     (10)
#define  RCC_CIR_HSIRDYIE_Msk                     (0x1U << RCC_CIR_HSIRDYIE_Pos) /*!<HSI Ready Interrupt Enable*/
#define  RCC_CIR_HSIRDYIE                         RCC_CIR_HSIRDYIE_Msk
#define  RCC_CIR_HSERDYIE_Pos                     (11)
#define  RCC_CIR_HSERDYIE_Msk                     (0x1U << RCC_CIR_HSERDYIE_Pos) /*!<HSE Ready Interrupt Enable*/
#define  RCC_CIR_HSERDYIE                         RCC_CIR_HSERDYIE_Msk
#define  RCC_CIR_LSIRDYC_Pos                      (16)
#define  RCC_CIR_LSIRDYC_Msk                      (0x1U << RCC_CIR_LSIRDYC_Pos)  /*!<LSI Ready Interrupt Clear*/
#define  RCC_CIR_LSIRDYC                          RCC_CIR_LSIRDYC_Msk
#define  RCC_CIR_HSIRDYC_Pos                      (18)
#define  RCC_CIR_HSIRDYC_Msk                      (0x1U << RCC_CIR_HSIRDYC_Pos)  /*!<HSI Ready Interrupt Clear*/
#define  RCC_CIR_HSIRDYC                          RCC_CIR_HSIRDYC_Msk
#define  RCC_CIR_HSERDYC_Pos                      (19)
#define  RCC_CIR_HSERDYC_Msk                      (0x1U << RCC_CIR_HSERDYC_Pos)  /*!<HSE Ready Interrupt Clear*/
#define  RCC_CIR_HSERDYC                          RCC_CIR_HSERDYC_Msk

/**
  * @brief RCC_APB1RSTR Register Bit Definition
  */
#define  RCC_APB1RSTR_TIM3_Pos                    (1)
#define  RCC_APB1RSTR_TIM3_Msk                    (0x1U << RCC_APB1RSTR_TIM3_Pos)   /*!<TIM3 Reset*/
#define  RCC_APB1RSTR_TIM3                        RCC_APB1RSTR_TIM3_Msk
#define  RCC_APB1RSTR_TIM1_Pos                    (2)
#define  RCC_APB1RSTR_TIM1_Msk                    (0x1U << RCC_APB1RSTR_TIM1_Pos)   /*!<TIM1 Reset*/
#define  RCC_APB1RSTR_TIM1                        RCC_APB1RSTR_TIM1_Msk
#define  RCC_APB1RSTR_TIM14_Pos                   (3)
#define  RCC_APB1RSTR_TIM14_Msk                   (0x1U << RCC_APB1RSTR_TIM14_Pos)  /*!<TIM14 Reset*/
#define  RCC_APB1RSTR_TIM14                       RCC_APB1RSTR_TIM14_Msk
#define  RCC_APB1RSTR_ADC1_Pos                    (9)
#define  RCC_APB1RSTR_ADC1_Msk                    (0x1U << RCC_APB1RSTR_ADC1_Pos)   /*!<ADC1 Reset*/
#define  RCC_APB1RSTR_ADC1                        RCC_APB1RSTR_ADC1_Msk
#define  RCC_APB1RSTR_SPI1_Pos                    (12)
#define  RCC_APB1RSTR_SPI1_Msk                    (0x1U << RCC_APB1RSTR_SPI1_Pos)   /*!<SPI1 Reset*/
#define  RCC_APB1RSTR_SPI1                        RCC_APB1RSTR_SPI1_Msk
#define  RCC_APB1RSTR_USART1_Pos                  (16)
#define  RCC_APB1RSTR_USART1_Msk                  (0x1U << RCC_APB1RSTR_USART1_Pos) /*!<USART1 Reset*/
#define  RCC_APB1RSTR_USART1                      RCC_APB1RSTR_USART1_Msk
#define  RCC_APB1RSTR_USART2_Pos                  (17)
#define  RCC_APB1RSTR_USART2_Msk                  (0x1U << RCC_APB1RSTR_USART2_Pos) /*!<USART2 Reset*/
#define  RCC_APB1RSTR_USART2                      RCC_APB1RSTR_USART2_Msk
#define  RCC_APB1RSTR_I2C1_Pos                    (21)
#define  RCC_APB1RSTR_I2C1_Msk                    (0x1U << RCC_APB1RSTR_I2C1_Pos)   /*!<2C1 Reset*/
#define  RCC_APB1RSTR_I2C1                        RCC_APB1RSTR_I2C1_Msk
#define  RCC_APB1RSTR_PWR_Pos                     (28)
#define  RCC_APB1RSTR_PWR_Msk                     (0x1U << RCC_APB1RSTR_PWR_Pos)    /*!<Power Interface Reset*/
#define  RCC_APB1RSTR_PWR                         RCC_APB1RSTR_PWR_Msk
#define  RCC_APB1RSTR_SYSCFG_Pos                  (30)
#define  RCC_APB1RSTR_SYSCFG_Msk                  (0x1U << RCC_APB1RSTR_SYSCFG_Pos) /*!<SYSCFG Reset*/
#define  RCC_APB1RSTR_SYSCFG                      RCC_APB1RSTR_SYSCFG_Msk

/**
  * @brief RCC_AHBENR Register Bit Definition
  */
#define  RCC_AHBENR_SRAM_Pos                      (2)
#define  RCC_AHBENR_SRAM_Msk                      (0x1U << RCC_AHBENR_SRAM_Pos)  /*!<SRAM Clock Enable*/
#define  RCC_AHBENR_SRAM                          RCC_AHBENR_SRAM_Msk
#define  RCC_AHBENR_FLASH_Pos                     (4)
#define  RCC_AHBENR_FLASH_Msk                     (0x1U << RCC_AHBENR_FLASH_Pos) /*!<FLASH Clock Enable*/
#define  RCC_AHBENR_FLASH                         RCC_AHBENR_FLASH_Msk
#define  RCC_AHBENR_CRC_Pos                       (6)
#define  RCC_AHBENR_CRC_Msk                       (0x1U << RCC_AHBENR_CRC_Pos)   /*!<CRC Clock Enable*/
#define  RCC_AHBENR_CRC                           RCC_AHBENR_CRC_Msk
#define  RCC_AHBENR_GPIOA_Pos                     (17)
#define  RCC_AHBENR_GPIOA_Msk                     (0x1U << RCC_AHBENR_GPIOA_Pos) /*!<GPIOA Clock Enable*/
#define  RCC_AHBENR_GPIOA                         RCC_AHBENR_GPIOA_Msk
#define  RCC_AHBENR_GPIOB_Pos                     (18)
#define  RCC_AHBENR_GPIOB_Msk                     (0x1U << RCC_AHBENR_GPIOB_Pos) /*!<GPIOB Clock Enable*/
#define  RCC_AHBENR_GPIOB                         RCC_AHBENR_GPIOB_Msk

/**
  * @brief RCC_APB1ENR Register Bit Definition
  */
#define  RCC_APB1ENR_TIM3_Pos                     (1)
#define  RCC_APB1ENR_TIM3_Msk                     (0x1U << RCC_APB1ENR_TIM3_Pos)   /*!<TIM3 Clock Enable*/
#define  RCC_APB1ENR_TIM3                         RCC_APB1ENR_TIM3_Msk
#define  RCC_APB1ENR_TIM1_Pos                     (2)
#define  RCC_APB1ENR_TIM1_Msk                     (0x1U << RCC_APB1ENR_TIM1_Pos)   /*!<TIM1 Clock Enable*/
#define  RCC_APB1ENR_TIM1                         RCC_APB1ENR_TIM1_Msk
#define  RCC_APB1ENR_TIM14_Pos                    (3)
#define  RCC_APB1ENR_TIM14_Msk                    (0x1U << RCC_APB1ENR_TIM14_Pos)  /*!<TIM14 Clock Enable*/
#define  RCC_APB1ENR_TIM14                        RCC_APB1ENR_TIM14_Msk
#define  RCC_APB1ENR_ADC1_Pos                     (9)
#define  RCC_APB1ENR_ADC1_Msk                     (0x1U << RCC_APB1ENR_ADC1_Pos)   /*!<ADC1 Clock Enable*/
#define  RCC_APB1ENR_ADC1                         RCC_APB1ENR_ADC1_Msk
#define  RCC_APB1ENR_SPI1_Pos                     (12)
#define  RCC_APB1ENR_SPI1_Msk                     (0x1U << RCC_APB1ENR_SPI1_Pos)   /*!<SPI1 Clock Enable*/
#define  RCC_APB1ENR_SPI1                         RCC_APB1ENR_SPI1_Msk
#define  RCC_APB1ENR_USART1_Pos                   (16)
#define  RCC_APB1ENR_USART1_Msk                   (0x1U << RCC_APB1ENR_USART1_Pos) /*!<USART1 Clock Enable*/
#define  RCC_APB1ENR_USART1                       RCC_APB1ENR_USART1_Msk
#define  RCC_APB1ENR_USART2_Pos                   (17)
#define  RCC_APB1ENR_USART2_Msk                   (0x1U << RCC_APB1ENR_USART2_Pos) /*!<USART2 Clock Enable*/
#define  RCC_APB1ENR_USART2                       RCC_APB1ENR_USART2_Msk
#define  RCC_APB1ENR_I2C1_Pos                     (21)
#define  RCC_APB1ENR_I2C1_Msk                     (0x1U << RCC_APB1ENR_I2C1_Pos)   /*!<I2C1 Clock Enable*/
#define  RCC_APB1ENR_I2C1                         RCC_APB1ENR_I2C1_Msk
#define  RCC_APB1ENR_PWR_Pos                      (28)
#define  RCC_APB1ENR_PWR_Msk                      (0x1U << RCC_APB1ENR_PWR_Pos)    /*!<Power Clock Enable*/
#define  RCC_APB1ENR_PWR                          RCC_APB1ENR_PWR_Msk
#define  RCC_APB1ENR_DBG_Pos                      (29)
#define  RCC_APB1ENR_DBG_Msk                      (0x1U << RCC_APB1ENR_DBG_Pos)    /*!<DBG Clock Enable*/
#define  RCC_APB1ENR_DBG                          RCC_APB1ENR_DBG_Msk
#define  RCC_APB1ENR_SYSCFG_Pos                   (30)
#define  RCC_APB1ENR_SYSCFG_Msk                   (0x1U << RCC_APB1ENR_SYSCFG_Pos) /*!<SYSCFG Clock Enable*/
#define  RCC_APB1ENR_SYSCFG                       RCC_APB1ENR_SYSCFG_Msk

/**
  * @brief RCC_CSR Register Bit Definition
  */
#define  RCC_CSR_LSION_Pos                        (0)
#define  RCC_CSR_LSION_Msk                        (0x1U << RCC_CSR_LSION_Pos)    /*!<Internal Low-speed Oscillator Enable*/
#define  RCC_CSR_LSION                            RCC_CSR_LSION_Msk
#define  RCC_CSR_LSIRDY_Pos                       (1)
#define  RCC_CSR_LSIRDY_Msk                       (0x1U << RCC_CSR_LSIRDY_Pos)   /*!<Internal Low-speed Oscillator Ready*/
#define  RCC_CSR_LSIRDY                           RCC_CSR_LSIRDY_Msk
#define  RCC_CSR_PVDRSTEN_Pos                     (6)
#define  RCC_CSR_PVDRSTEN_Msk                     (0x1U << RCC_CSR_PVDRSTEN_Pos) /*!<PVD Reset Enable*/
#define  RCC_CSR_PVDRSTEN                         RCC_CSR_PVDRSTEN_Msk
#define  RCC_CSR_LOCKUPEN_Pos                     (7)
#define  RCC_CSR_LOCKUPEN_Msk                     (0x1U << RCC_CSR_LOCKUPEN_Pos) /*!<CPU Lockup Reset Enable*/
#define  RCC_CSR_LOCKUPEN                         RCC_CSR_LOCKUPEN_Msk
#define  RCC_CSR_PVDRSTF_Pos                      (22)
#define  RCC_CSR_PVDRSTF_Msk                      (0x1U << RCC_CSR_PVDRSTF_Pos)  /*!<PVD Reset Flag*/
#define  RCC_CSR_PVDRSTF                          RCC_CSR_PVDRSTF_Msk
#define  RCC_CSR_LOCKUPF_Pos                      (23)
#define  RCC_CSR_LOCKUPF_Msk                      (0x1U << RCC_CSR_LOCKUPF_Pos)  /*!<CPU Lockup Reset Flag*/
#define  RCC_CSR_LOCKUPF                          RCC_CSR_LOCKUPF_Msk
#define  RCC_CSR_RMVF_Pos                         (24)
#define  RCC_CSR_RMVF_Msk                         (0x1U << RCC_CSR_RMVF_Pos)     /*!<Remove Reset Flag*/
#define  RCC_CSR_RMVF                             RCC_CSR_RMVF_Msk
#define  RCC_CSR_PINRSTF_Pos                      (26)
#define  RCC_CSR_PINRSTF_Msk                      (0x1U << RCC_CSR_PINRSTF_Pos)  /*!<PIN Reset Flag*/
#define  RCC_CSR_PINRSTF                          RCC_CSR_PINRSTF_Msk
#define  RCC_CSR_PORRSTF_Pos                      (27)
#define  RCC_CSR_PORRSTF_Msk                      (0x1U << RCC_CSR_PORRSTF_Pos)  /*!<POR/PDR Reset Flag*/
#define  RCC_CSR_PORRSTF                          RCC_CSR_PORRSTF_Msk
#define  RCC_CSR_SFTRSTF_Pos                      (28)
#define  RCC_CSR_SFTRSTF_Msk                      (0x1U << RCC_CSR_SFTRSTF_Pos)  /*!<Software Reset Flag*/
#define  RCC_CSR_SFTRSTF                          RCC_CSR_SFTRSTF_Msk
#define  RCC_CSR_IWDGRSTF_Pos                     (29)
#define  RCC_CSR_IWDGRSTF_Msk                     (0x1U << RCC_CSR_IWDGRSTF_Pos) /*!<Independent Watchdog Reset Flag*/
#define  RCC_CSR_IWDGRSTF                         RCC_CSR_IWDGRSTF_Msk

/**
  * @brief RCC_AHBRSTR Register Bit Definition
  */
#define  RCC_AHBRSTR_GPIOA_Pos                    (17)
#define  RCC_AHBRSTR_GPIOA_Msk                    (0x1U << RCC_AHBRSTR_GPIOA_Pos) /*!<GPIOA Reset*/
#define  RCC_AHBRSTR_GPIOA                        RCC_AHBRSTR_GPIOA_Msk
#define  RCC_AHBRSTR_GPIOB_Pos                    (18)
#define  RCC_AHBRSTR_GPIOB_Msk                    (0x1U << RCC_AHBRSTR_GPIOB_Pos) /*!<GPIOB Reset*/
#define  RCC_AHBRSTR_GPIOB                        RCC_AHBRSTR_GPIOB_Msk

/**
  * @brief RCC_SYSCFG Register Bit Definition
  */
#define  RCC_SYSCFG_PROG_CHECK_EN_Pos             (0)
#define  RCC_SYSCFG_PROG_CHECK_EN_Msk             (0x1U << RCC_SYSCFG_PROG_CHECK_EN_Pos) /*!<Check whether the data in Flash is 0xFF when writing Flash*/
#define  RCC_SYSCFG_PROG_CHECK_EN                 RCC_SYSCFG_PROG_CHECK_EN_Msk
#define  RCC_SYSCFG_SECTOR1KCFG_Pos               (1)
#define  RCC_SYSCFG_SECTOR1KCFG_Msk               (0x1U << RCC_SYSCFG_SECTOR1KCFG_Pos)   /*!<SECTOR_1K_CFG: size for Flash erase.*/
#define  RCC_SYSCFG_SECTOR1KCFG                   RCC_SYSCFG_SECTOR1KCFG_Msk
#define  RCC_SYSCFG_SFT_NRST_RMP_Pos              (2)
#define  RCC_SYSCFG_SFT_NRST_RMP_Msk              (0x1U << RCC_SYSCFG_SFT_NRST_RMP_Pos)  /*!<SFT_NRST_RMP: software mapping of nRST.*/
#define  RCC_SYSCFG_SFT_NRST_RMP                  RCC_SYSCFG_SFT_NRST_RMP_Msk

#endif

