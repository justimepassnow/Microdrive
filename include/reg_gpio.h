/***********************************************************************************************************************
    @file     reg_gpio.h
    @author   VV TEAM
    @brief    This flie contains all the GPIO's register and its field definition.
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

#ifndef __REG_GPIO_H
#define __REG_GPIO_H


/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>




/**
  * @brief GPIO Base Address Definition
  */
#define  GPIOA_BASE                                0x48000000                                       /*!<Base Address: 0x48000000*/
#define  GPIOB_BASE                                0x48000400                                       /*!<Base Address: 0x48000400*/

/**
  * @brief GPIO Register Structure Definition
  */
typedef struct
{
    __IO uint32_t CRL;                            /*!<GPIO Port configuration register low           offset: 0x00       */
    __IO uint32_t CRH;                            /*!<GPIO Port configuration register high          offset: 0x04       */
    __IO uint32_t IDR;                            /*!<GPIO Port input data register                  offset: 0x08       */
    __IO uint32_t ODR;                            /*!<GPIO Port output data register                 offset: 0x0C       */
    __IO uint32_t BSRR;                           /*!<GPIO Port bit set/reset register               offset: 0x10       */
    __IO uint32_t BRR;                            /*!<GPIO Port bit reset register                   offset: 0x14       */
    __IO uint32_t LCKR;                           /*!<GPIO Port configuration lock register          offset: 0x18       */
    __IO uint32_t DCR;                            /*!<GPIO Port output open drain control register   offset: 0x1C       */
    __IO uint32_t AFRL;                           /*!<GPIO Port alternate function register low      offset: 0x20       */
    __IO uint32_t AFRH;                           /*!<GPIO Port alternate function register high     offset: 0x24       */
} GPIO_TypeDef;

/**
  * @brief GPIO type pointer Definition
  */
#define GPIOA                                     ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB                                     ((GPIO_TypeDef *)GPIOB_BASE)

/**
  * @brief GPIO_CRL Register Bit Definition
  */
#define  GPIO_CRL_MODE0_Pos                       (0)
#define  GPIO_CRL_MODE0_Msk                       (0x3U << GPIO_CRL_MODE0_Pos)                      /*!<See MODE15*/
#define  GPIO_CRL_MODE0                           GPIO_CRL_MODE0_Msk
#define  GPIO_CRL_MODE0_0                         (0x1U << GPIO_CRL_MODE0_Pos) 
#define  GPIO_CRL_MODE0_1                         (0x2U << GPIO_CRL_MODE0_Pos) 
#define  GPIO_CRL_CNF0_Pos                        (2)
#define  GPIO_CRL_CNF0_Msk                        (0x3U << GPIO_CRL_CNF0_Pos)                       /*!<See CNF15*/
#define  GPIO_CRL_CNF0                            GPIO_CRL_CNF0_Msk
#define  GPIO_CRL_CNF0_0                          (0x1U << GPIO_CRL_CNF0_Pos) 
#define  GPIO_CRL_CNF0_1                          (0x2U << GPIO_CRL_CNF0_Pos) 
#define  GPIO_CRL_MODE1_Pos                       (4)
#define  GPIO_CRL_MODE1_Msk                       (0x3U << GPIO_CRL_MODE1_Pos)                      /*!<See MODE15*/
#define  GPIO_CRL_MODE1                           GPIO_CRL_MODE1_Msk
#define  GPIO_CRL_MODE1_0                         (0x1U << GPIO_CRL_MODE1_Pos) 
#define  GPIO_CRL_MODE1_1                         (0x2U << GPIO_CRL_MODE1_Pos) 
#define  GPIO_CRL_CNF1_Pos                        (6)
#define  GPIO_CRL_CNF1_Msk                        (0x3U << GPIO_CRL_CNF1_Pos)                       /*!<See CNF15*/
#define  GPIO_CRL_CNF1                            GPIO_CRL_CNF1_Msk
#define  GPIO_CRL_CNF1_0                          (0x1U << GPIO_CRL_CNF1_Pos) 
#define  GPIO_CRL_CNF1_1                          (0x2U << GPIO_CRL_CNF1_Pos) 
#define  GPIO_CRL_MODE2_Pos                       (8)
#define  GPIO_CRL_MODE2_Msk                       (0x3U << GPIO_CRL_MODE2_Pos)                      /*!<See MODE15*/
#define  GPIO_CRL_MODE2                           GPIO_CRL_MODE2_Msk
#define  GPIO_CRL_MODE2_0                         (0x1U << GPIO_CRL_MODE2_Pos) 
#define  GPIO_CRL_MODE2_1                         (0x2U << GPIO_CRL_MODE2_Pos) 
#define  GPIO_CRL_CNF2_Pos                        (10)
#define  GPIO_CRL_CNF2_Msk                        (0x3U << GPIO_CRL_CNF2_Pos)                       /*!<See CNF15*/
#define  GPIO_CRL_CNF2                            GPIO_CRL_CNF2_Msk
#define  GPIO_CRL_CNF2_0                          (0x1U << GPIO_CRL_CNF2_Pos) 
#define  GPIO_CRL_CNF2_1                          (0x2U << GPIO_CRL_CNF2_Pos) 
#define  GPIO_CRL_MODE3_Pos                       (12)
#define  GPIO_CRL_MODE3_Msk                       (0x3U << GPIO_CRL_MODE3_Pos)                      /*!<See MODE15*/
#define  GPIO_CRL_MODE3                           GPIO_CRL_MODE3_Msk
#define  GPIO_CRL_MODE3_0                         (0x1U << GPIO_CRL_MODE3_Pos) 
#define  GPIO_CRL_MODE3_1                         (0x2U << GPIO_CRL_MODE3_Pos) 
#define  GPIO_CRL_CNF3_Pos                        (14)
#define  GPIO_CRL_CNF3_Msk                        (0x3U << GPIO_CRL_CNF3_Pos)                       /*!<See CNF15*/
#define  GPIO_CRL_CNF3                            GPIO_CRL_CNF3_Msk
#define  GPIO_CRL_CNF3_0                          (0x1U << GPIO_CRL_CNF3_Pos) 
#define  GPIO_CRL_CNF3_1                          (0x2U << GPIO_CRL_CNF3_Pos) 
#define  GPIO_CRL_MODE4_Pos                       (16)
#define  GPIO_CRL_MODE4_Msk                       (0x3U << GPIO_CRL_MODE4_Pos)                      /*!<See MODE15*/
#define  GPIO_CRL_MODE4                           GPIO_CRL_MODE4_Msk
#define  GPIO_CRL_MODE4_0                         (0x1U << GPIO_CRL_MODE4_Pos) 
#define  GPIO_CRL_MODE4_1                         (0x2U << GPIO_CRL_MODE4_Pos) 
#define  GPIO_CRL_CNF4_Pos                        (18)
#define  GPIO_CRL_CNF4_Msk                        (0x3U << GPIO_CRL_CNF4_Pos)                       /*!<See CNF15*/
#define  GPIO_CRL_CNF4                            GPIO_CRL_CNF4_Msk
#define  GPIO_CRL_CNF4_0                          (0x1U << GPIO_CRL_CNF4_Pos) 
#define  GPIO_CRL_CNF4_1                          (0x2U << GPIO_CRL_CNF4_Pos) 
#define  GPIO_CRL_MODE5_Pos                       (20)
#define  GPIO_CRL_MODE5_Msk                       (0x3U << GPIO_CRL_MODE5_Pos)                      /*!<See MODE15*/
#define  GPIO_CRL_MODE5                           GPIO_CRL_MODE5_Msk
#define  GPIO_CRL_MODE5_0                         (0x1U << GPIO_CRL_MODE5_Pos) 
#define  GPIO_CRL_MODE5_1                         (0x2U << GPIO_CRL_MODE5_Pos) 
#define  GPIO_CRL_CNF5_Pos                        (22)
#define  GPIO_CRL_CNF5_Msk                        (0x3U << GPIO_CRL_CNF5_Pos)                       /*!<See CNF15*/
#define  GPIO_CRL_CNF5                            GPIO_CRL_CNF5_Msk
#define  GPIO_CRL_CNF5_0                          (0x1U << GPIO_CRL_CNF5_Pos) 
#define  GPIO_CRL_CNF5_1                          (0x2U << GPIO_CRL_CNF5_Pos) 
#define  GPIO_CRL_MODE6_Pos                       (24)
#define  GPIO_CRL_MODE6_Msk                       (0x3U << GPIO_CRL_MODE6_Pos)                      /*!<See MODE15*/
#define  GPIO_CRL_MODE6                           GPIO_CRL_MODE6_Msk
#define  GPIO_CRL_MODE6_0                         (0x1U << GPIO_CRL_MODE6_Pos) 
#define  GPIO_CRL_MODE6_1                         (0x2U << GPIO_CRL_MODE6_Pos) 
#define  GPIO_CRL_CNF6_Pos                        (26)
#define  GPIO_CRL_CNF6_Msk                        (0x3U << GPIO_CRL_CNF6_Pos)                       /*!<See CNF15*/
#define  GPIO_CRL_CNF6                            GPIO_CRL_CNF6_Msk
#define  GPIO_CRL_CNF6_0                          (0x1U << GPIO_CRL_CNF6_Pos) 
#define  GPIO_CRL_CNF6_1                          (0x2U << GPIO_CRL_CNF6_Pos) 
#define  GPIO_CRL_MODE7_Pos                       (28)
#define  GPIO_CRL_MODE7_Msk                       (0x3U << GPIO_CRL_MODE7_Pos)                      /*!<Port input/output configuration (MODEy)(y = 0..7)*/
#define  GPIO_CRL_MODE7                           GPIO_CRL_MODE7_Msk
#define  GPIO_CRL_MODE7_0                         (0x1U << GPIO_CRL_MODE7_Pos) 
#define  GPIO_CRL_MODE7_1                         (0x2U << GPIO_CRL_MODE7_Pos) 
#define  GPIO_CRL_CNF7_Pos                        (30)
#define  GPIO_CRL_CNF7_Msk                        (0x3U << GPIO_CRL_CNF7_Pos)                       /*!<Port configuration bits (y=7..0)*/
#define  GPIO_CRL_CNF7                            GPIO_CRL_CNF7_Msk
#define  GPIO_CRL_CNF7_0                          (0x1U << GPIO_CRL_CNF7_Pos) 
#define  GPIO_CRL_CNF7_1                          (0x2U << GPIO_CRL_CNF7_Pos) 

