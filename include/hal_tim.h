/***********************************************************************************************************************
    @file     hal_tim.h
    @author   VV TEAM
    @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE TIM FIRMWARE LIBRARY.
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
#ifndef __HAL_TIM_H
#define __HAL_TIM_H

/* Files includes ----------------------------------------------------------------------------------------------------*/
#include "mm32_device.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @defgroup TIM
  * @{
  */

/** @defgroup TIM_Exported_Types
  * @{
  */
/**
  * @brief  TIM Time Base Init structure definition
  */
typedef struct
{
    uint16_t    TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock. */
    uint32_t    TIM_CounterMode;       /*!< Specifies the counter mode. */
    uint32_t    TIM_Period;            /*!< Specifies the period value to be loaded into the active */
    uint32_t    TIM_ClockDivision;     /*!< Specifies the clock division. */
    uint8_t     TIM_RepetitionCounter; /*!< Specifies the repetition counter value. Each time the RCR downcounter */
} TIM_TimeBaseInitTypeDef;

/**
  * @brief  TIM Output Compare Init structure definition
  */
typedef struct
{
    uint32_t    TIM_OCMode;            /*!< Specifies the TIM mode. */
    uint32_t    TIM_OutputState;       /*!< Specifies the TIM Output Compare state. */
    uint32_t    TIM_OutputNState;      /*!< Specifies the TIM complementary Output Compare state. */
    uint32_t    TIM_Pulse;             /*!< Specifies the pulse value to be loaded into the Capture Compare Register. */
    uint32_t    TIM_OCPolarity;        /*!< Specifies the output polarity. */
    uint32_t    TIM_OCNPolarity;       /*!< Specifies the complementary output polarity. */
    uint32_t    TIM_OCIdleState;       /*!< Specifies the TIM Output Compare pin state during Idle state. */
    uint32_t    TIM_OCNIdleState;      /*!< Specifies the TIM Output Compare pin state during Idle state. */
} TIM_OCInitTypeDef;

/**
  * @brief  TIM Input Capture Init structure definition
  */
typedef struct
{
    uint16_t   TIM_Channel;            /*!< Specifies the TIM channel. */
    uint16_t   TIM_ICPolarity;         /*!< Specifies the active edge of the input signal. */
    uint16_t   TIM_ICSelection;        /*!< Specifies the input. */
    uint16_t   TIM_ICPrescaler;        /*!< Specifies the Input Capture Prescaler. */
    uint16_t   TIM_ICFilter;           /*!< Specifies the input capture filter. */
} TIM_ICInitTypeDef;

/**
  * @brief  BDTR structure definition
  */
typedef struct
{
    uint16_t    TIM_OSSRState;         /*!< Specifies the Off-State selection used in Run mode. */
    uint16_t    TIM_OSSIState;         /*!< Specifies the Off-State used in Idle state. */
    uint16_t    TIM_LOCKLevel;         /*!< Specifies the LOCK level parameters. */
    uint16_t    TIM_DeadTime;          /*!< Specifies the delay time between the switching-off and */
    uint16_t    TIM_Break;             /*!< Specifies whether the TIM Break input is enabled or not. */
    uint16_t    TIM_BreakPolarity;     /*!< Specifies the TIM Break Input pin polarity. */
    uint16_t    TIM_AutomaticOutput;   /*!< Specifies whether the TIM Automatic Output feature is enabled or not. */
} TIM_BDTRInitTypeDef;
/**
  * @}
  */

/** @defgroup TIM_Exported_Constants
  * @{
  */

/**
  * @brief TIM_Clock_Division_CKD
  */
#define TIM_CKD_Div1                      (0x00U << TIM_CR1_CKD_Pos)  /*!< TDTS = Tck_tim */
#define TIM_CKD_Div2                      (0x01U << TIM_CR1_CKD_Pos)  /*!< TDTS = 2 * Tck_tim */
#define TIM_CKD_Div4                      (0x02U << TIM_CR1_CKD_Pos)  /*!< TDTS = 4 * Tck_tim */

/**
  * @brief TIM_Counter_Mode
  */
#define TIM_CounterMode_Up                (0x00U << TIM_CR1_DIR_Pos)  /*!< TIM Up Counting Mode */
#define TIM_CounterMode_Down              (0x01U << TIM_CR1_DIR_Pos)  /*!< TIM Down Counting Mode */
#define TIM_CounterMode_CenterAligned1    (0x01U << TIM_CR1_CMS_Pos)  /*!< TIM Center Aligned Mode1 */
#define TIM_CounterMode_CenterAligned2    (0x02U << TIM_CR1_CMS_Pos)  /*!< TIM Center Aligned Mode2 */
#define TIM_CounterMode_CenterAligned3    (0x03U << TIM_CR1_CMS_Pos)  /*!< TIM Center Aligned Mode3 */

/**
  * @brief TIM_Prescaler_Reload_Mode
  */
#define TIM_PSCReloadMode_Update          (0x00U << TIM_EGR_UG_Pos)   /*!< The Prescaler is loaded at the update event */
#define TIM_PSCReloadMode_Immediate       (0x01U << TIM_EGR_UG_Pos)   /*!< The Prescaler is loaded immediately */

/**
  * @brief TIM_Output_Compare_and_PWM_modes_and_Forced_Action
  */
#define TIM_OCMode_Timing                 0x00U                       /*!< Output compare mode: Timing */
#define TIM_OCMode_Active                 0x01U                       /*!< Output compare mode: Active */
#define TIM_OCMode_Inactive               0x02U                       /*!< Output compare mode: Inactive */
#define TIM_OCMode_Toggle                 0x03U                       /*!< Output compare mode: Toggle */
#define TIM_ForcedAction_Inactive         0x04U                       /*!< Force inactive level on OCnREF */
#define TIM_ForcedAction_Active           0x05U                       /*!< Force active level on OCnREF */
#define TIM_OCMode_PWM1                   0x06U                       /*!< Output compare mode: PWM1 */
#define TIM_OCMode_PWM2                   0x07U                       /*!< Output compare mode: PWM2 */

/**
  * @brief TIM_Output_Compare_Polarity
  */
#define TIM_OCPolarity_High               0x00U                       /*!< Output Compare active high */
#define TIM_OCPolarity_Low                0x01U                       /*!< Output Compare active low */

/**
  * @brief TIM_Output_Compare_N_Polarity
  */
#define TIM_OCNPolarity_High              0x00U                       /*!< Output Compare active high */
#define TIM_OCNPolarity_Low               0x01U                       /*!< Output Compare active low */

/**
  * @brief TIM_Output_Compare_state
  */
#define TIM_OutputState_Disable           0x00U                       /*!< Output Compare Disable */
#define TIM_OutputState_Enable            0x01U                       /*!< Output Compare Enable */

/**
  * @brief TIM_Output_Compare_N_state
  */
#define TIM_OutputNState_Disable          0x00U                       /*!< Output Compare N Disable */
#define TIM_OutputNState_Enable           0x01U                       /*!< Output Compare N Enable */

/**
  * @brief TIM_Output_Compare_Idle_State
  */
#define TIM_OCIdleState_Reset             0x00U                       /*!< OCn=0 (after a dead-time if OCnN is implemented) when MOE=0.(n= 0 : 4) */
#define TIM_OCIdleState_Set               0x01U                       /*!< OCn=1 (after a dead-time if OCnN is implemented) when MOE=0.(n= 0 : 4) */

/**
  * @brief TIM_Output_Compare_N_Idle_State
  */
#define TIM_OCNIdleState_Reset            0x00U                       /*!< OCnN=0 after a dead-time when MOE=0.(n= 0 : 4) */
#define TIM_OCNIdleState_Set              0x01U                       /*!< OCnN=1 after a dead-time when MOE=0.(n= 0 : 4) */

/**
  * @brief TIM_Channel
  */
#define TIM_Channel_1                     0x0000                      /*!< TIM Channel 1 */
#define TIM_Channel_2                     0x0004                      /*!< TIM Channel 2 */
#define TIM_Channel_3                     0x0008                      /*!< TIM Channel 3 */
#define TIM_Channel_4                     0x000C                      /*!< TIM Channel 4 */
#define TIM_Channel_5                     0x0010                      /*!< TIM Channel 5 */

/**
  * @brief TIM_Input_Capture_Polarity
  */
#define TIM_ICPolarity_Rising             (0x00 << TIM_CCER_CC1P_Pos) /*!< IC Rising edge */
#define TIM_ICPolarity_Falling            (0x01 << TIM_CCER_CC1P_Pos) /*!< IC Falling edge */
#define TIM_ICPolarity_BothEdge           ((0x01 << TIM_CCER_CC1P_Pos) | (0x01 << TIM_CCER_CC1NP_Pos))

/**
  * @brief TIM_Input_Capture_Selection
  */
#define TIM_ICSelection_DirectTI          0x01U
#define TIM_ICSelection_IndirectTI        0x02U
#define TIM_ICSelection_TRC               0x03U

/**
  * @brief TIM_Input_Capture_Prescaler
  */
#define TIM_ICPSC_Div1                    0x0000 /*!< no prescaler */
#define TIM_ICPSC_Div2                    0x0004 /*!< capture is done once every 2 events */
#define TIM_ICPSC_Div4                    0x0008 /*!< capture is done once every 4 events */
#define TIM_ICPSC_Div8                    0x000C /*!< capture is done once every 8 events */

/**
  * @brief OSSR_Off_State_Selection_for_Run_mode_state
  */
#define TIM_OSSRState_Disable             (0x00U << TIM_BDTR_OSSR_Pos)
#define TIM_OSSRState_Enable              (0x01U << TIM_BDTR_OSSR_Pos)

/**
  * @brief OSSI_Off_State_Selection_for_Idle_mode_state
  */
#define TIM_OSSIState_Disable             (0x00U << TIM_BDTR_OSSI_Pos)
#define TIM_OSSIState_Enable              (0x01U << TIM_BDTR_OSSI_Pos)

/**
  * @brief Lock_level
  */
#define TIM_LockLevel_OFF                 (0x00U << TIM_BDTR_LOCK_Pos)
#define TIM_LockLevel_1                   (0x01U << TIM_BDTR_LOCK_Pos)
#define TIM_LockLevel_2                   (0x02U << TIM_BDTR_LOCK_Pos)
#define TIM_LockLevel_3                   (0x03U << TIM_BDTR_LOCK_Pos)

/**
  * @brief Break_Input_enable_disable
  */
#define TIM_Break_Disable                 (0x00U << TIM_BDTR_BKE_Pos)   /*!< Break inputs (BRK and CSS clock failure event) disabled */
#define TIM_Break_Enable                  (0x01U << TIM_BDTR_BKE_Pos)   /*!< Break inputs (BRK and CSS clock failure event) enabled */

/**
  * @brief Break_Polarity
  */
#define TIM_BreakPolarity_Low             (0x00U << TIM_BDTR_BKP_Pos)   /*!< Break input BRK is active low */
#define TIM_BreakPolarity_High            (0x01U << TIM_BDTR_BKP_Pos)   /*!< Break input BRK is active high */

/**
  * @brief TIM_AOE_Bit_Set_Reset
  */
#define TIM_AutomaticOutput_Disable       (0x00U << TIM_BDTR_AOE_Pos)   /*!< MOE can be set only by software. */
#define TIM_AutomaticOutput_Enable        (0x01U << TIM_BDTR_AOE_Pos)   /*!< MOE can be set by software or automatically at the next
                                                                           update event (if the break input is not be active). */
/**
  * @brief TIM_DOE_Bit_Set_Reset
  */
#define TIM_DirectOutput_Disable          (0x00U << TIM_BDTR_DOE_Pos)   /*!< Direct output disable, output waiting for dead time */
#define TIM_DirectOutput_Enable           (0x01U << TIM_BDTR_DOE_Pos)   /*!< Direct output enable, no longer waiting for output after dead time */

/**
  * @brief TIM_interrupt_sources
  */
#define TIM_IT_Update                     (0x01U << TIM_DIER_UIE_Pos)   /*!< TIM update Interrupt source */
#define TIM_IT_CC1                        (0x01U << TIM_DIER_CC1IE_Pos) /*!< TIM Capture Compare 1 Interrupt source */
#define TIM_IT_CC2                        (0x01U << TIM_DIER_CC2IE_Pos) /*!< TIM Capture Compare 2 Interrupt source */
#define TIM_IT_CC3                        (0x01U << TIM_DIER_CC3IE_Pos) /*!< TIM Capture Compare 3 Interrupt source */
#define TIM_IT_CC4                        (0x01U << TIM_DIER_CC4IE_Pos) /*!< TIM Capture Compare 4 Interrupt source */
#define TIM_IT_COM                        (0x01U << TIM_DIER_COMIE_Pos) /*!< TIM Commutation Interrupt source */
#define TIM_IT_Trigger                    (0x01U << TIM_DIER_TIE_Pos)   /*!< TIM Trigger Interrupt source */
#define TIM_IT_Break                      (0x01U << TIM_DIER_BIE_Pos)   /*!< TIM Break Interrupt source */
#define TIM_IT_CC5                        (0x01U << TIM_DIER_CC5IE_Pos) /*!< TIM Capture Compare 5 Interrupt source */

/**
  * @brief TIM_Event_Source
  */
#define TIM_EventSource_Update             (0x01U << TIM_EGR_UG_Pos)     /*!< Timer update Event source */
#define TIM_EventSource_CC1                (0x01U << TIM_EGR_CC1G_Pos)   /*!< Timer Capture Compare 1 Event source */
#define TIM_EventSource_CC2                (0x01U << TIM_EGR_CC2G_Pos)   /*!< Timer Capture Compare 2 Event source */
#define TIM_EventSource_CC3                (0x01U << TIM_EGR_CC3G_Pos)   /*!< Timer Capture Compare 3 Event source */
#define TIM_EventSource_CC4                (0x01U << TIM_EGR_CC4G_Pos)   /*!< Timer Capture Compare 4 Event source */
#define TIM_EventSource_COM                (0x01U << TIM_EGR_COMG_Pos)   /*!< Timer COM event source */
#define TIM_EventSource_Trigger            (0x01U << TIM_EGR_TG_Pos)     /*!< Timer Trigger Event source */
#define TIM_EventSource_Break              (0x01U << TIM_EGR_BG_Pos)     /*!< Timer Break event source */
#define TIM_EventSource_CC5                (0x01U << TIM_EGR_CC5G_Pos)   /*!< Timer Capture Compare 5 Event source */

/**
  * @brief TIM_Internal_Trigger_Selection
  */
#define TIM_TS_ITR0                       (0x00U << TIM_SMCR_TS_Pos)    /*!< Internal Trigger 0 */
#define TIM_TS_ITR1                       (0x01U << TIM_SMCR_TS_Pos)    /*!< Internal Trigger 1 */
#define TIM_TS_ITR2                       (0x02U << TIM_SMCR_TS_Pos)    /*!< Internal Trigger 2 */
#define TIM_TS_ITR3                       (0x03U << TIM_SMCR_TS_Pos)    /*!< Internal Trigger 3 */
#define TIM_TS_TI1F_ED                    (0x04U << TIM_SMCR_TS_Pos)    /*!< TI1 Edge Detector */
#define TIM_TS_TI1FP1                     (0x05U << TIM_SMCR_TS_Pos)    /*!< Filtered Timer Input 1 */
#define TIM_TS_TI2FP2                     (0x06U << TIM_SMCR_TS_Pos)    /*!< Filtered Timer Input 2 */
#define TIM_TS_ETRF                       (0x07U << TIM_SMCR_TS_Pos)    /*!< TI1 Edge Detector */

/**
  * @brief TIM_Encoder_Mode
  */
#define TIM_EncoderMode_TI1               (0x01U << TIM_SMCR_SMS_Pos)   /*!< Counter counts on TI1FP1 edge depending on TI2FP2 level. */
#define TIM_EncoderMode_TI2               (0x02U << TIM_SMCR_SMS_Pos)   /*!< Counter counts on TI2FP2 edge depending on TI1FP1 level. */
#define TIM_EncoderMode_TI12              (0x03U << TIM_SMCR_SMS_Pos)   /*!< Counter counts on both TI1FP1 and TI2FP2 edges depending on the level of the other input. */

#define TIM_CCMR1_CC1S_OC                 (0x00U << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC1S_DirectTI           (0x01U << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC1S_IndirectTI         (0x02U << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC1S_TRC                (0x03U << TIM_CCMR1_CC1S_Pos)

#define TIM_CCMR1_CC2S_OC                 (0x00U << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC2S_DirectTI           (0x01U << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC2S_IndirectTI         (0x02U << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC2S_TRC                (0x03U << TIM_CCMR1_CC2S_Pos)

/**
  * @brief TIM_Output_Compare_Preload_State
  */
#define TIM_OCPreload_Disable             (0x00U << TIM_CCMR1_OC1PE_Pos) /*!< TIM output compare preload disable */
#define TIM_OCPreload_Enable              (0x01U << TIM_CCMR1_OC1PE_Pos) /*!< TIM output compare preload enable */

/**
  * @brief TIM_Output_Compare_Clear_State
  */
#define TIM_OCClear_Disable               (0x01U << TIM_CCMR1_OC1CE_Pos) /*!< TIM Output clear disable */
#define TIM_OCClear_Enable                (0x01U << TIM_CCMR1_OC1CE_Pos) /*!< TIM Output clear enable */

/**
  * @brief TIM_Output_Compare_Fast_State
  */
#define TIM_OCFast_Disable                (0x01U << TIM_CCMR1_OC1FE_Pos) /*!< TIM output compare fast disable */
#define TIM_OCFast_Enable                 (0x01U << TIM_CCMR1_OC1FE_Pos) /*!< TIM output compare fast enable */

/**
  * @brief TIM_Capture_Compare_state
  */
#define TIM_CCx_Disable                   (0x00U << TIM_CCER_CC1E_Pos)   /*!< Capture/Compare Enable */
#define TIM_CCx_Enable                    (0x01U << TIM_CCER_CC1E_Pos)   /*!< Capture/Compare Enable */

/**
  * @brief TIM_Capture_Compare_N_state
  */
#define TIM_CCxN_Disable                  (0x00U << TIM_CCER_CC1NE_Pos)  /*!< Capture/Compare N Enable */
#define TIM_CCxN_Enable                   (0x01U << TIM_CCER_CC1NE_Pos)  /*!< Capture/Compare N Enable */

/**
  * @brief TIM_Update_Source
  */
#define TIM_UpdateSource_Global           (0x00U << TIM_CR1_URS_Pos)     /*!< Source of update is counter overflow/underflow. */
#define TIM_UpdateSource_Regular          (0x01U << TIM_CR1_URS_Pos)     /*!< Source of update is the counter overflow/underflow
                                                                            or the setting of UG bit, or an update generation
                                                                            through the slave mode controller. */

/**
  * @brief TIM_One_Pulse_Mode
  */
#define TIM_OPMode_Repetitive             (0x00U << TIM_CR1_OPM_Pos)     /*!< Counter is not stopped at update event */
#define TIM_OPMode_Single                 (0x01U << TIM_CR1_OPM_Pos)     /*!< Counter stops counting at the next update event (clearing the bit CEN) */

/**
  * @brief TIM_Trigger_Output_Source
  */
#define TIM_TRIGSource_Reset              (0x00U << TIM_CR2_MMS_Pos)     /*!< The UG bit in the TIM_EGR register is used as the trigger output (TRIG). */
#define TIM_TRIGSource_Enable             (0x01U << TIM_CR2_MMS_Pos)     /*!< The Counter Enable CEN is used as the trigger output (TRIG). */
#define TIM_TRIGSource_Update             (0x02U << TIM_CR2_MMS_Pos)     /*!< The update event is used as the trigger output (TRIG). */
#define TIM_TRIGSource_OC1                (0x03U << TIM_CR2_MMS_Pos)     /*!< The trigger output sends a positive pulse when the CC1IF flag */
#define TIM_TRIGSource_OC1REF             (0x04U << TIM_CR2_MMS_Pos)     /*!< OC1REF signal is used as the trigger output (TRIG). */
#define TIM_TRIGSource_OC2REF             (0x05U << TIM_CR2_MMS_Pos)     /*!< OC2REF signal is used as the trigger output (TRIG). */
#define TIM_TRIGSource_OC3REF             (0x06U << TIM_CR2_MMS_Pos)     /*!< OC3REF signal is used as the trigger output (TRIG). */
#define TIM_TRIGSource_OC4REF             (0x07U << TIM_CR2_MMS_Pos)     /*!< OC4REF signal is used as the trigger output (TRIG). */

/**
  * @brief TIM_Slave_Mode
  */
#define TIM_SlaveMode_Reset               (0x04U << TIM_SMCR_SMS_Pos)    /*!< Rising edge of the selected trigger signal (TRGI) re-initializes */
#define TIM_SlaveMode_Gated               (0x05U << TIM_SMCR_SMS_Pos)    /*!< The counter clock is enabled when the trigger signal (TRGI) is high. */
#define TIM_SlaveMode_Trigger             (0x06U << TIM_SMCR_SMS_Pos)    /*!< The counter starts at a rising edge of the trigger TRGI. */
#define TIM_SlaveMode_External1           (0x07U << TIM_SMCR_SMS_Pos)    /*!< Rising edges of the selected trigger (TRGI) clock the counter. */

/**
  * @brief TIM_Master_Slave_Mode
  */
#define TIM_MasterSlaveMode_Disable       (0x00U << TIM_SMCR_MSM_Pos)    /*!< No action */
#define TIM_MasterSlaveMode_Enable        (0x01U << TIM_SMCR_MSM_Pos)    /*!< synchronization between the current timer and its slaves (through TRIG) */

/**
  * @brief TIM_Flags
  */
#define TIM_FLAG_Update                   (0x01U << TIM_SR_UIF_Pos)      /*!< TIM update Flag */
#define TIM_FLAG_CC1                      (0x01U << TIM_SR_CC1IF_Pos)    /*!< TIM Capture Compare 1 Flag */
#define TIM_FLAG_CC2                      (0x01U << TIM_SR_CC2IF_Pos)    /*!< TIM Capture Compare 2 Flag */
#define TIM_FLAG_CC3                      (0x01U << TIM_SR_CC3IF_Pos)    /*!< TIM Capture Compare 3 Flag */
#define TIM_FLAG_CC4                      (0x01U << TIM_SR_CC4IF_Pos)    /*!< TIM Capture Compare 4 Flag */
#define TIM_FLAG_COM                      (0x01U << TIM_SR_COMIF_Pos)    /*!< TIM Commutation Flag */
#define TIM_FLAG_Trigger                  (0x01U << TIM_SR_TIF_Pos)      /*!< TIM Trigger Flag */
#define TIM_FLAG_Break                    (0x01U << TIM_SR_BIF_Pos)      /*!< TIM Break Flag */
#define TIM_FLAG_CC1OF                    (0x01U << TIM_SR_CC1OF_Pos)    /*!< TIM Capture Compare 1 overcapture Flag */
#define TIM_FLAG_CC2OF                    (0x01U << TIM_SR_CC2OF_Pos)    /*!< TIM Capture Compare 2 overcapture Flag */
#define TIM_FLAG_CC3OF                    (0x01U << TIM_SR_CC3OF_Pos)    /*!< TIM Capture Compare 3 overcapture Flag */
#define TIM_FLAG_CC4OF                    (0x01U << TIM_SR_CC4OF_Pos)    /*!< TIM Capture Compare 4 overcapture Flag */
#define TIM_FLAG_CC5                      (0x01U << TIM_SR_CC5IF_Pos)    /*!< TIM Capture Compare 5 Flag */

/**
  * @brief PWM phase shift and DMA repeat update
  */
#define TIM_PDER_CCR1SHIFTEN               (0x01U << TIM_PDER_CCR1_SHIFT_EN_Pos)   /*!< TIM Channel 1 output PWM phase shift enable bit */
#define TIM_PDER_CCR2SHIFTEN               (0x01U << TIM_PDER_CCR2_SHIFT_EN_Pos)   /*!< TIM Channel 2 output PWM phase shift enable bit */
#define TIM_PDER_CCR3SHIFTEN               (0x01U << TIM_PDER_CCR3_SHIFT_EN_Pos)   /*!< TIM Channel 3 output PWM phase shift enable bit */
#define TIM_PDER_CCR4SHIFTEN               (0x01U << TIM_PDER_CCR4_SHIFT_EN_Pos)   /*!< TIM Channel 4 output PWM phase shift enable bit */
#define TIM_PDER_CCR5SHIFTEN               (0x01U << TIM_PDER_CCR5_SHIFT_EN_Pos)   /*!< TIM Channel 5 output PWM phase shift enable bit */

/**
  * @}
  */

/** @defgroup TIM_Exported_Functions
  * @{
  */
void TIM_DeInit(TIM_TypeDef *tim);

void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *init_struct);
void TIM_TimeBaseInit(TIM_TypeDef *tim, TIM_TimeBaseInitTypeDef *init_struct);

