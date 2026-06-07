/***********************************************************************************************************************
    @file     hal_tim.c
    @author   VV TEAM
    @brief    THIS FILE PROVIDES ALL THE TIM FIRMWARE FUNCTIONS.
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
#include "hal_tim.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */

/** @defgroup TIM_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup TIM_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the tim peripheral registers to their default reset values.
  * @param  tim: select the TIM peripheral.
  * @retval None.
  */
void TIM_DeInit(TIM_TypeDef *tim)
{
    if (tim == TIM1)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TIM1, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TIM1, DISABLE);
    }
    else if (tim == TIM3)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TIM3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TIM3, DISABLE);
    }
    else if (tim == TIM14)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TIM14, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TIM14, DISABLE);
    }
}

/**
  * @brief  Fills each init_struct member with its default value.
  * @param  init_struct : pointer to a TIM_TimeBaseInitTypeDef
  *         structure which will be initialized.
  * @retval None.
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *init_struct)
{
    init_struct->TIM_Period            = 0xFFFFFFFF;
    init_struct->TIM_Prescaler         = 0x0000;
    init_struct->TIM_ClockDivision     = TIM_CKD_Div1;
    init_struct->TIM_CounterMode       = TIM_CounterMode_Up;
    init_struct->TIM_RepetitionCounter = 0x00;
}

/**
  * @brief  Initializes the tim Time Base Unit peripheral according to
  *         the specified parameters in the init_struct.
  * @param  tim: select the TIM peripheral.
  * @param  init_struct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for the
  *         specified TIM peripheral.
  * @retval None.
  */
void TIM_TimeBaseInit(TIM_TypeDef *tim, TIM_TimeBaseInitTypeDef *init_struct)
{
    MODIFY_REG(tim->CR1, TIM_CR1_CKD_Msk, init_struct->TIM_ClockDivision);

    if ((tim == TIM1) || (tim == TIM3))
    {
        MODIFY_REG(tim->CR1, TIM_CR1_CMS_Msk | TIM_CR1_DIR_Msk, init_struct->TIM_CounterMode);
    }

    if (tim == TIM1)
    {
        MODIFY_REG(tim->RCR, TIM_RCR_REP_Msk, init_struct->TIM_RepetitionCounter);
    }

    tim->ARR = init_struct->TIM_Period;
    tim->PSC = init_struct->TIM_Prescaler;

    tim->EGR = TIM_PSCReloadMode_Immediate;
}

/**
  * @brief  Fills each init_struct member with its default value.
  * @param  init_struct : pointer to a TIM_OCInitTypeDef structure which will be initialized.
  * @retval None.
  */
void TIM_OCStructInit(TIM_OCInitTypeDef *init_struct)
{
    init_struct->TIM_OCMode       = TIM_OCMode_Timing;
    init_struct->TIM_OutputState  = TIM_OutputState_Disable;
    init_struct->TIM_OutputNState = TIM_OutputNState_Disable;
    init_struct->TIM_Pulse        = 0x00000000;
    init_struct->TIM_OCPolarity   = TIM_OCPolarity_High;
    init_struct->TIM_OCNPolarity  = TIM_OCNPolarity_High;
    init_struct->TIM_OCIdleState  = TIM_OCIdleState_Reset;
    init_struct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
  * @brief  Initializes the tim Channel1 according to the specified
  *         parameters in the init_struct.
  * @param  tim:  select the TIM peripheral.
  * @param  init_struct: pointer to a TIM_OCInitTypeDef structure that
  *         contains the configuration information for the specified TIM peripheral.
  * @retval None.
  */
void TIM_OC1Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC1M_Msk, init_struct->TIM_OCMode << TIM_CCMR1_OC1M_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC1E_Msk, init_struct->TIM_OutputState << TIM_CCER_CC1E_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC1P_Msk, init_struct->TIM_OCPolarity << TIM_CCER_CC1P_Pos);

    tim->CCR1 = init_struct->TIM_Pulse;

    if (tim == TIM1)
    {
        MODIFY_REG(tim->CCER, TIM_CCER_CC1NE_Msk, init_struct->TIM_OutputNState << TIM_CCER_CC1NE_Pos);
        MODIFY_REG(tim->CCER, TIM_CCER_CC1NP_Msk, init_struct->TIM_OCNPolarity << TIM_CCER_CC1NP_Pos);

        MODIFY_REG(tim->CR2, TIM_CR2_OIS1_Msk, init_struct->TIM_OCIdleState << TIM_CR2_OIS1_Pos);
        MODIFY_REG(tim->CR2, TIM_CR2_OIS1N_Msk, init_struct->TIM_OCNIdleState << TIM_CR2_OIS1N_Pos);
    }
}

/**
  * @brief  Initializes the tim Channel2 according to the specified
  *         parameters in the init_struct.
  * @param  tim: select the TIM peripheral.
  * @param  init_struct: pointer to a TIM_OCInitTypeDef structure that
  *         contains the configuration information for the specified TIM peripheral.
  * @retval None.
  */
void TIM_OC2Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC2M_Msk, init_struct->TIM_OCMode << TIM_CCMR1_OC2M_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC2E_Msk, init_struct->TIM_OutputState << TIM_CCER_CC2E_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC2P_Msk, init_struct->TIM_OCPolarity << TIM_CCER_CC2P_Pos);

    tim->CCR2 = init_struct->TIM_Pulse;

    if (tim == TIM1)
    {
        MODIFY_REG(tim->CCER, TIM_CCER_CC2NE_Msk, init_struct->TIM_OutputNState << TIM_CCER_CC2NE_Pos);
        MODIFY_REG(tim->CCER, TIM_CCER_CC2NP_Msk, init_struct->TIM_OCNPolarity << TIM_CCER_CC2NP_Pos);

        MODIFY_REG(tim->CR2, TIM_CR2_OIS2_Msk, init_struct->TIM_OCIdleState << TIM_CR2_OIS2_Pos);
        MODIFY_REG(tim->CR2, TIM_CR2_OIS2N_Msk, init_struct->TIM_OCNIdleState << TIM_CR2_OIS2N_Pos);
    }
}

/**
  * @brief  Initializes the tim Channel3 according to the specified
  *         parameters in the init_struct.
  * @param  tim: select the TIM peripheral.
  * @param  init_struct: pointer to a TIM_OCInitTypeDef structure that
  *         contains the configuration information for the specified TIM peripheral.
  * @retval None.
  */
void TIM_OC3Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC3M_Msk, init_struct->TIM_OCMode << TIM_CCMR2_OC3M_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC3E_Msk, init_struct->TIM_OutputState << TIM_CCER_CC3E_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC3P_Msk, init_struct->TIM_OCPolarity << TIM_CCER_CC3P_Pos);

    tim->CCR3 = init_struct->TIM_Pulse;

    if (tim == TIM1)
    {
        MODIFY_REG(tim->CCER, TIM_CCER_CC3NE_Msk, init_struct->TIM_OutputNState << TIM_CCER_CC3NE_Pos);
        MODIFY_REG(tim->CCER, TIM_CCER_CC3NP_Msk, init_struct->TIM_OCNPolarity << TIM_CCER_CC3NP_Pos);

        MODIFY_REG(tim->CR2, TIM_CR2_OIS3_Msk, init_struct->TIM_OCIdleState << TIM_CR2_OIS3_Pos);
        MODIFY_REG(tim->CR2, TIM_CR2_OIS3N_Msk, init_struct->TIM_OCNIdleState << TIM_CR2_OIS3N_Pos);
    }
}

