/*
 * app.h
 *
 *  Created on: Feb 4, 2023
 *      Author: scdk
 */

#ifndef APP_H_
#define APP_H_

enum MOTOR_POWER {
	LOW = 479,
	MEDIUM = 956,
	HIGH = 14439
};

void app_init(void);
void app_loop(void);
void app_button_interrupt(void);
void app_sensor_interrupt(void);

#endif /* APP_H_ */
