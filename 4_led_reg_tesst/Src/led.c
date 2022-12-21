/*
 * led.c
 *
 *  Created on: Dec 21, 2022
 *      Author: dev_fw
 */

#include <stdint.h>
#include "led.h"
//Data sheet Table 10, Peripheral RCC
//See 6.3.9 RM0383
#define RCC_AHB1ENR 	(*(volatile uint32_t *)(0x40023830))
#define GPIOD_RCC_AHB1ENR (1 << 3)
//Data sheet Table 10, Peripheral GPIOD
//See GPIO registers 8.4
#define AHB1_GPIOD 		0x40020c00 //
#define GPIOD_MODER 	(*(volatile uint32_t *)(AHB1_GPIOD + 0x00))
#define GPIOD_OTYPE 	(*(volatile uint32_t *)(AHB1_GPIOD + 0x04))
#define GPIOD_OTYPE 	(*(volatile uint32_t *)(AHB1_GPIOD + 0x04))
#define GPIOD_PUPDR 		(*(volatile uint32_t *)(AHB1_GPIOD + 0x0c))
#define GPIOD_ODR  		(*(volatile uint32_t *)(AHB1_GPIOD + 0x14))
#define GPIOD_BSRR 		(*(volatile uint32_t *)(AHB1_GPIOD + 0x18))
#define LED_PIN 		(12)
#define MODER_LEN		(2)
#define LED_SELECT		(LED_PIN * MODER_LEN)
void led_setup(void)
{
    uint32_t reg;
    //Activamos el puerto D de AHB1
    RCC_AHB1ENR |= GPIOD_RCC_AHB1ENR;
    //limpiamos los flags y ponemos en cero
    reg = GPIOD_MODER & ~ (0x03 << LED_SELECT);
    //seteamos como general purpose output mode
    GPIOD_MODER = reg | (1 << LED_SELECT);
    //dejamos el valor que tiene el registro de ese pin
    reg = GPIOD_PUPDR & (0x03 << LED_SELECT);
    //ponemos pull down
    GPIOD_PUPDR = reg | (0x02 << LED_SELECT);
}

void led_on(void)
{
    GPIOD_BSRR |= (1 << LED_PIN); //BS config
}

void led_off(void)
{
    GPIOD_BSRR |= (1 << (LED_PIN + 16)); //BR config
}

void led_toggle(void)
{
	//Leemos el estado del led
    if ((GPIOD_ODR & (1 << LED_PIN)) == (1 << LED_PIN))
        led_off();
    else
        led_on();
}