/**
  * @brief  Initializes the tim Channel4 according to the specified
  *         parameters in the init_struct.
  * @param  tim:select the TIM peripheral.
  * @param  init_struct: pointer to a TIM_OCInitTypeDef structure that
  *         contains the configuration information for the specified TIM peripheral.
  * @retval None.
  */
void TIM_OC4Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC4M_Msk, init_struct->TIM_OCMode << TIM_CCMR2_OC4M_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC4E_Msk, init_struct->TIM_OutputState << TIM_CCER_CC4E_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC4P_Msk, init_struct->TIM_OCPolarity << TIM_CCER_CC4P_Pos);

    tim->CCR4 = init_struct->TIM_Pulse;

    if (tim == TIM1)
    {
        MODIFY_REG(tim->CCER, TIM_CCER_CC4NP_Msk, init_struct->TIM_OCNPolarity << TIM_CCER_CC4NP_Pos);

        MODIFY_REG(tim->CR2, TIM_CR2_OIS4_Msk, init_struct->TIM_OCIdleState << TIM_CR2_OIS4_Pos);
    }
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  tim:  select the TIM peripheral.
  * @param  polarity : The Input Polarity.
  *     @arg TIM_ICPolarity_Rising  
  *     @arg TIM_ICPolarity_Falling 
  *     @arg TIM_ICPolarity_BothEdge
  * @param  selection: specifies the input to be used.
  *     @arg TIM_ICSelection_DirectTI: TIM Input 1 is selected to be connected to IC1.
  *     @arg TIM_ICSelection_IndirectTI: TIM Input 1 is selected to be connected to IC2.
  *     @arg TIM_ICSelection_TRC: TIM Input 1 is selected to be connected to TRC.
  * @param  filter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None.
  */
static void TI1_Configure(TIM_TypeDef *tim, uint16_t polarity, uint16_t selection, uint16_t filter)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_CC1S_Msk, selection << TIM_CCMR1_CC1S_Pos);
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_IC1F_Msk, filter << TIM_CCMR1_IC1F_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC1E_Msk | TIM_CCER_CC1P_Msk | TIM_CCER_CC1NP_Msk, polarity | TIM_CCER_CC1E_Msk);
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  tim: select the TIM peripheral.
  * @param  polarity : The Input Polarity.
  *     @arg TIM_ICPolarity_Rising  
  *     @arg TIM_ICPolarity_Falling 
  *     @arg TIM_ICPolarity_BothEdge
  * @param  selection: specifies the input to be used.
  *     @arg TIM_ICSelection_DirectTI: TIM Input 2 is selected to be connected to IC2.
  *     @arg TIM_ICSelection_IndirectTI: TIM Input 2 is selected to be connected to IC1.
  *     @arg TIM_ICSelection_TRC: TIM Input 2 is selected to be connected to TRC.
  * @param  filter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None.
  */
static void TI2_Configure(TIM_TypeDef *tim, uint16_t polarity, uint16_t selection, uint16_t filter)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_CC2S_Msk, selection << TIM_CCMR1_CC2S_Pos);
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_IC2F_Msk, filter << TIM_CCMR1_IC2F_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC2E_Msk | TIM_CCER_CC2P_Msk | TIM_CCER_CC2NP_Msk, (polarity << 4) | TIM_CCER_CC2E_Msk);
}

/**
  * @brief  Configure the TI3 as Input.
  * @param  tim: select the TIM peripheral.
  * @param  polarity : The Input Polarity.
  *     @arg TIM_ICPolarity_Rising  
  *     @arg TIM_ICPolarity_Falling 
  *     @arg TIM_ICPolarity_BothEdge
  * @param  selection: specifies the input to be used.
  *     @arg TIM_ICSelection_DirectTI: TIM Input 3 is selected to be connected to IC3.
  *     @arg TIM_ICSelection_IndirectTI: TIM Input 3 is selected to be connected to IC4.
  *     @arg TIM_ICSelection_TRC: TIM Input 3 is selected to be connected to TRC.
  * @param  filter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None.
  */
static void TI3_Configure(TIM_TypeDef *tim, uint16_t polarity, uint16_t selection, uint16_t filter)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_CC3S_Msk, selection << TIM_CCMR2_CC3S_Pos);
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_IC3F_Msk, filter << TIM_CCMR2_IC3F_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC3E_Msk | TIM_CCER_CC3P_Msk | TIM_CCER_CC3NP_Msk, (polarity << 8) | TIM_CCER_CC3E_Msk);
}

/**
  * @brief  Configure the TI4 as Input.
  * @param  tim: select the TIM peripheral.
  * @param  polarity : The Input Polarity.
  *     @arg TIM_ICPolarity_Rising  
  *     @arg TIM_ICPolarity_Falling 
  *     @arg TIM_ICPolarity_BothEdge
  * @param  selection: specifies the input to be used.
  *     @arg TIM_ICSelection_DirectTI: TIM Input 4 is selected to be connected to IC4.
  *     @arg TIM_ICSelection_IndirectTI: TIM Input 4 is selected to be connected to IC3.
  *     @arg TIM_ICSelection_TRC: TIM Input 4 is selected to be connected to TRC.
  * @param  filter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None.
  */
static void TI4_Configure(TIM_TypeDef *tim, uint16_t polarity, uint16_t selection, uint16_t filter)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_CC4S_Msk, selection << TIM_CCMR2_CC4S_Pos);
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_IC4F_Msk, filter << TIM_CCMR2_IC4F_Pos);
    MODIFY_REG(tim->CCER, TIM_CCER_CC4E_Msk | TIM_CCER_CC4P_Msk | TIM_CCER_CC4NP_Msk, (polarity << 12) | TIM_CCER_CC4E_Msk);
}

/**
  * @brief  Sets the tim Input Capture 1 prescaler.
  * @param  tim:  select the TIM peripheral.
  * @param  psc: specifies the Input Capture1 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPSC_Div1: no prescaler
  *     @arg TIM_ICPSC_Div2: capture is done once every 2 events
  *     @arg TIM_ICPSC_Div4: capture is done once every 4 events
  *     @arg TIM_ICPSC_Div8: capture is done once every 8 events
  * @retval None.
  */
void TIM_SetIC1Prescaler(TIM_TypeDef *tim, uint32_t psc)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_IC1PSC_Msk, psc);
}

/**
  * @brief  Sets the tim Input Capture 2 prescaler.
  * @param  tim: select the TIM peripheral.
  * @param  psc: specifies the Input Capture2 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPSC_Div1: no prescaler
  *     @arg TIM_ICPSC_Div2: capture is done once every 2 events
  *     @arg TIM_ICPSC_Div4: capture is done once every 4 events
  *     @arg TIM_ICPSC_Div8: capture is done once every 8 events
  * @retval None.
  */
void TIM_SetIC2Prescaler(TIM_TypeDef *tim, uint32_t psc)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_IC2PSC_Msk, psc << 8);
}

/**
  * @brief  Sets the tim Input Capture 3 prescaler.
  * @param  tim: select the TIM peripheral.
  * @param  psc: specifies the Input Capture3 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPSC_Div1: no prescaler
  *     @arg TIM_ICPSC_Div2: capture is done once every 2 events
  *     @arg TIM_ICPSC_Div4: capture is done once every 4 events
  *     @arg TIM_ICPSC_Div8: capture is done once every 8 events
  * @retval None.
  */
void TIM_SetIC3Prescaler(TIM_TypeDef *tim, uint32_t psc)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_IC3PSC_Msk, psc);
}

