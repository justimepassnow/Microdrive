/***********************************************************************************************************************
    @file     reg_flash.h
    @author   VV TEAM
    @brief    This flie contains all the FLASH's register and its field definition.
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

#ifndef __REG_FLASH_H
#define __REG_FLASH_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief FLASH Base Address Definition
  */
#define  FLASH_BASE                                0x40022000 /*!<Base Address: 0x40022000*/

/**
  * @brief FLASH Register Structure Definition
  */
typedef struct
{
    __IO uint32_t ACR;                 /*!<FLASH Flash access control register            offset: 0x00       */
    __IO uint32_t KEYR;                /*!<FLASH FPEC key register                        offset: 0x04       */
    __IO uint32_t OPTKEYR;             /*!<FLASH Flash OPTKEY register                    offset: 0x08       */
    __IO uint32_t SR;                  /*!<FLASH Flash status register                    offset: 0x0C       */
    __IO uint32_t CR;                  /*!<FLASH Flash control register                   offset: 0x10       */
    __IO uint32_t AR;                  /*!<FLASH Flash address register                   offset: 0x14       */
    __IO uint32_t RESERVED0x18[1];     /*!<                                               offset: 0x18       */
    __IO uint32_t OBR;                 /*!<FLASH Option byte register                     offset: 0x1C       */
    __IO uint32_t WRPR;                /*!<FLASH Write protection register                offset: 0x20       */
} FLASH_TypeDef;

/**
  * @brief FLASH type pointer Definition
  */
#define FLASH                                     ((FLASH_TypeDef *)FLASH_BASE)

/**
  * @brief FLASH_ACR Register Bit Definition
  */
#define  FLASH_ACR_LATENCY_Pos                    (0)
#define  FLASH_ACR_LATENCY_Msk                    (0x7U << FLASH_ACR_LATENCY_Pos) /*!<Latency*/
#define  FLASH_ACR_LATENCY                        FLASH_ACR_LATENCY_Msk
#define  FLASH_ACR_LATENCY_0                      (0x1U << FLASH_ACR_LATENCY_Pos)
#define  FLASH_ACR_LATENCY_1                      (0x2U << FLASH_ACR_LATENCY_Pos)
#define  FLASH_ACR_LATENCY_2                      (0x4U << FLASH_ACR_LATENCY_Pos)
#define  FLASH_ACR_PRFTBE_Pos                     (4)
#define  FLASH_ACR_PRFTBE_Msk                     (0x1U << FLASH_ACR_PRFTBE_Pos) /*!<Prefetch buffer enable*/
#define  FLASH_ACR_PRFTBE                         FLASH_ACR_PRFTBE_Msk

/**
  * @brief FLASH_KEYR Register Bit Definition
  */
#define  FLASH_KEYR_FKEYR_Pos                     (0)
#define  FLASH_KEYR_FKEYR_Msk                     (0xFFFFFFFFU << FLASH_KEYR_FKEYR_Pos) /*!<FPEC Flash key*/
#define  FLASH_KEYR_FKEYR                         FLASH_KEYR_FKEYR_Msk
#define  FLASH_KEYR_FKEYR_0                       (0x00000001U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_1                       (0x00000002U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_2                       (0x00000004U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_3                       (0x00000008U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_4                       (0x00000010U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_5                       (0x00000020U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_6                       (0x00000040U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_7                       (0x00000080U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_8                       (0x00000100U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_9                       (0x00000200U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_10                      (0x00000400U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_11                      (0x00000800U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_12                      (0x00001000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_13                      (0x00002000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_14                      (0x00004000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_15                      (0x00008000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_16                      (0x00010000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_17                      (0x00020000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_18                      (0x00040000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_19                      (0x00080000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_20                      (0x00100000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_21                      (0x00200000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_22                      (0x00400000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_23                      (0x00800000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_24                      (0x01000000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_25                      (0x02000000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_26                      (0x04000000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_27                      (0x08000000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_28                      (0x10000000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_29                      (0x20000000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_30                      (0x40000000U << FLASH_KEYR_FKEYR_Pos)
#define  FLASH_KEYR_FKEYR_31                      (0x80000000U << FLASH_KEYR_FKEYR_Pos)

