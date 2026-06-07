/***********************************************************************************************************************
    @file     reg_exti.h
    @author   VV TEAM
    @brief    This flie contains all the EXTI's register and its field definition.
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

#ifndef __REG_EXTI_H
#define __REG_EXTI_H


/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>




/**
  * @brief EXTI Base Address Definition
  */
#define  EXTI_BASE                                 0x40010400                                       /*!<Base Address: 0x40010400*/

/**
  * @brief EXTI Register Structure Definition
  */
typedef struct
{
    __IO uint32_t IMR;                            /*!<EXTI Interrupt mask register                   offset: 0x00       */
    __IO uint32_t EMR;                            /*!<EXTI Event mask register                       offset: 0x04       */
    __IO uint32_t RTSR;                           /*!<EXTI Rising edge trigger selection register    offset: 0x08       */
    __IO uint32_t FTSR;                           /*!<EXTI Falling edge trigger selection register   offset: 0x0C       */
    __IO uint32_t SWIER;                          /*!<EXTI Software interrupt event register         offset: 0x10       */
    __IO uint32_t PR;                             /*!<EXTI Pending register                          offset: 0x14       */
} EXTI_TypeDef;

/**
  * @brief EXTI type pointer Definition
  */
#define EXTI                                      ((EXTI_TypeDef *)EXTI_BASE)

/**
  * @brief EXTI_IMR Register Bit Definition
  */
#define  EXTI_IMR_IMR0_Pos                        (0)
#define  EXTI_IMR_IMR0_Msk                        (0x1U << EXTI_IMR_IMR0_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR0                            EXTI_IMR_IMR0_Msk
#define  EXTI_IMR_IMR1_Pos                        (1)
#define  EXTI_IMR_IMR1_Msk                        (0x1U << EXTI_IMR_IMR1_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR1                            EXTI_IMR_IMR1_Msk
#define  EXTI_IMR_IMR2_Pos                        (2)
#define  EXTI_IMR_IMR2_Msk                        (0x1U << EXTI_IMR_IMR2_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR2                            EXTI_IMR_IMR2_Msk
#define  EXTI_IMR_IMR3_Pos                        (3)
#define  EXTI_IMR_IMR3_Msk                        (0x1U << EXTI_IMR_IMR3_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR3                            EXTI_IMR_IMR3_Msk
#define  EXTI_IMR_IMR4_Pos                        (4)
#define  EXTI_IMR_IMR4_Msk                        (0x1U << EXTI_IMR_IMR4_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR4                            EXTI_IMR_IMR4_Msk
#define  EXTI_IMR_IMR5_Pos                        (5)
#define  EXTI_IMR_IMR5_Msk                        (0x1U << EXTI_IMR_IMR5_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR5                            EXTI_IMR_IMR5_Msk
#define  EXTI_IMR_IMR6_Pos                        (6)
#define  EXTI_IMR_IMR6_Msk                        (0x1U << EXTI_IMR_IMR6_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR6                            EXTI_IMR_IMR6_Msk
#define  EXTI_IMR_IMR7_Pos                        (7)
#define  EXTI_IMR_IMR7_Msk                        (0x1U << EXTI_IMR_IMR7_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR7                            EXTI_IMR_IMR7_Msk
#define  EXTI_IMR_IMR8_Pos                        (8)
#define  EXTI_IMR_IMR8_Msk                        (0x1U << EXTI_IMR_IMR8_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR8                            EXTI_IMR_IMR8_Msk
#define  EXTI_IMR_IMR9_Pos                        (9)
#define  EXTI_IMR_IMR9_Msk                        (0x1U << EXTI_IMR_IMR9_Pos)                       /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR9                            EXTI_IMR_IMR9_Msk
#define  EXTI_IMR_IMR10_Pos                       (10)
#define  EXTI_IMR_IMR10_Msk                       (0x1U << EXTI_IMR_IMR10_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR10                           EXTI_IMR_IMR10_Msk
#define  EXTI_IMR_IMR11_Pos                       (11)
#define  EXTI_IMR_IMR11_Msk                       (0x1U << EXTI_IMR_IMR11_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR11                           EXTI_IMR_IMR11_Msk
#define  EXTI_IMR_IMR12_Pos                       (12)
#define  EXTI_IMR_IMR12_Msk                       (0x1U << EXTI_IMR_IMR12_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR12                           EXTI_IMR_IMR12_Msk
#define  EXTI_IMR_IMR13_Pos                       (13)
#define  EXTI_IMR_IMR13_Msk                       (0x1U << EXTI_IMR_IMR13_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR13                           EXTI_IMR_IMR13_Msk
#define  EXTI_IMR_IMR14_Pos                       (14)
#define  EXTI_IMR_IMR14_Msk                       (0x1U << EXTI_IMR_IMR14_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR14                           EXTI_IMR_IMR14_Msk
#define  EXTI_IMR_IMR15_Pos                       (15)
#define  EXTI_IMR_IMR15_Msk                       (0x1U << EXTI_IMR_IMR15_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR15                           EXTI_IMR_IMR15_Msk
#define  EXTI_IMR_IMR16_Pos                       (16)
#define  EXTI_IMR_IMR16_Msk                       (0x1U << EXTI_IMR_IMR16_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR16                           EXTI_IMR_IMR16_Msk
#define  EXTI_IMR_IMR17_Pos                       (17)
#define  EXTI_IMR_IMR17_Msk                       (0x1U << EXTI_IMR_IMR17_Pos)                      /*!<interrupt enable bit*/
#define  EXTI_IMR_IMR17                           EXTI_IMR_IMR17_Msk