/**
  * @brief  Sets the tim Input Capture 4 prescaler.
  * @param  tim: select the TIM peripheral.
  * @param  psc: specifies the Input Capture4 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPSC_Div1: no prescaler
  *     @arg TIM_ICPSC_Div2: capture is done once every 2 events
  *     @arg TIM_ICPSC_Div4: capture is done once every 4 events
  *     @arg TIM_ICPSC_Div8: capture is done once every 8 events
  * @retval None.
  */
void TIM_SetIC4Prescaler(TIM_TypeDef *tim, uint32_t psc)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_IC4PSC_Msk, psc << 8);
}

/**
  * @brief  Fills each init_struct member with its default value.
  * @param  init_struct: pointer to a TIM_ICInitTypeDef structure which will
  *         be initialized.
  * @retval None.
  */
void TIM_ICStructInit(TIM_ICInitTypeDef *init_struct)
{
    init_struct->TIM_Channel     = TIM_Channel_1;
    init_struct->TIM_ICPolarity  = TIM_ICPolarity_Rising;
    init_struct->TIM_ICSelection = TIM_ICSelection_DirectTI;
    init_struct->TIM_ICPrescaler = TIM_ICPSC_Div1;
    init_struct->TIM_ICFilter    = 0x00;
}

/**
  * @brief  Initializes the TIM peripheral according to the specified
  *         parameters in the init_struct.
  * @param  tim:  select the TIM peripheral.
  * @param  init_struct: pointer to a TIM_ICInitTypeDef structure that
  *         contains the configuration information for the specified TIM peripheral.
  * @retval None.
  */
void TIM_ICInit(TIM_TypeDef *tim, TIM_ICInitTypeDef *init_struct)
{
    switch (init_struct->TIM_Channel)
    {
        case TIM_Channel_1:
            TI1_Configure(tim, init_struct->TIM_ICPolarity, init_struct->TIM_ICSelection, init_struct->TIM_ICFilter);
            TIM_SetIC1Prescaler(tim, init_struct->TIM_ICPrescaler);
            break;

        case TIM_Channel_2:
            TI2_Configure(tim, init_struct->TIM_ICPolarity, init_struct->TIM_ICSelection, init_struct->TIM_ICFilter);
            TIM_SetIC2Prescaler(tim, init_struct->TIM_ICPrescaler);
            break;

        case TIM_Channel_3:
            TI3_Configure(tim, init_struct->TIM_ICPolarity, init_struct->TIM_ICSelection, init_struct->TIM_ICFilter);
            TIM_SetIC3Prescaler(tim, init_struct->TIM_ICPrescaler);
            break;

        case TIM_Channel_4:
            TI4_Configure(tim, init_struct->TIM_ICPolarity, init_struct->TIM_ICSelection, init_struct->TIM_ICFilter);
            TIM_SetIC4Prescaler(tim, init_struct->TIM_ICPrescaler);
            break;

        default:
            break;
    }
}

/**
  * @brief  Configures the TIM peripheral according to the specified
  *         parameters in the init_struct to measure an external PWM signal.
  * @param  tim: select the TIM peripheral.
  * @param  init_struct: pointer to a TIM_ICInitTypeDef structure that
  *         contains the configuration information for the specified TIM peripheral.
  * @retval None.
  */
void TIM_PWMIConfig(TIM_TypeDef *tim, TIM_ICInitTypeDef *init_struct)
{
    uint16_t icoppositepolarity  = TIM_ICPolarity_Rising;
    uint16_t icoppositeselection = TIM_ICSelection_DirectTI;

    icoppositepolarity  = (init_struct->TIM_ICPolarity == TIM_ICPolarity_Rising) ? TIM_ICPolarity_Falling : TIM_ICPolarity_Rising;
    icoppositeselection = (init_struct->TIM_ICSelection == TIM_ICSelection_DirectTI) ? TIM_ICSelection_IndirectTI : TIM_ICSelection_DirectTI;

    if (init_struct->TIM_Channel == TIM_Channel_1)
    {
        TI1_Configure(tim, init_struct->TIM_ICPolarity, init_struct->TIM_ICSelection, init_struct->TIM_ICFilter);
        TIM_SetIC1Prescaler(tim, init_struct->TIM_ICPrescaler);
        TI2_Configure(tim, icoppositepolarity, icoppositeselection, init_struct->TIM_ICFilter);
        TIM_SetIC2Prescaler(tim, init_struct->TIM_ICPrescaler);
    }
    else
    {
        TI2_Configure(tim, init_struct->TIM_ICPolarity, init_struct->TIM_ICSelection, init_struct->TIM_ICFilter);
        TIM_SetIC2Prescaler(tim, init_struct->TIM_ICPrescaler);
        TI1_Configure(tim, icoppositepolarity, icoppositeselection, init_struct->TIM_ICFilter);
        TIM_SetIC1Prescaler(tim, init_struct->TIM_ICPrescaler);
    }
}