/**
  * @brief GPIO_CRH Register Bit Definition
  */
#define  GPIO_CRH_MODE8_Pos                       (0)
#define  GPIO_CRH_MODE8_Msk                       (0x3U << GPIO_CRH_MODE8_Pos)                      /*!<See MODE15*/
#define  GPIO_CRH_MODE8                           GPIO_CRH_MODE8_Msk
#define  GPIO_CRH_MODE8_0                         (0x1U << GPIO_CRH_MODE8_Pos) 
#define  GPIO_CRH_MODE8_1                         (0x2U << GPIO_CRH_MODE8_Pos) 
#define  GPIO_CRH_CNF8_Pos                        (2)
#define  GPIO_CRH_CNF8_Msk                        (0x3U << GPIO_CRH_CNF8_Pos)                       /*!<See CNF15*/
#define  GPIO_CRH_CNF8                            GPIO_CRH_CNF8_Msk
#define  GPIO_CRH_CNF8_0                          (0x1U << GPIO_CRH_CNF8_Pos) 
#define  GPIO_CRH_CNF8_1                          (0x2U << GPIO_CRH_CNF8_Pos) 
#define  GPIO_CRH_MODE9_Pos                       (4)
#define  GPIO_CRH_MODE9_Msk                       (0x3U << GPIO_CRH_MODE9_Pos)                      /*!<See MODE15*/
#define  GPIO_CRH_MODE9                           GPIO_CRH_MODE9_Msk
#define  GPIO_CRH_MODE9_0                         (0x1U << GPIO_CRH_MODE9_Pos) 
#define  GPIO_CRH_MODE9_1                         (0x2U << GPIO_CRH_MODE9_Pos) 
#define  GPIO_CRH_CNF9_Pos                        (6)
#define  GPIO_CRH_CNF9_Msk                        (0x3U << GPIO_CRH_CNF9_Pos)                       /*!<See CNF15*/
#define  GPIO_CRH_CNF9                            GPIO_CRH_CNF9_Msk
#define  GPIO_CRH_CNF9_0                          (0x1U << GPIO_CRH_CNF9_Pos) 
#define  GPIO_CRH_CNF9_1                          (0x2U << GPIO_CRH_CNF9_Pos) 
#define  GPIO_CRH_MODE10_Pos                      (8)
#define  GPIO_CRH_MODE10_Msk                      (0x3U << GPIO_CRH_MODE10_Pos)                     /*!<See MODE15*/
#define  GPIO_CRH_MODE10                          GPIO_CRH_MODE10_Msk
#define  GPIO_CRH_MODE10_0                        (0x1U << GPIO_CRH_MODE10_Pos) 
#define  GPIO_CRH_MODE10_1                        (0x2U << GPIO_CRH_MODE10_Pos) 
#define  GPIO_CRH_CNF10_Pos                       (10)
#define  GPIO_CRH_CNF10_Msk                       (0x3U << GPIO_CRH_CNF10_Pos)                      /*!<See CNF15*/
#define  GPIO_CRH_CNF10                           GPIO_CRH_CNF10_Msk
#define  GPIO_CRH_CNF10_0                         (0x1U << GPIO_CRH_CNF10_Pos) 
#define  GPIO_CRH_CNF10_1                         (0x2U << GPIO_CRH_CNF10_Pos) 
#define  GPIO_CRH_MODE11_Pos                      (12)
#define  GPIO_CRH_MODE11_Msk                      (0x3U << GPIO_CRH_MODE11_Pos)                     /*!<See MODE15*/
#define  GPIO_CRH_MODE11                          GPIO_CRH_MODE11_Msk
#define  GPIO_CRH_MODE11_0                        (0x1U << GPIO_CRH_MODE11_Pos) 
#define  GPIO_CRH_MODE11_1                        (0x2U << GPIO_CRH_MODE11_Pos) 
#define  GPIO_CRH_CNF11_Pos                       (14)
#define  GPIO_CRH_CNF11_Msk                       (0x3U << GPIO_CRH_CNF11_Pos)                      /*!<See CNF15*/
#define  GPIO_CRH_CNF11                           GPIO_CRH_CNF11_Msk
#define  GPIO_CRH_CNF11_0                         (0x1U << GPIO_CRH_CNF11_Pos) 
#define  GPIO_CRH_CNF11_1                         (0x2U << GPIO_CRH_CNF11_Pos) 
#define  GPIO_CRH_MODE12_Pos                      (16)
#define  GPIO_CRH_MODE12_Msk                      (0x3U << GPIO_CRH_MODE12_Pos)                     /*!<See MODE15*/
#define  GPIO_CRH_MODE12                          GPIO_CRH_MODE12_Msk
#define  GPIO_CRH_MODE12_0                        (0x1U << GPIO_CRH_MODE12_Pos) 
#define  GPIO_CRH_MODE12_1                        (0x2U << GPIO_CRH_MODE12_Pos) 
#define  GPIO_CRH_CNF12_Pos                       (18)
#define  GPIO_CRH_CNF12_Msk                       (0x3U << GPIO_CRH_CNF12_Pos)                      /*!<See CNF15*/
#define  GPIO_CRH_CNF12                           GPIO_CRH_CNF12_Msk
#define  GPIO_CRH_CNF12_0                         (0x1U << GPIO_CRH_CNF12_Pos) 
#define  GPIO_CRH_CNF12_1                         (0x2U << GPIO_CRH_CNF12_Pos) 
#define  GPIO_CRH_MODE13_Pos                      (20)
#define  GPIO_CRH_MODE13_Msk                      (0x3U << GPIO_CRH_MODE13_Pos)                     /*!<See MODE15*/
#define  GPIO_CRH_MODE13                          GPIO_CRH_MODE13_Msk
#define  GPIO_CRH_MODE13_0                        (0x1U << GPIO_CRH_MODE13_Pos) 
#define  GPIO_CRH_MODE13_1                        (0x2U << GPIO_CRH_MODE13_Pos) 
#define  GPIO_CRH_CNF13_Pos                       (22)
#define  GPIO_CRH_CNF13_Msk                       (0x3U << GPIO_CRH_CNF13_Pos)                      /*!<See CNF15*/
#define  GPIO_CRH_CNF13                           GPIO_CRH_CNF13_Msk
#define  GPIO_CRH_CNF13_0                         (0x1U << GPIO_CRH_CNF13_Pos) 
#define  GPIO_CRH_CNF13_1                         (0x2U << GPIO_CRH_CNF13_Pos) 
#define  GPIO_CRH_MODE14_Pos                      (24)
#define  GPIO_CRH_MODE14_Msk                      (0x3U << GPIO_CRH_MODE14_Pos)                     /*!<See MODE15*/
#define  GPIO_CRH_MODE14                          GPIO_CRH_MODE14_Msk
#define  GPIO_CRH_MODE14_0                        (0x1U << GPIO_CRH_MODE14_Pos) 
#define  GPIO_CRH_MODE14_1                        (0x2U << GPIO_CRH_MODE14_Pos) 
#define  GPIO_CRH_CNF14_Pos                       (26)
#define  GPIO_CRH_CNF14_Msk                       (0x3U << GPIO_CRH_CNF14_Pos)                      /*!<See CNF15*/
#define  GPIO_CRH_CNF14                           GPIO_CRH_CNF14_Msk
#define  GPIO_CRH_CNF14_0                         (0x1U << GPIO_CRH_CNF14_Pos) 
#define  GPIO_CRH_CNF14_1                         (0x2U << GPIO_CRH_CNF14_Pos) 
#define  GPIO_CRH_MODE15_Pos                      (28)
#define  GPIO_CRH_MODE15_Msk                      (0x3U << GPIO_CRH_MODE15_Pos)                     /*!<Set MODEy to 0 and port to input mode*/
#define  GPIO_CRH_MODE15                          GPIO_CRH_MODE15_Msk
#define  GPIO_CRH_MODE15_0                        (0x1U << GPIO_CRH_MODE15_Pos) 
#define  GPIO_CRH_MODE15_1                        (0x2U << GPIO_CRH_MODE15_Pos) 
#define  GPIO_CRH_CNF15_Pos                       (30)
#define  GPIO_CRH_CNF15_Msk                       (0x3U << GPIO_CRH_CNF15_Pos)                      /*!<Port configuration bits (y=7..0)*/
#define  GPIO_CRH_CNF15                           GPIO_CRH_CNF15_Msk
#define  GPIO_CRH_CNF15_0                         (0x1U << GPIO_CRH_CNF15_Pos) 
#define  GPIO_CRH_CNF15_1                         (0x2U << GPIO_CRH_CNF15_Pos) 