/**
  * @brief EXTI_EMR Register Bit Definition
  */
#define  EXTI_EMR_EMR0_Pos                        (0)
#define  EXTI_EMR_EMR0_Msk                        (0x1U << EXTI_EMR_EMR0_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR0                            EXTI_EMR_EMR0_Msk
#define  EXTI_EMR_EMR1_Pos                        (1)
#define  EXTI_EMR_EMR1_Msk                        (0x1U << EXTI_EMR_EMR1_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR1                            EXTI_EMR_EMR1_Msk
#define  EXTI_EMR_EMR2_Pos                        (2)
#define  EXTI_EMR_EMR2_Msk                        (0x1U << EXTI_EMR_EMR2_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR2                            EXTI_EMR_EMR2_Msk
#define  EXTI_EMR_EMR3_Pos                        (3)
#define  EXTI_EMR_EMR3_Msk                        (0x1U << EXTI_EMR_EMR3_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR3                            EXTI_EMR_EMR3_Msk
#define  EXTI_EMR_EMR4_Pos                        (4)
#define  EXTI_EMR_EMR4_Msk                        (0x1U << EXTI_EMR_EMR4_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR4                            EXTI_EMR_EMR4_Msk
#define  EXTI_EMR_EMR5_Pos                        (5)
#define  EXTI_EMR_EMR5_Msk                        (0x1U << EXTI_EMR_EMR5_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR5                            EXTI_EMR_EMR5_Msk
#define  EXTI_EMR_EMR6_Pos                        (6)
#define  EXTI_EMR_EMR6_Msk                        (0x1U << EXTI_EMR_EMR6_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR6                            EXTI_EMR_EMR6_Msk
#define  EXTI_EMR_EMR7_Pos                        (7)
#define  EXTI_EMR_EMR7_Msk                        (0x1U << EXTI_EMR_EMR7_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR7                            EXTI_EMR_EMR7_Msk
#define  EXTI_EMR_EMR8_Pos                        (8)
#define  EXTI_EMR_EMR8_Msk                        (0x1U << EXTI_EMR_EMR8_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR8                            EXTI_EMR_EMR8_Msk
#define  EXTI_EMR_EMR9_Pos                        (9)
#define  EXTI_EMR_EMR9_Msk                        (0x1U << EXTI_EMR_EMR9_Pos)                       /*!<event enable bit*/
#define  EXTI_EMR_EMR9                            EXTI_EMR_EMR9_Msk
#define  EXTI_EMR_EMR10_Pos                       (10)
#define  EXTI_EMR_EMR10_Msk                       (0x1U << EXTI_EMR_EMR10_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR10                           EXTI_EMR_EMR10_Msk
#define  EXTI_EMR_EMR11_Pos                       (11)
#define  EXTI_EMR_EMR11_Msk                       (0x1U << EXTI_EMR_EMR11_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR11                           EXTI_EMR_EMR11_Msk
#define  EXTI_EMR_EMR12_Pos                       (12)
#define  EXTI_EMR_EMR12_Msk                       (0x1U << EXTI_EMR_EMR12_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR12                           EXTI_EMR_EMR12_Msk
#define  EXTI_EMR_EMR13_Pos                       (13)
#define  EXTI_EMR_EMR13_Msk                       (0x1U << EXTI_EMR_EMR13_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR13                           EXTI_EMR_EMR13_Msk
#define  EXTI_EMR_EMR14_Pos                       (14)
#define  EXTI_EMR_EMR14_Msk                       (0x1U << EXTI_EMR_EMR14_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR14                           EXTI_EMR_EMR14_Msk
#define  EXTI_EMR_EMR15_Pos                       (15)
#define  EXTI_EMR_EMR15_Msk                       (0x1U << EXTI_EMR_EMR15_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR15                           EXTI_EMR_EMR15_Msk
#define  EXTI_EMR_EMR16_Pos                       (16)
#define  EXTI_EMR_EMR16_Msk                       (0x1U << EXTI_EMR_EMR16_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR16                           EXTI_EMR_EMR16_Msk
#define  EXTI_EMR_EMR17_Pos                       (17)
#define  EXTI_EMR_EMR17_Msk                       (0x1U << EXTI_EMR_EMR17_Pos)                      /*!<event enable bit*/
#define  EXTI_EMR_EMR17                           EXTI_EMR_EMR17_Msk

