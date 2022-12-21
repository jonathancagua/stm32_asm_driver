/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "led.h"
// datasheet 3.12 clock and startup el clock de 16 MHZ es seleccionado como default
int main(void)
{
    /* Loop forever */
	led_setup();
	while(1){
		led_toggle();
		for(int i=0;i<90000;i++);
	}

}