/**
  * @brief  Fills each init_struct member with its default value.
  * @param  init_struct: pointer to a TIM_BDTRInitTypeDef structure which will be initialized.
  * @retval None.
  */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *init_struct)
{
    init_struct->TIM_OSSRState       = TIM_OSSRState_Disable;
    init_struct->TIM_OSSIState       = TIM_OSSIState_Disable;
    init_struct->TIM_LOCKLevel       = TIM_LockLevel_OFF;
    init_struct->TIM_DeadTime        = 0x00;
    init_struct->TIM_Break           = TIM_Break_Disable;
    init_struct->TIM_BreakPolarity   = TIM_BreakPolarity_Low;
    init_struct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/**
  * @brief  Configures the: Break feature, dead time, Lock level, the OSSI,
  *         the OSSR State and the AOE(automatic output enable).
  * @param  tim: select the TIM
  * @param  init_struct: pointer to a TIM_BDTRInitTypeDef structure that
  *         contains the BDTR Register configuration  information for the TIM peripheral.
  * @retval None.
  */
void TIM_BDTRConfig(TIM_TypeDef *tim, TIM_BDTRInitTypeDef *init_struct)
{
    tim->BDTR = (uint32_t)init_struct->TIM_OSSRState | init_struct->TIM_OSSIState | init_struct->TIM_LOCKLevel |
                init_struct->TIM_DeadTime | init_struct->TIM_Break | init_struct->TIM_BreakPolarity |
                init_struct->TIM_AutomaticOutput;
}

/**
  * @brief  Enables or disables the specified TIM peripheral.
  * @param  tim: select the TIM peripheral.
  * @param  state: new state of the tim peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_Cmd(TIM_TypeDef *tim, FunctionalState state)
{
    (state) ?                                  \
    (tim->CR1 |= (0x01U << TIM_CR1_CEN_Pos)) : \
    (tim->CR1 &= ~(0x01U << TIM_CR1_CEN_Pos));
}

/**
  * @brief  Enables or disables the TIM peripheral Main Outputs.
  * @param  tim: select the TIM peripheral.
  * @param  state: new state of the TIM peripheral Main Outputs.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_CtrlPWMOutputs(TIM_TypeDef *tim, FunctionalState state)
{
    (state) ?                                    \
    (tim->BDTR |= (0x01U << TIM_BDTR_MOE_Pos)) : \
    (tim->BDTR &= ~(0x01U << TIM_BDTR_MOE_Pos));
}

/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  tim:  select the tim peripheral.
  * @param  it: specifies the TIM interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_IT_Update: TIM update Interrupt source
  *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *     @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
  *     @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
  *     @arg TIM_IT_COM: TIM Commutation Interrupt source
  *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *     @arg TIM_IT_Break: TIM Break Interrupt source
  *     @arg TIM_IT_CC5
  * @param  state: new state of the TIM interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_ITConfig(TIM_TypeDef *tim, uint32_t it, FunctionalState state) // TIMIT_TypeDef
{
    (state) ?           \
    (tim->DIER |= it) : \
    (tim->DIER &= ~it);
}

/**
  * @brief  Configures the tim event to be generate by software.
  * @param  tim:  select the TIM peripheral.
  * @param  source: specifies the event source.
  *   This parameter can be one or more of the following values:
  *     @arg TIM_EventSource_Update :Timer update Event source
  *     @arg TIM_EventSource_CC1    :Timer Capture Compare 1 Event source
  *     @arg TIM_EventSource_CC2    :Timer Capture Compare 2 Event source
  *     @arg TIM_EventSource_CC3    :Timer Capture Compare 3 Event source
  *     @arg TIM_EventSource_CC4    :Timer Capture Compare 4 Event source
  *     @arg TIM_EventSource_COM    :Timer COM event source
  *     @arg TIM_EventSource_Trigger:Timer Trigger Event source
  *     @arg TIM_EventSource_Break  :Timer Break event source
  *     @arg TIM_EventSource_CC5    :Timer Capture Compare 5 Event source
  * @note
  *   - TIM_EventSource_COM and TIM_EventSource_Break are used only with partial timer.
  * @retval None.
  */
void TIM_GenerateEvent(TIM_TypeDef *tim, uint32_t source)
{
    tim->EGR = source;
}

/**
  * @brief  Configures the tim internal Clock
  * @param  tim: select the TIM peripheral.
  * @retval None.
  */
void TIM_InternalClockConfig(TIM_TypeDef *tim)
{
    tim->SMCR &= (uint16_t)(~(uint16_t)TIM_SMCR_SMS_Msk);
}

/**
  * @brief  Configures the tim Internal Trigger as External Clock
  * @param  tim: select the TIM peripheral.
  * @param  source: Trigger source.
  *   This parameter can be one of the following values:
  *     @arg TIM_TS_ITR0: Internal Trigger 0
  *     @arg TIM_TS_ITR1: Internal Trigger 1
  *     @arg TIM_TS_ITR2: Internal Trigger 2
  *     @arg TIM_TS_ITR3: Internal Trigger 3
  *     @arg TIM_TS_TI1F_ED : TI1 Edge Detector
  *     @arg TIM_TS_TI1FP1 : Filtered Timer Input
  *     @arg TIM_TS_TI2FP2 : Filtered Timer Input
  *     @arg TIM_TS_ETRF : TI1 Edge Detector
  * @retval None.
  */
void TIM_ITRxExternalClockConfig(TIM_TypeDef *tim, uint32_t source)
{
    TIM_SelectInputTrigger(tim, source);
    tim->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @brief  Selects the Input Trigger source
  * @param  tim: select the TIM peripheral.
  * @param  source: The Input Trigger source.
  *   This parameter can be one of the following values:
  *     @arg TIM_TS_ITR0: Internal Trigger 0
  *     @arg TIM_TS_ITR1: Internal Trigger 1
  *     @arg TIM_TS_ITR2: Internal Trigger 2
  *     @arg TIM_TS_ITR3: Internal Trigger 3
  *     @arg TIM_TS_TI1F_ED: TI1 Edge Detector
  *     @arg TIM_TS_TI1FP1: Filtered Timer Input 1
  *     @arg TIM_TS_TI2FP2: Filtered Timer Input 2
  *     @arg TIM_TS_ETRF: External Trigger input
  * @retval None.
  */
void TIM_SelectInputTrigger(TIM_TypeDef *tim, uint16_t source)
{
    MODIFY_REG(tim->SMCR, TIM_SMCR_TS_Msk, source);
}

/**
  * @brief  Configures the tim Prescaler.
  * @param  tim:  select the TIM peripheral.
  * @param  prescaler: specifies the Prescaler Register value
  * @param  reloadMode: specifies the TIM Prescaler Reload mode
  *     @arg TIM_PSCReloadMode_Update    :The Prescaler is loaded at the update event.
  *     @arg TIM_PSCReloadMode_Immediate :The Prescaler is loaded immediately.
  * @retval None.
  */
void TIM_PrescalerConfig(TIM_TypeDef *tim, uint16_t prescaler, uint16_t reloadMode)
{
    tim->PSC = prescaler;
    tim->EGR = reloadMode;
}

/**
  * @brief  Specifies the tim Counter Mode to be used.
  * @param  tim:select the TIM peripheral.
  * @param  counter_mode: specifies the Counter Mode to be used
  *   This parameter can be one of the following values:
  *     @arg TIM_CounterMode_Up            : TIM Up Counting Mode
  *     @arg TIM_CounterMode_Down          : TIM Down Counting Mode
  *     @arg TIM_CounterMode_CenterAligned1: TIM Center Aligned Mode1
  *     @arg TIM_CounterMode_CenterAligned2: TIM Center Aligned Mode2
  *     @arg TIM_CounterMode_CenterAligned3: TIM Center Aligned Mode3
  * @retval None.
  */
void TIM_CounterModeConfig(TIM_TypeDef *tim, uint32_t counter_mode)
{
    MODIFY_REG(tim->CR1, TIM_CR1_CMS_Msk | TIM_CR1_DIR_Msk, counter_mode);
}

/**
  * @brief  Configures the tim Encoder Interface.
  * @param  tim: select the TIM peripheral.
  * @param  encoder_mode: specifies the tim Encoder Mode.
  *   This parameter can be one of the following values:
  *     @arg TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
  *     @arg TIM_EncoderMode_TI2: Counter counts on TI2FP2 edge depending on TI1FP1 level.
  *     @arg TIM_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
  *                                on the level of the other input.
  * @param  ic1_polarity: specifies the IC1 Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPolarity_Falling: IC Falling edge.
  *     @arg TIM_ICPolarity_Rising: IC Rising edge.
  * @param  ic2_polarity: specifies the IC2 Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_ICPolarity_Falling: IC Falling edge.
  *     @arg TIM_ICPolarity_Rising: IC Rising edge.
  * @retval None.
  */
void TIM_EncoderInterfaceConfig(TIM_TypeDef *tim, uint32_t   encoder_mode, uint32_t  ic1_polarity, uint32_t  ic2_polarity)
{
    MODIFY_REG(tim->SMCR, TIM_SMCR_SMS_Msk, encoder_mode);
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_CC1S_Msk | TIM_CCMR1_CC2S_Msk, TIM_CCMR1_CC1S_DirectTI | TIM_CCMR1_CC2S_DirectTI);
    MODIFY_REG(tim->CCER, TIM_CCER_CC1P_Msk | TIM_CCER_CC2P_Msk, ic1_polarity | (ic2_polarity << 4));
}

/**
  * @brief  Forces the tim output 1 waveform to active or inactive level.
  * @param  tim:  select the TIM peripheral.
  * @param  forced_action: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TIM_ForcedAction_Active:   Force active level on OC1REF
  *     @arg TIM_ForcedAction_Inactive: Force inactive level on OC1REF.
  * @retval None.
  */
void TIM_ForcedOC1Config(TIM_TypeDef *tim, uint32_t forced_action)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC1M_Msk, forced_action << TIM_CCMR1_OC1M_Pos);
}

/**
  * @brief  Forces the tim output 2 waveform to active or inactive level.
  * @param  tim: select the TIM peripheral.
  * @param  forced_action: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TIM_ForcedAction_Active:   Force active level on OC2REF
  *     @arg TIM_ForcedAction_Inactive: Force inactive level on OC2REF.
  * @retval None.
  */