/**
  * @brief GPIO_IDR Register Bit Definition
  */
#define  GPIO_IDR_IDR0_Pos                        (0)
#define  GPIO_IDR_IDR0_Msk                        (0x1U << GPIO_IDR_IDR0_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR0                            GPIO_IDR_IDR0_Msk
#define  GPIO_IDR_IDR1_Pos                        (1)
#define  GPIO_IDR_IDR1_Msk                        (0x1U << GPIO_IDR_IDR1_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR1                            GPIO_IDR_IDR1_Msk
#define  GPIO_IDR_IDR2_Pos                        (2)
#define  GPIO_IDR_IDR2_Msk                        (0x1U << GPIO_IDR_IDR2_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR2                            GPIO_IDR_IDR2_Msk
#define  GPIO_IDR_IDR3_Pos                        (3)
#define  GPIO_IDR_IDR3_Msk                        (0x1U << GPIO_IDR_IDR3_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR3                            GPIO_IDR_IDR3_Msk
#define  GPIO_IDR_IDR4_Pos                        (4)
#define  GPIO_IDR_IDR4_Msk                        (0x1U << GPIO_IDR_IDR4_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR4                            GPIO_IDR_IDR4_Msk
#define  GPIO_IDR_IDR5_Pos                        (5)
#define  GPIO_IDR_IDR5_Msk                        (0x1U << GPIO_IDR_IDR5_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR5                            GPIO_IDR_IDR5_Msk
#define  GPIO_IDR_IDR6_Pos                        (6)
#define  GPIO_IDR_IDR6_Msk                        (0x1U << GPIO_IDR_IDR6_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR6                            GPIO_IDR_IDR6_Msk
#define  GPIO_IDR_IDR7_Pos                        (7)
#define  GPIO_IDR_IDR7_Msk                        (0x1U << GPIO_IDR_IDR7_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR7                            GPIO_IDR_IDR7_Msk
#define  GPIO_IDR_IDR8_Pos                        (8)
#define  GPIO_IDR_IDR8_Msk                        (0x1U << GPIO_IDR_IDR8_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR8                            GPIO_IDR_IDR8_Msk
#define  GPIO_IDR_IDR9_Pos                        (9)
#define  GPIO_IDR_IDR9_Msk                        (0x1U << GPIO_IDR_IDR9_Pos)                       /*!<Port input data*/
#define  GPIO_IDR_IDR9                            GPIO_IDR_IDR9_Msk
#define  GPIO_IDR_IDR10_Pos                       (10)
#define  GPIO_IDR_IDR10_Msk                       (0x1U << GPIO_IDR_IDR10_Pos)                      /*!<Port input data*/
#define  GPIO_IDR_IDR10                           GPIO_IDR_IDR10_Msk
#define  GPIO_IDR_IDR11_Pos                       (11)
#define  GPIO_IDR_IDR11_Msk                       (0x1U << GPIO_IDR_IDR11_Pos)                      /*!<Port input data*/
#define  GPIO_IDR_IDR11                           GPIO_IDR_IDR11_Msk
#define  GPIO_IDR_IDR12_Pos                       (12)
#define  GPIO_IDR_IDR12_Msk                       (0x1U << GPIO_IDR_IDR12_Pos)                      /*!<Port input data*/
#define  GPIO_IDR_IDR12                           GPIO_IDR_IDR12_Msk
#define  GPIO_IDR_IDR13_Pos                       (13)
#define  GPIO_IDR_IDR13_Msk                       (0x1U << GPIO_IDR_IDR13_Pos)                      /*!<Port input data*/
#define  GPIO_IDR_IDR13                           GPIO_IDR_IDR13_Msk
#define  GPIO_IDR_IDR14_Pos                       (14)
#define  GPIO_IDR_IDR14_Msk                       (0x1U << GPIO_IDR_IDR14_Pos)                      /*!<Port input data*/
#define  GPIO_IDR_IDR14                           GPIO_IDR_IDR14_Msk
#define  GPIO_IDR_IDR15_Pos                       (15)
#define  GPIO_IDR_IDR15_Msk                       (0x1U << GPIO_IDR_IDR15_Pos)                      /*!<Port input data*/
#define  GPIO_IDR_IDR15                           GPIO_IDR_IDR15_Msk

/**
  * @brief GPIO_ODR Register Bit Definition
  */