/**
  * @brief EXTI_RTSR Register Bit Definition
  */
#define  EXTI_RTSR_TR0_Pos                        (0)
#define  EXTI_RTSR_TR0_Msk                        (0x1U << EXTI_RTSR_TR0_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR0                            EXTI_RTSR_TR0_Msk
#define  EXTI_RTSR_TR1_Pos                        (1)
#define  EXTI_RTSR_TR1_Msk                        (0x1U << EXTI_RTSR_TR1_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR1                            EXTI_RTSR_TR1_Msk
#define  EXTI_RTSR_TR2_Pos                        (2)
#define  EXTI_RTSR_TR2_Msk                        (0x1U << EXTI_RTSR_TR2_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR2                            EXTI_RTSR_TR2_Msk
#define  EXTI_RTSR_TR3_Pos                        (3)
#define  EXTI_RTSR_TR3_Msk                        (0x1U << EXTI_RTSR_TR3_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR3                            EXTI_RTSR_TR3_Msk
#define  EXTI_RTSR_TR4_Pos                        (4)
#define  EXTI_RTSR_TR4_Msk                        (0x1U << EXTI_RTSR_TR4_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR4                            EXTI_RTSR_TR4_Msk
#define  EXTI_RTSR_TR5_Pos                        (5)
#define  EXTI_RTSR_TR5_Msk                        (0x1U << EXTI_RTSR_TR5_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR5                            EXTI_RTSR_TR5_Msk
#define  EXTI_RTSR_TR6_Pos                        (6)
#define  EXTI_RTSR_TR6_Msk                        (0x1U << EXTI_RTSR_TR6_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR6                            EXTI_RTSR_TR6_Msk
#define  EXTI_RTSR_TR7_Pos                        (7)
#define  EXTI_RTSR_TR7_Msk                        (0x1U << EXTI_RTSR_TR7_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR7                            EXTI_RTSR_TR7_Msk
#define  EXTI_RTSR_TR8_Pos                        (8)
#define  EXTI_RTSR_TR8_Msk                        (0x1U << EXTI_RTSR_TR8_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR8                            EXTI_RTSR_TR8_Msk
#define  EXTI_RTSR_TR9_Pos                        (9)
#define  EXTI_RTSR_TR9_Msk                        (0x1U << EXTI_RTSR_TR9_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR9                            EXTI_RTSR_TR9_Msk
#define  EXTI_RTSR_TR10_Pos                       (10)
#define  EXTI_RTSR_TR10_Msk                       (0x1U << EXTI_RTSR_TR10_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR10                           EXTI_RTSR_TR10_Msk
#define  EXTI_RTSR_TR11_Pos                       (11)
#define  EXTI_RTSR_TR11_Msk                       (0x1U << EXTI_RTSR_TR11_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR11                           EXTI_RTSR_TR11_Msk
#define  EXTI_RTSR_TR12_Pos                       (12)
#define  EXTI_RTSR_TR12_Msk                       (0x1U << EXTI_RTSR_TR12_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR12                           EXTI_RTSR_TR12_Msk
#define  EXTI_RTSR_TR13_Pos                       (13)
#define  EXTI_RTSR_TR13_Msk                       (0x1U << EXTI_RTSR_TR13_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR13                           EXTI_RTSR_TR13_Msk
#define  EXTI_RTSR_TR14_Pos                       (14)
#define  EXTI_RTSR_TR14_Msk                       (0x1U << EXTI_RTSR_TR14_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR14                           EXTI_RTSR_TR14_Msk
#define  EXTI_RTSR_TR15_Pos                       (15)
#define  EXTI_RTSR_TR15_Msk                       (0x1U << EXTI_RTSR_TR15_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR15                           EXTI_RTSR_TR15_Msk
#define  EXTI_RTSR_TR16_Pos                       (16)
#define  EXTI_RTSR_TR16_Msk                       (0x1U << EXTI_RTSR_TR16_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR16                           EXTI_RTSR_TR16_Msk
#define  EXTI_RTSR_TR17_Pos                       (17)
#define  EXTI_RTSR_TR17_Msk                       (0x1U << EXTI_RTSR_TR17_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_RTSR_TR17                           EXTI_RTSR_TR17_Msk