void TIM_ForcedOC2Config(TIM_TypeDef *tim, uint32_t forced_action)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC2M_Msk, forced_action << TIM_CCMR1_OC2M_Pos);
}

/**
  * @brief  Forces the tim output 3 waveform to active or inactive level.
  * @param  tim: select the TIM peripheral.
  * @param  forced_action: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TIM_ForcedAction_Active:   Force active level on OC3REF
  *     @arg TIM_ForcedAction_Inactive: Force inactive level on OC3REF.
  * @retval None.
  */
void TIM_ForcedOC3Config(TIM_TypeDef *tim, uint32_t forced_action)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC3M_Msk, forced_action << TIM_CCMR2_OC3M_Pos);
}

/**
  * @brief  Forces the tim output 4 waveform to active or inactive level.
  * @param  tim: select the TIM peripheral.
  * @param  forced_action: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TIM_ForcedAction_Active:   Force active level on OC4REF
  *     @arg TIM_ForcedAction_Inactive: Force inactive level on OC4REF.
  * @retval None.
  */
void TIM_ForcedOC4Config(TIM_TypeDef *tim, uint32_t forced_action)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC4M_Msk, forced_action << TIM_CCMR2_OC4M_Pos);
}

/**
  * @brief  Enables or disables tim peripheral Preload register on ARR.
  * @param  tim:  select the TIM peripheral.
  * @param  state: new state of the tim peripheral Preload register
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_ARRPreloadConfig(TIM_TypeDef *tim, FunctionalState state)
{
    (state) ?                                   \
    (tim->CR1 |= (0x01U << TIM_CR1_ARPE_Pos)) : \
    (tim->CR1 &= ~(0x01U << TIM_CR1_ARPE_Pos));
}

/**
  * @brief  Selects the TIM peripheral Commutation event.
  * @param  tim: select the tim peripheral.
  * @param  state: new state of the Commutation event.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_SelectCOM(TIM_TypeDef *tim, FunctionalState state)
{
    (state) ?                                   \
    (tim->CR2 |= (0x01U << TIM_CR2_CCUS_Pos)) : \
    (tim->CR2 &= ~(0x01U << TIM_CR2_CCUS_Pos));
}

/**
  * @brief  Sets or Resets the TIM peripheral Capture Compare Preload Control bit.
  * @param  tim: select the tim peripheral.
  * @param  state: new state of the Capture Compare Preload Control bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_CCPreloadControl(TIM_TypeDef *tim, FunctionalState state)
{
    (state) ?                                   \
    (tim->CR2 |= (0x01U << TIM_CR2_CCPC_Pos)) : \
    (tim->CR2 &= ~(0x01U << TIM_CR2_CCPC_Pos));
}

/**
  * @brief  Enables or disables the tim peripheral Preload register on CCR1.
  * @param  tim:  select the TIM peripheral.
  * @param  preload: new state of the tim peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPreload_Disable
  *     @arg TIM_OCPreload_Enable 
  * @retval None.
  */
void TIM_OC1PreloadConfig(TIM_TypeDef *tim, uint32_t preload)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC1PE_Msk, preload);
}

/**
  * @brief  Enables or disables the tim peripheral Preload register on CCR2.
  * @param  tim: select the TIM peripheral.
  * @param  preload: new state of the tim peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPreload_Disable
  *     @arg TIM_OCPreload_Enable 
  * @retval None.
  */
void TIM_OC2PreloadConfig(TIM_TypeDef *tim, uint32_t preload)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC2PE_Msk, preload << 8);
}

/**
  * @brief  Enables or disables the tim peripheral Preload register on CCR3.
  * @param  tim: select the TIM peripheral.
  * @param  preload: new state of the tim peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPreload_Disable
  *     @arg TIM_OCPreload_Enable 
  * @retval None.
  */
void TIM_OC3PreloadConfig(TIM_TypeDef *tim, uint32_t preload)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC3PE_Msk, preload);
}

/**
  * @brief  Enables or disables the tim peripheral Preload register on CCR4.
  * @param  tim: select the TIM peripheral.
  * @param  preload: new state of the tim peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPreload_Disable
  *     @arg TIM_OCPreload_Enable 
  * @retval None.
  */
void TIM_OC4PreloadConfig(TIM_TypeDef *tim, uint32_t preload)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC4PE_Msk, preload << 8);
}

/**
  * @brief  Enables or disables the tim peripheral Preload register on CCR5.
  * @param  tim: select the TIM peripheral.
  * @param  preload: new state of the tim peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPreload_Disable
  *     @arg TIM_OCPreload_Enable 
  * @retval None.
  */
void TIM_OC5PreloadConfig(TIM_TypeDef *tim, uint32_t preload)
{
    MODIFY_REG(tim->CCMR3, TIM_CCMR3_OC5PE_Msk, preload);
}

/**
  * @brief  Configures the tim Output Compare 1 Fast feature.
  * @param  tim: select the TIM peripheral.
  * @param  fast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TIM_OCFast_Enable: TIM output compare fast enable
  *     @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None.
  */
void TIM_OC1FastConfig(TIM_TypeDef *tim, uint32_t fast)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC1FE_Msk, fast);
}

/**
  * @brief  Configures the tim Output Compare 2 Fast feature.
  * @param  tim: select the TIM peripheral.
  * @param  fast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TIM_OCFast_Enable: TIM output compare fast enable
  *     @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None.
  */
void TIM_OC2FastConfig(TIM_TypeDef *tim, uint32_t fast)
{
    MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC2FE_Msk, fast << 8);
}

/**
  * @brief  Configures the tim Output Compare 3 Fast feature.
  * @param  tim: select the TIM peripheral.
  * @param  fast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TIM_OCFast_Enable: TIM output compare fast enable
  *     @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None.
  */
void TIM_OC3FastConfig(TIM_TypeDef *tim, uint32_t fast)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC3FE_Msk, fast);
}

/**
  * @brief  Configures the tim Output Compare 4 Fast feature.
  * @param  tim: select the TIM peripheral.
  * @param  fast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TIM_OCFast_Enable: TIM output compare fast enable
  *     @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None.
  */
void TIM_OC4FastConfig(TIM_TypeDef *tim, uint32_t fast)
{
    MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC4FE_Msk, fast << 8);
}

/**
  * @brief  Configures the tim channel 1 polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC1 Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPolarity_High: Output Compare active high
  *     @arg TIM_OCPolarity_Low:  Output Compare active low
  * @retval None.
  */
void TIM_OC1PolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC1P_Msk, polarity << TIM_CCER_CC1P_Pos);
}

/**
  * @brief  Configures the tim Channel 1N polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC1N Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCNPolarity_High: Output Compare active high
  *     @arg TIM_OCNPolarity_Low:  Output Compare active low
  * @retval None.
  */
void TIM_OC1NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC1NP_Msk, polarity << TIM_CCER_CC1NP_Pos);
}

/**
  * @brief  Configures the tim channel 2 polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC2 Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPolarity_High: Output Compare active high
  *     @arg TIM_OCPolarity_Low:  Output Compare active low
  * @retval None.
  */
void TIM_OC2PolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC2P_Msk, polarity << TIM_CCER_CC2P_Pos);
}

/**
  * @brief  Configures the tim Channel 2N polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC2N Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCNPolarity_High: Output Compare active high
  *     @arg TIM_OCNPolarity_Low:  Output Compare active low
  * @retval None.
  */
void TIM_OC2NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC2NP_Msk, polarity << TIM_CCER_CC2NP_Pos);
}