#define  GPIO_ODR_ODR0_Pos                        (0)
#define  GPIO_ODR_ODR0_Msk                        (0x1U << GPIO_ODR_ODR0_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR0                            GPIO_ODR_ODR0_Msk
#define  GPIO_ODR_ODR1_Pos                        (1)
#define  GPIO_ODR_ODR1_Msk                        (0x1U << GPIO_ODR_ODR1_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR1                            GPIO_ODR_ODR1_Msk
#define  GPIO_ODR_ODR2_Pos                        (2)
#define  GPIO_ODR_ODR2_Msk                        (0x1U << GPIO_ODR_ODR2_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR2                            GPIO_ODR_ODR2_Msk
#define  GPIO_ODR_ODR3_Pos                        (3)
#define  GPIO_ODR_ODR3_Msk                        (0x1U << GPIO_ODR_ODR3_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR3                            GPIO_ODR_ODR3_Msk
#define  GPIO_ODR_ODR4_Pos                        (4)
#define  GPIO_ODR_ODR4_Msk                        (0x1U << GPIO_ODR_ODR4_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR4                            GPIO_ODR_ODR4_Msk
#define  GPIO_ODR_ODR5_Pos                        (5)
#define  GPIO_ODR_ODR5_Msk                        (0x1U << GPIO_ODR_ODR5_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR5                            GPIO_ODR_ODR5_Msk
#define  GPIO_ODR_ODR6_Pos                        (6)
#define  GPIO_ODR_ODR6_Msk                        (0x1U << GPIO_ODR_ODR6_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR6                            GPIO_ODR_ODR6_Msk
#define  GPIO_ODR_ODR7_Pos                        (7)
#define  GPIO_ODR_ODR7_Msk                        (0x1U << GPIO_ODR_ODR7_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR7                            GPIO_ODR_ODR7_Msk
#define  GPIO_ODR_ODR8_Pos                        (8)
#define  GPIO_ODR_ODR8_Msk                        (0x1U << GPIO_ODR_ODR8_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR8                            GPIO_ODR_ODR8_Msk
#define  GPIO_ODR_ODR9_Pos                        (9)
#define  GPIO_ODR_ODR9_Msk                        (0x1U << GPIO_ODR_ODR9_Pos)                       /*!<Port output data*/
#define  GPIO_ODR_ODR9                            GPIO_ODR_ODR9_Msk
#define  GPIO_ODR_ODR10_Pos                       (10)
#define  GPIO_ODR_ODR10_Msk                       (0x1U << GPIO_ODR_ODR10_Pos)                      /*!<Port output data*/
#define  GPIO_ODR_ODR10                           GPIO_ODR_ODR10_Msk
#define  GPIO_ODR_ODR11_Pos                       (11)
#define  GPIO_ODR_ODR11_Msk                       (0x1U << GPIO_ODR_ODR11_Pos)                      /*!<Port output data*/
#define  GPIO_ODR_ODR11                           GPIO_ODR_ODR11_Msk
#define  GPIO_ODR_ODR12_Pos                       (12)
#define  GPIO_ODR_ODR12_Msk                       (0x1U << GPIO_ODR_ODR12_Pos)                      /*!<Port output data*/
#define  GPIO_ODR_ODR12                           GPIO_ODR_ODR12_Msk
#define  GPIO_ODR_ODR13_Pos                       (13)
#define  GPIO_ODR_ODR13_Msk                       (0x1U << GPIO_ODR_ODR13_Pos)                      /*!<Port output data*/
#define  GPIO_ODR_ODR13                           GPIO_ODR_ODR13_Msk
#define  GPIO_ODR_ODR14_Pos                       (14)
#define  GPIO_ODR_ODR14_Msk                       (0x1U << GPIO_ODR_ODR14_Pos)                      /*!<Port output data*/
#define  GPIO_ODR_ODR14                           GPIO_ODR_ODR14_Msk
#define  GPIO_ODR_ODR15_Pos                       (15)
#define  GPIO_ODR_ODR15_Msk                       (0x1U << GPIO_ODR_ODR15_Pos)                      /*!<Port output data*/
#define  GPIO_ODR_ODR15                           GPIO_ODR_ODR15_Msk

/**
  * @brief GPIO_BSRR Register Bit Definition
  */
#define  GPIO_BSRR_BS0_Pos                        (0)
#define  GPIO_BSRR_BS0_Msk                        (0x1U << GPIO_BSRR_BS0_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS0                            GPIO_BSRR_BS0_Msk
#define  GPIO_BSRR_BS1_Pos                        (1)
#define  GPIO_BSRR_BS1_Msk                        (0x1U << GPIO_BSRR_BS1_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS1                            GPIO_BSRR_BS1_Msk
#define  GPIO_BSRR_BS2_Pos                        (2)
#define  GPIO_BSRR_BS2_Msk                        (0x1U << GPIO_BSRR_BS2_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS2                            GPIO_BSRR_BS2_Msk
#define  GPIO_BSRR_BS3_Pos                        (3)
#define  GPIO_BSRR_BS3_Msk                        (0x1U << GPIO_BSRR_BS3_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS3                            GPIO_BSRR_BS3_Msk
#define  GPIO_BSRR_BS4_Pos                        (4)
#define  GPIO_BSRR_BS4_Msk                        (0x1U << GPIO_BSRR_BS4_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS4                            GPIO_BSRR_BS4_Msk
#define  GPIO_BSRR_BS5_Pos                        (5)
#define  GPIO_BSRR_BS5_Msk                        (0x1U << GPIO_BSRR_BS5_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS5                            GPIO_BSRR_BS5_Msk
#define  GPIO_BSRR_BS6_Pos                        (6)
#define  GPIO_BSRR_BS6_Msk                        (0x1U << GPIO_BSRR_BS6_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS6                            GPIO_BSRR_BS6_Msk
#define  GPIO_BSRR_BS7_Pos                        (7)
#define  GPIO_BSRR_BS7_Msk                        (0x1U << GPIO_BSRR_BS7_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS7                            GPIO_BSRR_BS7_Msk
#define  GPIO_BSRR_BS8_Pos                        (8)
#define  GPIO_BSRR_BS8_Msk                        (0x1U << GPIO_BSRR_BS8_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS8                            GPIO_BSRR_BS8_Msk
#define  GPIO_BSRR_BS9_Pos                        (9)
#define  GPIO_BSRR_BS9_Msk                        (0x1U << GPIO_BSRR_BS9_Pos)                       /*!<Port Set bit*/
#define  GPIO_BSRR_BS9                            GPIO_BSRR_BS9_Msk
#define  GPIO_BSRR_BS10_Pos                       (10)
#define  GPIO_BSRR_BS10_Msk                       (0x1U << GPIO_BSRR_BS10_Pos)                      /*!<Port Set bit*/
#define  GPIO_BSRR_BS10                           GPIO_BSRR_BS10_Msk
#define  GPIO_BSRR_BS11_Pos                       (11)
#define  GPIO_BSRR_BS11_Msk                       (0x1U << GPIO_BSRR_BS11_Pos)                      /*!<Port Set bit*/
#define  GPIO_BSRR_BS11                           GPIO_BSRR_BS11_Msk
#define  GPIO_BSRR_BS12_Pos                       (12)
#define  GPIO_BSRR_BS12_Msk                       (0x1U << GPIO_BSRR_BS12_Pos)                      /*!<Port Set bit*/
#define  GPIO_BSRR_BS12                           GPIO_BSRR_BS12_Msk
#define  GPIO_BSRR_BS13_Pos                       (13)
#define  GPIO_BSRR_BS13_Msk                       (0x1U << GPIO_BSRR_BS13_Pos)                      /*!<Port Set bit*/
#define  GPIO_BSRR_BS13                           GPIO_BSRR_BS13_Msk
#define  GPIO_BSRR_BS14_Pos                       (14)
#define  GPIO_BSRR_BS14_Msk                       (0x1U << GPIO_BSRR_BS14_Pos)                      /*!<Port Set bit*/
#define  GPIO_BSRR_BS14                           GPIO_BSRR_BS14_Msk
#define  GPIO_BSRR_BS15_Pos                       (15)
#define  GPIO_BSRR_BS15_Msk                       (0x1U << GPIO_BSRR_BS15_Pos)                      /*!<Port Set bit*/
#define  GPIO_BSRR_BS15                           GPIO_BSRR_BS15_Msk
#define  GPIO_BSRR_BR0_Pos                        (16)
#define  GPIO_BSRR_BR0_Msk                        (0x1U << GPIO_BSRR_BR0_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR0                            GPIO_BSRR_BR0_Msk
#define  GPIO_BSRR_BR1_Pos                        (17)
#define  GPIO_BSRR_BR1_Msk                        (0x1U << GPIO_BSRR_BR1_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR1                            GPIO_BSRR_BR1_Msk
#define  GPIO_BSRR_BR2_Pos                        (18)
#define  GPIO_BSRR_BR2_Msk                        (0x1U << GPIO_BSRR_BR2_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR2                            GPIO_BSRR_BR2_Msk
#define  GPIO_BSRR_BR3_Pos                        (19)
#define  GPIO_BSRR_BR3_Msk                        (0x1U << GPIO_BSRR_BR3_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR3                            GPIO_BSRR_BR3_Msk
#define  GPIO_BSRR_BR4_Pos                        (20)
#define  GPIO_BSRR_BR4_Msk                        (0x1U << GPIO_BSRR_BR4_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR4                            GPIO_BSRR_BR4_Msk
#define  GPIO_BSRR_BR5_Pos                        (21)
#define  GPIO_BSRR_BR5_Msk                        (0x1U << GPIO_BSRR_BR5_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR5                            GPIO_BSRR_BR5_Msk
#define  GPIO_BSRR_BR6_Pos                        (22)
#define  GPIO_BSRR_BR6_Msk                        (0x1U << GPIO_BSRR_BR6_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR6                            GPIO_BSRR_BR6_Msk
#define  GPIO_BSRR_BR7_Pos                        (23)
#define  GPIO_BSRR_BR7_Msk                        (0x1U << GPIO_BSRR_BR7_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR7                            GPIO_BSRR_BR7_Msk
#define  GPIO_BSRR_BR8_Pos                        (24)
#define  GPIO_BSRR_BR8_Msk                        (0x1U << GPIO_BSRR_BR8_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR8                            GPIO_BSRR_BR8_Msk
#define  GPIO_BSRR_BR9_Pos                        (25)
#define  GPIO_BSRR_BR9_Msk                        (0x1U << GPIO_BSRR_BR9_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BSRR_BR9                            GPIO_BSRR_BR9_Msk
#define  GPIO_BSRR_BR10_Pos                       (26)
#define  GPIO_BSRR_BR10_Msk                       (0x1U << GPIO_BSRR_BR10_Pos)                      /*!<Port Reset bit*/
#define  GPIO_BSRR_BR10                           GPIO_BSRR_BR10_Msk
#define  GPIO_BSRR_BR11_Pos                       (27)
#define  GPIO_BSRR_BR11_Msk                       (0x1U << GPIO_BSRR_BR11_Pos)                      /*!<Port Reset bit*/
#define  GPIO_BSRR_BR11                           GPIO_BSRR_BR11_Msk
#define  GPIO_BSRR_BR12_Pos                       (28)
#define  GPIO_BSRR_BR12_Msk                       (0x1U << GPIO_BSRR_BR12_Pos)                      /*!<Port Reset bit*/
#define  GPIO_BSRR_BR12                           GPIO_BSRR_BR12_Msk
#define  GPIO_BSRR_BR13_Pos                       (29)
#define  GPIO_BSRR_BR13_Msk                       (0x1U << GPIO_BSRR_BR13_Pos)                      /*!<Port Reset bit*/
#define  GPIO_BSRR_BR13                           GPIO_BSRR_BR13_Msk
#define  GPIO_BSRR_BR14_Pos                       (30)
#define  GPIO_BSRR_BR14_Msk                       (0x1U << GPIO_BSRR_BR14_Pos)                      /*!<Port Reset bit*/
#define  GPIO_BSRR_BR14                           GPIO_BSRR_BR14_Msk
#define  GPIO_BSRR_BR15_Pos                       (31)
#define  GPIO_BSRR_BR15_Msk                       (0x1U << GPIO_BSRR_BR15_Pos)                      /*!<Port Reset bit*/
#define  GPIO_BSRR_BR15                           GPIO_BSRR_BR15_Msk

