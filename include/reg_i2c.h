/***********************************************************************************************************************
    @file     reg_i2c.h
    @author   VV TEAM
    @brief    This flie contains all the I2C's register and its field definition.
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

#ifndef __REG_I2C_H
#define __REG_I2C_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include <core_cm0.h>

/**
  * @brief I2C Base Address Definition
  */
#define  I2C1_BASE                                 0x40005400 /*!<Base Address: 0x40005400*/

/**
  * @brief I2C Register Structure Definition
  */
typedef struct
{
    __IO uint32_t CR;                  /*!<I2C Control Register                           offset: 0x00       */
    __IO uint32_t TAR;                 /*!<I2C Target Address Register                    offset: 0x04       */
    __IO uint32_t SAR;                 /*!<I2C Slave Address Register                     offset: 0x08       */
    __IO uint32_t RESERVED0x0C[1];     /*!<                                               offset: 0x0C       */
    __IO uint32_t DR;                  /*!<I2C Data Command Register                      offset: 0x10       */
    __IO uint32_t SSHR;                /*!<I2C Standard Mode SCL High Count Register      offset: 0x14       */
    __IO uint32_t SSLR;                /*!<I2C Standard Mode SCL Low Count Register       offset: 0x18       */
    __IO uint32_t FSHR;                /*!<I2C Fast Mode SCL High Count Register          offset: 0x1C       */
    __IO uint32_t FSLR;                /*!<I2C Fast Mode SCL Low Count Register           offset: 0x20       */
    __IO uint32_t RESERVED0x24[2];     /*!<                                               offset: 0x24~0x28  */
    __IO uint32_t ISR;                 /*!<I2C Interrupt Status Register                  offset: 0x2C       */
    __IO uint32_t IMR;                 /*!<I2C Interrupt Mask Register                    offset: 0x30       */
    __IO uint32_t RAWISR;              /*!<I2C RAW Interrupt Status Register              offset: 0x34       */
    __IO uint32_t RXTLR;               /*!<I2C Receive Threshold Register                 offset: 0x38       */
    __IO uint32_t TXTLR;               /*!<I2C Transmit Threshold Register                offset: 0x3C       */
    __IO uint32_t ICR;                 /*!<I2C Combined and Independent Interrupt Clear   offset: 0x40
                                           Register                                                          */
    __IO uint32_t RX_UNDER;            /*!<I2C RX_UNDER Interrupt Clear Register          offset: 0x44       */
    __IO uint32_t RX_OVER;             /*!<I2C RX_OVER Interrupt Clear Register           offset: 0x48       */
    __IO uint32_t TX_OVER;             /*!<I2C TX_OVER Interrupt Clear Register           offset: 0x4C       */
    __IO uint32_t RD_REQ;              /*!<I2C RD_REQ Interrupt Clear Register            offset: 0x50       */
    __IO uint32_t TX_ABRT;             /*!<I2C TX_ABRT Interrupt Clear Register           offset: 0x54       */
    __IO uint32_t RX_DONE;             /*!<I2C RX_DONE Interrupt Clear Register           offset: 0x58       */
    __IO uint32_t ACTIV;               /*!<I2C ACTIVITY Interrupt Clear Register          offset: 0x5C       */
    __IO uint32_t STOP;                /*!<I2C STOP_DET Interrupt Clear Register          offset: 0x60       */
    __IO uint32_t START;               /*!<I2C START_DET Interrupt Clear Register         offset: 0x64       */
    __IO uint32_t GC;                  /*!<I2C GEN_CALL Interrupt Clear Register          offset: 0x68       */
    __IO uint32_t ENR;                 /*!<I2C Enable Register                            offset: 0x6C       */
    __IO uint32_t SR;                  /*!<I2C Status Register                            offset: 0x70       */
    __IO uint32_t TXFLR;               /*!<I2C Transmit FIFO Level Register               offset: 0x74       */
    __IO uint32_t RXFLR;               /*!<I2C Receive FIFO Level Register                offset: 0x78       */
    __IO uint32_t HOLD;                /*!<I2C SDA Hold Time Register                     offset: 0x7C       */
    __IO uint32_t RESERVED0x80[5];     /*!<                                               offset: 0x80~0x90  */
    __IO uint32_t SETUP;               /*!<I2C SDA Setup Time Register                    offset: 0x94       */
    __IO uint32_t GCR;                 /*!<I2C General Call ACK Register                  offset: 0x98       */
    __IO uint32_t RESERVED0x9C[5];     /*!<                                               offset: 0x9C~0xAC  */
    __IO uint32_t SLVMASK;             /*!<I2C Slave Address Mask Register                offset: 0xB0       */
    __IO uint32_t SLVRCVADDR;          /*!<I2C Slave Address Receive Register             offset: 0xB4       */
} I2C_TypeDef;

/**
  * @brief I2C type pointer Definition
  */
#define I2C1                                      ((I2C_TypeDef *)I2C1_BASE)

/**
  * @brief I2C_CR Register Bit Definition
  */