/**
  * @brief FLASH_OPTKEYR Register Bit Definition
  */
#define  FLASH_OPTKEYR_OPTKEYR_Pos                (0)
#define  FLASH_OPTKEYR_OPTKEYR_Msk                (0xFFFFFFFFU << FLASH_OPTKEYR_OPTKEYR_Pos) /*!<Option byte key*/
#define  FLASH_OPTKEYR_OPTKEYR                    FLASH_OPTKEYR_OPTKEYR_Msk
#define  FLASH_OPTKEYR_OPTKEYR_0                  (0x00000001U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_1                  (0x00000002U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_2                  (0x00000004U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_3                  (0x00000008U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_4                  (0x00000010U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_5                  (0x00000020U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_6                  (0x00000040U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_7                  (0x00000080U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_8                  (0x00000100U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_9                  (0x00000200U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_10                 (0x00000400U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_11                 (0x00000800U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_12                 (0x00001000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_13                 (0x00002000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_14                 (0x00004000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_15                 (0x00008000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_16                 (0x00010000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_17                 (0x00020000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_18                 (0x00040000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_19                 (0x00080000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_20                 (0x00100000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_21                 (0x00200000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_22                 (0x00400000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_23                 (0x00800000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_24                 (0x01000000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_25                 (0x02000000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_26                 (0x04000000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_27                 (0x08000000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_28                 (0x10000000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_29                 (0x20000000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_30                 (0x40000000U << FLASH_OPTKEYR_OPTKEYR_Pos)
#define  FLASH_OPTKEYR_OPTKEYR_31                 (0x80000000U << FLASH_OPTKEYR_OPTKEYR_Pos)

/**
  * @brief FLASH_SR Register Bit Definition
  */
#define  FLASH_SR_BSY_Pos                         (0)
#define  FLASH_SR_BSY_Msk                         (0x1U << FLASH_SR_BSY_Pos)      /*!<Busy*/
#define  FLASH_SR_BSY                             FLASH_SR_BSY_Msk
#define  FLASH_SR_PGERR_Pos                       (2)
#define  FLASH_SR_PGERR_Msk                       (0x1U << FLASH_SR_PGERR_Pos)    /*!<Programming error*/
#define  FLASH_SR_PGERR                           FLASH_SR_PGERR_Msk
#define  FLASH_SR_WRPRTERR_Pos                    (4)
#define  FLASH_SR_WRPRTERR_Msk                    (0x1U << FLASH_SR_WRPRTERR_Pos) /*!<Write protection error*/
#define  FLASH_SR_WRPRTERR                        FLASH_SR_WRPRTERR_Msk
#define  FLASH_SR_EOP_Pos                         (5)
#define  FLASH_SR_EOP_Msk                         (0x1U << FLASH_SR_EOP_Pos)      /*!<End of operation*/
#define  FLASH_SR_EOP                             FLASH_SR_EOP_Msk

/**
  * @brief FLASH_CR Register Bit Definition
  */
