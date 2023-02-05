/*
 * hw.h
 *
 *  Created on: Feb 4, 2023
 *      Author: scdk
 */

#ifndef HW_H_
#define HW_H_

bool hw_button_get(void);
void hw_led_state_set(bool state);
void hw_delay_ms(uint32_t time_ms);

#endif /* HW_H_ */