#define  I2C_CR_MASTER_Pos                        (0)
#define  I2C_CR_MASTER_Msk                        (0x1U << I2C_CR_MASTER_Pos) /*!<This bit controls whether the I2C master is enabled.*/
#define  I2C_CR_MASTER                            I2C_CR_MASTER_Msk
#define  I2C_CR_SPEED_Pos                         (1)
#define  I2C_CR_SPEED_Msk                         (0x3U << I2C_CR_SPEED_Pos)  /*!<These bits control at which speed the I2C operates in the Master mode.*/
#define  I2C_CR_SPEED                             I2C_CR_SPEED_Msk
#define  I2C_CR_SPEED_0                           (0x1U << I2C_CR_SPEED_Pos)
#define  I2C_CR_SPEED_1                           (0x2U << I2C_CR_SPEED_Pos)
#define  I2C_CR_SLAVE10_Pos                       (3)
#define  I2C_CR_SLAVE10_Msk                       (0x1U << I2C_CR_SLAVE10_Pos)  /*!<When I2C is acting as a slave, this bit controls whether it responds to 7-or 10-bit addresses.*/
#define  I2C_CR_SLAVE10                           I2C_CR_SLAVE10_Msk
#define  I2C_CR_MASTER10_Pos                      (4)
#define  I2C_CR_MASTER10_Msk                      (0x1U << I2C_CR_MASTER10_Pos) /*!<Addressing mode when I2C is acting as a master*/
#define  I2C_CR_MASTER10                          I2C_CR_MASTER10_Msk
#define  I2C_CR_REPEN_Pos                         (5)
#define  I2C_CR_REPEN_Msk                         (0x1U << I2C_CR_REPEN_Pos)    /*!<This bit determines whether RESTART conditions may be sent when I2C is acting as a master.*/
#define  I2C_CR_REPEN                             I2C_CR_REPEN_Msk
#define  I2C_CR_DISSLAVE_Pos                      (6)
#define  I2C_CR_DISSLAVE_Msk                      (0x1U << I2C_CR_DISSLAVE_Pos) /*!<This bit controls whether I2C has its slave disabled*/
#define  I2C_CR_DISSLAVE                          I2C_CR_DISSLAVE_Msk
#define  I2C_CR_STOPINT_Pos                       (7)
#define  I2C_CR_STOPINT_Msk                       (0x1U << I2C_CR_STOPINT_Pos)  /*!<This bit controls whether a STOP interrupt is generated in the Slave mode.*/
#define  I2C_CR_STOPINT                           I2C_CR_STOPINT_Msk
#define  I2C_CR_EMPINT_Pos                        (8)
#define  I2C_CR_EMPINT_Msk                        (0x1U << I2C_CR_EMPINT_Pos)   /*!<This bit controls whether a TX_EMPTY interrupt is generated. For details, refer to the I2C_RAWISR register.*/
#define  I2C_CR_EMPINT                            I2C_CR_EMPINT_Msk
#define  I2C_CR_PAD_SEL_Pos                       (12)
#define  I2C_CR_PAD_SEL_Msk                       (0x1U << I2C_CR_PAD_SEL_Pos)  /*!<PAD MUX Swap the PAD corresponding to SCL and SDA*/
#define  I2C_CR_PAD_SEL                           I2C_CR_PAD_SEL_Msk

/**
  * @brief I2C_TAR Register Bit Definition
  */
#define  I2C_TAR_ADDR_Pos                         (0)
#define  I2C_TAR_ADDR_Msk                         (0x3FFU << I2C_TAR_ADDR_Pos) /*!<This is the target address for any master transaction.*/
#define  I2C_TAR_ADDR                             I2C_TAR_ADDR_Msk
#define  I2C_TAR_ADDR_0                           (0x001U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_1                           (0x002U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_2                           (0x004U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_3                           (0x008U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_4                           (0x010U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_5                           (0x020U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_6                           (0x040U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_7                           (0x080U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_8                           (0x100U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_ADDR_9                           (0x200U << I2C_TAR_ADDR_Pos)
#define  I2C_TAR_GC_Pos                           (10)
#define  I2C_TAR_GC_Msk                           (0x1U << I2C_TAR_GC_Pos)      /*!<If bit 11 (SPECIAL) is set to 1, then this bit indicates whether a General Call or START byte command is to be performed by the I2C.*/
#define  I2C_TAR_GC                               I2C_TAR_GC_Msk
#define  I2C_TAR_SPECIAL_Pos                      (11)
#define  I2C_TAR_SPECIAL_Msk                      (0x1U << I2C_TAR_SPECIAL_Pos) /*!<This bit indicates whether software performs a special command (General Call or Start Byte command).*/
#define  I2C_TAR_SPECIAL                          I2C_TAR_SPECIAL_Msk

/**
  * @brief I2C_SAR Register Bit Definition
  */
#define  I2C_SAR_ADDR_Pos                         (0)
#define  I2C_SAR_ADDR_Msk                         (0x3FFU << I2C_SAR_ADDR_Pos) /*!<The slave address of I2C. For 7-bit addressing, only ADDR [6:0] is valid.*/
#define  I2C_SAR_ADDR                             I2C_SAR_ADDR_Msk
#define  I2C_SAR_ADDR_0                           (0x001U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_1                           (0x002U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_2                           (0x004U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_3                           (0x008U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_4                           (0x010U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_5                           (0x020U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_6                           (0x040U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_7                           (0x080U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_8                           (0x100U << I2C_SAR_ADDR_Pos)
#define  I2C_SAR_ADDR_9                           (0x200U << I2C_SAR_ADDR_Pos)

/**
  * @brief I2C_DR Register Bit Definition
  */
