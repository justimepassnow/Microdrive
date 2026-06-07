/***********************************************************************************************************************
    @file     reg_syscfg.h
    @author   VV TEAM
    @brief    This flie contains all the SYSCFG's register and its field definition.
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

#ifndef __REG_SYSCFG_H
#define __REG_SYSCFG_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief SYSCFG Base Address Definition
  */
#define  SYSCFG_BASE                               0x40010000 /*!<Base Address: 0x40010000*/

/**
  * @brief SYSCFG Register Structure Definition
  */
typedef struct
{
    __IO uint32_t CFGR;                /*!<SYSCFG SYSCFG configuration register 1         offset: 0x00       */
    __IO uint32_t RESERVED0x04[1];     /*!<                                               offset: 0x04       */
    __IO uint32_t EXTICR1;             /*!<SYSCFG SYSCFG external interrupt               offset: 0x08
                                           configuration register 1                                          */
    __IO uint32_t EXTICR2;             /*!<SYSCFG SYSCFG external interrupt               offset: 0x0C
                                           configuration register 2                                          */
    __IO uint32_t EXTICR3;             /*!<SYSCFG SYSCFG external interrupt               offset: 0x10
                                           configuration register 3                                          */
    __IO uint32_t EXTICR4;             /*!<SYSCFG SYSCFG external interrupt               offset: 0x14
                                           configuration register 4                                          */
    __IO uint32_t PADHYS;              /*!<SYSCFG SYSCFG PAD configuration register       offset: 0x18       */
} SYSCFG_TypeDef;

/**
  * @brief SYSCFG type pointer Definition
  */
#define SYSCFG                                    ((SYSCFG_TypeDef *)SYSCFG_BASE)

/**
  * @brief SYSCFG_CFGR Register Bit Definition
  */
#define  SYSCFG_CFGR_MEM_MODE_Pos                 (0)
#define  SYSCFG_CFGR_MEM_MODE_Msk                 (0x3U << SYSCFG_CFGR_MEM_MODE_Pos) /*!<Memory selection Bit*/
#define  SYSCFG_CFGR_MEM_MODE                     SYSCFG_CFGR_MEM_MODE_Msk
#define  SYSCFG_CFGR_MEM_MODE_0                   (0x1U << SYSCFG_CFGR_MEM_MODE_Pos)
#define  SYSCFG_CFGR_MEM_MODE_1                   (0x2U << SYSCFG_CFGR_MEM_MODE_Pos)

/**
  * @brief SYSCFG_EXTICR1 Register Bit Definition
  */
#define  SYSCFG_EXTICR1_EXTI0_Pos                 (0)
#define  SYSCFG_EXTICR1_EXTI0_Msk                 (0xFU << SYSCFG_EXTICR1_EXTI0_Pos) /*!<EXTIx configuration (x=0...3) */
#define  SYSCFG_EXTICR1_EXTI0                     SYSCFG_EXTICR1_EXTI0_Msk
#define  SYSCFG_EXTICR1_EXTI0_0                   (0x1U << SYSCFG_EXTICR1_EXTI0_Pos)
#define  SYSCFG_EXTICR1_EXTI0_1                   (0x2U << SYSCFG_EXTICR1_EXTI0_Pos)
#define  SYSCFG_EXTICR1_EXTI0_2                   (0x4U << SYSCFG_EXTICR1_EXTI0_Pos)
#define  SYSCFG_EXTICR1_EXTI0_3                   (0x8U << SYSCFG_EXTICR1_EXTI0_Pos)
#define  SYSCFG_EXTICR1_EXTI1_Pos                 (4)
#define  SYSCFG_EXTICR1_EXTI1_Msk                 (0xFU << SYSCFG_EXTICR1_EXTI1_Pos) /*!<EXTIx configuration (x=0...3) */
#define  SYSCFG_EXTICR1_EXTI1                     SYSCFG_EXTICR1_EXTI1_Msk
#define  SYSCFG_EXTICR1_EXTI1_0                   (0x1U << SYSCFG_EXTICR1_EXTI1_Pos)
#define  SYSCFG_EXTICR1_EXTI1_1                   (0x2U << SYSCFG_EXTICR1_EXTI1_Pos)
#define  SYSCFG_EXTICR1_EXTI1_2                   (0x4U << SYSCFG_EXTICR1_EXTI1_Pos)
#define  SYSCFG_EXTICR1_EXTI1_3                   (0x8U << SYSCFG_EXTICR1_EXTI1_Pos)
#define  SYSCFG_EXTICR1_EXTI2_Pos                 (8)
#define  SYSCFG_EXTICR1_EXTI2_Msk                 (0xFU << SYSCFG_EXTICR1_EXTI2_Pos) /*!<EXTIx configuration (x=0...3) */
#define  SYSCFG_EXTICR1_EXTI2                     SYSCFG_EXTICR1_EXTI2_Msk
#define  SYSCFG_EXTICR1_EXTI2_0                   (0x1U << SYSCFG_EXTICR1_EXTI2_Pos)
#define  SYSCFG_EXTICR1_EXTI2_1                   (0x2U << SYSCFG_EXTICR1_EXTI2_Pos)
#define  SYSCFG_EXTICR1_EXTI2_2                   (0x4U << SYSCFG_EXTICR1_EXTI2_Pos)
#define  SYSCFG_EXTICR1_EXTI2_3                   (0x8U << SYSCFG_EXTICR1_EXTI2_Pos)
#define  SYSCFG_EXTICR1_EXTI3_Pos                 (12)
#define  SYSCFG_EXTICR1_EXTI3_Msk                 (0xFU << SYSCFG_EXTICR1_EXTI3_Pos) /*!<EXTIx configuration (x=0...3) */
#define  SYSCFG_EXTICR1_EXTI3                     SYSCFG_EXTICR1_EXTI3_Msk
#define  SYSCFG_EXTICR1_EXTI3_0                   (0x1U << SYSCFG_EXTICR1_EXTI3_Pos)
#define  SYSCFG_EXTICR1_EXTI3_1                   (0x2U << SYSCFG_EXTICR1_EXTI3_Pos)
#define  SYSCFG_EXTICR1_EXTI3_2                   (0x4U << SYSCFG_EXTICR1_EXTI3_Pos)
#define  SYSCFG_EXTICR1_EXTI3_3                   (0x8U << SYSCFG_EXTICR1_EXTI3_Pos)