void TIM_OCStructInit(TIM_OCInitTypeDef *init_struct);
void TIM_OC1Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct);
void TIM_OC2Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct);
void TIM_OC3Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct);
void TIM_OC4Init(TIM_TypeDef *tim, TIM_OCInitTypeDef *init_struct);

void TIM_SetIC1Prescaler(TIM_TypeDef *tim, uint32_t psc);
void TIM_SetIC2Prescaler(TIM_TypeDef *tim, uint32_t psc);
void TIM_SetIC3Prescaler(TIM_TypeDef *tim, uint32_t psc);
void TIM_SetIC4Prescaler(TIM_TypeDef *tim, uint32_t psc);
void TIM_ICStructInit(TIM_ICInitTypeDef *init_struct);
void TIM_ICInit(TIM_TypeDef *tim, TIM_ICInitTypeDef *init_struct);
void TIM_PWMIConfig(TIM_TypeDef *tim, TIM_ICInitTypeDef *init_struct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *init_struct);
void TIM_BDTRConfig(TIM_TypeDef *tim, TIM_BDTRInitTypeDef *init_struct);
void TIM_CtrlPWMOutputs(TIM_TypeDef *tim, FunctionalState state);

void TIM_Cmd(TIM_TypeDef *tim, FunctionalState state);