#define  I2C_DR_DAT_Pos                           (0)
#define  I2C_DR_DAT_Msk                           (0xFFU << I2C_DR_DAT_Pos) /*!<This register contains the data to be transmitted or received on the I2C bus.*/
#define  I2C_DR_DAT                               I2C_DR_DAT_Msk
#define  I2C_DR_DAT_0                             (0x01U << I2C_DR_DAT_Pos)
#define  I2C_DR_DAT_1                             (0x02U << I2C_DR_DAT_Pos)
#define  I2C_DR_DAT_2                             (0x04U << I2C_DR_DAT_Pos)
#define  I2C_DR_DAT_3                             (0x08U << I2C_DR_DAT_Pos)
#define  I2C_DR_DAT_4                             (0x10U << I2C_DR_DAT_Pos)
#define  I2C_DR_DAT_5                             (0x20U << I2C_DR_DAT_Pos)
#define  I2C_DR_DAT_6                             (0x40U << I2C_DR_DAT_Pos)
#define  I2C_DR_DAT_7                             (0x80U << I2C_DR_DAT_Pos)
#define  I2C_DR_CMD_Pos                           (8)
#define  I2C_DR_CMD_Msk                           (0x1U << I2C_DR_CMD_Pos)     /*!<This bit controls whether a read or a write is performed in the Master mode.*/
#define  I2C_DR_CMD                               I2C_DR_CMD_Msk
#define  I2C_DR_STOP_Pos                          (9)
#define  I2C_DR_STOP_Msk                          (0x1U << I2C_DR_STOP_Pos)    /*!<Whether to generate STOP after sending or receiving bytes*/
#define  I2C_DR_STOP                              I2C_DR_STOP_Msk
#define  I2C_DR_RESTART_Pos                       (10)
#define  I2C_DR_RESTART_Msk                       (0x1U << I2C_DR_RESTART_Pos) /*!<Whether to generate RESTART before sending or receiving bytes*/
#define  I2C_DR_RESTART                           I2C_DR_RESTART_Msk

/**
  * @brief I2C_SSHR Register Bit Definition
  */
#define  I2C_SSHR_CNT_Pos                         (0)
#define  I2C_SSHR_CNT_Msk                         (0xFFFFU << I2C_SSHR_CNT_Pos) /*!<This register sets the SCL clock high-period count (min valid value is 6) for Standard mode.*/
#define  I2C_SSHR_CNT                             I2C_SSHR_CNT_Msk
#define  I2C_SSHR_CNT_0                           (0x0001U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_1                           (0x0002U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_2                           (0x0004U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_3                           (0x0008U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_4                           (0x0010U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_5                           (0x0020U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_6                           (0x0040U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_7                           (0x0080U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_8                           (0x0100U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_9                           (0x0200U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_10                          (0x0400U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_11                          (0x0800U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_12                          (0x1000U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_13                          (0x2000U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_14                          (0x4000U << I2C_SSHR_CNT_Pos)
#define  I2C_SSHR_CNT_15                          (0x8000U << I2C_SSHR_CNT_Pos)

/**
  * @brief I2C_SSLR Register Bit Definition
  */
#define  I2C_SSLR_CNT_Pos                         (0)
#define  I2C_SSLR_CNT_Msk                         (0xFFFFU << I2C_SSLR_CNT_Pos) /*!<This register sets the SCL clock low-period count (min valid value is 8) for Standard mode.*/
#define  I2C_SSLR_CNT                             I2C_SSLR_CNT_Msk
#define  I2C_SSLR_CNT_0                           (0x0001U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_1                           (0x0002U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_2                           (0x0004U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_3                           (0x0008U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_4                           (0x0010U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_5                           (0x0020U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_6                           (0x0040U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_7                           (0x0080U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_8                           (0x0100U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_9                           (0x0200U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_10                          (0x0400U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_11                          (0x0800U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_12                          (0x1000U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_13                          (0x2000U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_14                          (0x4000U << I2C_SSLR_CNT_Pos)
#define  I2C_SSLR_CNT_15                          (0x8000U << I2C_SSLR_CNT_Pos)

/**
  * @brief I2C_FSHR Register Bit Definition
  */
#define  I2C_FSHR_CNT_Pos                         (0)
#define  I2C_FSHR_CNT_Msk                         (0xFFFFU << I2C_FSHR_CNT_Pos) /*!<This register sets the SCL clock high-period count (min valid value is 6) for Fast mode.*/
#define  I2C_FSHR_CNT                             I2C_FSHR_CNT_Msk
#define  I2C_FSHR_CNT_0                           (0x0001U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_1                           (0x0002U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_2                           (0x0004U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_3                           (0x0008U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_4                           (0x0010U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_5                           (0x0020U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_6                           (0x0040U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_7                           (0x0080U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_8                           (0x0100U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_9                           (0x0200U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_10                          (0x0400U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_11                          (0x0800U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_12                          (0x1000U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_13                          (0x2000U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_14                          (0x4000U << I2C_FSHR_CNT_Pos)
#define  I2C_FSHR_CNT_15                          (0x8000U << I2C_FSHR_CNT_Pos)

/**
  * @brief I2C_FSLR Register Bit Definition
  */
#define  I2C_FSLR_CNT_Pos                         (0)
#define  I2C_FSLR_CNT_Msk                         (0xFFFFU << I2C_FSLR_CNT_Pos) /*!<This register sets the SCL clock low-period count (min valid value is 8) for Fast mode.*/
#define  I2C_FSLR_CNT                             I2C_FSLR_CNT_Msk
#define  I2C_FSLR_CNT_0                           (0x0001U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_1                           (0x0002U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_2                           (0x0004U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_3                           (0x0008U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_4                           (0x0010U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_5                           (0x0020U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_6                           (0x0040U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_7                           (0x0080U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_8                           (0x0100U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_9                           (0x0200U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_10                          (0x0400U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_11                          (0x0800U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_12                          (0x1000U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_13                          (0x2000U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_14                          (0x4000U << I2C_FSLR_CNT_Pos)
#define  I2C_FSLR_CNT_15                          (0x8000U << I2C_FSLR_CNT_Pos)

/**
  * @brief I2C_ISR Register Bit Definition
  */
