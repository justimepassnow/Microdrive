/***********************************************************************************************************************
    @file     hal_rcc.c
    @author   VV TEAM
    @brief    THIS FILE PROVIDES ALL THE RCC FIRMWARE FUNCTIONS.
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
#include "hal_rcc.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Private_Defines
  * @{
  */
static __I uint8_t AHBPreTable[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9
};
static __I uint8_t APBPreTable[] =
{
    0, 0, 0, 0, 1, 2, 3, 4
};

/**
  * @}
  */

/** @defgroup RCC_Private_Functions
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to default state.
  * @param  None.
  * @retval None.
  */
void RCC_DeInit(void)
{
     /* Set HSION bit */
    RCC->CR |= (0x01U << RCC_CR_HSION_Pos);

     /* Reset SW, HPRE, PPRE1 and MCO bits */
    RCC->CFGR &= ~RCC_CFGR_SW_Msk;
    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
    RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
    RCC->CFGR &= ~RCC_CFGR_MCO_Msk;
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the following values:
  * @arg    RCC_FLAG_HSIRDY: HSI oscillator clock ready
  * @arg    RCC_FLAG_LSIRDY: LSI oscillator clock ready
  * @arg    RCC_FLAG_PINRST: Pin reset
  * @arg    RCC_FLAG_PORRST: POR/PDR reset
  * @arg    RCC_FLAG_SFTRST: Software reset
  * @arg    RCC_FLAG_IWDGRST: Independent Watchdog reset
  * @retval The new state of flag (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t flag)
{
    uint32_t tmp = 0;
    uint32_t statusreg = 0;

    tmp = flag >> 5;

    if (tmp == 1)                      /* The flag to check is in CR register */
    {
        statusreg = RCC->CR;
    }
    else                               /* The flag to check is in CSR register */
    {
        statusreg = RCC->CSR;
    }

     /* Get the flag position */
    tmp = flag & 0x1F;

     /* Return the flag status */
    return ((statusreg & ((uint32_t)1 << tmp)) ? SET : RESET);
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @param  state: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void RCC_HSICmd(FunctionalState state)
{
    (state) ?                                  \
    (RCC->CR |= (0x01U << RCC_CR_HSION_Pos)) : \
    (RCC->CR &= ~(0x01U << RCC_CR_HSION_Pos));
}

/**
  * @brief  Configures the system clock (SYSCLK).
  * @param  sys_clk_source: specifies the clock source used as system
  *         clock. This parameter can be one of the following values:
  * @arg    RCC_SYSCLKSource_HSI_Div6 : specifies HSI Div6  as system clock
  * @arg    RCC_SYSCLKSource_HSE      : specifies HSE as system clock
  * @arg    RCC_SYSCLKSource_HSI      : specifies HSI as system clock
  * @arg    RCC_SYSCLKSource_LSI      : specifies LSI as system clock
  * @retval None.
  */
void RCC_SYSCLKConfig(uint32_t sys_clk_source)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, sys_clk_source);
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None.
  * @retval The clock source used as system clock. The returned value can
  *         be one of the following:
  *         - 0x00: HSI used as system clock
  *         - 0x0C: LSI used as system clock
  */
uint8_t RCC_GetSYSCLKSource(void)
{
    return (RCC->CFGR & RCC_CFGR_SWS_Msk);
}

/**
  * @brief  Configures the AHB clock (hclk).
  * @param  clk: defines the AHB clock divider. This clock is derived
  *                    from the system clock (SYSCLK).
  *         This parameter can be one of the following values:
  * @arg    RCC_SYSCLK_Div1:   AHB clock = SYSCLK
  * @arg    RCC_SYSCLK_Div2:   AHB clock = SYSCLK/2
  * @arg    RCC_SYSCLK_Div4:   AHB clock = SYSCLK/4
  * @arg    RCC_SYSCLK_Div8:   AHB clock = SYSCLK/8
  * @arg    RCC_SYSCLK_Div16:  AHB clock = SYSCLK/16
  * @arg    RCC_SYSCLK_Div64:  AHB clock = SYSCLK/64
  * @arg    RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  * @arg    RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  * @arg    RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None.
  */
void RCC_HCLKConfig(uint32_t clk)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE_Msk, clk);
}