/**
  * @brief  Configures the tim channel 3 polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC3 Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPolarity_High: Output Compare active high
  *     @arg TIM_OCPolarity_Low:  Output Compare active low
  * @retval None.
  */
void TIM_OC3PolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC3P_Msk, polarity << TIM_CCER_CC3P_Pos);
}

/**
  * @brief  Configures the tim Channel 3N polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC3N Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCNPolarity_High: Output Compare active high
  *     @arg TIM_OCNPolarity_Low:  Output Compare active low
  * @retval None.
  */
void TIM_OC3NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC3NP_Msk, polarity << TIM_CCER_CC3NP_Pos);
}

/**
  * @brief  Configures the tim channel 4 polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC4 Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPolarity_High: Output Compare active high
  *     @arg TIM_OCPolarity_Low: Output Compare active low
  * @retval None.
  */
void TIM_OC4PolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC4P_Msk, polarity << TIM_CCER_CC4P_Pos);
}

/**
  * @brief  Configures the tim channel 4N polarity.
  * @param  tim: select the TIM peripheral.
  * @param  polarity: specifies the OC4N Polarity
  *   This parameter can be one of the following values:
  *     @arg TIM_OCNPolarity_High: Output Compare active high
  *     @arg TIM_OCNPolarity_Low: Output Compare active low
  * @retval None.
  */
void TIM_OC4NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC4NP_Msk, polarity << TIM_CCER_CC4NP_Pos);
}

/**
  * @brief  Enables or disables the TIM Capture Compare Channel x.
  * @param  tim:  select the TIM peripheral.
  * @param  channel: specifies the TIM Channel
  *   This parameter can be one of the following values:
  *     @arg TIM_Channel_1: TIM Channel 1
  *     @arg TIM_Channel_2: TIM Channel 2
  *     @arg TIM_Channel_3: TIM Channel 3
  *     @arg TIM_Channel_4: TIM Channel 4
  *     @arg TIM_Channel_5: TIM Channel 5(Only for some MM32 TIM1/8)
  * @param  TIM_CCx: specifies the TIM Channel CCxE bit new state.
  *   This parameter can be: TIM_CCx_Enable or TIM_CCx_Disable.
  * @retval None.
  */
void TIM_CCxCmd(TIM_TypeDef *tim, uint16_t channel, uint32_t ccx_en)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC1E_Msk << channel, ccx_en << channel);
}

/**
  * @brief  Enables or disables the TIM Capture Compare Channel xN.
  * @param  tim: select the TIM peripheral.
  * @param  channel: specifies the TIM Channel
  *   This parameter can be one of the following values:
  *     @arg TIM_Channel_1: TIM Channel 1
  *     @arg TIM_Channel_2: TIM Channel 2
  *     @arg TIM_Channel_3: TIM Channel 3
  *     @arg TIM_Channel_4: TIM Channel 4
  * @param  TTIM_CHANNEL_5IM_CCxN: specifies the TIM Channel CCxNE bit new state.
  *   This parameter can be: TIM_CCXN_ENABLE or TIM_CCXN_Disable.
  * @retval None.
  */
void TIM_CCxNCmd(TIM_TypeDef *tim, uint16_t channel, uint32_t ccxn_en)
{
    MODIFY_REG(tim->CCER, TIM_CCER_CC1NE_Msk << channel, ccxn_en << channel);
}

/**
  * @brief  Selects the TIM Output Compare Mode.
  * @note   This function disables the selected channel before changing the Output  Compare Mode.
  *         User has to enable this channel using TIM_CCxCmd and TIM_CCxNCmd functions.
  * @param  tim:  select the TIM peripheral.
  * @param  channel: specifies the TIM Channel
  *     @arg TIM_Channel_1: TIM Channel 1
  *     @arg TIM_Channel_2: TIM Channel 2
  *     @arg TIM_Channel_3: TIM Channel 3
  *     @arg TIM_Channel_4: TIM Channel 4
  *     @arg TIM_Channel_5: TIM Channel 5
  * @param  mode: specifies the TIM Output Compare Mode.
  *     @arg TIM_OCMode_Timing        
  *     @arg TIM_OCMode_Active        
  *     @arg TIM_OCMode_Inactive      
  *     @arg TIM_OCMode_Toggle        
  *     @arg TIM_ForcedAction_Inactive
  *     @arg TIM_ForcedAction_Active  
  *     @arg TIM_OCMode_PWM1          
  *     @arg TIM_OCMode_PWM2          
  * @retval None.
  */
void TIM_SelectOCxM(TIM_TypeDef *tim, uint16_t channel, uint32_t mode)
{
    tim->CCER &= ~(TIM_CCER_CC1E_Msk << channel);

    switch (channel)
    {
        case TIM_Channel_1:
            MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC1M_Msk, mode << TIM_CCMR1_OC1M_Pos);
            break;

        case TIM_Channel_2:
            MODIFY_REG(tim->CCMR1, TIM_CCMR1_OC2M_Msk, mode << TIM_CCMR1_OC2M_Pos);
            break;

        case TIM_Channel_3:
            MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC3M_Msk, mode << TIM_CCMR2_OC3M_Pos);
            break;

        case TIM_Channel_4:
            MODIFY_REG(tim->CCMR2, TIM_CCMR2_OC4M_Msk, mode << TIM_CCMR2_OC4M_Pos);
            break;

        default:
            break;
    }
}

/**
  * @brief  Enables or Disables the tim Update event.
  * @param  tim:  select the TIM peripheral.
  * @param  state: new state of the tim UDIS bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_UpdateDisableConfig(TIM_TypeDef *tim, FunctionalState state)
{
    (state) ?                                   \
    (tim->CR1 |= (0x01U << TIM_CR1_UDIS_Pos)) : \
    (tim->CR1 &= ~(0x01U << TIM_CR1_UDIS_Pos));
}

/**
  * @brief  Configures the tim Update Request Interrupt source.
  * @param  tim:  select the TIM peripheral.
  * @param  source: specifies the Update source.
  *   This parameter can be one of the following values:
  *     @arg TIM_UPDATESOURCE_REGULAR: Source of update is the counter overflow/underflow
  *                                    or the setting of UG bit, or an update generation
  *                                    through the slave mode controller.
  *     @arg TIM_UPDATESOURCE_GLOBAL: Source of update is counter overflow/underflow.
  * @retval None.
  */
void TIM_UpdateRequestConfig(TIM_TypeDef *tim, uint32_t source)
{
    MODIFY_REG(tim->CR1, TIM_CR1_URS_Msk, source);
}

/**
  * @brief  Enables or disables the tim's Hall sensor interface.
  * @param  tim: select the TIM peripheral.
  * @param  state: new state of the tim Hall sensor interface.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_SelectHallSensor(TIM_TypeDef *tim, FunctionalState state)
{
    (state) ?                                   \
    (tim->CR2 |= (0x01U << TIM_CR2_TI1S_Pos)) : \
    (tim->CR2 &= ~(0x01U << TIM_CR2_TI1S_Pos));
}

/**
  * @brief  Selects the tim's One Pulse Mode.
  * @param  tim:  select the TIM peripheral.
  * @param  mode: specifies the OPM Mode to be used.
  *   This parameter can be one of the following values:
  *     @arg TIM_OPMode_Repetitive 
  *     @arg TIM_OPMode_Single
  * @retval None.
  */
void TIM_SelectOnePulseMode(TIM_TypeDef *tim, uint32_t mode)
{
    MODIFY_REG(tim->CR1, TIM_CR1_OPM_Msk, mode);
}