/**
  * @brief GPIO_BRR Register Bit Definition
  */
#define  GPIO_BRR_BR0_Pos                         (0)
#define  GPIO_BRR_BR0_Msk                         (0x1U << GPIO_BRR_BR0_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR0                             GPIO_BRR_BR0_Msk
#define  GPIO_BRR_BR1_Pos                         (1)
#define  GPIO_BRR_BR1_Msk                         (0x1U << GPIO_BRR_BR1_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR1                             GPIO_BRR_BR1_Msk
#define  GPIO_BRR_BR2_Pos                         (2)
#define  GPIO_BRR_BR2_Msk                         (0x1U << GPIO_BRR_BR2_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR2                             GPIO_BRR_BR2_Msk
#define  GPIO_BRR_BR3_Pos                         (3)
#define  GPIO_BRR_BR3_Msk                         (0x1U << GPIO_BRR_BR3_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR3                             GPIO_BRR_BR3_Msk
#define  GPIO_BRR_BR4_Pos                         (4)
#define  GPIO_BRR_BR4_Msk                         (0x1U << GPIO_BRR_BR4_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR4                             GPIO_BRR_BR4_Msk
#define  GPIO_BRR_BR5_Pos                         (5)
#define  GPIO_BRR_BR5_Msk                         (0x1U << GPIO_BRR_BR5_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR5                             GPIO_BRR_BR5_Msk
#define  GPIO_BRR_BR6_Pos                         (6)
#define  GPIO_BRR_BR6_Msk                         (0x1U << GPIO_BRR_BR6_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR6                             GPIO_BRR_BR6_Msk
#define  GPIO_BRR_BR7_Pos                         (7)
#define  GPIO_BRR_BR7_Msk                         (0x1U << GPIO_BRR_BR7_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR7                             GPIO_BRR_BR7_Msk
#define  GPIO_BRR_BR8_Pos                         (8)
#define  GPIO_BRR_BR8_Msk                         (0x1U << GPIO_BRR_BR8_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR8                             GPIO_BRR_BR8_Msk
#define  GPIO_BRR_BR9_Pos                         (9)
#define  GPIO_BRR_BR9_Msk                         (0x1U << GPIO_BRR_BR9_Pos)                        /*!<Port Reset bit*/
#define  GPIO_BRR_BR9                             GPIO_BRR_BR9_Msk
#define  GPIO_BRR_BR10_Pos                        (10)
#define  GPIO_BRR_BR10_Msk                        (0x1U << GPIO_BRR_BR10_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BRR_BR10                            GPIO_BRR_BR10_Msk
#define  GPIO_BRR_BR11_Pos                        (11)
#define  GPIO_BRR_BR11_Msk                        (0x1U << GPIO_BRR_BR11_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BRR_BR11                            GPIO_BRR_BR11_Msk
#define  GPIO_BRR_BR12_Pos                        (12)
#define  GPIO_BRR_BR12_Msk                        (0x1U << GPIO_BRR_BR12_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BRR_BR12                            GPIO_BRR_BR12_Msk
#define  GPIO_BRR_BR13_Pos                        (13)
#define  GPIO_BRR_BR13_Msk                        (0x1U << GPIO_BRR_BR13_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BRR_BR13                            GPIO_BRR_BR13_Msk
#define  GPIO_BRR_BR14_Pos                        (14)
#define  GPIO_BRR_BR14_Msk                        (0x1U << GPIO_BRR_BR14_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BRR_BR14                            GPIO_BRR_BR14_Msk
#define  GPIO_BRR_BR15_Pos                        (15)
#define  GPIO_BRR_BR15_Msk                        (0x1U << GPIO_BRR_BR15_Pos)                       /*!<Port Reset bit*/
#define  GPIO_BRR_BR15                            GPIO_BRR_BR15_Msk

/**
  * @brief GPIO_LCKR Register Bit Definition
  */
