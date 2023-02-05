/*
 * app.c
 *
 *  Created on: Feb 4, 2023
 *      Author: scdk
 */

#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "hw.h"

void app_init(void)
{

}

void app_loop(void)
{
	uint32_t led_time_ms;
	bool button_state = hw_button_get();

	if(button_state)
		led_time_ms = 400;
	else
		led_time_ms = 100;

	hw_led_state_set(true);
	hw_delay_ms(led_time_ms);

	hw_led_state_set(false);
	hw_delay_ms(led_time_ms);

}
