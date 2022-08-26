@ GPIO_BASE_D 			0x40020C00
@ RCC_BASE 				0x40023800
@ RCCAHB1ENR_OFFSET		0X30
@ GPIOD_EN				1<<3
@ MODER5_OUT			1<<10
@ MODER4_OUT			1<<8
@ GPIOX_MODER_OFFSET	0X00
@ GPIOX_ODR_OFFSET		0X14
@ LED_ON				1<<5
.syntax unified
.cpu cortex-m4

.equ 		GPIO_BASE_D, 		0x40020C00
.equ		GPIOX_MODER_OFFSET,	0X00
.equ		GPIOX_ODR_OFFSET,	0X14

.equ		GPIOD_MODER,		GPIO_BASE_D + GPIOX_MODER_OFFSET
.equ		GPIOD_ODR,			GPIO_BASE_D + GPIOX_ODR_OFFSET

.equ		RCC_BASE,			0x40023800
.equ		RCCAHB1ENR_OFFSET,	0X30
.equ		RCCAHB1ENR,			RCC_BASE+RCCAHB1ENR_OFFSET

.equ		GPIOD_EN,			1<<3
.equ		MODER5_OUT,			1<<10
.equ		MODER4_OUT,			1<<8
.equ		LED5_ON,			1<<5
.equ		LED4_ON,			1<<4

		.section .text
		.global		main

main:
		BL		GPIO_Init

GPIO_Init:
		//RCC->AHB1ENR != GPIOD_EN
		//cargar la direccion de RCCAHB1ENR a r0
		LDR		R0,=RCCAHB1ENR
		//cargar el valor de r0 en r1
		LDR		R1,[R0]
		ORR		R1,#GPIOD_EN
		//alamacenar el contenido en R1 de la direccion encontrada en R0
		STR		R1,[R0]

		//GPIOD->MODER != MODER5_OUT
		LDR		R0,=GPIOD_MODER
		LDR		R1,[R0]
		ORR		R1,#MODER5_OUT
		STR		R1,[R0]
		ORR		R1,#MODER4_OUT
		STR		R1,[R0]

		//GPIOA->ODR != LED_ON
		LDR		R0,=GPIOD_ODR
		LDR		R1,=LED4_ON
		STR		R1,[R0]
		LDR		R1,=LED5_ON
		STR		R1,[R0]

		BX		LR

		.end
