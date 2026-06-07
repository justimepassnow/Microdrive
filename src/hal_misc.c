/***********************************************************************************************************************
    @file     hal_misc.c
    @author   VV TEAM
    @brief    THIS FILE PROVIDES ALL THE MSIC FIRMWARE FUNCTIONS.
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

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "hal_misc.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @addtogroup NVIC
  * @{
  */

/** @defgroup NVIC_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup NVIC_Private_Functions
  * @{
  */

/**
  * @brief  NVIC initialization.
  * @param  init_struct
  * @retval None.
  */
void NVIC_Init(NVIC_InitTypeDef *init_struct)
{
    if (init_struct->NVIC_IRQChannelCmd != DISABLE)
    {
        NVIC->IP[init_struct->NVIC_IRQChannel >> 0x02] =
            (NVIC->IP[init_struct->NVIC_IRQChannel >> 0x02] &
             (~(((uint32_t)0xFF) << ((init_struct->NVIC_IRQChannel & 0x03) * 8)))) |
            ((((uint32_t)init_struct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((init_struct->NVIC_IRQChannel & 0x03) * 8));

        NVIC->ISER[0] = 0x01 << (init_struct->NVIC_IRQChannel & 0x1F);
    }
    else
    {
        NVIC->ICER[0] = 0x01 << (init_struct->NVIC_IRQChannel & 0x1F);
    }
}

/**
  * @brief  SysTick clock source configuration.
  * @param  systick_clk_source
  *         This parameter can be any combination of the following values:
  *    @arg SYSTICK_CLKSOURCE_EXTCLK
  *    @arg SYSTICK_CLKSOURCE_HCLK
  * @retval None.
  */
void SysTick_CLKSourceConfig(uint32_t systick_clk_source)
{
    (systick_clk_source == SysTick_CLKSource_HCLK) ? \
    (SysTick->CTRL |= SysTick_CLKSource_HCLK) :      \
    (SysTick->CTRL &= ~SysTick_CLKSource_HCLK);
}

/**
  * @brief  System low power mode configuration.
  * @param  low_power_mode
  *         This parameter can be any combination of the following values:
  *    @arg NVIC_LP_SEVONPEND
  *    @arg NVIC_LP_SLEEPDEEP
  *    @arg NVIC_LP_SLEEPONEXIT
  * @param  state: new state of the low power mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void NVIC_SystemLPConfig(uint8_t low_power_mode, FunctionalState state)
{
    (state) ?                      \
    (SCB->SCR |= low_power_mode) : \
    (SCB->SCR &= ~(uint32_t)low_power_mode);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