#define  I2C_ISR_RX_UNDER_Pos                     (0)
#define  I2C_ISR_RX_UNDER_Msk                     (0x1U << I2C_ISR_RX_UNDER_Pos) /*!<Receive buffer over*/
#define  I2C_ISR_RX_UNDER                         I2C_ISR_RX_UNDER_Msk
#define  I2C_ISR_RX_OVER_Pos                      (1)
#define  I2C_ISR_RX_OVER_Msk                      (0x1U << I2C_ISR_RX_OVER_Pos)  /*!<Receive buffer over*/
#define  I2C_ISR_RX_OVER                          I2C_ISR_RX_OVER_Msk
#define  I2C_ISR_RX_FULL_Pos                      (2)
#define  I2C_ISR_RX_FULL_Msk                      (0x1U << I2C_ISR_RX_FULL_Pos)  /*!<Receive buffer full*/
#define  I2C_ISR_RX_FULL                          I2C_ISR_RX_FULL_Msk
#define  I2C_ISR_TX_OVER_Pos                      (3)
#define  I2C_ISR_TX_OVER_Msk                      (0x1U << I2C_ISR_TX_OVER_Pos)  /*!<Transmit buffer over*/
#define  I2C_ISR_TX_OVER                          I2C_ISR_TX_OVER_Msk
#define  I2C_ISR_TX_EMPTY_Pos                     (4)
#define  I2C_ISR_TX_EMPTY_Msk                     (0x1U << I2C_ISR_TX_EMPTY_Pos) /*!<Transmit buffer empty*/
#define  I2C_ISR_TX_EMPTY                         I2C_ISR_TX_EMPTY_Msk
#define  I2C_ISR_RD_REQ_Pos                       (5)
#define  I2C_ISR_RD_REQ_Msk                       (0x1U << I2C_ISR_RD_REQ_Pos)   /*!<Read request*/
#define  I2C_ISR_RD_REQ                           I2C_ISR_RD_REQ_Msk
#define  I2C_ISR_TX_ABRT_Pos                      (6)
#define  I2C_ISR_TX_ABRT_Msk                      (0x1U << I2C_ISR_TX_ABRT_Pos)  /*!<Transmit abort*/
#define  I2C_ISR_TX_ABRT                          I2C_ISR_TX_ABRT_Msk
#define  I2C_ISR_RX_DONE_Pos                      (7)
#define  I2C_ISR_RX_DONE_Msk                      (0x1U << I2C_ISR_RX_DONE_Pos)  /*!<Slave transmit done*/
#define  I2C_ISR_RX_DONE                          I2C_ISR_RX_DONE_Msk
#define  I2C_ISR_ACTIV_Pos                        (8)
#define  I2C_ISR_ACTIV_Msk                        (0x1U << I2C_ISR_ACTIV_Pos)    /*!<This bit captures I2C module activity. Once this bit is set, it stays set unless one of the four methods is used to clear it*/
#define  I2C_ISR_ACTIV                            I2C_ISR_ACTIV_Msk
#define  I2C_ISR_STOP_Pos                         (9)
#define  I2C_ISR_STOP_Msk                         (0x1U << I2C_ISR_STOP_Pos)     /*!<STOP condition detection*/
#define  I2C_ISR_STOP                             I2C_ISR_STOP_Msk
#define  I2C_ISR_START_Pos                        (10)
#define  I2C_ISR_START_Msk                        (0x1U << I2C_ISR_START_Pos)    /*!<START condition detection This bit is set to 1 once a START or RESTART condition has occurred on the I2C interface regardless of whether I2C is operating in Master or Slave mode.*/
#define  I2C_ISR_START                            I2C_ISR_START_Msk
#define  I2C_ISR_GC_Pos                           (11)
#define  I2C_ISR_GC_Msk                           (0x1U << I2C_ISR_GC_Pos)       /*!<General Call*/
#define  I2C_ISR_GC                               I2C_ISR_GC_Msk

/**
  * @brief I2C_IMR Register Bit Definition
  */
#define  I2C_IMR_RX_UNDER_Pos                     (0)
#define  I2C_IMR_RX_UNDER_Msk                     (0x1U << I2C_IMR_RX_UNDER_Pos) /*!<Receive buffer over*/
#define  I2C_IMR_RX_UNDER                         I2C_IMR_RX_UNDER_Msk
#define  I2C_IMR_RX_OVER_Pos                      (1)
#define  I2C_IMR_RX_OVER_Msk                      (0x1U << I2C_IMR_RX_OVER_Pos)  /*!<Receive buffer over*/
#define  I2C_IMR_RX_OVER                          I2C_IMR_RX_OVER_Msk
#define  I2C_IMR_RX_FULL_Pos                      (2)
#define  I2C_IMR_RX_FULL_Msk                      (0x1U << I2C_IMR_RX_FULL_Pos)  /*!<Receive buffer full*/
#define  I2C_IMR_RX_FULL                          I2C_IMR_RX_FULL_Msk
#define  I2C_IMR_TX_OVER_Pos                      (3)
#define  I2C_IMR_TX_OVER_Msk                      (0x1U << I2C_IMR_TX_OVER_Pos)  /*!<Transmit buffer over*/
#define  I2C_IMR_TX_OVER                          I2C_IMR_TX_OVER_Msk
#define  I2C_IMR_TX_EMPTY_Pos                     (4)
#define  I2C_IMR_TX_EMPTY_Msk                     (0x1U << I2C_IMR_TX_EMPTY_Pos) /*!<Transmit buffer empty*/
#define  I2C_IMR_TX_EMPTY                         I2C_IMR_TX_EMPTY_Msk
#define  I2C_IMR_RD_REQ_Pos                       (5)
#define  I2C_IMR_RD_REQ_Msk                       (0x1U << I2C_IMR_RD_REQ_Pos)   /*!<Read request*/
#define  I2C_IMR_RD_REQ                           I2C_IMR_RD_REQ_Msk
#define  I2C_IMR_TX_ABRT_Pos                      (6)
#define  I2C_IMR_TX_ABRT_Msk                      (0x1U << I2C_IMR_TX_ABRT_Pos)  /*!<Transmit abort*/
#define  I2C_IMR_TX_ABRT                          I2C_IMR_TX_ABRT_Msk
#define  I2C_IMR_RX_DONE_Pos                      (7)
#define  I2C_IMR_RX_DONE_Msk                      (0x1U << I2C_IMR_RX_DONE_Pos)  /*!<Slave transmit done*/
#define  I2C_IMR_RX_DONE                          I2C_IMR_RX_DONE_Msk
#define  I2C_IMR_ACTIV_Pos                        (8)
#define  I2C_IMR_ACTIV_Msk                        (0x1U << I2C_IMR_ACTIV_Pos)    /*!<This bit captures I2C module activity. Once this bit is set, it stays set unless one of the four methods is used to clear it*/
#define  I2C_IMR_ACTIV                            I2C_IMR_ACTIV_Msk
#define  I2C_IMR_STOP_Pos                         (9)
#define  I2C_IMR_STOP_Msk                         (0x1U << I2C_IMR_STOP_Pos)     /*!<STOP condition detection*/
#define  I2C_IMR_STOP                             I2C_IMR_STOP_Msk
#define  I2C_IMR_START_Pos                        (10)
#define  I2C_IMR_START_Msk                        (0x1U << I2C_IMR_START_Pos)    /*!<START condition detection This bit is set to 1 once a START or RESTART condition has occurred on the I2C interface regardless of whether I2C is operating in Master or Slave mode.*/
#define  I2C_IMR_START                            I2C_IMR_START_Msk
#define  I2C_IMR_GC_Pos                           (11)
#define  I2C_IMR_GC_Msk                           (0x1U << I2C_IMR_GC_Pos)       /*!<General Call*/
#define  I2C_IMR_GC                               I2C_IMR_GC_Msk