/**
  * @brief  Configures the Low Speed APB clock (pclk1).
  * @param  clk: defines the APB1 clock divider. This clock is derived from
  *                  the AHB clock (hclk).
  *         This parameter can be one of the following values:
  * @arg    RCC_HCLK_Div1:  APB1 clock = hclk
  * @arg    RCC_HCLK_Div2:  APB1 clock = hclk/2
  * @arg    RCC_HCLK_Div4:  APB1 clock = hclk/4
  * @arg    RCC_HCLK_Div8:  APB1 clock = hclk/8
  * @arg    RCC_HCLK_Div16: APB1 clock = hclk/16
  * @retval None.
  */
void RCC_PCLK1Config(uint32_t clk)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1_Msk, clk << RCC_CFGR_PPRE1_Pos);
}

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @param  it: specifies the RCC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  * @arg RCC_IT_LSIRDY: LSI ready interrupt
  * @arg RCC_IT_HSIRDY: HSI ready interrupt
  * @arg RCC_IT_HSERDY: HSE ready interrupt
  * @param  state: new state of the specified RCC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void RCC_ITConfig(uint8_t it, FunctionalState state)
{
    (state) ?                                    \
    (RCC->CIR |= (it << RCC_CIR_LSIRDYIE_Pos)) : \
    (RCC->CIR &= ~(it << RCC_CIR_LSIRDYIE_Pos));
}

/**
  * @brief  Checks whether the specified RCC interrupt has occurred or not.
  * @param  it: specifies the RCC interrupt source to check.
  *   This parameter can be one of the following values:
  * @arg RCC_IT_LSIRDY: LSI ready interrupt
  * @arg RCC_IT_HSIRDY: HSI ready interrupt
  * @arg RCC_IT_HSIRDY: HSE ready interrupt
  * @retval The new state of it (SET or RESET).
  */
ITStatus RCC_GetITStatus(uint8_t it)
{
    return ((ITStatus)(RCC->CIR & (it << RCC_CIR_LSIRDYF_Pos)));
}

/**
  * @brief  Clears the RCC interrupt pending bits.
  * @param  it: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  * @arg RCC_IT_LSIRDY: LSI ready interrupt
  * @arg RCC_IT_HSIRDY: HSI ready interrupt
  * @retval None.
  */