void TIM_ITConfig(TIM_TypeDef *tim, uint32_t it, FunctionalState state);
void TIM_GenerateEvent(TIM_TypeDef *tim, uint32_t source);

void TIM_InternalClockConfig(TIM_TypeDef *tim);
void TIM_ITRxExternalClockConfig(TIM_TypeDef *tim, uint32_t source);

void TIM_SelectInputTrigger(TIM_TypeDef *tim, uint16_t source);

void TIM_PrescalerConfig(TIM_TypeDef *tim, uint16_t prescaler, uint16_t reloadMode);
void TIM_CounterModeConfig(TIM_TypeDef *tim, uint32_t counter_mode);

void TIM_EncoderInterfaceConfig(TIM_TypeDef *tim, uint32_t encoder_mode, uint32_t ic1_polarity, uint32_t ic2_polarity);
void TIM_ForcedOC1Config(TIM_TypeDef *tim, uint32_t forced_action);
void TIM_ForcedOC2Config(TIM_TypeDef *tim, uint32_t forced_action);
void TIM_ForcedOC3Config(TIM_TypeDef *tim, uint32_t forced_action);
void TIM_ForcedOC4Config(TIM_TypeDef *tim, uint32_t forced_action);

void TIM_ARRPreloadConfig(TIM_TypeDef *tim, FunctionalState state);
void TIM_SelectCOM(TIM_TypeDef *tim, FunctionalState state);
void TIM_SelectCCDMA(TIM_TypeDef *tim, FunctionalState state);
void TIM_CCPreloadControl(TIM_TypeDef *tim, FunctionalState state);