/**
  * @brief EXTI_FTSR Register Bit Definition
  */
#define  EXTI_FTSR_TR0_Pos                        (0)
#define  EXTI_FTSR_TR0_Msk                        (0x1U << EXTI_FTSR_TR0_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR0                            EXTI_FTSR_TR0_Msk
#define  EXTI_FTSR_TR1_Pos                        (1)
#define  EXTI_FTSR_TR1_Msk                        (0x1U << EXTI_FTSR_TR1_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR1                            EXTI_FTSR_TR1_Msk
#define  EXTI_FTSR_TR2_Pos                        (2)
#define  EXTI_FTSR_TR2_Msk                        (0x1U << EXTI_FTSR_TR2_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR2                            EXTI_FTSR_TR2_Msk
#define  EXTI_FTSR_TR3_Pos                        (3)
#define  EXTI_FTSR_TR3_Msk                        (0x1U << EXTI_FTSR_TR3_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR3                            EXTI_FTSR_TR3_Msk
#define  EXTI_FTSR_TR4_Pos                        (4)
#define  EXTI_FTSR_TR4_Msk                        (0x1U << EXTI_FTSR_TR4_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR4                            EXTI_FTSR_TR4_Msk
#define  EXTI_FTSR_TR5_Pos                        (5)
#define  EXTI_FTSR_TR5_Msk                        (0x1U << EXTI_FTSR_TR5_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR5                            EXTI_FTSR_TR5_Msk
#define  EXTI_FTSR_TR6_Pos                        (6)
#define  EXTI_FTSR_TR6_Msk                        (0x1U << EXTI_FTSR_TR6_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR6                            EXTI_FTSR_TR6_Msk
#define  EXTI_FTSR_TR7_Pos                        (7)
#define  EXTI_FTSR_TR7_Msk                        (0x1U << EXTI_FTSR_TR7_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR7                            EXTI_FTSR_TR7_Msk
#define  EXTI_FTSR_TR8_Pos                        (8)
#define  EXTI_FTSR_TR8_Msk                        (0x1U << EXTI_FTSR_TR8_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR8                            EXTI_FTSR_TR8_Msk
#define  EXTI_FTSR_TR9_Pos                        (9)
#define  EXTI_FTSR_TR9_Msk                        (0x1U << EXTI_FTSR_TR9_Pos)                       /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR9                            EXTI_FTSR_TR9_Msk
#define  EXTI_FTSR_TR10_Pos                       (10)
#define  EXTI_FTSR_TR10_Msk                       (0x1U << EXTI_FTSR_TR10_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR10                           EXTI_FTSR_TR10_Msk
#define  EXTI_FTSR_TR11_Pos                       (11)
#define  EXTI_FTSR_TR11_Msk                       (0x1U << EXTI_FTSR_TR11_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR11                           EXTI_FTSR_TR11_Msk
#define  EXTI_FTSR_TR12_Pos                       (12)
#define  EXTI_FTSR_TR12_Msk                       (0x1U << EXTI_FTSR_TR12_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR12                           EXTI_FTSR_TR12_Msk
#define  EXTI_FTSR_TR13_Pos                       (13)
#define  EXTI_FTSR_TR13_Msk                       (0x1U << EXTI_FTSR_TR13_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR13                           EXTI_FTSR_TR13_Msk
#define  EXTI_FTSR_TR14_Pos                       (14)
#define  EXTI_FTSR_TR14_Msk                       (0x1U << EXTI_FTSR_TR14_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR14                           EXTI_FTSR_TR14_Msk
#define  EXTI_FTSR_TR15_Pos                       (15)
#define  EXTI_FTSR_TR15_Msk                       (0x1U << EXTI_FTSR_TR15_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR15                           EXTI_FTSR_TR15_Msk
#define  EXTI_FTSR_TR16_Pos                       (16)
#define  EXTI_FTSR_TR16_Msk                       (0x1U << EXTI_FTSR_TR16_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR16                           EXTI_FTSR_TR16_Msk
#define  EXTI_FTSR_TR17_Pos                       (17)
#define  EXTI_FTSR_TR17_Msk                       (0x1U << EXTI_FTSR_TR17_Pos)                      /*!<interrupt or event trigger polarity*/
#define  EXTI_FTSR_TR17                           EXTI_FTSR_TR17_Msk