/**
  * @brief I2C_RAWISR Register Bit Definition
  */
#define  I2C_RAWISR_RX_UNDER_Pos                  (0)
#define  I2C_RAWISR_RX_UNDER_Msk                  (0x1U << I2C_RAWISR_RX_UNDER_Pos) /*!<Receive buffer over*/
#define  I2C_RAWISR_RX_UNDER                      I2C_RAWISR_RX_UNDER_Msk
#define  I2C_RAWISR_RX_OVER_Pos                   (1)
#define  I2C_RAWISR_RX_OVER_Msk                   (0x1U << I2C_RAWISR_RX_OVER_Pos)  /*!<Receive buffer over*/
#define  I2C_RAWISR_RX_OVER                       I2C_RAWISR_RX_OVER_Msk
#define  I2C_RAWISR_RX_FULL_Pos                   (2)
#define  I2C_RAWISR_RX_FULL_Msk                   (0x1U << I2C_RAWISR_RX_FULL_Pos)  /*!<Receive buffer full*/
#define  I2C_RAWISR_RX_FULL                       I2C_RAWISR_RX_FULL_Msk
#define  I2C_RAWISR_TX_OVER_Pos                   (3)
#define  I2C_RAWISR_TX_OVER_Msk                   (0x1U << I2C_RAWISR_TX_OVER_Pos)  /*!<Transmit buffer over*/
#define  I2C_RAWISR_TX_OVER                       I2C_RAWISR_TX_OVER_Msk
#define  I2C_RAWISR_TX_EMPTY_Pos                  (4)
#define  I2C_RAWISR_TX_EMPTY_Msk                  (0x1U << I2C_RAWISR_TX_EMPTY_Pos) /*!<Transmit buffer empty*/
#define  I2C_RAWISR_TX_EMPTY                      I2C_RAWISR_TX_EMPTY_Msk
#define  I2C_RAWISR_RD_REQ_Pos                    (5)
#define  I2C_RAWISR_RD_REQ_Msk                    (0x1U << I2C_RAWISR_RD_REQ_Pos)   /*!<Read request*/
#define  I2C_RAWISR_RD_REQ                        I2C_RAWISR_RD_REQ_Msk
#define  I2C_RAWISR_TX_ABRT_Pos                   (6)
#define  I2C_RAWISR_TX_ABRT_Msk                   (0x1U << I2C_RAWISR_TX_ABRT_Pos)  /*!<Transmit abort*/
#define  I2C_RAWISR_TX_ABRT                       I2C_RAWISR_TX_ABRT_Msk
#define  I2C_RAWISR_RX_DONE_Pos                   (7)
#define  I2C_RAWISR_RX_DONE_Msk                   (0x1U << I2C_RAWISR_RX_DONE_Pos)  /*!<Slave transmit done*/
#define  I2C_RAWISR_RX_DONE                       I2C_RAWISR_RX_DONE_Msk
#define  I2C_RAWISR_ACTIV_Pos                     (8)
#define  I2C_RAWISR_ACTIV_Msk                     (0x1U << I2C_RAWISR_ACTIV_Pos)    /*!<This bit captures I2C module activity. Once this bit is set, it stays set unless one of the four methods is used to clear it*/
#define  I2C_RAWISR_ACTIV                         I2C_RAWISR_ACTIV_Msk
#define  I2C_RAWISR_STOP_Pos                      (9)
#define  I2C_RAWISR_STOP_Msk                      (0x1U << I2C_RAWISR_STOP_Pos)     /*!<STOP condition detection*/
#define  I2C_RAWISR_STOP                          I2C_RAWISR_STOP_Msk
#define  I2C_RAWISR_START_Pos                     (10)
#define  I2C_RAWISR_START_Msk                     (0x1U << I2C_RAWISR_START_Pos)    /*!<START condition detection This bit is set to 1 once a START or RESTART condition has occurred on the I2C interface regardless of whether I2C is operating in Master or Slave mode.*/
#define  I2C_RAWISR_START                         I2C_RAWISR_START_Msk
#define  I2C_RAWISR_GC_Pos                        (11)
#define  I2C_RAWISR_GC_Msk                        (0x1U << I2C_RAWISR_GC_Pos)       /*!<General Call*/
#define  I2C_RAWISR_GC                            I2C_RAWISR_GC_Msk