/**
  * @brief SYSCFG_EXTICR2 Register Bit Definition
  */
#define  SYSCFG_EXTICR2_EXTI4_Pos                 (0)
#define  SYSCFG_EXTICR2_EXTI4_Msk                 (0xFU << SYSCFG_EXTICR2_EXTI4_Pos) /*!<EXTIx configuration (x=4...7) */
#define  SYSCFG_EXTICR2_EXTI4                     SYSCFG_EXTICR2_EXTI4_Msk
#define  SYSCFG_EXTICR2_EXTI4_0                   (0x1U << SYSCFG_EXTICR2_EXTI4_Pos)
#define  SYSCFG_EXTICR2_EXTI4_1                   (0x2U << SYSCFG_EXTICR2_EXTI4_Pos)
#define  SYSCFG_EXTICR2_EXTI4_2                   (0x4U << SYSCFG_EXTICR2_EXTI4_Pos)
#define  SYSCFG_EXTICR2_EXTI4_3                   (0x8U << SYSCFG_EXTICR2_EXTI4_Pos)
#define  SYSCFG_EXTICR2_EXTI5_Pos                 (4)
#define  SYSCFG_EXTICR2_EXTI5_Msk                 (0xFU << SYSCFG_EXTICR2_EXTI5_Pos) /*!<EXTIx configuration (x=4...7) */
#define  SYSCFG_EXTICR2_EXTI5                     SYSCFG_EXTICR2_EXTI5_Msk
#define  SYSCFG_EXTICR2_EXTI5_0                   (0x1U << SYSCFG_EXTICR2_EXTI5_Pos)
#define  SYSCFG_EXTICR2_EXTI5_1                   (0x2U << SYSCFG_EXTICR2_EXTI5_Pos)
#define  SYSCFG_EXTICR2_EXTI5_2                   (0x4U << SYSCFG_EXTICR2_EXTI5_Pos)
#define  SYSCFG_EXTICR2_EXTI5_3                   (0x8U << SYSCFG_EXTICR2_EXTI5_Pos)
#define  SYSCFG_EXTICR2_EXTI6_Pos                 (8)
#define  SYSCFG_EXTICR2_EXTI6_Msk                 (0xFU << SYSCFG_EXTICR2_EXTI6_Pos) /*!<EXTIx configuration (x=4...7) */
#define  SYSCFG_EXTICR2_EXTI6                     SYSCFG_EXTICR2_EXTI6_Msk
#define  SYSCFG_EXTICR2_EXTI6_0                   (0x1U << SYSCFG_EXTICR2_EXTI6_Pos)
#define  SYSCFG_EXTICR2_EXTI6_1                   (0x2U << SYSCFG_EXTICR2_EXTI6_Pos)
#define  SYSCFG_EXTICR2_EXTI6_2                   (0x4U << SYSCFG_EXTICR2_EXTI6_Pos)
#define  SYSCFG_EXTICR2_EXTI6_3                   (0x8U << SYSCFG_EXTICR2_EXTI6_Pos)
#define  SYSCFG_EXTICR2_EXTI7_Pos                 (12)
#define  SYSCFG_EXTICR2_EXTI7_Msk                 (0xFU << SYSCFG_EXTICR2_EXTI7_Pos) /*!<EXTIx configuration (x=4...7) */
#define  SYSCFG_EXTICR2_EXTI7                     SYSCFG_EXTICR2_EXTI7_Msk
#define  SYSCFG_EXTICR2_EXTI7_0                   (0x1U << SYSCFG_EXTICR2_EXTI7_Pos)
#define  SYSCFG_EXTICR2_EXTI7_1                   (0x2U << SYSCFG_EXTICR2_EXTI7_Pos)
#define  SYSCFG_EXTICR2_EXTI7_2                   (0x4U << SYSCFG_EXTICR2_EXTI7_Pos)
#define  SYSCFG_EXTICR2_EXTI7_3                   (0x8U << SYSCFG_EXTICR2_EXTI7_Pos)