#define  GPIO_LCKR_LCK0_Pos                       (0)
#define  GPIO_LCKR_LCK0_Msk                       (0x1U << GPIO_LCKR_LCK0_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK0                           GPIO_LCKR_LCK0_Msk
#define  GPIO_LCKR_LCK1_Pos                       (1)
#define  GPIO_LCKR_LCK1_Msk                       (0x1U << GPIO_LCKR_LCK1_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK1                           GPIO_LCKR_LCK1_Msk
#define  GPIO_LCKR_LCK2_Pos                       (2)
#define  GPIO_LCKR_LCK2_Msk                       (0x1U << GPIO_LCKR_LCK2_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK2                           GPIO_LCKR_LCK2_Msk
#define  GPIO_LCKR_LCK3_Pos                       (3)
#define  GPIO_LCKR_LCK3_Msk                       (0x1U << GPIO_LCKR_LCK3_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK3                           GPIO_LCKR_LCK3_Msk
#define  GPIO_LCKR_LCK4_Pos                       (4)
#define  GPIO_LCKR_LCK4_Msk                       (0x1U << GPIO_LCKR_LCK4_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK4                           GPIO_LCKR_LCK4_Msk
#define  GPIO_LCKR_LCK5_Pos                       (5)
#define  GPIO_LCKR_LCK5_Msk                       (0x1U << GPIO_LCKR_LCK5_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK5                           GPIO_LCKR_LCK5_Msk
#define  GPIO_LCKR_LCK6_Pos                       (6)
#define  GPIO_LCKR_LCK6_Msk                       (0x1U << GPIO_LCKR_LCK6_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK6                           GPIO_LCKR_LCK6_Msk
#define  GPIO_LCKR_LCK7_Pos                       (7)
#define  GPIO_LCKR_LCK7_Msk                       (0x1U << GPIO_LCKR_LCK7_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK7                           GPIO_LCKR_LCK7_Msk
#define  GPIO_LCKR_LCK8_Pos                       (8)
#define  GPIO_LCKR_LCK8_Msk                       (0x1U << GPIO_LCKR_LCK8_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK8                           GPIO_LCKR_LCK8_Msk
#define  GPIO_LCKR_LCK9_Pos                       (9)
#define  GPIO_LCKR_LCK9_Msk                       (0x1U << GPIO_LCKR_LCK9_Pos)                      /*!<Lock bit*/
#define  GPIO_LCKR_LCK9                           GPIO_LCKR_LCK9_Msk
#define  GPIO_LCKR_LCK10_Pos                      (10)
#define  GPIO_LCKR_LCK10_Msk                      (0x1U << GPIO_LCKR_LCK10_Pos)                     /*!<Lock bit*/
#define  GPIO_LCKR_LCK10                          GPIO_LCKR_LCK10_Msk
#define  GPIO_LCKR_LCK11_Pos                      (11)
#define  GPIO_LCKR_LCK11_Msk                      (0x1U << GPIO_LCKR_LCK11_Pos)                     /*!<Lock bit*/
#define  GPIO_LCKR_LCK11                          GPIO_LCKR_LCK11_Msk
#define  GPIO_LCKR_LCK12_Pos                      (12)
#define  GPIO_LCKR_LCK12_Msk                      (0x1U << GPIO_LCKR_LCK12_Pos)                     /*!<Lock bit*/
#define  GPIO_LCKR_LCK12                          GPIO_LCKR_LCK12_Msk
#define  GPIO_LCKR_LCK13_Pos                      (13)
#define  GPIO_LCKR_LCK13_Msk                      (0x1U << GPIO_LCKR_LCK13_Pos)                     /*!<Lock bit*/
#define  GPIO_LCKR_LCK13                          GPIO_LCKR_LCK13_Msk
#define  GPIO_LCKR_LCK14_Pos                      (14)
#define  GPIO_LCKR_LCK14_Msk                      (0x1U << GPIO_LCKR_LCK14_Pos)                     /*!<Lock bit*/
#define  GPIO_LCKR_LCK14                          GPIO_LCKR_LCK14_Msk
#define  GPIO_LCKR_LCK15_Pos                      (15)
#define  GPIO_LCKR_LCK15_Msk                      (0x1U << GPIO_LCKR_LCK15_Pos)                     /*!<Lock bit*/
#define  GPIO_LCKR_LCK15                          GPIO_LCKR_LCK15_Msk
#define  GPIO_LCKR_LCKK_Pos                       (16)
#define  GPIO_LCKR_LCKK_Msk                       (0x1U << GPIO_LCKR_LCKK_Pos)                      /*!<Lock key*/
#define  GPIO_LCKR_LCKK                           GPIO_LCKR_LCKK_Msk

/**
  * @brief GPIO_DCR Register Bit Definition
  */