void TIM_OC1PreloadConfig(TIM_TypeDef *tim, uint32_t preload);
void TIM_OC2PreloadConfig(TIM_TypeDef *tim, uint32_t preload);
void TIM_OC3PreloadConfig(TIM_TypeDef *tim, uint32_t preload);
void TIM_OC4PreloadConfig(TIM_TypeDef *tim, uint32_t preload);
void TIM_OC5PreloadConfig(TIM_TypeDef *tim, uint32_t preload);
void TIM_OC1FastConfig(TIM_TypeDef *tim, uint32_t fast);
void TIM_OC2FastConfig(TIM_TypeDef *tim, uint32_t fast);
void TIM_OC3FastConfig(TIM_TypeDef *tim, uint32_t fast);
void TIM_OC4FastConfig(TIM_TypeDef *tim, uint32_t fast);
void TIM_OC1PolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_OC2PolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_OC3PolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_OC4PolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_OC4NPolarityConfig(TIM_TypeDef *tim, uint32_t polarity);
void TIM_CCxCmd(TIM_TypeDef *tim, uint16_t channel, uint32_t ccx_en);
void TIM_CCxNCmd(TIM_TypeDef *tim, uint16_t channel, uint32_t ccxn_en);

void TIM_SelectOCxM(TIM_TypeDef *tim, uint16_t channel, uint32_t mode);
void TIM_SetCompare1(TIM_TypeDef *tim, uint32_t compare);
void TIM_SetCompare2(TIM_TypeDef *tim, uint32_t compare);
void TIM_SetCompare3(TIM_TypeDef *tim, uint32_t compare);
void TIM_SetCompare4(TIM_TypeDef *tim, uint32_t compare);
void TIM_SetCompare5(TIM_TypeDef *tim, uint32_t compare);