/**
  * @brief EXTI_SWIER Register Bit Definition
  */
#define  EXTI_SWIER_SWIER0_Pos                    (0)
#define  EXTI_SWIER_SWIER0_Msk                    (0x1U << EXTI_SWIER_SWIER0_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER0                        EXTI_SWIER_SWIER0_Msk
#define  EXTI_SWIER_SWIER1_Pos                    (1)
#define  EXTI_SWIER_SWIER1_Msk                    (0x1U << EXTI_SWIER_SWIER1_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER1                        EXTI_SWIER_SWIER1_Msk
#define  EXTI_SWIER_SWIER2_Pos                    (2)
#define  EXTI_SWIER_SWIER2_Msk                    (0x1U << EXTI_SWIER_SWIER2_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER2                        EXTI_SWIER_SWIER2_Msk
#define  EXTI_SWIER_SWIER3_Pos                    (3)
#define  EXTI_SWIER_SWIER3_Msk                    (0x1U << EXTI_SWIER_SWIER3_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER3                        EXTI_SWIER_SWIER3_Msk
#define  EXTI_SWIER_SWIER4_Pos                    (4)
#define  EXTI_SWIER_SWIER4_Msk                    (0x1U << EXTI_SWIER_SWIER4_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER4                        EXTI_SWIER_SWIER4_Msk
#define  EXTI_SWIER_SWIER5_Pos                    (5)
#define  EXTI_SWIER_SWIER5_Msk                    (0x1U << EXTI_SWIER_SWIER5_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER5                        EXTI_SWIER_SWIER5_Msk
#define  EXTI_SWIER_SWIER6_Pos                    (6)
#define  EXTI_SWIER_SWIER6_Msk                    (0x1U << EXTI_SWIER_SWIER6_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER6                        EXTI_SWIER_SWIER6_Msk
#define  EXTI_SWIER_SWIER7_Pos                    (7)
#define  EXTI_SWIER_SWIER7_Msk                    (0x1U << EXTI_SWIER_SWIER7_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER7                        EXTI_SWIER_SWIER7_Msk
#define  EXTI_SWIER_SWIER8_Pos                    (8)
#define  EXTI_SWIER_SWIER8_Msk                    (0x1U << EXTI_SWIER_SWIER8_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER8                        EXTI_SWIER_SWIER8_Msk
#define  EXTI_SWIER_SWIER9_Pos                    (9)
#define  EXTI_SWIER_SWIER9_Msk                    (0x1U << EXTI_SWIER_SWIER9_Pos)                   /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER9                        EXTI_SWIER_SWIER9_Msk
#define  EXTI_SWIER_SWIER10_Pos                   (10)
#define  EXTI_SWIER_SWIER10_Msk                   (0x1U << EXTI_SWIER_SWIER10_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER10                       EXTI_SWIER_SWIER10_Msk
#define  EXTI_SWIER_SWIER11_Pos                   (11)
#define  EXTI_SWIER_SWIER11_Msk                   (0x1U << EXTI_SWIER_SWIER11_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER11                       EXTI_SWIER_SWIER11_Msk
#define  EXTI_SWIER_SWIER12_Pos                   (12)
#define  EXTI_SWIER_SWIER12_Msk                   (0x1U << EXTI_SWIER_SWIER12_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER12                       EXTI_SWIER_SWIER12_Msk
#define  EXTI_SWIER_SWIER13_Pos                   (13)
#define  EXTI_SWIER_SWIER13_Msk                   (0x1U << EXTI_SWIER_SWIER13_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER13                       EXTI_SWIER_SWIER13_Msk
#define  EXTI_SWIER_SWIER14_Pos                   (14)
#define  EXTI_SWIER_SWIER14_Msk                   (0x1U << EXTI_SWIER_SWIER14_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER14                       EXTI_SWIER_SWIER14_Msk
#define  EXTI_SWIER_SWIER15_Pos                   (15)
#define  EXTI_SWIER_SWIER15_Msk                   (0x1U << EXTI_SWIER_SWIER15_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER15                       EXTI_SWIER_SWIER15_Msk
#define  EXTI_SWIER_SWIER16_Pos                   (16)
#define  EXTI_SWIER_SWIER16_Msk                   (0x1U << EXTI_SWIER_SWIER16_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER16                       EXTI_SWIER_SWIER16_Msk
#define  EXTI_SWIER_SWIER17_Pos                   (17)
#define  EXTI_SWIER_SWIER17_Msk                   (0x1U << EXTI_SWIER_SWIER17_Pos)                  /*!<software interrupt or event enable*/
#define  EXTI_SWIER_SWIER17                       EXTI_SWIER_SWIER17_Msk

