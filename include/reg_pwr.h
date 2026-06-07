/***********************************************************************************************************************
    @file     reg_pwr.h
    @author   VV TEAM
    @brief    This flie contains all the PWR's register and its field definition.
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

#ifndef __REG_PWR_H
#define __REG_PWR_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief PWR Base Address Definition
  */
#define  PWR_BASE                                  0x40007000 /*!<Base Address: 0x40007000*/

/**
  * @brief PWR Register Structure Definition
  */
typedef struct
{
    __IO uint32_t CR;                  /*!<PWR Power control register                     offset: 0x00       */
    __IO uint32_t CSR;                 /*!<PWR Power control status register              offset: 0x04       */
} PWR_TypeDef;

/**
  * @brief PWR type pointer Definition
  */
#define PWR                                       ((PWR_TypeDef *)PWR_BASE)

/**
  * @brief PWR_CR Register Bit Definition
  */
#define  PWR_CR_LPDS_Pos                          (0)
#define  PWR_CR_LPDS_Msk                          (0x1U << PWR_CR_LPDS_Pos) /*!<Low power deepsleep*/
#define  PWR_CR_LPDS                              PWR_CR_LPDS_Msk
#define  PWR_CR_PVDE_Pos                          (4)
#define  PWR_CR_PVDE_Msk                          (0x1U << PWR_CR_PVDE_Pos) /*!<Power voltage detector enable*/
#define  PWR_CR_PVDE                              PWR_CR_PVDE_Msk
#define  PWR_CR_PLS_Pos                           (9)
#define  PWR_CR_PLS_Msk                           (0xFU << PWR_CR_PLS_Pos)  /*!<PVD level selection*/
#define  PWR_CR_PLS                               PWR_CR_PLS_Msk
#define  PWR_CR_PLS_0                             (0x1U << PWR_CR_PLS_Pos)
#define  PWR_CR_PLS_1                             (0x2U << PWR_CR_PLS_Pos)
#define  PWR_CR_PLS_2                             (0x4U << PWR_CR_PLS_Pos)
#define  PWR_CR_PLS_3                             (0x8U << PWR_CR_PLS_Pos)

/**
  * @brief PWR_CSR Register Bit Definition
  */
#define  PWR_CSR_PVDO_Pos                         (2)
#define  PWR_CSR_PVDO_Msk                         (0x1U << PWR_CSR_PVDO_Pos) /*!<PVD output*/
#define  PWR_CSR_PVDO                             PWR_CSR_PVDO_Msk

#endif

