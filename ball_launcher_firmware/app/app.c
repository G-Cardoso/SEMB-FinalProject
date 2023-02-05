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

#define APP_DEBOUCING_TIME_MS 50
#define APP_TIME_TO_RESET_MS 5000

bool app_started = false;
uint32_t launch_counter = 0;
enum MOTOR_POWER motor_power = MEDIUM;

void app_init(void)
{
	hw_pwm_init();
	app_started = true;
}

void app_loop(void)
{
	hw_cpu_sleep();
}

void app_reset(void)
{
	launch_counter = 0;
	motor_power = MEDIUM;
	hw_reset_display();
}

void app_change_motor_speed(void)
{
	switch (motor_power) {
		case LOW:
			motor_power = MEDIUM;
			break;
		case MEDIUM:
			motor_power = HIGH;
			break;
		case HIGH:
			motor_power = LOW;
			break;
		default:
			motor_power = LOW;
	}

	hw_change_motor_power(motor_power);
}

void app_handle_button_press(void)
{
	static uint32_t button_press_time_ms = 0;
	bool button_state = hw_button_get();
	uint32_t current_time_ms =  hw_get_current_time_ms();

	if(!button_state)
	{
		button_press_time_ms = current_time_ms;
		return;
	}

	if((current_time_ms - button_press_time_ms) < APP_TIME_TO_RESET_MS)
		app_change_motor_speed();
	else
		app_reset();
}

void app_button_debounce(void)
{
	static uint32_t debaucing_time_ms = 0;
	uint32_t current_time_ms =  hw_get_current_time_ms();

	if((current_time_ms - debaucing_time_ms) < APP_DEBOUCING_TIME_MS) return;

	debaucing_time_ms = current_time_ms;
	app_handle_button_press();
}


void app_button_interrupt(void)
{
	if(!app_started) return;

	app_button_debounce();
}


void app_sensor_interrupt(void)
{
	if(!app_started) return;

	hw_start_motor();
	hw_timer3_start();
}