void RCC_ClearITPendingBit(uint8_t it)
{
    RCC->CIR |= (it << RCC_CIR_LSIRDYC_Pos);
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  *         LSI can not be disabled if the IWDG is running.
  * @param  state: new state of the LSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void RCC_LSICmd(FunctionalState state)
{
    (state) ?                                    \
    (RCC->CSR |= (0x01U << RCC_CSR_LSION_Pos)) : \
    (RCC->CSR &= ~(0x01U << RCC_CSR_LSION_Pos));
}

/**
  * @brief  Returns the frequency of different on chip clocks.
  * @param  clk: pointer to a RCC_ClocksTypeDef structure which
  *   will hold the clocks frequency.
  * @retval None.
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef *clk)
{
    uint32_t tmp     = 0;
    uint8_t  divider = 0;

     /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFGR & RCC_CFGR_SWS_Msk;

    switch (tmp)
    {
        case 0x00:                     /* HSI DIV6 used as system clock */
            clk->SYSCLK_Frequency = HSI_48MHz_DIV6;
            break;

        case 0x04:                     /* HSE used as system clock */
            clk->SYSCLK_Frequency = HSE_VALUE;
            break;

        case 0x08:                     /* HSI used as system clock */
            clk->SYSCLK_Frequency = HSI_48MHz;
            break;

        case 0x0C:                     /* LSI used as system clock */
            clk->SYSCLK_Frequency = LSI_VALUE;
            break;

        default:
            clk->SYSCLK_Frequency = HSI_48MHz_DIV6;
            break;
    }

    /* Compute HCLK, PCLK1 clocks frequencies ----------------*/

     /* Get HCLK prescaler */
    tmp     = (RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos;
    divider = AHBPreTable[tmp];
     /* HCLK clock frequency */
    clk->HCLK_Frequency = clk->SYSCLK_Frequency >> divider;

     /* Get PCLK1 prescaler */
    tmp     = (RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos;
    divider = APBPreTable[tmp];
     /* PCLK1 clock frequency */
    clk->PCLK1_Frequency = clk->HCLK_Frequency >> divider;
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @param  ahb_periph: specifies the AHB peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *   @arg  RCC_AHBPERIPH_SRAM
  *   @arg  RCC_AHBPERIPH_FLASH
  *   @arg  RCC_AHBPERIPH_CRC
  *   @arg  RCC_AHBPERIPH_GPIOA
  *   @arg  RCC_AHBPERIPH_GPIOB
  * @param  state: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void RCC_AHBPeriphClockCmd(uint32_t ahb_periph, FunctionalState state)
{
    (state) ?                     \
    (RCC->AHBENR |= ahb_periph) : \
    (RCC->AHBENR &= ~ahb_periph);
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @param  apb1_periph: specifies the APB1 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *   @arg  RCC_APB1PERIPH_TIM3
  *   @arg  RCC_APB1PERIPH_TIM1
  *   @arg  RCC_APB1PERIPH_TIM14
  *   @arg  RCC_APB1PERIPH_ADC1
  *   @arg  RCC_APB1PERIPH_SPI1
  *   @arg  RCC_APB1PERIPH_USART1
  *   @arg  RCC_APB1PERIPH_USART2
  *   @arg  RCC_APB1PERIPH_I2C1
  *   @arg  RCC_APB1PERIPH_PWR
  *   @arg  RCC_APB1PERIPH_DBG
  *   @arg  RCC_APB1PERIPH_SYSCFG
  * @param  state: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void RCC_APB1PeriphClockCmd(uint32_t apb1_periph, FunctionalState state)
{
    (state) ?                       \
    (RCC->APB1ENR |= apb1_periph) : \
    (RCC->APB1ENR &= ~apb1_periph);
}

/**
  * @brief  Forces or releases the AHB peripheral  peripheral reset.
  * @param  ahb_periph: specifies the AHB peripheral
  *   This parameter can be any combination of the following values:
  *   @arg  RCC_AHBPERIPH_GPIOA
  *   @arg  RCC_AHBPERIPH_GPIOB
  * @param  state: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void RCC_AHBPeriphResetCmd(uint32_t ahb_periph, FunctionalState state)
{
    (state) ?                      \
    (RCC->AHBRSTR |= ahb_periph) : \
    (RCC->AHBRSTR &= ~ahb_periph);
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  apb1_periph: specifies the APB1 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *   @arg  RCC_APB1PERIPH_TIM3
  *   @arg  RCC_APB1PERIPH_TIM1
  *   @arg  RCC_APB1PERIPH_TIM14
  *   @arg  RCC_APB1PERIPH_ADC1
  *   @arg  RCC_APB1PERIPH_SPI1
  *   @arg  RCC_APB1PERIPH_USART1
  *   @arg  RCC_APB1PERIPH_USART2
  *   @arg  RCC_APB1PERIPH_I2C1
  *   @arg  RCC_APB1PERIPH_PWR
  *   @arg  RCC_APB1PERIPH_DBG
  *   @arg  RCC_APB1PERIPH_SYSCFG
  * @param  state: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void RCC_APB1PeriphResetCmd(uint32_t apb1_periph, FunctionalState state)
{
    (state) ?                        \
    (RCC->APB1RSTR |= apb1_periph) : \
    (RCC->APB1RSTR &= ~apb1_periph);
}

/**
  * @brief  Selects the clock source to output on MCO pin.
  * @param  mco_src: specifies the clock source to output.
  *   This parameter can be one of the following values:
  * @arg RCC_MCO_NoClock
  * @arg RCC_MCO_LSI
  * @arg RCC_MCO_SYSCLK
  * @arg RCC_MCO_HSI_Div4
  * @arg RCC_MCO_HSE
  * @retval None.
  */
void RCC_MCOConfig(uint32_t mco_src)
{
    MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO_Msk, mco_src);
}

/**
  * @brief  Clears the RCC reset flags.
  * @param  None.
  * @retval None.
  */
void RCC_ClearFlag(void)
{
    RCC->CSR |= (1 << RCC_CSR_RMVF_Pos);
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