#define  FLASH_CR_PG_Pos                          (0)
#define  FLASH_CR_PG_Msk                          (0x1U << FLASH_CR_PG_Pos)     /*!<Programming*/
#define  FLASH_CR_PG                              FLASH_CR_PG_Msk
#define  FLASH_CR_PER_Pos                         (1)
#define  FLASH_CR_PER_Msk                         (0x1U << FLASH_CR_PER_Pos)    /*!<Page erase*/
#define  FLASH_CR_PER                             FLASH_CR_PER_Msk
#define  FLASH_CR_MER_Pos                         (2)
#define  FLASH_CR_MER_Msk                         (0x1U << FLASH_CR_MER_Pos)    /*!<Mass erase*/
#define  FLASH_CR_MER                             FLASH_CR_MER_Msk
#define  FLASH_CR_OPTPG_Pos                       (4)
#define  FLASH_CR_OPTPG_Msk                       (0x1U << FLASH_CR_OPTPG_Pos)  /*!<Option byte programming*/
#define  FLASH_CR_OPTPG                           FLASH_CR_OPTPG_Msk
#define  FLASH_CR_OPTER_Pos                       (5)
#define  FLASH_CR_OPTER_Msk                       (0x1U << FLASH_CR_OPTER_Pos)  /*!<Option byte erase*/
#define  FLASH_CR_OPTER                           FLASH_CR_OPTER_Msk
#define  FLASH_CR_STRT_Pos                        (6)
#define  FLASH_CR_STRT_Msk                        (0x1U << FLASH_CR_STRT_Pos)   /*!<Start*/
#define  FLASH_CR_STRT                            FLASH_CR_STRT_Msk
#define  FLASH_CR_LOCK_Pos                        (7)
#define  FLASH_CR_LOCK_Msk                        (0x1U << FLASH_CR_LOCK_Pos)   /*!<Lock*/
#define  FLASH_CR_LOCK                            FLASH_CR_LOCK_Msk
#define  FLASH_CR_OPTWRE_Pos                      (9)
#define  FLASH_CR_OPTWRE_Msk                      (0x1U << FLASH_CR_OPTWRE_Pos) /*!<Option byte write enable*/
#define  FLASH_CR_OPTWRE                          FLASH_CR_OPTWRE_Msk
#define  FLASH_CR_ERRIE_Pos                       (10)
#define  FLASH_CR_ERRIE_Msk                       (0x1U << FLASH_CR_ERRIE_Pos)  /*!<Error interrupt enable*/
#define  FLASH_CR_ERRIE                           FLASH_CR_ERRIE_Msk
#define  FLASH_CR_EOPIE_Pos                       (12)
#define  FLASH_CR_EOPIE_Msk                       (0x1U << FLASH_CR_EOPIE_Pos)  /*!<End of operation interrupt enable*/
#define  FLASH_CR_EOPIE                           FLASH_CR_EOPIE_Msk

/**
  * @brief FLASH_AR Register Bit Definition
  */
#define  FLASH_AR_FAR_Pos                         (0)
#define  FLASH_AR_FAR_Msk                         (0xFFFFFFFFU << FLASH_AR_FAR_Pos) /*!<Flash Address*/
#define  FLASH_AR_FAR                             FLASH_AR_FAR_Msk
#define  FLASH_AR_FAR_0                           (0x00000001U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_1                           (0x00000002U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_2                           (0x00000004U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_3                           (0x00000008U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_4                           (0x00000010U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_5                           (0x00000020U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_6                           (0x00000040U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_7                           (0x00000080U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_8                           (0x00000100U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_9                           (0x00000200U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_10                          (0x00000400U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_11                          (0x00000800U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_12                          (0x00001000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_13                          (0x00002000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_14                          (0x00004000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_15                          (0x00008000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_16                          (0x00010000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_17                          (0x00020000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_18                          (0x00040000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_19                          (0x00080000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_20                          (0x00100000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_21                          (0x00200000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_22                          (0x00400000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_23                          (0x00800000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_24                          (0x01000000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_25                          (0x02000000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_26                          (0x04000000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_27                          (0x08000000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_28                          (0x10000000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_29                          (0x20000000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_30                          (0x40000000U << FLASH_AR_FAR_Pos)
#define  FLASH_AR_FAR_31                          (0x80000000U << FLASH_AR_FAR_Pos)

/**
  * @brief FLASH_OBR Register Bit Definition
  */