/**
  * @brief I2C_RXTLR Register Bit Definition
  */
#define  I2C_RXTLR_TL_Pos                         (0)
#define  I2C_RXTLR_TL_Msk                         (0xFFU << I2C_RXTLR_TL_Pos) /*!<Receive FIFO threshold level*/
#define  I2C_RXTLR_TL                             I2C_RXTLR_TL_Msk
#define  I2C_RXTLR_TL_0                           (0x01U << I2C_RXTLR_TL_Pos)
#define  I2C_RXTLR_TL_1                           (0x02U << I2C_RXTLR_TL_Pos)
#define  I2C_RXTLR_TL_2                           (0x04U << I2C_RXTLR_TL_Pos)
#define  I2C_RXTLR_TL_3                           (0x08U << I2C_RXTLR_TL_Pos)
#define  I2C_RXTLR_TL_4                           (0x10U << I2C_RXTLR_TL_Pos)
#define  I2C_RXTLR_TL_5                           (0x20U << I2C_RXTLR_TL_Pos)
#define  I2C_RXTLR_TL_6                           (0x40U << I2C_RXTLR_TL_Pos)
#define  I2C_RXTLR_TL_7                           (0x80U << I2C_RXTLR_TL_Pos)

/**
  * @brief I2C_TXTLR Register Bit Definition
  */
#define  I2C_TXTLR_TL_Pos                         (0)
#define  I2C_TXTLR_TL_Msk                         (0xFFU << I2C_TXTLR_TL_Pos) /*!<Transmit FIFO threshold level*/
#define  I2C_TXTLR_TL                             I2C_TXTLR_TL_Msk
#define  I2C_TXTLR_TL_0                           (0x01U << I2C_TXTLR_TL_Pos)
#define  I2C_TXTLR_TL_1                           (0x02U << I2C_TXTLR_TL_Pos)
#define  I2C_TXTLR_TL_2                           (0x04U << I2C_TXTLR_TL_Pos)
#define  I2C_TXTLR_TL_3                           (0x08U << I2C_TXTLR_TL_Pos)
#define  I2C_TXTLR_TL_4                           (0x10U << I2C_TXTLR_TL_Pos)
#define  I2C_TXTLR_TL_5                           (0x20U << I2C_TXTLR_TL_Pos)
#define  I2C_TXTLR_TL_6                           (0x40U << I2C_TXTLR_TL_Pos)
#define  I2C_TXTLR_TL_7                           (0x80U << I2C_TXTLR_TL_Pos)

/**
  * @brief I2C_ICR Register Bit Definition
  */
#define  I2C_ICR_ICR_Pos                          (0)
#define  I2C_ICR_ICR_Msk                          (0x1U << I2C_ICR_ICR_Pos) /*!<Reading this register clears all combined and independent interrupts.*/
#define  I2C_ICR_ICR                              I2C_ICR_ICR_Msk

/**
  * @brief I2C_RX_UNDER Register Bit Definition
  */
#define  I2C_RX_UNDER_RX_UNDER_Pos                (0)
#define  I2C_RX_UNDER_RX_UNDER_Msk                (0x1U << I2C_RX_UNDER_RX_UNDER_Pos) /*!<Reading this register clears the RX_UNDER interrupt (I2C_RAWISR[0]).*/
#define  I2C_RX_UNDER_RX_UNDER                    I2C_RX_UNDER_RX_UNDER_Msk

/**
  * @brief I2C_RX_OVER Register Bit Definition
  */
#define  I2C_RX_OVER_RX_OVER_Pos                  (0)
#define  I2C_RX_OVER_RX_OVER_Msk                  (0x1U << I2C_RX_OVER_RX_OVER_Pos) /*!<Reading this register clears the RX_OVER interrupt (I2C_RAWISR[1]).*/
#define  I2C_RX_OVER_RX_OVER                      I2C_RX_OVER_RX_OVER_Msk

/**
  * @brief I2C_TX_OVER Register Bit Definition
  */
#define  I2C_TX_OVER_TX_OVER_Pos                  (0)
#define  I2C_TX_OVER_TX_OVER_Msk                  (0x1U << I2C_TX_OVER_TX_OVER_Pos) /*!<Reading this register clears the TX_OVER interrupt (I2C_RAWISR[3]).*/
#define  I2C_TX_OVER_TX_OVER                      I2C_TX_OVER_TX_OVER_Msk

/**
  * @brief I2C_RD_REQ Register Bit Definition
  */
#define  I2C_RD_REQ_RD_REQ_Pos                    (0)
#define  I2C_RD_REQ_RD_REQ_Msk                    (0x1U << I2C_RD_REQ_RD_REQ_Pos) /*!<Reading this register clears the RD_REQ interrupt (I2C_RAWISR[5]).*/
#define  I2C_RD_REQ_RD_REQ                        I2C_RD_REQ_RD_REQ_Msk

/**
  * @brief I2C_TX_ABRT Register Bit Definition
  */
#define  I2C_TX_ABRT_TX_ABRT_Pos                  (0)
#define  I2C_TX_ABRT_TX_ABRT_Msk                  (0x1U << I2C_TX_ABRT_TX_ABRT_Pos) /*!<Reading this register clears the TX_ABRT interrupt (I2C_RAWISR[6]).*/
#define  I2C_TX_ABRT_TX_ABRT                      I2C_TX_ABRT_TX_ABRT_Msk

/**
  * @brief I2C_RX_DONE Register Bit Definition
  */
