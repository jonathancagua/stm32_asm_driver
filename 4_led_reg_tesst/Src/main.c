/**
 * @file main.c
 * @author jonathan cagua
 * @brief main que maneja la libreria de led
 * @version 0.1
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2022
 * 
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