void TIM_UpdateDisableConfig(TIM_TypeDef *tim, FunctionalState state);
void TIM_UpdateRequestConfig(TIM_TypeDef *tim, uint32_t source);
void TIM_SelectHallSensor(TIM_TypeDef *tim, FunctionalState state);
void TIM_SelectOnePulseMode(TIM_TypeDef *tim, uint32_t mode);
void TIM_SelectOutputTrigger(TIM_TypeDef *tim, uint32_t source);

void TIM_SelectSlaveMode(TIM_TypeDef *tim, uint32_t mode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef *tim, uint32_t mode);

void TIM_SetAutoreload(TIM_TypeDef *tim, uint16_t auto_reload);
void TIM_SetCounter(TIM_TypeDef *tim, uint32_t counter);

void TIM_SetClockDivision(TIM_TypeDef *tim, uint32_t clock_div);

uint32_t TIM_GetCapture1(TIM_TypeDef *tim);
uint32_t TIM_GetCapture2(TIM_TypeDef *tim);
uint32_t TIM_GetCapture3(TIM_TypeDef *tim);
uint32_t TIM_GetCapture4(TIM_TypeDef *tim);
uint32_t TIM_GetCapture5(TIM_TypeDef *tim);

uint32_t TIM_GetCounter(TIM_TypeDef *tim);
uint16_t TIM_GetPrescaler(TIM_TypeDef *tim);

FlagStatus TIM_GetFlagStatus(TIM_TypeDef *tim, uint32_t flag);
void TIM_ClearFlag(TIM_TypeDef *tim, uint32_t flag);
ITStatus TIM_GetITStatus(TIM_TypeDef *tim, uint32_t it);
void TIM_ClearITPendingBit(TIM_TypeDef *tim, uint32_t it);

void TIM_PWMShiftConfig(TIM_TypeDef *tim, uint32_t it, FunctionalState state);
void TIM_SetCCR1FALL(TIM_TypeDef *tim, uint32_t shift);
void TIM_SetCCR2FALL(TIM_TypeDef *tim, uint32_t shift);
void TIM_SetCCR3FALL(TIM_TypeDef *tim, uint32_t shift);
void TIM_SetCCR4FALL(TIM_TypeDef *tim, uint32_t shift);
void TIM_SetCCR5FALL(TIM_TypeDef *tim, uint32_t shift);
FlagStatus TIM_GetCountDirection(TIM_TypeDef *tim);

uint32_t TIM_GetTIMxClock(TIM_TypeDef *tim);

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

