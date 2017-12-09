/**
* @file - gpio.h
* @brief - Gives the HAL implementation for GPIO ports/pins
*
* @author Gunj/Ashish University of Colorado Boulder
* @date 27/10/2017
**/

#include "gpio.h"

//Stores all the GPIO ports' base address
GPIO_Type * const g_GPIO_PORT[5] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};

PORT_Type * const g_PORT[5] = {PORTA, PORTB, PORTC, PORTD, PORTE};

void GPIO_PORTA_ENABLE()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA(1);
}

void GPIO_PORTB_ENABLE()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB(1);
}

void GPIO_PORTC_ENABLE()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC(1);
}

void GPIO_PORTD_ENABLE()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTD(1);
}

void GPIO_PORTE_ENABLE()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTE(1);
}

void GPIO_PORT_ENABLE(GPIO_PORT_t gpio)
{
	switch(gpio)
	{
	case 0:
		GPIO_PORTA_ENABLE();
		break;
	case 1:
		GPIO_PORTB_ENABLE();
		break;
	case 2:
		GPIO_PORTC_ENABLE();
		break;
	case 3:
		GPIO_PORTD_ENABLE();
		break;
	case 4:
		GPIO_PORTE_ENABLE();
		break;
	default:
		break;
	}
}

void GPIO_PinDir(GPIO_PORT_t gpioPort, uint8_t pin, GPIO_PORT_DIR_t dir)
{
	if(dir == gpio_output)
		g_GPIO_PORT[gpioPort]->PDDR |= (1<<pin);
	else
		g_GPIO_PORT[gpioPort]->PDDR &= ~(1<<pin);
}

void GPIO_PinOutClear(GPIO_PORT_t gpioPort, uint8_t pin)
{
	g_GPIO_PORT[gpioPort]->PCOR |= (1 << pin);
}

void GPIO_PinOutSet(GPIO_PORT_t gpioPort, uint8_t pin)
{
	g_GPIO_PORT[gpioPort]->PSOR |= (1 << pin);
}

void GPIO_PinOutToggle(GPIO_PORT_t gpioPort, uint8_t pin)
{
	g_GPIO_PORT[gpioPort]->PTOR |= (1 << pin);
}

uint8_t GPIO_PinOutGet(GPIO_PORT_t gpioPort, uint8_t pin)
{
	return (((g_GPIO_PORT[gpioPort]->PDOR) >> pin) & 1);
}

uint8_t GPIO_PinInGet(GPIO_PORT_t gpioPort, uint8_t pin)
{
	return (((g_GPIO_PORT[gpioPort]->PDIR) >> pin) & 1);
}

void GPIO_PinAltFuncSel(GPIO_PORT_t gpioPort, uint8_t pin, GPIO_ALT_FUNC_t altFunctionSel)
{
	g_PORT[gpioPort]->PCR[pin] |= (altFunctionSel << 8);
}

void GPIO_Red_Led_En()
{
	GPIO_PORTB_ENABLE();
	GPIO_PinDir(gpioPortB,18,gpio_output);
	GPIO_PinAltFuncSel(gpioPortB,18,gpioAlt1_GPIO);
}

void GPIO_Green_Led_En()
{
	GPIO_PORTB_ENABLE();
	GPIO_PinDir(gpioPortB,19,gpio_output);
	GPIO_PinAltFuncSel(gpioPortB,19,gpioAlt1_GPIO);
}

void GPIO_Blue_Led_En()
{
	GPIO_PORTD_ENABLE();
	GPIO_PinDir(gpioPortD,1,gpio_output);
	GPIO_PinAltFuncSel(gpioPortD,1,gpioAlt1_GPIO);
}

void GPIO_Red_On()
{
	GPIO_PinOutClear(gpioPortB,18);
}
void GPIO_Red_Off()
{
	GPIO_PinOutSet(gpioPortB,18);
}
void GPIO_Red_Toggle()
{
	GPIO_PinOutToggle(gpioPortB,18);
}

void GPIO_Green_On()
{
	GPIO_PinOutClear(gpioPortB,19);
}
void GPIO_Green_Off()
{
	GPIO_PinOutSet(gpioPortB,19);
}
void GPIO_Green_Toggle()
{
	GPIO_PinOutToggle(gpioPortB,19);
}

void GPIO_Blue_On()
{
	GPIO_PinOutClear(gpioPortD,1);
}
void GPIO_Blue_Off()
{
	GPIO_PinOutSet(gpioPortD,1);
}
void GPIO_Blue_Toggle()
{
	GPIO_PinOutToggle(gpioPortD,1);
}