/**
  * @brief  Selects the tim Trigger Output Mode.
  * @param  tim:select the TIM peripheral.
  * @param  source: specifies the Trigger Output source.
  *   This paramter can be one of the following values:
  *  - For all tim
  *     @arg TIM_TRIGSource_Reset : The UG bit in the TIM_EGR register is used as the trigger output (TRIG).
  *     @arg TIM_TRIGSource_Enable: The Counter Enable CEN is used as the trigger output (TRIG).
  *     @arg TIM_TRIGSource_Update: The update event is selected as the trigger output (TRIG).
  *     @arg TIM_TRIGSource_OC1   : The trigger output sends a positive pulse when the CC1IF flag is to be set, as soon as a capture or compare match occurs (TRIG).
  *     @arg TIM_TRIGSource_OC1REF: OC1REF signal is used as the trigger output (TRIG).
  *     @arg TIM_TRIGSource_OC2REF: OC2REF signal is used as the trigger output (TRIG).
  *     @arg TIM_TRIGSource_OC3REF: OC3REF signal is used as the trigger output (TRIG).
  *     @arg TIM_TRIGSource_OC4REF: OC4REF signal is used as the trigger output (TRIG).
  *
  * @retval None.
  */
void TIM_SelectOutputTrigger(TIM_TypeDef *tim, uint32_t source)
{
    MODIFY_REG(tim->CR2, TIM_CR2_MMS_Msk, source);
}

/**
  * @brief  Selects the tim Slave Mode.
  * @param  tim: select the TIM peripheral.
  * @param  mode: specifies the Timer Slave Mode.
  *     @arg TIM_SlaveMode_Reset    : Rising edge of the selected trigger signal (TRGI) re-initialize the counter and triggers an update of the registers.
  *     @arg TIM_SlaveMode_Gated    : The counter clock is enabled when the trigger signal (TRGI) is high.
  *     @arg TIM_SlaveMode_Trigger  : The counter starts at a rising edge of the trigger TRGI.
  *     @arg TIM_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter.
  * @retval None.
  */
void TIM_SelectSlaveMode(TIM_TypeDef *tim, uint32_t mode)
{
    MODIFY_REG(tim->SMCR, TIM_SMCR_SMS_Msk, mode);
}

/**
  * @brief  Sets or Resets the tim Master/Slave Mode.
  * @param  tim: select the TIM peripheral.
  * @param  mode: specifies the Timer Master Slave Mode.
  *     @arg TIM_MasterSlaveMode_Enable: synchronization between the current timer and its slaves (through TRIG).
  *     @arg TIM_MasterSlaveMode_Disable: No action
  * @retval None.
  */
void TIM_SelectMasterSlaveMode(TIM_TypeDef *tim, uint32_t mode)
{
    MODIFY_REG(tim->SMCR, TIM_SMCR_MSM_Msk, mode);
}

/**
  * @brief  Sets the tim Counter Register value
  * @param  tim:  select the TIM peripheral.
  * @param  auto_reload: specifies the Counter register new value.
  * @retval None.
  */
void TIM_SetAutoreload(TIM_TypeDef *tim, uint16_t auto_reload)
{
    tim->ARR = auto_reload;
}

/**
  * @brief  Sets the tim Counter Register value
  * @param  tim:  select the TIM peripheral.
  * @param  counter: specifies the Counter register new value.
  * @retval None.
  */
void TIM_SetCounter(TIM_TypeDef *tim, uint32_t counter)
{
    tim->CNT = counter;
}

/**
  * @brief  Sets the tim Clock Division value.
  * @param  tim:  select
  *   the TIM peripheral.
  * @param  clock_div: specifies the clock division value.
  *   This parameter can be one of the following value:
  *     @arg TIM_CKD_DIV_1: TDTS = Tck_tim
  *     @arg TIM_CKD_DIV_2: TDTS = 2 * Tck_tim
  *     @arg TIM_CKD_DIV_4: TDTS = 4 * Tck_tim
  * @retval None.
  */
void TIM_SetClockDivision(TIM_TypeDef *tim, uint32_t clock_div)
{
    MODIFY_REG(tim->CR1, TIM_CR1_CKD_Msk, clock_div);
}

/**
  * @brief  Sets the tim Capture Compare1 Register value
  * @param  tim:  select the TIM peripheral.
  * @param  compare: specifies the Capture Compare1 register new value.
  * @retval None.
  */
void TIM_SetCompare1(TIM_TypeDef *tim, uint32_t compare)
{
    tim->CCR1 = (uint16_t)compare;
}

/**
  * @brief  Sets the tim Capture Compare2 Register value
  * @param  tim: select the TIM peripheral.
  * @param  compare: specifies the Capture Compare2 register new value.
  * @retval None.
  */
void TIM_SetCompare2(TIM_TypeDef *tim, uint32_t compare)
{
    tim->CCR2 = (uint16_t)compare;
}

/**
  * @brief  Sets the tim Capture Compare3 Register value
  * @param  tim: select the TIM peripheral.
  * @param  compare: specifies the Capture Compare3 register new value.
  * @retval None.
  */
void TIM_SetCompare3(TIM_TypeDef *tim, uint32_t compare)
{
    tim->CCR3 = (uint16_t)compare;
}

/**
  * @brief  Sets the tim Capture Compare4 Register value
  * @param  tim:  select the TIM peripheral.
  * @param  compare: specifies the Capture Compare4 register new value.
  * @retval None.
  */
void TIM_SetCompare4(TIM_TypeDef *tim, uint32_t compare)
{
    tim->CCR4 = (uint16_t)compare;
}

/**
  * @brief  Sets the tim Capture Compare 5 Register value
  * @param  tim: select the TIM peripheral.
  * @param  compare: specifies the Capture Compare5 register new value.
  * @retval None.
  */
void TIM_SetCompare5(TIM_TypeDef *tim, uint32_t compare)
{
    tim->CCR5 = (uint16_t)compare;
}

/**
  * @brief  Gets the tim Input Capture 1 value.
  * @param  tim:  select the TIM peripheral.
  * @retval Value: Capture Compare 1 Register value.
  */
uint32_t TIM_GetCapture1(TIM_TypeDef *tim)
{
    return (tim->CCR1);
}

/**
  * @brief  Gets the tim Input Capture 2 value.
  * @param  tim: select the TIM peripheral.
  * @retval Value: Capture Compare 2 Register value.
  */
uint32_t TIM_GetCapture2(TIM_TypeDef *tim)
{
    return (tim->CCR2);
}

/**
  * @brief  Gets the tim Input Capture 3 value.
  * @param  tim: select the TIM peripheral.
  * @retval Value: Capture Compare 3 Register value.
  */
uint32_t TIM_GetCapture3(TIM_TypeDef *tim)
{
    return (tim->CCR3);
}

/**
  * @brief  Gets the tim Input Capture 4 value.
  * @param  tim: select the TIM peripheral.
  * @retval Value: Capture Compare 4 Register value.
  */
uint32_t TIM_GetCapture4(TIM_TypeDef *tim)
{
    return (tim->CCR4);
}

/**
  * @brief  Gets the tim Input Capture 5 value.
  * @param  tim: select the TIM peripheral.
  * @retval Value: Capture Compare 5 Register value.
  */
uint32_t TIM_GetCapture5(TIM_TypeDef *tim)
{
    return (tim->CCR5);
}

/**
  * @brief  Gets the tim Counter value.
  * @param  tim:  select the TIM peripheral.
  * @retval Value: Counter Register value.
  */
uint32_t TIM_GetCounter(TIM_TypeDef *tim)
{
    return (tim->CNT);
}

