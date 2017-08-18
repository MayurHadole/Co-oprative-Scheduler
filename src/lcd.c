#include <stdint.h>
#include <stdio.h>
#include "common.h"
#include "stm32f3xx_hal.h"




void delay(int ms)
{
counter = 0;
while(counter <= ms)
{
	counter++;
}
}



void enable(int state)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,state);
	
}

void gpiostate(int GPIONumber , int GPIOState)
{
	switch(GPIONumber)
	{
		case 0:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIOState);
			break;	
		}		
		case 1:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIOState);
			break;	
		}
		case 2:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIOState);
			break;	
		}
		case 3:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIOState);
			break;	
		}
		case 4:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIOState);
			break;	
		}
		case 5:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIOState);
			break;
		}
		case 6:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIOState);	
			break;
		}
		case 7:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIOState);	
			break;
		}
		case 8:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIOState);
			break;	
		}
		case 9:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIOState);
			break;	
		}
		case 10:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIOState);
			break;	
		}
		case 11:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIOState);
			break;	
		}
		case 12:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIOState);
			break;	
		}
		case 13:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIOState);
			break;	
		}
		case 14:
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIOState);
			break;	
		}
		default:
		{
			printf("Entred GPIO PIN number is wrong!!!");
			break;
		}
	}
}

void lcdclear()
{
	delay(400);
	gpiostate(10,0); //RS
	gpiostate(9,0);  //R/W
	enable(1);
	gpiostate(7,0);  //Data 0000001
	gpiostate(6,0);   
	gpiostate(5,0);
	gpiostate(4,0);
	gpiostate(3,0);
	gpiostate(2,0);
	gpiostate(1,0);
	gpiostate(0,1);
	delay(10);
	enable(0);
	
}

void lcd5x8mode()
{
	delay(400);

	gpiostate(10,0); //RS
	gpiostate(9,0);  //R/W
	enable(1);
	gpiostate(7,0);  //Data 00111000
	gpiostate(6,0);   
	gpiostate(5,1);
	gpiostate(4,1);
	gpiostate(3,1);
	gpiostate(2,0);
	gpiostate(1,0);
	gpiostate(0,0);
	delay(10);
	enable(0);
	delay(10);
	enable(1);
	delay(10);
	enable(1);
}

void lcdcursor()
{
	delay(400);
	gpiostate(10,0); //RS
	gpiostate(9,0);  //R/W
	enable(1);
	gpiostate(7,0);  //Data 00001111
	gpiostate(6,0);   
	gpiostate(5,0);
	gpiostate(4,0);
	gpiostate(3,1);
	gpiostate(2,1);
	gpiostate(1,1);
	gpiostate(0,1);
	delay(10);
	enable(0);
	delay(10);
	enable(1);
	delay(10);
	enable(1);
}
void pa10()
{
	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.Pin = (GPIO_PIN_10);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);
}
void cmdlcdinit(int mode)
{
	if(mode != CMD_INTERACTIVE) 
	{
    	return;
	}
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.Pin = (GPIO_PIN_0 |GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	pa10();
	delay(100);
	lcd5x8mode();
	lcdclear();
	lcdcursor();
		
}
ADD_CMD("lcdinit",cmdlcdinit,"               LCD initialization");
