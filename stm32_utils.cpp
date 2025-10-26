/*
 * stm32_utils.cpp
 *
 *  Created on: Oct 16, 2025
 *      Author: Oleksiy
 */

#include "stm32_utils.hpp"

void gpio_clk_enable(GPIO_TypeDef* Port)
{

		if(Port == GPIOA)	__HAL_RCC_GPIOA_CLK_ENABLE();
		else if(Port == GPIOB)	__HAL_RCC_GPIOB_CLK_ENABLE();
		else if(Port == GPIOC)	__HAL_RCC_GPIOC_CLK_ENABLE();
#ifdef GPIOH
		else if(Port == GPIOH)	__HAL_RCC_GPIOH_CLK_ENABLE();
#endif
}