/**
  * @brief  Gets the tim Prescaler value.
  * @param  tim:  select the TIM peripheral.
  * @retval Value: Prescaler Register value.
  */
uint16_t TIM_GetPrescaler(TIM_TypeDef *tim)
{
    return (tim->PSC);
}

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  tim:  select the TIM peripheral.
  * @param  flag: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg TIM_FLAG_Update: TIM update Flag
  *     @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
  *     @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
  *     @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
  *     @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
  *     @arg TIM_FLAG_COM: TIM Commutation Flag
  *     @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *     @arg TIM_FLAG_Break: TIM Break Flag
  *     @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
  *     @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
  *     @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
  *     @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
  *     @arg TIM_FLAG_CC5: TIM Capture Compare 5 Flag
  * @retval State: The new state of TIM_FLAG (SET or RESET).
  */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef *tim, uint32_t flag)
{
    return ((tim->SR & flag) ? SET : RESET);
}

/**
  * @brief  Clears the tim's pending flags.
  * @param  tim:  select the TIM peripheral.
  * @param  flag: specifies the flag bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_FLAG_Update: TIM update Flag
  *     @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
  *     @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
  *     @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
  *     @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
  *     @arg TIM_FLAG_COM: TIM Commutation Flag
  *     @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *     @arg TIM_FLAG_Break: TIM Break Flag
  *     @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
  *     @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
  *     @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
  *     @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
  *     @arg TIM_FLAG_CC5: TIM Capture Compare 5 Flag
  * @retval None.
  */
void TIM_ClearFlag(TIM_TypeDef *tim, uint32_t flag)
{
    tim->SR = ~flag;
}

/**
  * @brief  Checks whether the TIM interrupt has occurred or not.
  * @param  tim:  select the TIM peripheral.
  * @param  it: specifies the TIM interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg TIM_IT_Update: TIM update Interrupt source
  *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *     @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
  *     @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
  *     @arg TIM_IT_COM: TIM Commutation Interrupt source
  *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *     @arg TIM_IT_Break: TIM Break Interrupt source
  * @retval State: The new state of the TIM_IT(SET or RESET).
  */
ITStatus TIM_GetITStatus(TIM_TypeDef *tim, uint32_t it)
{
    return (((tim->SR & it) && (tim->DIER & it)) ? SET : RESET);
}

/**
  * @brief  Clears the tim's interrupt pending bits.
  * @param  tim:  select the TIM peripheral.
  * @param  it: specifies the pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_IT_Update: TIM update Interrupt source
  *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *     @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
  *     @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
  *     @arg TIM_IT_COM: TIM Commutation Interrupt source
  *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *     @arg TIM_IT_Break: TIM Break Interrupt source
  * @note
  *   - TIM14, TIM16 and TIM17 can have TIM_IT_Update or TIM_IT_CC1.
  *   - TIM_IT_Break is used only with TIM1 and TIM8.
  *   - TIM_IT_COM is used only with TIM1, TIM8, TIM16 and TIM17.
  * @retval None.
  */
void TIM_ClearITPendingBit(TIM_TypeDef *tim, uint32_t it)
{
    tim->SR = ~it;
}

/**
  * @brief  Enables or disables the specified TIM PWM shift /DMA reqeat.
  * @param  tim: select the tim peripheral.
  * @param  it: Specifies the TIM PWM shift channel to enable or disable.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_PDER_CCDREPE: TIM DMA reqeat enable bit
  *     @arg TIM_PDER_CCR1SHIFTEN: TIM Channel 1 output PWM phase shift enable bit
  *     @arg TIM_PDER_CCR2SHIFTEN: TIM Channel 2 output PWM phase shift enable bit
  *     @arg TIM_PDER_CCR3SHIFTEN: TIM Channel 3 output PWM phase shift enable bit
  *     @arg TIM_PDER_CCR4SHIFTEN: TIM Channel 4 output PWM phase shift enable bit
  *     @arg TIM_PDER_CCR5SHIFTEN: TIM Channel 5 output PWM phase shift enable bit
  * @param  state: new state of the TIM interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void TIM_PWMShiftConfig(TIM_TypeDef *tim, uint32_t it, FunctionalState state)
{
    (state) ?           \
    (tim->PDER |= it) : \
    (tim->PDER &= ~it);
}

/**
  * @brief  Sets the tim CCR1 shift Register value
  * @param  tim:  select the TIM peripheral.
  * @param  compare: specifies the Capture Compare1 register new value.
  * @retval None.
  */
void TIM_SetCCR1FALL(TIM_TypeDef *tim, uint32_t shift)
{
    tim->CCR1FALL = shift;
}

/**
  * @brief  Sets the tim CCR2 shift Register value
  * @param  tim:  select the TIM peripheral.
  * @param  compare: specifies the Capture Compare1 register new value.
  * @retval None.
  */
void TIM_SetCCR2FALL(TIM_TypeDef *tim, uint32_t shift)
{
    tim->CCR2FALL = shift;
}

/**
  * @brief  Sets the tim CCR3 shift Register value
  * @param  tim:  select the TIM peripheral.
  * @param  compare: specifies the Capture Compare1 register new value.
  * @retval None.
  */
void TIM_SetCCR3FALL(TIM_TypeDef *tim, uint32_t shift)
{
    tim->CCR3FALL = shift;
}

/**
  * @brief  Sets the tim CCR4 shift Register value
  * @param  tim:  select the TIM peripheral.
  * @param  compare: specifies the Capture Compare1 register new value.
  * @retval None.
  */
void TIM_SetCCR4FALL(TIM_TypeDef *tim, uint32_t shift)
{
    tim->CCR4FALL = shift;
}

/**
  * @brief  Sets the tim CCR5 shift Register value
  * @param  tim:  select the TIM peripheral.
  * @param  compare: specifies the Capture Compare1 register new value.
  * @retval None.
  */
void TIM_SetCCR5FALL(TIM_TypeDef *tim, uint32_t shift)
{
    tim->CCR5FALL = shift;
}

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  tim:  select the TIM peripheral.
  * @retval None.
  */
FlagStatus TIM_GetCountDirection(TIM_TypeDef *tim)
{
    return ((tim->CR1 & TIM_CR1_DIR_Msk) ? SET : RESET);
}

/**
  * @brief  Gets the TIMx clock.
  * @param  tim:  select the TIM peripheral.
  * @retval Returns The TIMx clock.
  */
uint32_t TIM_GetTIMxClock(TIM_TypeDef *tim)
{
    uint32_t tempclk1 = 0, timclk = 0;
    uint8_t tempdiv = 0, temhdiv = 0;
    uint8_t pclk1pre[] = {0, 0, 0, 0, 2, 4, 8, 16 };
    uint8_t hclkpre[]  = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    RCC_ClocksTypeDef RCC_ClocksStatus;

    RCC_GetClocksFreq(&RCC_ClocksStatus);

    tempclk1 = RCC_ClocksStatus.PCLK1_Frequency;
    tempdiv = (RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos;

    if (tim == TIM1)
    {
        temhdiv = (RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos;

        if(hclkpre[temhdiv] == 0)
        {
            timclk = (pclk1pre[tempdiv] == 0) ? tempclk1 : (tempclk1 * 2);
        }
        else
        {
            timclk = ((pclk1pre[tempdiv] == 0) ? tempclk1 * 2 : tempclk1 * 4) >> hclkpre[temhdiv]; 
        }
    }
    else
    {
        timclk = (pclk1pre[tempdiv] == 0) ? tempclk1 : (tempclk1 * 2);
    }

    return (timclk);
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