#define  I2C_RX_DONE_RX_DONE_Pos                  (0)
#define  I2C_RX_DONE_RX_DONE_Msk                  (0x1U << I2C_RX_DONE_RX_DONE_Pos) /*!<Reading this register clears the RX_DONE interrupt (I2C_RAWISR[7]).*/
#define  I2C_RX_DONE_RX_DONE                      I2C_RX_DONE_RX_DONE_Msk

/**
  * @brief I2C_ACTIV Register Bit Definition
  */
#define  I2C_ACTIV_ACTIV_Pos                      (0)
#define  I2C_ACTIV_ACTIV_Msk                      (0x1U << I2C_ACTIV_ACTIV_Pos) /*!<Reading this register clears the ACTIV interrupt (I2C_RAWISR[8]) if the I2C is not active anymore.*/
#define  I2C_ACTIV_ACTIV                          I2C_ACTIV_ACTIV_Msk

/**
  * @brief I2C_STOP Register Bit Definition
  */
#define  I2C_STOP_STOP_Pos                        (0)
#define  I2C_STOP_STOP_Msk                        (0x1U << I2C_STOP_STOP_Pos) /*!<Reading this register clears the STOP interrupt (I2C_RAWISR[9]).*/
#define  I2C_STOP_STOP                            I2C_STOP_STOP_Msk

/**
  * @brief I2C_START Register Bit Definition
  */
#define  I2C_START_START_Pos                      (0)
#define  I2C_START_START_Msk                      (0x1U << I2C_START_START_Pos) /*!<Reading this register clears the START interrupt (I2C_RAWISR[10]).*/
#define  I2C_START_START                          I2C_START_START_Msk

/**
  * @brief I2C_GC Register Bit Definition
  */
#define  I2C_GC_GC_Pos                            (0)
#define  I2C_GC_GC_Msk                            (0x1U << I2C_GC_GC_Pos) /*!<Reading this register clears the GC interrupt (I2C_RAWISR[11]).*/
#define  I2C_GC_GC                                I2C_GC_GC_Msk

/**
  * @brief I2C_ENR Register Bit Definition
  */
#define  I2C_ENR_ENABLE_Pos                       (0)
#define  I2C_ENR_ENABLE_Msk                       (0x1U << I2C_ENR_ENABLE_Pos) /*!<I2C module enable*/
#define  I2C_ENR_ENABLE                           I2C_ENR_ENABLE_Msk
#define  I2C_ENR_ABORT_Pos                        (1)
#define  I2C_ENR_ABORT_Msk                        (0x1U << I2C_ENR_ABORT_Pos)  /*!<I2C transfer abort*/
#define  I2C_ENR_ABORT                            I2C_ENR_ABORT_Msk

/**
  * @brief I2C_SR Register Bit Definition
  */
#define  I2C_SR_ACTIV_Pos                         (0)
#define  I2C_SR_ACTIV_Msk                         (0x1U << I2C_SR_ACTIV_Pos)     /*!<I2C activity status*/
#define  I2C_SR_ACTIV                             I2C_SR_ACTIV_Msk
#define  I2C_SR_TFNF_Pos                          (1)
#define  I2C_SR_TFNF_Msk                          (0x1U << I2C_SR_TFNF_Pos)      /*!<Transmit FIFO not full*/
#define  I2C_SR_TFNF                              I2C_SR_TFNF_Msk
#define  I2C_SR_TFE_Pos                           (2)
#define  I2C_SR_TFE_Msk                           (0x1U << I2C_SR_TFE_Pos)       /*!<Transmit FIFO completely empty*/
#define  I2C_SR_TFE                               I2C_SR_TFE_Msk
#define  I2C_SR_RFNE_Pos                          (3)
#define  I2C_SR_RFNE_Msk                          (0x1U << I2C_SR_RFNE_Pos)      /*!<Receive FIFO not empty*/
#define  I2C_SR_RFNE                              I2C_SR_RFNE_Msk
#define  I2C_SR_RFF_Pos                           (4)
#define  I2C_SR_RFF_Msk                           (0x1U << I2C_SR_RFF_Pos)       /*!<Receive FIFO completely full*/
#define  I2C_SR_RFF                               I2C_SR_RFF_Msk
#define  I2C_SR_MST_ACTIV_Pos                     (5)
#define  I2C_SR_MST_ACTIV_Msk                     (0x1U << I2C_SR_MST_ACTIV_Pos) /*!<Master FSM activity status*/
#define  I2C_SR_MST_ACTIV                         I2C_SR_MST_ACTIV_Msk
#define  I2C_SR_SLV_ACTIV_Pos                     (6)
#define  I2C_SR_SLV_ACTIV_Msk                     (0x1U << I2C_SR_SLV_ACTIV_Pos) /*!<Slave FSM activity status*/
#define  I2C_SR_SLV_ACTIV                         I2C_SR_SLV_ACTIV_Msk

/**
  * @brief I2C_TXFLR Register Bit Definition
  */
#define  I2C_TXFLR_CNT_Pos                        (0)
#define  I2C_TXFLR_CNT_Msk                        (0x3U << I2C_TXFLR_CNT_Pos) /*!<Contains the number of valid data entries in the transmit FIFO (0~2)*/
#define  I2C_TXFLR_CNT                            I2C_TXFLR_CNT_Msk
#define  I2C_TXFLR_CNT_0                          (0x1U << I2C_TXFLR_CNT_Pos)
#define  I2C_TXFLR_CNT_1                          (0x2U << I2C_TXFLR_CNT_Pos)

/**
  * @brief I2C_RXFLR Register Bit Definition
  */