#define  GPIO_DCR_PX0_Pos                         (0)
#define  GPIO_DCR_PX0_Msk                         (0x3U << GPIO_DCR_PX0_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX0                             GPIO_DCR_PX0_Msk
#define  GPIO_DCR_PX0_0                           (0x1U << GPIO_DCR_PX0_Pos) 
#define  GPIO_DCR_PX0_1                           (0x2U << GPIO_DCR_PX0_Pos) 
#define  GPIO_DCR_PX1_Pos                         (2)
#define  GPIO_DCR_PX1_Msk                         (0x3U << GPIO_DCR_PX1_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX1                             GPIO_DCR_PX1_Msk
#define  GPIO_DCR_PX1_0                           (0x1U << GPIO_DCR_PX1_Pos) 
#define  GPIO_DCR_PX1_1                           (0x2U << GPIO_DCR_PX1_Pos) 
#define  GPIO_DCR_PX2_Pos                         (4)
#define  GPIO_DCR_PX2_Msk                         (0x3U << GPIO_DCR_PX2_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX2                             GPIO_DCR_PX2_Msk
#define  GPIO_DCR_PX2_0                           (0x1U << GPIO_DCR_PX2_Pos) 
#define  GPIO_DCR_PX2_1                           (0x2U << GPIO_DCR_PX2_Pos) 
#define  GPIO_DCR_PX3_Pos                         (6)
#define  GPIO_DCR_PX3_Msk                         (0x3U << GPIO_DCR_PX3_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX3                             GPIO_DCR_PX3_Msk
#define  GPIO_DCR_PX3_0                           (0x1U << GPIO_DCR_PX3_Pos) 
#define  GPIO_DCR_PX3_1                           (0x2U << GPIO_DCR_PX3_Pos) 
#define  GPIO_DCR_PX4_Pos                         (8)
#define  GPIO_DCR_PX4_Msk                         (0x3U << GPIO_DCR_PX4_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX4                             GPIO_DCR_PX4_Msk
#define  GPIO_DCR_PX4_0                           (0x1U << GPIO_DCR_PX4_Pos) 
#define  GPIO_DCR_PX4_1                           (0x2U << GPIO_DCR_PX4_Pos) 
#define  GPIO_DCR_PX5_Pos                         (10)
#define  GPIO_DCR_PX5_Msk                         (0x3U << GPIO_DCR_PX5_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX5                             GPIO_DCR_PX5_Msk
#define  GPIO_DCR_PX5_0                           (0x1U << GPIO_DCR_PX5_Pos) 
#define  GPIO_DCR_PX5_1                           (0x2U << GPIO_DCR_PX5_Pos) 
#define  GPIO_DCR_PX6_Pos                         (12)
#define  GPIO_DCR_PX6_Msk                         (0x3U << GPIO_DCR_PX6_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX6                             GPIO_DCR_PX6_Msk
#define  GPIO_DCR_PX6_0                           (0x1U << GPIO_DCR_PX6_Pos) 
#define  GPIO_DCR_PX6_1                           (0x2U << GPIO_DCR_PX6_Pos) 
#define  GPIO_DCR_PX7_Pos                         (14)
#define  GPIO_DCR_PX7_Msk                         (0x3U << GPIO_DCR_PX7_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX7                             GPIO_DCR_PX7_Msk
#define  GPIO_DCR_PX7_0                           (0x1U << GPIO_DCR_PX7_Pos) 
#define  GPIO_DCR_PX7_1                           (0x2U << GPIO_DCR_PX7_Pos) 
#define  GPIO_DCR_PX8_Pos                         (16)
#define  GPIO_DCR_PX8_Msk                         (0x3U << GPIO_DCR_PX8_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX8                             GPIO_DCR_PX8_Msk
#define  GPIO_DCR_PX8_0                           (0x1U << GPIO_DCR_PX8_Pos) 
#define  GPIO_DCR_PX8_1                           (0x2U << GPIO_DCR_PX8_Pos) 
#define  GPIO_DCR_PX9_Pos                         (18)
#define  GPIO_DCR_PX9_Msk                         (0x3U << GPIO_DCR_PX9_Pos)                        /*!<PX*/
#define  GPIO_DCR_PX9                             GPIO_DCR_PX9_Msk
#define  GPIO_DCR_PX9_0                           (0x1U << GPIO_DCR_PX9_Pos) 
#define  GPIO_DCR_PX9_1                           (0x2U << GPIO_DCR_PX9_Pos) 
#define  GPIO_DCR_PX10_Pos                        (20)
#define  GPIO_DCR_PX10_Msk                        (0x3U << GPIO_DCR_PX10_Pos)                       /*!<PX*/
#define  GPIO_DCR_PX10                            GPIO_DCR_PX10_Msk
#define  GPIO_DCR_PX10_0                          (0x1U << GPIO_DCR_PX10_Pos) 
#define  GPIO_DCR_PX10_1                          (0x2U << GPIO_DCR_PX10_Pos) 
#define  GPIO_DCR_PX11_Pos                        (22)
#define  GPIO_DCR_PX11_Msk                        (0x3U << GPIO_DCR_PX11_Pos)                       /*!<PX*/
#define  GPIO_DCR_PX11                            GPIO_DCR_PX11_Msk
#define  GPIO_DCR_PX11_0                          (0x1U << GPIO_DCR_PX11_Pos) 
#define  GPIO_DCR_PX11_1                          (0x2U << GPIO_DCR_PX11_Pos) 
#define  GPIO_DCR_PX12_Pos                        (24)
#define  GPIO_DCR_PX12_Msk                        (0x3U << GPIO_DCR_PX12_Pos)                       /*!<PX*/
#define  GPIO_DCR_PX12                            GPIO_DCR_PX12_Msk
#define  GPIO_DCR_PX12_0                          (0x1U << GPIO_DCR_PX12_Pos) 
#define  GPIO_DCR_PX12_1                          (0x2U << GPIO_DCR_PX12_Pos) 
#define  GPIO_DCR_PX13_Pos                        (26)
#define  GPIO_DCR_PX13_Msk                        (0x3U << GPIO_DCR_PX13_Pos)                       /*!<PX*/
#define  GPIO_DCR_PX13                            GPIO_DCR_PX13_Msk
#define  GPIO_DCR_PX13_0                          (0x1U << GPIO_DCR_PX13_Pos) 
#define  GPIO_DCR_PX13_1                          (0x2U << GPIO_DCR_PX13_Pos) 
#define  GPIO_DCR_PX14_Pos                        (28)
#define  GPIO_DCR_PX14_Msk                        (0x3U << GPIO_DCR_PX14_Pos)                       /*!<PX*/
#define  GPIO_DCR_PX14                            GPIO_DCR_PX14_Msk
#define  GPIO_DCR_PX14_0                          (0x1U << GPIO_DCR_PX14_Pos) 
#define  GPIO_DCR_PX14_1                          (0x2U << GPIO_DCR_PX14_Pos) 
#define  GPIO_DCR_PX15_Pos                        (30)
#define  GPIO_DCR_PX15_Msk                        (0x3U << GPIO_DCR_PX15_Pos)                       /*!<PX*/
#define  GPIO_DCR_PX15                            GPIO_DCR_PX15_Msk
#define  GPIO_DCR_PX15_0                          (0x1U << GPIO_DCR_PX15_Pos) 
#define  GPIO_DCR_PX15_1                          (0x2U << GPIO_DCR_PX15_Pos) 

/**
  * @brief GPIO_AFRL Register Bit Definition
  */
#define  GPIO_AFRL_AFR0_Pos                       (0)
#define  GPIO_AFRL_AFR0_Msk                       (0xFU << GPIO_AFRL_AFR0_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR0                           GPIO_AFRL_AFR0_Msk
#define  GPIO_AFRL_AFR0_0                         (0x1U << GPIO_AFRL_AFR0_Pos) 
#define  GPIO_AFRL_AFR0_1                         (0x2U << GPIO_AFRL_AFR0_Pos) 
#define  GPIO_AFRL_AFR0_2                         (0x4U << GPIO_AFRL_AFR0_Pos) 
#define  GPIO_AFRL_AFR0_3                         (0x8U << GPIO_AFRL_AFR0_Pos) 
#define  GPIO_AFRL_AFR1_Pos                       (4)
#define  GPIO_AFRL_AFR1_Msk                       (0xFU << GPIO_AFRL_AFR1_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR1                           GPIO_AFRL_AFR1_Msk
#define  GPIO_AFRL_AFR1_0                         (0x1U << GPIO_AFRL_AFR1_Pos) 
#define  GPIO_AFRL_AFR1_1                         (0x2U << GPIO_AFRL_AFR1_Pos) 
#define  GPIO_AFRL_AFR1_2                         (0x4U << GPIO_AFRL_AFR1_Pos) 
#define  GPIO_AFRL_AFR1_3                         (0x8U << GPIO_AFRL_AFR1_Pos) 
#define  GPIO_AFRL_AFR2_Pos                       (8)
#define  GPIO_AFRL_AFR2_Msk                       (0xFU << GPIO_AFRL_AFR2_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR2                           GPIO_AFRL_AFR2_Msk
#define  GPIO_AFRL_AFR2_0                         (0x1U << GPIO_AFRL_AFR2_Pos) 
#define  GPIO_AFRL_AFR2_1                         (0x2U << GPIO_AFRL_AFR2_Pos) 
#define  GPIO_AFRL_AFR2_2                         (0x4U << GPIO_AFRL_AFR2_Pos) 
#define  GPIO_AFRL_AFR2_3                         (0x8U << GPIO_AFRL_AFR2_Pos) 
#define  GPIO_AFRL_AFR3_Pos                       (12)
#define  GPIO_AFRL_AFR3_Msk                       (0xFU << GPIO_AFRL_AFR3_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR3                           GPIO_AFRL_AFR3_Msk
#define  GPIO_AFRL_AFR3_0                         (0x1U << GPIO_AFRL_AFR3_Pos) 
#define  GPIO_AFRL_AFR3_1                         (0x2U << GPIO_AFRL_AFR3_Pos) 
#define  GPIO_AFRL_AFR3_2                         (0x4U << GPIO_AFRL_AFR3_Pos) 
#define  GPIO_AFRL_AFR3_3                         (0x8U << GPIO_AFRL_AFR3_Pos) 
#define  GPIO_AFRL_AFR4_Pos                       (16)
#define  GPIO_AFRL_AFR4_Msk                       (0xFU << GPIO_AFRL_AFR4_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR4                           GPIO_AFRL_AFR4_Msk
#define  GPIO_AFRL_AFR4_0                         (0x1U << GPIO_AFRL_AFR4_Pos) 
#define  GPIO_AFRL_AFR4_1                         (0x2U << GPIO_AFRL_AFR4_Pos) 
#define  GPIO_AFRL_AFR4_2                         (0x4U << GPIO_AFRL_AFR4_Pos) 
#define  GPIO_AFRL_AFR4_3                         (0x8U << GPIO_AFRL_AFR4_Pos) 
#define  GPIO_AFRL_AFR5_Pos                       (20)
#define  GPIO_AFRL_AFR5_Msk                       (0xFU << GPIO_AFRL_AFR5_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR5                           GPIO_AFRL_AFR5_Msk
#define  GPIO_AFRL_AFR5_0                         (0x1U << GPIO_AFRL_AFR5_Pos) 
#define  GPIO_AFRL_AFR5_1                         (0x2U << GPIO_AFRL_AFR5_Pos) 
#define  GPIO_AFRL_AFR5_2                         (0x4U << GPIO_AFRL_AFR5_Pos) 
#define  GPIO_AFRL_AFR5_3                         (0x8U << GPIO_AFRL_AFR5_Pos) 
#define  GPIO_AFRL_AFR6_Pos                       (24)
#define  GPIO_AFRL_AFR6_Msk                       (0xFU << GPIO_AFRL_AFR6_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR6                           GPIO_AFRL_AFR6_Msk
#define  GPIO_AFRL_AFR6_0                         (0x1U << GPIO_AFRL_AFR6_Pos) 
#define  GPIO_AFRL_AFR6_1                         (0x2U << GPIO_AFRL_AFR6_Pos) 
#define  GPIO_AFRL_AFR6_2                         (0x4U << GPIO_AFRL_AFR6_Pos) 
#define  GPIO_AFRL_AFR6_3                         (0x8U << GPIO_AFRL_AFR6_Pos) 
#define  GPIO_AFRL_AFR7_Pos                       (28)
#define  GPIO_AFRL_AFR7_Msk                       (0xFU << GPIO_AFRL_AFR7_Pos)                      /*!<Port x alternate function bit y (y = 0..7), which can be accessed by software to configure the function.*/
#define  GPIO_AFRL_AFR7                           GPIO_AFRL_AFR7_Msk
#define  GPIO_AFRL_AFR7_0                         (0x1U << GPIO_AFRL_AFR7_Pos) 
#define  GPIO_AFRL_AFR7_1                         (0x2U << GPIO_AFRL_AFR7_Pos) 
#define  GPIO_AFRL_AFR7_2                         (0x4U << GPIO_AFRL_AFR7_Pos) 
#define  GPIO_AFRL_AFR7_3                         (0x8U << GPIO_AFRL_AFR7_Pos) 

