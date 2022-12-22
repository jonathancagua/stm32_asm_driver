/**
 * @file led.c
 * @author jonathan cagua
 * @brief libreria para manejo de led en bare metal
 * @version 0.1
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include "led.h"
//Data sheet Table 10, Peripheral RCC
//See 6.3.9 RM0383
#define PERIPH_BASE			(0X40000000UL)
#define AHB1_PERIPH_OFFSET	(0X00020000UL)
#define GPIOD_OFFSET		(0X0C00UL)
#define RCC_OFFSET			(0X3800UL)

#define RCC_AHB1ENR_OFFSET	(0x30UL)


#define AHB1_PERIPH_BASE	(PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define GPIOD_BASE			(AHB1_PERIPH_BASE + GPIOD_OFFSET)
#define RCC_BASE			(AHB1_PERIPH_BASE + RCC_OFFSET)

#define RCC_AHB1ENR 		(*(volatile uint32_t *)(RCC_BASE+RCC_AHB1ENR_OFFSET))
#define GPIOD_RCC_AHB1ENR 	(1 << 3)
//Data sheet Table 10, Peripheral GPIOD
//See GPIO registers 8.4
#define GPIOD_MODER 		(*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_OTYPE 		(*(volatile uint32_t *)(GPIOD_BASE + 0x04))
#define GPIOD_OTYPE 		(*(volatile uint32_t *)(GPIOD_BASE + 0x04))
#define GPIOD_PUPDR     	(*(volatile uint32_t *)(GPIOD_BASE + 0x0c))
#define GPIOD_ODR  			(*(volatile uint32_t *)(GPIOD_BASE + 0x14))
#define GPIOD_BSRR 			(*(volatile uint32_t *)(GPIOD_BASE + 0x18))
#define LED_PIN 			(12)
#define MODER_LEN			(2)
#define LED_SELECT			(LED_PIN * MODER_LEN)
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
