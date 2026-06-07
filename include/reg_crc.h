/***********************************************************************************************************************
    @file     reg_crc.h
    @author   VV TEAM
    @brief    This flie contains all the CRC's register and its field definition.
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

#ifndef __REG_CRC_H
#define __REG_CRC_H


/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>




/**
  * @brief CRC Base Address Definition
  */
#define  CRC_BASE                                  0x40023000                                       /*!<Base Address: 0x40023000*/

/**
  * @brief CRC Register Structure Definition
  */
typedef struct
{
    __IO uint32_t DR;                             /*!<CRC CRC data register                          offset: 0x00       */
    __IO uint32_t IDR;                            /*!<CRC CRC independent data register              offset: 0x04       */
    __IO uint32_t CR;                             /*!<CRC CRC control register                       offset: 0x08       */
} CRC_TypeDef;

/**
  * @brief CRC type pointer Definition
  */
#define CRC                                       ((CRC_TypeDef *)CRC_BASE)

/**
  * @brief CRC_DR Register Bit Definition
  */
#define  CRC_DR_DR_Pos                            (0)
#define  CRC_DR_DR_Msk                            (0xFFFFFFFFU << CRC_DR_DR_Pos)                    /*!<Data Register*/
#define  CRC_DR_DR                                CRC_DR_DR_Msk
#define  CRC_DR_DR_0                              (0x00000001U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_1                              (0x00000002U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_2                              (0x00000004U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_3                              (0x00000008U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_4                              (0x00000010U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_5                              (0x00000020U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_6                              (0x00000040U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_7                              (0x00000080U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_8                              (0x00000100U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_9                              (0x00000200U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_10                             (0x00000400U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_11                             (0x00000800U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_12                             (0x00001000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_13                             (0x00002000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_14                             (0x00004000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_15                             (0x00008000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_16                             (0x00010000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_17                             (0x00020000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_18                             (0x00040000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_19                             (0x00080000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_20                             (0x00100000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_21                             (0x00200000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_22                             (0x00400000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_23                             (0x00800000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_24                             (0x01000000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_25                             (0x02000000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_26                             (0x04000000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_27                             (0x08000000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_28                             (0x10000000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_29                             (0x20000000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_30                             (0x40000000U << CRC_DR_DR_Pos) 
#define  CRC_DR_DR_31                             (0x80000000U << CRC_DR_DR_Pos) 

/**
  * @brief CRC_IDR Register Bit Definition
  */
#define  CRC_IDR_IDR_Pos                          (0)
#define  CRC_IDR_IDR_Msk                          (0xFFU << CRC_IDR_IDR_Pos)                        /*!<General-purpose 8-bit Data Register*/
#define  CRC_IDR_IDR                              CRC_IDR_IDR_Msk
#define  CRC_IDR_IDR_0                            (0x01U << CRC_IDR_IDR_Pos) 
#define  CRC_IDR_IDR_1                            (0x02U << CRC_IDR_IDR_Pos) 
#define  CRC_IDR_IDR_2                            (0x04U << CRC_IDR_IDR_Pos) 
#define  CRC_IDR_IDR_3                            (0x08U << CRC_IDR_IDR_Pos) 
#define  CRC_IDR_IDR_4                            (0x10U << CRC_IDR_IDR_Pos) 
#define  CRC_IDR_IDR_5                            (0x20U << CRC_IDR_IDR_Pos) 
#define  CRC_IDR_IDR_6                            (0x40U << CRC_IDR_IDR_Pos) 
#define  CRC_IDR_IDR_7                            (0x80U << CRC_IDR_IDR_Pos) 

/**
  * @brief CRC_CR Register Bit Definition
  */
#define  CRC_CR_RST_Pos                           (0)
#define  CRC_CR_RST_Msk                           (0x1U << CRC_CR_RST_Pos)                          /*!<CRC Reset*/
#define  CRC_CR_RST                               CRC_CR_RST_Msk


#endif