/**
  * @brief GPIO_AFRH Register Bit Definition
  */
#define  GPIO_AFRH_AFR8_Pos                       (0)
#define  GPIO_AFRH_AFR8_Msk                       (0xFU << GPIO_AFRH_AFR8_Pos)                      /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR8                           GPIO_AFRH_AFR8_Msk
#define  GPIO_AFRH_AFR8_0                         (0x1U << GPIO_AFRH_AFR8_Pos) 
#define  GPIO_AFRH_AFR8_1                         (0x2U << GPIO_AFRH_AFR8_Pos) 
#define  GPIO_AFRH_AFR8_2                         (0x4U << GPIO_AFRH_AFR8_Pos) 
#define  GPIO_AFRH_AFR8_3                         (0x8U << GPIO_AFRH_AFR8_Pos) 
#define  GPIO_AFRH_AFR9_Pos                       (4)
#define  GPIO_AFRH_AFR9_Msk                       (0xFU << GPIO_AFRH_AFR9_Pos)                      /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR9                           GPIO_AFRH_AFR9_Msk
#define  GPIO_AFRH_AFR9_0                         (0x1U << GPIO_AFRH_AFR9_Pos) 
#define  GPIO_AFRH_AFR9_1                         (0x2U << GPIO_AFRH_AFR9_Pos) 
#define  GPIO_AFRH_AFR9_2                         (0x4U << GPIO_AFRH_AFR9_Pos) 
#define  GPIO_AFRH_AFR9_3                         (0x8U << GPIO_AFRH_AFR9_Pos) 
#define  GPIO_AFRH_AFR10_Pos                      (8)
#define  GPIO_AFRH_AFR10_Msk                      (0xFU << GPIO_AFRH_AFR10_Pos)                     /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR10                          GPIO_AFRH_AFR10_Msk
#define  GPIO_AFRH_AFR10_0                        (0x1U << GPIO_AFRH_AFR10_Pos) 
#define  GPIO_AFRH_AFR10_1                        (0x2U << GPIO_AFRH_AFR10_Pos) 
#define  GPIO_AFRH_AFR10_2                        (0x4U << GPIO_AFRH_AFR10_Pos) 
#define  GPIO_AFRH_AFR10_3                        (0x8U << GPIO_AFRH_AFR10_Pos) 
#define  GPIO_AFRH_AFR11_Pos                      (12)
#define  GPIO_AFRH_AFR11_Msk                      (0xFU << GPIO_AFRH_AFR11_Pos)                     /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR11                          GPIO_AFRH_AFR11_Msk
#define  GPIO_AFRH_AFR11_0                        (0x1U << GPIO_AFRH_AFR11_Pos) 
#define  GPIO_AFRH_AFR11_1                        (0x2U << GPIO_AFRH_AFR11_Pos) 
#define  GPIO_AFRH_AFR11_2                        (0x4U << GPIO_AFRH_AFR11_Pos) 
#define  GPIO_AFRH_AFR11_3                        (0x8U << GPIO_AFRH_AFR11_Pos) 
#define  GPIO_AFRH_AFR12_Pos                      (16)
#define  GPIO_AFRH_AFR12_Msk                      (0xFU << GPIO_AFRH_AFR12_Pos)                     /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR12                          GPIO_AFRH_AFR12_Msk
#define  GPIO_AFRH_AFR12_0                        (0x1U << GPIO_AFRH_AFR12_Pos) 
#define  GPIO_AFRH_AFR12_1                        (0x2U << GPIO_AFRH_AFR12_Pos) 
#define  GPIO_AFRH_AFR12_2                        (0x4U << GPIO_AFRH_AFR12_Pos) 
#define  GPIO_AFRH_AFR12_3                        (0x8U << GPIO_AFRH_AFR12_Pos) 
#define  GPIO_AFRH_AFR13_Pos                      (20)
#define  GPIO_AFRH_AFR13_Msk                      (0xFU << GPIO_AFRH_AFR13_Pos)                     /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR13                          GPIO_AFRH_AFR13_Msk
#define  GPIO_AFRH_AFR13_0                        (0x1U << GPIO_AFRH_AFR13_Pos) 
#define  GPIO_AFRH_AFR13_1                        (0x2U << GPIO_AFRH_AFR13_Pos) 
#define  GPIO_AFRH_AFR13_2                        (0x4U << GPIO_AFRH_AFR13_Pos) 
#define  GPIO_AFRH_AFR13_3                        (0x8U << GPIO_AFRH_AFR13_Pos) 
#define  GPIO_AFRH_AFR14_Pos                      (24)
#define  GPIO_AFRH_AFR14_Msk                      (0xFU << GPIO_AFRH_AFR14_Pos)                     /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR14                          GPIO_AFRH_AFR14_Msk
#define  GPIO_AFRH_AFR14_0                        (0x1U << GPIO_AFRH_AFR14_Pos) 
#define  GPIO_AFRH_AFR14_1                        (0x2U << GPIO_AFRH_AFR14_Pos) 
#define  GPIO_AFRH_AFR14_2                        (0x4U << GPIO_AFRH_AFR14_Pos) 
#define  GPIO_AFRH_AFR14_3                        (0x8U << GPIO_AFRH_AFR14_Pos) 
#define  GPIO_AFRH_AFR15_Pos                      (28)
#define  GPIO_AFRH_AFR15_Msk                      (0xFU << GPIO_AFRH_AFR15_Pos)                     /*!<Port x alternate function bit, which can be accessed by software to configure the function.*/
#define  GPIO_AFRH_AFR15                          GPIO_AFRH_AFR15_Msk
#define  GPIO_AFRH_AFR15_0                        (0x1U << GPIO_AFRH_AFR15_Pos) 
#define  GPIO_AFRH_AFR15_1                        (0x2U << GPIO_AFRH_AFR15_Pos) 
#define  GPIO_AFRH_AFR15_2                        (0x4U << GPIO_AFRH_AFR15_Pos) 
#define  GPIO_AFRH_AFR15_3                        (0x8U << GPIO_AFRH_AFR15_Pos) 


#endif