/**
  * @brief SYSCFG_EXTICR3 Register Bit Definition
  */
#define  SYSCFG_EXTICR3_EXTI8_Pos                 (0)
#define  SYSCFG_EXTICR3_EXTI8_Msk                 (0xFU << SYSCFG_EXTICR3_EXTI8_Pos) /*!<EXTIx configuration (x=8...11) */
#define  SYSCFG_EXTICR3_EXTI8                     SYSCFG_EXTICR3_EXTI8_Msk
#define  SYSCFG_EXTICR3_EXTI8_0                   (0x1U << SYSCFG_EXTICR3_EXTI8_Pos)
#define  SYSCFG_EXTICR3_EXTI8_1                   (0x2U << SYSCFG_EXTICR3_EXTI8_Pos)
#define  SYSCFG_EXTICR3_EXTI8_2                   (0x4U << SYSCFG_EXTICR3_EXTI8_Pos)
#define  SYSCFG_EXTICR3_EXTI8_3                   (0x8U << SYSCFG_EXTICR3_EXTI8_Pos)
#define  SYSCFG_EXTICR3_EXTI9_Pos                 (4)
#define  SYSCFG_EXTICR3_EXTI9_Msk                 (0xFU << SYSCFG_EXTICR3_EXTI9_Pos) /*!<EXTIx configuration (x=8...11) */
#define  SYSCFG_EXTICR3_EXTI9                     SYSCFG_EXTICR3_EXTI9_Msk
#define  SYSCFG_EXTICR3_EXTI9_0                   (0x1U << SYSCFG_EXTICR3_EXTI9_Pos)
#define  SYSCFG_EXTICR3_EXTI9_1                   (0x2U << SYSCFG_EXTICR3_EXTI9_Pos)
#define  SYSCFG_EXTICR3_EXTI9_2                   (0x4U << SYSCFG_EXTICR3_EXTI9_Pos)
#define  SYSCFG_EXTICR3_EXTI9_3                   (0x8U << SYSCFG_EXTICR3_EXTI9_Pos)
#define  SYSCFG_EXTICR3_EXTI10_Pos                (8)
#define  SYSCFG_EXTICR3_EXTI10_Msk                (0xFU << SYSCFG_EXTICR3_EXTI10_Pos) /*!<EXTIx configuration (x=8...11) */
#define  SYSCFG_EXTICR3_EXTI10                    SYSCFG_EXTICR3_EXTI10_Msk
#define  SYSCFG_EXTICR3_EXTI10_0                  (0x1U << SYSCFG_EXTICR3_EXTI10_Pos)
#define  SYSCFG_EXTICR3_EXTI10_1                  (0x2U << SYSCFG_EXTICR3_EXTI10_Pos)
#define  SYSCFG_EXTICR3_EXTI10_2                  (0x4U << SYSCFG_EXTICR3_EXTI10_Pos)
#define  SYSCFG_EXTICR3_EXTI10_3                  (0x8U << SYSCFG_EXTICR3_EXTI10_Pos)
#define  SYSCFG_EXTICR3_EXTI11_Pos                (12)
#define  SYSCFG_EXTICR3_EXTI11_Msk                (0xFU << SYSCFG_EXTICR3_EXTI11_Pos) /*!<EXTIx configuration (x=8...11) */
#define  SYSCFG_EXTICR3_EXTI11                    SYSCFG_EXTICR3_EXTI11_Msk
#define  SYSCFG_EXTICR3_EXTI11_0                  (0x1U << SYSCFG_EXTICR3_EXTI11_Pos)
#define  SYSCFG_EXTICR3_EXTI11_1                  (0x2U << SYSCFG_EXTICR3_EXTI11_Pos)
#define  SYSCFG_EXTICR3_EXTI11_2                  (0x4U << SYSCFG_EXTICR3_EXTI11_Pos)
#define  SYSCFG_EXTICR3_EXTI11_3                  (0x8U << SYSCFG_EXTICR3_EXTI11_Pos)

