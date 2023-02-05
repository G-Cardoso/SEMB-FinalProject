/*
 * hw.c
 *
 *  Created on: Feb 4, 2023
 *      Author: scdk
 */


#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"

#define PWM_TIMER_CHANNEL TIM_CHANNEL_1

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

bool hw_button_get(void)
{
	GPIO_PinState button_state = HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin);

	return button_state == GPIO_PIN_SET ? true : false;
}

void hw_timer3_start(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
}

void hw_timer3_stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim3);
}

void hw_pwm_init(void)
{
	HAL_TIM_PWM_Init(&htim1);
}

void hw_start_motor(void)
{
	HAL_TIM_PWM_Start(&htim1, PWM_TIMER_CHANNEL);
}

void hw_stop_motor(void)
{
	HAL_TIM_PWM_Stop(&htim1, PWM_TIMER_CHANNEL);
}

void hw_change_motor_power(uint32_t power_value)
{
	__HAL_TIM_SET_COMPARE(&htim1, PWM_TIMER_CHANNEL, power_value);
}

void hw_reset_display(void)
{
	HAL_GPIO_WritePin(PROXIMITY_SENSOR_GPIO_Port, PROXIMITY_SENSOR_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(PROXIMITY_SENSOR_GPIO_Port, PROXIMITY_SENSOR_Pin, GPIO_PIN_SET);
}

uint32_t hw_get_current_time_ms(void)
{
	return HAL_GetTick();
}

void hw_cpu_sleep()
{
	__WFI();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case USER_BUTTON_Pin:
			app_button_interrupt();
			break;
		case PROXIMITY_SENSOR_Pin:
			app_sensor_interrupt();
			break;
		default:
			break;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim != &htim3) return;

	hw_stop_motor();
	hw_timer3_stop();
}