/**
  * @brief EXTI_PR Register Bit Definition
  */
#define  EXTI_PR_PR0_Pos                          (0)
#define  EXTI_PR_PR0_Msk                          (0x1U << EXTI_PR_PR0_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR0                              EXTI_PR_PR0_Msk
#define  EXTI_PR_PR1_Pos                          (1)
#define  EXTI_PR_PR1_Msk                          (0x1U << EXTI_PR_PR1_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR1                              EXTI_PR_PR1_Msk
#define  EXTI_PR_PR2_Pos                          (2)
#define  EXTI_PR_PR2_Msk                          (0x1U << EXTI_PR_PR2_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR2                              EXTI_PR_PR2_Msk
#define  EXTI_PR_PR3_Pos                          (3)
#define  EXTI_PR_PR3_Msk                          (0x1U << EXTI_PR_PR3_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR3                              EXTI_PR_PR3_Msk
#define  EXTI_PR_PR4_Pos                          (4)
#define  EXTI_PR_PR4_Msk                          (0x1U << EXTI_PR_PR4_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR4                              EXTI_PR_PR4_Msk
#define  EXTI_PR_PR5_Pos                          (5)
#define  EXTI_PR_PR5_Msk                          (0x1U << EXTI_PR_PR5_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR5                              EXTI_PR_PR5_Msk
#define  EXTI_PR_PR6_Pos                          (6)
#define  EXTI_PR_PR6_Msk                          (0x1U << EXTI_PR_PR6_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR6                              EXTI_PR_PR6_Msk
#define  EXTI_PR_PR7_Pos                          (7)
#define  EXTI_PR_PR7_Msk                          (0x1U << EXTI_PR_PR7_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR7                              EXTI_PR_PR7_Msk
#define  EXTI_PR_PR8_Pos                          (8)
#define  EXTI_PR_PR8_Msk                          (0x1U << EXTI_PR_PR8_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR8                              EXTI_PR_PR8_Msk
#define  EXTI_PR_PR9_Pos                          (9)
#define  EXTI_PR_PR9_Msk                          (0x1U << EXTI_PR_PR9_Pos)                         /*!<trigger pending bit*/
#define  EXTI_PR_PR9                              EXTI_PR_PR9_Msk
#define  EXTI_PR_PR10_Pos                         (10)
#define  EXTI_PR_PR10_Msk                         (0x1U << EXTI_PR_PR10_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR10                             EXTI_PR_PR10_Msk
#define  EXTI_PR_PR11_Pos                         (11)
#define  EXTI_PR_PR11_Msk                         (0x1U << EXTI_PR_PR11_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR11                             EXTI_PR_PR11_Msk
#define  EXTI_PR_PR12_Pos                         (12)
#define  EXTI_PR_PR12_Msk                         (0x1U << EXTI_PR_PR12_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR12                             EXTI_PR_PR12_Msk
#define  EXTI_PR_PR13_Pos                         (13)
#define  EXTI_PR_PR13_Msk                         (0x1U << EXTI_PR_PR13_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR13                             EXTI_PR_PR13_Msk
#define  EXTI_PR_PR14_Pos                         (14)
#define  EXTI_PR_PR14_Msk                         (0x1U << EXTI_PR_PR14_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR14                             EXTI_PR_PR14_Msk
#define  EXTI_PR_PR15_Pos                         (15)
#define  EXTI_PR_PR15_Msk                         (0x1U << EXTI_PR_PR15_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR15                             EXTI_PR_PR15_Msk
#define  EXTI_PR_PR16_Pos                         (16)
#define  EXTI_PR_PR16_Msk                         (0x1U << EXTI_PR_PR16_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR16                             EXTI_PR_PR16_Msk
#define  EXTI_PR_PR17_Pos                         (17)
#define  EXTI_PR_PR17_Msk                         (0x1U << EXTI_PR_PR17_Pos)                        /*!<trigger pending bit*/
#define  EXTI_PR_PR17                             EXTI_PR_PR17_Msk


#endif