#define  I2C_RXFLR_CNT_Pos                        (0)
#define  I2C_RXFLR_CNT_Msk                        (0x3U << I2C_RXFLR_CNT_Pos) /*!<Contains the number of valid data entries in the receive FIFO (0~2)*/
#define  I2C_RXFLR_CNT                            I2C_RXFLR_CNT_Msk
#define  I2C_RXFLR_CNT_0                          (0x1U << I2C_RXFLR_CNT_Pos)
#define  I2C_RXFLR_CNT_1                          (0x2U << I2C_RXFLR_CNT_Pos)

/**
  * @brief I2C_HOLD Register Bit Definition
  */
#define  I2C_HOLD_TX_HOLD_Pos                     (0)
#define  I2C_HOLD_TX_HOLD_Msk                     (0xFFFFU << I2C_HOLD_TX_HOLD_Pos) /*!<Sets the SDA hold time (after SCL goes from high to low ) in units of APB clock period, when I2C device acts as a transmitter.*/
#define  I2C_HOLD_TX_HOLD                         I2C_HOLD_TX_HOLD_Msk
#define  I2C_HOLD_TX_HOLD_0                       (0x0001U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_1                       (0x0002U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_2                       (0x0004U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_3                       (0x0008U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_4                       (0x0010U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_5                       (0x0020U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_6                       (0x0040U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_7                       (0x0080U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_8                       (0x0100U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_9                       (0x0200U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_10                      (0x0400U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_11                      (0x0800U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_12                      (0x1000U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_13                      (0x2000U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_14                      (0x4000U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_TX_HOLD_15                      (0x8000U << I2C_HOLD_TX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_Pos                     (16)
#define  I2C_HOLD_RX_HOLD_Msk                     (0xFFU << I2C_HOLD_RX_HOLD_Pos) /*!<Sets the internal SDA hold time (valid while SCL is high) in units of APB clock period, when I2C device acts as a receiver.*/
#define  I2C_HOLD_RX_HOLD                         I2C_HOLD_RX_HOLD_Msk
#define  I2C_HOLD_RX_HOLD_0                       (0x01U << I2C_HOLD_RX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_1                       (0x02U << I2C_HOLD_RX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_2                       (0x04U << I2C_HOLD_RX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_3                       (0x08U << I2C_HOLD_RX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_4                       (0x10U << I2C_HOLD_RX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_5                       (0x20U << I2C_HOLD_RX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_6                       (0x40U << I2C_HOLD_RX_HOLD_Pos)
#define  I2C_HOLD_RX_HOLD_7                       (0x80U << I2C_HOLD_RX_HOLD_Pos)

/**
  * @brief I2C_SETUP Register Bit Definition
  */
#define  I2C_SETUP_CNT_Pos                        (0)
#define  I2C_SETUP_CNT_Msk                        (0xFFU << I2C_SETUP_CNT_Pos) /*!<SDA setup time (min value is 2)*/
#define  I2C_SETUP_CNT                            I2C_SETUP_CNT_Msk
#define  I2C_SETUP_CNT_0                          (0x01U << I2C_SETUP_CNT_Pos)
#define  I2C_SETUP_CNT_1                          (0x02U << I2C_SETUP_CNT_Pos)
#define  I2C_SETUP_CNT_2                          (0x04U << I2C_SETUP_CNT_Pos)
#define  I2C_SETUP_CNT_3                          (0x08U << I2C_SETUP_CNT_Pos)
#define  I2C_SETUP_CNT_4                          (0x10U << I2C_SETUP_CNT_Pos)
#define  I2C_SETUP_CNT_5                          (0x20U << I2C_SETUP_CNT_Pos)
#define  I2C_SETUP_CNT_6                          (0x40U << I2C_SETUP_CNT_Pos)
#define  I2C_SETUP_CNT_7                          (0x80U << I2C_SETUP_CNT_Pos)

/**
  * @brief I2C_GCR Register Bit Definition
  */
#define  I2C_GCR_GC_Pos                           (0)
#define  I2C_GCR_GC_Msk                           (0x1U << I2C_GCR_GC_Pos) /*!<ACK General Call*/
#define  I2C_GCR_GC                               I2C_GCR_GC_Msk

/**
  * @brief I2C_SLVMASK Register Bit Definition
  */
#define  I2C_SLVMASK_MASK_Pos                     (0)
#define  I2C_SLVMASK_MASK_Msk                     (0x3FFU << I2C_SLVMASK_MASK_Pos) /*!<Slave address mask*/
#define  I2C_SLVMASK_MASK                         I2C_SLVMASK_MASK_Msk
#define  I2C_SLVMASK_MASK_0                       (0x001U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_1                       (0x002U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_2                       (0x004U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_3                       (0x008U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_4                       (0x010U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_5                       (0x020U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_6                       (0x040U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_7                       (0x080U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_8                       (0x100U << I2C_SLVMASK_MASK_Pos)
#define  I2C_SLVMASK_MASK_9                       (0x200U << I2C_SLVMASK_MASK_Pos)

/**
  * @brief I2C_SLVRCVADDR Register Bit Definition
  */
#define  I2C_SLVRCVADDR_ADDR_Pos                  (0)
#define  I2C_SLVRCVADDR_ADDR_Msk                  (0x3FFU << I2C_SLVRCVADDR_ADDR_Pos) /*!<Slave address actually received by I2C*/
#define  I2C_SLVRCVADDR_ADDR                      I2C_SLVRCVADDR_ADDR_Msk
#define  I2C_SLVRCVADDR_ADDR_0                    (0x001U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_1                    (0x002U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_2                    (0x004U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_3                    (0x008U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_4                    (0x010U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_5                    (0x020U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_6                    (0x040U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_7                    (0x080U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_8                    (0x100U << I2C_SLVRCVADDR_ADDR_Pos)
#define  I2C_SLVRCVADDR_ADDR_9                    (0x200U << I2C_SLVRCVADDR_ADDR_Pos)

#endif

