/***********************************************************************************************************************
    @file     hal_gpio.c
    @author   VV TEAM
    @brief    THIS FILE PROVIDES ALL THE GPIO FIRMWARE FUNCTIONS.
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
#include "hal_gpio.h"

/** @addtogroup MM32_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIO_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the gpio peripheral registers to their default reset
  *         values.
  * @param  gpio: select the GPIO peripheral.
  * @retval None.
  */
void GPIO_DeInit(GPIO_TypeDef *gpio)
{
    if (gpio == GPIOA)
    {
        RCC_AHBPeriphResetCmd(RCC_AHBPERIPH_GPIOA, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBPERIPH_GPIOA, DISABLE);
    }
    else if (gpio == GPIOB)
    {
        RCC_AHBPeriphResetCmd(RCC_AHBPERIPH_GPIOB, ENABLE);
        RCC_AHBPeriphResetCmd(RCC_AHBPERIPH_GPIOB, DISABLE);
    }
}

/**
  * @brief  Deinitializes the Alternate Functions (remap, event control
  *         and EXTI configuration) registers to their default reset values.
  * @param  None.
  * @retval None.
  */
void GPIO_AFIODeInit()
{
    GPIOA->AFRL = 0xFFFFFFFF;
    GPIOA->AFRH = 0xF00FFFFF;          /* PA14:SWCLK, PA13:PSWDIO */
    GPIOB->AFRL = 0xFFFFFFFF;
    GPIOB->AFRH = 0xFFFFFFFF;
}

/**
  * @brief  Initializes the gpio peripheral according to the specified
  *         parameters in the init_struct.
  * @param  gpio: select the GPIO peripheral.
  * @param  init_struct: pointer to a GPIO_InitTypeDef structure that
  *         contains the configuration information for the specified GPIO
  *         peripheral.
  * @retval None.
  */
void GPIO_Init(GPIO_TypeDef *gpio, GPIO_InitTypeDef *init_struct)
{
    uint8_t   idx;
    uint8_t i;
    uint32_t tmp;
    __IO uint32_t *reg;

     /* 1x */
    uint32_t dat = init_struct->GPIO_Mode & 0x0F;

    if (init_struct->GPIO_Mode & 0x10)
    {
        dat |= init_struct->GPIO_Speed;
    }

     /* 0x */
    reg  = &gpio->CRL;

    for (i = 0; i < 8; i++)
    {
        idx = i * 4;

        if ((init_struct->GPIO_Pin) & (1 << i))
        {
            *reg  = (*reg & ~(0xF << idx)) | (dat << idx);
        }
    }

    reg     = &gpio->CRH;
    tmp     = init_struct->GPIO_Pin >> 8;

    for (i = 0; i < 8; i++)
    {
        idx = i * 4;

        if (tmp & (1 << i))
        {
            *reg  = (*reg & ~(0xF << idx)) | (dat << idx);
        }
    }

     /* 2x,4x */
    if (init_struct->GPIO_Mode == GPIO_Mode_IPD)
    {
        gpio->BRR |= init_struct->GPIO_Pin;
    }
    else if (init_struct->GPIO_Mode == GPIO_Mode_IPU)
    {
        gpio->BSRR |= init_struct->GPIO_Pin;
    }
}

/**
  * @brief  Fills each init_struct member with its default value.
  * @param init_struct : pointer to a GPIO_InitTypeDef structure
  *   which will be initialized.
  * @retval : None
  */
void GPIO_StructInit(GPIO_InitTypeDef *init_struct)
{
     /* Reset GPIO init structure parameters values */
    init_struct->GPIO_Pin   = GPIO_Pin_All;
    init_struct->GPIO_Speed = GPIO_Speed_High;
    init_struct->GPIO_Mode  = GPIO_Mode_FLOATING;
}

