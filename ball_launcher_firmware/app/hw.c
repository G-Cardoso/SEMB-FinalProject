/*
 * hw.c
 *
 *  Created on: Feb 4, 2023
 *      Author: scdk
 */


#include <stdint.h>
#include <stdbool.h>
#include "main.h"

bool hw_button_get(void)
{
	GPIO_PinState button_state = HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin);

	return button_state == GPIO_PIN_SET ? true : false;
}

void hw_led_state_set(bool state)
{
	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;

	HAL_GPIO_WritePin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin, led_state);
}

void hw_delay_ms(uint32_t time_ms)
{
	HAL_Delay(time_ms);
}