#define  FLASH_OBR_OPTERR_Pos                     (0)
#define  FLASH_OBR_OPTERR_Msk                     (0x1U << FLASH_OBR_OPTERR_Pos)    /*!<Option byte error*/
#define  FLASH_OBR_OPTERR                         FLASH_OBR_OPTERR_Msk
#define  FLASH_OBR_RDPRT_Pos                      (1)
#define  FLASH_OBR_RDPRT_Msk                      (0x1U << FLASH_OBR_RDPRT_Pos)     /*!<Read protection level status*/
#define  FLASH_OBR_RDPRT                          FLASH_OBR_RDPRT_Msk
#define  FLASH_OBR_WDG_SW_Pos                     (2)
#define  FLASH_OBR_WDG_SW_Msk                     (0x1U << FLASH_OBR_WDG_SW_Pos)    /*!<Select watchdog event*/
#define  FLASH_OBR_WDG_SW                         FLASH_OBR_WDG_SW_Msk
#define  FLASH_OBR_nRST_STOP_Pos                  (3)
#define  FLASH_OBR_nRST_STOP_Msk                  (0x1U << FLASH_OBR_nRST_STOP_Pos) /*!<Reset event in stop mode*/
#define  FLASH_OBR_nRST_STOP                      FLASH_OBR_nRST_STOP_Msk
#define  FLASH_OBR_Data0_Pos                      (10)
#define  FLASH_OBR_Data0_Msk                      (0xFFU << FLASH_OBR_Data0_Pos)    /*!<Data0*/
#define  FLASH_OBR_Data0                          FLASH_OBR_Data0_Msk
#define  FLASH_OBR_Data0_0                        (0x01U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data0_1                        (0x02U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data0_2                        (0x04U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data0_3                        (0x08U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data0_4                        (0x10U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data0_5                        (0x20U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data0_6                        (0x40U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data0_7                        (0x80U << FLASH_OBR_Data0_Pos)
#define  FLASH_OBR_Data1_Pos                      (18)
#define  FLASH_OBR_Data1_Msk                      (0xFFU << FLASH_OBR_Data1_Pos) /*!<Data1*/
#define  FLASH_OBR_Data1                          FLASH_OBR_Data1_Msk
#define  FLASH_OBR_Data1_0                        (0x01U << FLASH_OBR_Data1_Pos)
#define  FLASH_OBR_Data1_1                        (0x02U << FLASH_OBR_Data1_Pos)
#define  FLASH_OBR_Data1_2                        (0x04U << FLASH_OBR_Data1_Pos)
#define  FLASH_OBR_Data1_3                        (0x08U << FLASH_OBR_Data1_Pos)
#define  FLASH_OBR_Data1_4                        (0x10U << FLASH_OBR_Data1_Pos)
#define  FLASH_OBR_Data1_5                        (0x20U << FLASH_OBR_Data1_Pos)
#define  FLASH_OBR_Data1_6                        (0x40U << FLASH_OBR_Data1_Pos)
#define  FLASH_OBR_Data1_7                        (0x80U << FLASH_OBR_Data1_Pos)

/**
  * @brief FLASH_WRPR Register Bit Definition
  */
#define  FLASH_WRPR_WRP_Pos                       (0)
#define  FLASH_WRPR_WRP_Msk                       (0xFU << FLASH_WRPR_WRP_Pos) /*!<Write protect*/
#define  FLASH_WRPR_WRP                           FLASH_WRPR_WRP_Msk
#define  FLASH_WRPR_WRP_0                         (0x1U << FLASH_WRPR_WRP_Pos)
#define  FLASH_WRPR_WRP_1                         (0x2U << FLASH_WRPR_WRP_Pos)
#define  FLASH_WRPR_WRP_2                         (0x4U << FLASH_WRPR_WRP_Pos)
#define  FLASH_WRPR_WRP_3                         (0x8U << FLASH_WRPR_WRP_Pos)

#endif