/**
  * @brief  Reads the input data of specified GPIO port pin.
  * @param  gpio:  select the GPIO peripheral.
  * @param  pin:  specifies the port pin to be read.
  *         This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *gpio, uint16_t pin)
{
    return (((gpio->IDR & pin)) ? Bit_SET : Bit_RESET);
}

/**
  * @brief  Reads all GPIO port pins input data.
  * @param  gpio: select the GPIO peripheral.
  * @retval GPIO port input data value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef *gpio)
{
    return (gpio->IDR);
}

/**
  * @brief  Reads the output data of specified GPIO port pin.
  * @param  gpio: select the GPIO peripheral.
  * @param  pin:  specifies the port bit to be read.
  *         This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *gpio, uint16_t pin)
{
    return ((gpio->ODR & pin) ? Bit_SET : Bit_RESET);
}

/**
  * @brief  Reads all GPIO port pins output data.
  * @param  gpio: select the GPIO peripheral.
  * @retval GPIO port output data value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *gpio)
{
    return (gpio->ODR);
}

/**
  * @brief  Sets the selected GPIO port pin.
  * @param  gpio: where x can be (A..D) to select the GPIO peripheral.
  * @param  pin: specifies the port pins to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be
  *         (0..15).
  * @retval None.
  */
void GPIO_SetBits(GPIO_TypeDef *gpio, uint16_t pin)
{
    gpio->BSRR = pin;
}

/**
  * @brief  Clears the selected GPIO port bit.
  * @param  gpio: where x can be (A..D) to select the GPIO peripheral.
  * @param  pin: specifies the port pins to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be
  *         (0..15).
  * @retval None.
  */
void GPIO_ResetBits(GPIO_TypeDef *gpio, uint16_t pin)
{
    gpio->BRR = pin;
}

/**
  * @brief  Sets or clears the selected GPIO port pin.
  * @param  gpio: select the GPIO peripheral.
  * @param  pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..15).
  * @param  value: specifies the value to be written to the selected bit.
  *         This parameter can be one of the BitAction enum values:
  * @arg    BIT_RESET: to clear the port pin
  * @arg    BIT_SET: to set the port pin
  * @retval None.
  */
void GPIO_WriteBit(GPIO_TypeDef *gpio, uint16_t pin, BitAction value)
{
    (value) ? (gpio->BSRR = pin) : (gpio->BRR = pin);
}

/**
  * @brief  Writes data to all GPIO port pins.
  * @param  gpio: where x can be (A, B) to select the GPIO peripheral.
  * @param  value: specifies the value to be written to the port output data
  *         register.
  * @retval None.
  */
void GPIO_Write(GPIO_TypeDef *gpio, uint16_t value)
{
    gpio->ODR = value;
}

/**
  * @brief  Locks GPIO Pins configuration registers until next system reset.
  * @param  gpio: to select the GPIO peripheral.
  * @param  pin: This parameter can be GPIO_Pin_All or GPIO_Pin_x where x can be (0..15).
  * @param  lock: 0 unlock; 1 lock.
  * @retval None.
  */
void GPIO_PinLockConfig(GPIO_TypeDef *gpio, uint16_t pin, uint16_t lock)
{
    gpio->LCKR |= pin;

    gpio->LCKR |= (0x01U << GPIO_LCKR_LCKK_Pos);
    gpio->LCKR &= ~(0x01U << GPIO_LCKR_LCKK_Pos);
    gpio->LCKR |= (0x01U << GPIO_LCKR_LCKK_Pos);

    (lock) ?                                        \
    (gpio->LCKR |= (0x01U << GPIO_LCKR_LCKK_Pos)) : \
    (gpio->LCKR &= ~(0x01U << GPIO_LCKR_LCKK_Pos));
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  gpio: select the GPIO peripheral.
  * @param  pin: specifies the pin for the Alternate function.
  *         This parameter can be GPIO_PinSourcex where x can be (0..15) for
  *         GPIOA, GPIOB .
  * @param  alternate_function: selects the pin to used as Alternate function.
  *         This parameter can be the GPIO_AF_x where x can be (0..7).
  * @note   The pin should be used for Digital IP.
  * @retval None.
  */
void GPIO_PinAFConfig(GPIO_TypeDef *gpio, uint8_t pin, uint8_t alternate_function)
{
    uint8_t shift = (pin & 0x07) * 4;
    uint32_t *ptr = (pin < 8) ? (uint32_t *)&gpio->AFRL : (uint32_t *)&gpio->AFRH;

    *ptr = (*ptr & ~(0x0F << shift)) | (alternate_function << shift);
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

