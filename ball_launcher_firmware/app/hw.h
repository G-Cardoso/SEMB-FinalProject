/*
 * hw.h
 *
 *  Created on: Feb 4, 2023
 *      Author: scdk
 */

#ifndef HW_H_
#define HW_H_

bool hw_button_get(void);
void hw_timer3_start(void);
void hw_pwm_init(void);
void hw_start_motor(void);
void hw_change_motor_power(uint32_t power_value);
void hw_reset_display(void);
uint32_t hw_get_current_time_ms(void);
void hw_cpu_sleep(void);

#endif /* HW_H_ */
