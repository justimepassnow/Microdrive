/***********************************************************************************************************************
    @file     reg_dbg.h
    @author   VV TEAM
    @brief    This flie contains all the DBG's register and its field definition.
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

#ifndef __REG_DBG_H
#define __REG_DBG_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief DBG Base Address Definition
  */
#define  DBG_BASE                                  0x40013400 /*!<Base Address: 0x40013400*/

/**
  * @brief DBG Register Structure Definition
  */
typedef struct
{
    __IO uint32_t IDCODE;              /*!<DBG DBG ID encode register                     offset: 0x00       */
    __IO uint32_t CR;                  /*!<DBG DBG control register                       offset: 0x04       */
} DBG_TypeDef;

/**
  * @brief DBG type pointer Definition
  */
#define DBG                                       ((DBG_TypeDef *)DBG_BASE)

/**
  * @brief DBG_IDCODE Register Bit Definition
  */
#define  DBG_IDCODE_DEV_ID_Pos                    (0)
#define  DBG_IDCODE_DEV_ID_Msk                    (0xFFFFFFFFU << DBG_IDCODE_DEV_ID_Pos) /*!<Device Identifier*/
#define  DBG_IDCODE_DEV_ID                        DBG_IDCODE_DEV_ID_Msk
#define  DBG_IDCODE_DEV_ID_0                      (0x00000001U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_1                      (0x00000002U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_2                      (0x00000004U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_3                      (0x00000008U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_4                      (0x00000010U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_5                      (0x00000020U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_6                      (0x00000040U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_7                      (0x00000080U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_8                      (0x00000100U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_9                      (0x00000200U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_10                     (0x00000400U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_11                     (0x00000800U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_12                     (0x00001000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_13                     (0x00002000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_14                     (0x00004000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_15                     (0x00008000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_16                     (0x00010000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_17                     (0x00020000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_18                     (0x00040000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_19                     (0x00080000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_20                     (0x00100000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_21                     (0x00200000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_22                     (0x00400000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_23                     (0x00800000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_24                     (0x01000000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_25                     (0x02000000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_26                     (0x04000000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_27                     (0x08000000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_28                     (0x10000000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_29                     (0x20000000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_30                     (0x40000000U << DBG_IDCODE_DEV_ID_Pos)
#define  DBG_IDCODE_DEV_ID_31                     (0x80000000U << DBG_IDCODE_DEV_ID_Pos)

/**
  * @brief DBG_CR Register Bit Definition
  */
#define  DBG_CR_DBG_SLEEP_Pos                     (0)
#define  DBG_CR_DBG_SLEEP_Msk                     (0x1U << DBG_CR_DBG_SLEEP_Pos)        /*!<Debug sleep mode*/
#define  DBG_CR_DBG_SLEEP                         DBG_CR_DBG_SLEEP_Msk
#define  DBG_CR_DBG_STOP_Pos                      (1)
#define  DBG_CR_DBG_STOP_Msk                      (0x1U << DBG_CR_DBG_STOP_Pos)         /*!<Debug stop mode*/
#define  DBG_CR_DBG_STOP                          DBG_CR_DBG_STOP_Msk
#define  DBG_CR_DBG_STOP_FOR_LDO_Pos              (3)
#define  DBG_CR_DBG_STOP_FOR_LDO_Msk              (0x1U << DBG_CR_DBG_STOP_FOR_LDO_Pos) /*!<Debug stop mode LDO status*/
#define  DBG_CR_DBG_STOP_FOR_LDO                  DBG_CR_DBG_STOP_FOR_LDO_Msk
#define  DBG_CR_DBG_IWDG_STOP_Pos                 (8)
#define  DBG_CR_DBG_IWDG_STOP_Msk                 (0x1U << DBG_CR_DBG_IWDG_STOP_Pos)    /*!<Independent watchdog stops work*/
#define  DBG_CR_DBG_IWDG_STOP                     DBG_CR_DBG_IWDG_STOP_Msk
#define  DBG_CR_DBG_TIM1_STOP_Pos                 (10)
#define  DBG_CR_DBG_TIM1_STOP_Msk                 (0x1U << DBG_CR_DBG_TIM1_STOP_Pos)    /*!<TIM1 stops work when the core enters the debug mode*/
#define  DBG_CR_DBG_TIM1_STOP                     DBG_CR_DBG_TIM1_STOP_Msk
#define  DBG_CR_DBG_TIM3_STOP_Pos                 (12)
#define  DBG_CR_DBG_TIM3_STOP_Msk                 (0x1U << DBG_CR_DBG_TIM3_STOP_Pos)    /*!<TIM3 stops work when the core enters the debug mode*/
#define  DBG_CR_DBG_TIM3_STOP                     DBG_CR_DBG_TIM3_STOP_Msk
#define  DBG_CR_DBG_TIM1_PWM_OFF_Pos              (13)
#define  DBG_CR_DBG_TIM1_PWM_OFF_Msk              (0x1U << DBG_CR_DBG_TIM1_PWM_OFF_Pos) /*!<TIM1 PWM outputs 0 when the core enters the debug mode*/
#define  DBG_CR_DBG_TIM1_PWM_OFF                  DBG_CR_DBG_TIM1_PWM_OFF_Msk
#define  DBG_CR_DBG_TIM3_PWM_OFF_Pos              (15)
#define  DBG_CR_DBG_TIM3_PWM_OFF_Msk              (0x1U << DBG_CR_DBG_TIM3_PWM_OFF_Pos) /*!<TIM3 PWM outputs 0 when the core enters the debug mode*/
#define  DBG_CR_DBG_TIM3_PWM_OFF                  DBG_CR_DBG_TIM3_PWM_OFF_Msk
#define  DBG_CR_DBG_TIM14_STOP_Pos                (18)
#define  DBG_CR_DBG_TIM14_STOP_Msk                (0x1U << DBG_CR_DBG_TIM14_STOP_Pos)   /*!<TIM14 stops work when the core enters the debug mode*/
#define  DBG_CR_DBG_TIM14_STOP                    DBG_CR_DBG_TIM14_STOP_Msk

#endif