/**
  * @brief SYSCFG_EXTICR4 Register Bit Definition
  */
#define  SYSCFG_EXTICR4_EXTI12_Pos                (0)
#define  SYSCFG_EXTICR4_EXTI12_Msk                (0xFU << SYSCFG_EXTICR4_EXTI12_Pos) /*!<EXTIx configuration (x=12...15) */
#define  SYSCFG_EXTICR4_EXTI12                    SYSCFG_EXTICR4_EXTI12_Msk
#define  SYSCFG_EXTICR4_EXTI12_0                  (0x1U << SYSCFG_EXTICR4_EXTI12_Pos)
#define  SYSCFG_EXTICR4_EXTI12_1                  (0x2U << SYSCFG_EXTICR4_EXTI12_Pos)
#define  SYSCFG_EXTICR4_EXTI12_2                  (0x4U << SYSCFG_EXTICR4_EXTI12_Pos)
#define  SYSCFG_EXTICR4_EXTI12_3                  (0x8U << SYSCFG_EXTICR4_EXTI12_Pos)
#define  SYSCFG_EXTICR4_EXTI13_Pos                (4)
#define  SYSCFG_EXTICR4_EXTI13_Msk                (0xFU << SYSCFG_EXTICR4_EXTI13_Pos) /*!<EXTIx configuration (x=12...15) */
#define  SYSCFG_EXTICR4_EXTI13                    SYSCFG_EXTICR4_EXTI13_Msk
#define  SYSCFG_EXTICR4_EXTI13_0                  (0x1U << SYSCFG_EXTICR4_EXTI13_Pos)
#define  SYSCFG_EXTICR4_EXTI13_1                  (0x2U << SYSCFG_EXTICR4_EXTI13_Pos)
#define  SYSCFG_EXTICR4_EXTI13_2                  (0x4U << SYSCFG_EXTICR4_EXTI13_Pos)
#define  SYSCFG_EXTICR4_EXTI13_3                  (0x8U << SYSCFG_EXTICR4_EXTI13_Pos)
#define  SYSCFG_EXTICR4_EXTI14_Pos                (8)
#define  SYSCFG_EXTICR4_EXTI14_Msk                (0xFU << SYSCFG_EXTICR4_EXTI14_Pos) /*!<EXTIx configuration (x=12...15) */
#define  SYSCFG_EXTICR4_EXTI14                    SYSCFG_EXTICR4_EXTI14_Msk
#define  SYSCFG_EXTICR4_EXTI14_0                  (0x1U << SYSCFG_EXTICR4_EXTI14_Pos)
#define  SYSCFG_EXTICR4_EXTI14_1                  (0x2U << SYSCFG_EXTICR4_EXTI14_Pos)
#define  SYSCFG_EXTICR4_EXTI14_2                  (0x4U << SYSCFG_EXTICR4_EXTI14_Pos)
#define  SYSCFG_EXTICR4_EXTI14_3                  (0x8U << SYSCFG_EXTICR4_EXTI14_Pos)
#define  SYSCFG_EXTICR4_EXTI15_Pos                (12)
#define  SYSCFG_EXTICR4_EXTI15_Msk                (0xFU << SYSCFG_EXTICR4_EXTI15_Pos) /*!<EXTIx configuration (x=12...15) */
#define  SYSCFG_EXTICR4_EXTI15                    SYSCFG_EXTICR4_EXTI15_Msk
#define  SYSCFG_EXTICR4_EXTI15_0                  (0x1U << SYSCFG_EXTICR4_EXTI15_Pos)
#define  SYSCFG_EXTICR4_EXTI15_1                  (0x2U << SYSCFG_EXTICR4_EXTI15_Pos)
#define  SYSCFG_EXTICR4_EXTI15_2                  (0x4U << SYSCFG_EXTICR4_EXTI15_Pos)
#define  SYSCFG_EXTICR4_EXTI15_3                  (0x8U << SYSCFG_EXTICR4_EXTI15_Pos)

/**
  * @brief SYSCFG_PADHYS Register Bit Definition
  */
#define  SYSCFG_PADHYS_I2C1_MODE_SEL_Pos          (16)
#define  SYSCFG_PADHYS_I2C1_MODE_SEL_Msk          (0x1U << SYSCFG_PADHYS_I2C1_MODE_SEL_Pos) /*!<I2C1 port mode selection bit*/
#define  SYSCFG_PADHYS_I2C1_MODE_SEL              SYSCFG_PADHYS_I2C1_MODE_SEL_Msk

#endif

