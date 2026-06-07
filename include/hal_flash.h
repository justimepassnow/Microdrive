/***********************************************************************************************************************
    @file     hal_flash.h
    @author   VV TEAM
    @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE FLASH FIRMWARE LIBRARY.
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
#ifndef __HAL_FLASH_H
#define __HAL_FLASH_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH
  * @{
  */

/** @defgroup FLASH_Exported_Types
  * @{
  */

/**
  * @brief  FLASH Status
  */
typedef enum
{
    FLASH_BUSY = 1,                    /*!< FLASH busy status */
    FLASH_ERROR_PG,                    /*!< FLASH programming error status */
    FLASH_ERROR_WRP,                   /*!< FLASH write protection error status */
    FLASH_COMPLETE,                    /*!< FLASH end of operation status */
    FLASH_TIMEOUT                      /*!< FLASH Last operation timed out status */
} FLASH_Status;
/**
  * @}
  */

/** @defgroup FLASH_Exported_Constants
  * @{
  */

#define FLASH_START_ADDR                 (0x08000000U)                    /*!< FLASH base address in the alias region */
#define OB_BASE                          (0x1FFFF800U)                    /*!< Flash Option Bytes base address */

/**
  * @brief  FLASH Latency
  */
#define FLASH_Latency_0                  (0x00U << FLASH_ACR_LATENCY_Pos) /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                  (0x01U << FLASH_ACR_LATENCY_Pos) /*!< FLASH One Latency cycle */

/**
  * @brief  Prefetch_Buffer_Enable_Disable
  */
#define FLASH_Prefetch_Buffer_Enable     (0x01U << FLASH_ACR_PRFTBE_Pos)  /*!< FLASH Prefetch Buffer Enable */
#define FLASH_Prefetch_Buffer_Disable    (0x00U << FLASH_ACR_PRFTBE_Pos)  /*!< FLASH Prefetch Buffer Disable */

/**
  * @brief  Option_Bytes_IWatchdog
  */
#define OB_IWDG_SW                       0x0001                           /*!< Software IWDG selected */
#define OB_IWDG_HW                       0x0000                           /*!< Hardware IWDG selected */

/**
  * @brief  Option_Bytes_nRST_STOP
  */
#define OB_STOP_NORST                    0x0002                           /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                      0x0000                           /*!< Reset generated when entering in STOP */

/**
  * @brief  Option_Bytes_nRST_STDBY
  */
#define OB_STDBY_NORST                   0x0004                           /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                     0x0000                           /*!< Reset generated when entering in STANDBY */

/**
  * @brief  FLASH_Flags
  */
#define FLASH_FLAG_EOP                   (0x01U << FLASH_SR_EOP_Pos)      /*!< FLASH End of Operation flag */
#define FLASH_FLAG_PGERR                 (0x01U << FLASH_SR_PGERR_Pos)    /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTERR              (0x01U << FLASH_SR_WRPRTERR_Pos) /*!< FLASH Write protected error flag */
#define FLASH_FLAG_BSY                   (0x01U << FLASH_SR_BSY_Pos)      /*!< FLASH Busy flag */
#define FLASH_FLAG_OPTERR                (0x01U << FLASH_OBR_OPTERR_Pos)  /*!< FLASH Option Byte error flag */

#define FLASH_KEY1                       ((uint32_t)0x45670123)
#define FLASH_KEY2                       ((uint32_t)0xCDEF89AB)
#define FLASH_Erase_Timeout              ((uint32_t)0x00002FFF) /*!< new Flash page/sector erase request 6ms, Mass erase 40ms */
#define FLASH_Program_Timeout            ((uint32_t)0x0000012F) /*!< new Flash half word program request 155us */

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions
  * @{
  */
void FLASH_SetLatency(uint32_t latency);
void FLASH_PrefetchBufferCmd(uint32_t prefetch_buffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_OPTB_Enable(void);
FLASH_Status FLASH_ErasePage(uint32_t page_address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramHalfWord(uint32_t address, uint16_t data);
FLASH_Status FLASH_ProgramWord(uint32_t address, uint32_t data);
FLASH_Status FLASH_ProgramOptionHalfWord(uint32_t address, uint16_t data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t address, uint8_t data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t page);
FLASH_Status FLASH_UserOptionByteConfig(uint32_t ob_iwdg, uint32_t ob_stop, uint32_t ob_standby);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t time_out);
void FLASH_ClearFlag(uint16_t flag);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);

FlagStatus FLASH_GetFlagStatus(uint16_t flag);
FLASH_Status FLASH_EraseDataAreaPage(uint32_t page_address);
FLASH_Status FLASH_ProgramDataAreaHalfWord(uint32_t address, uint16_t data);
void FLASH_OPTB_Disable(void);

#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

