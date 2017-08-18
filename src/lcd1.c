#include <stdint.h>
#include <stdio.h>
#include "common.h"
#include "stm32f3xx_hal.h"

//#include <stm32f30x_gpio.h>
//#include <stm32f30x_rcc.h>

#define RS GPIOD_Pin_13 // RS is named as Port 13
#define RW GPIOD_Pin_14 // RW is named as Port 14
#define EN GPIOD_Pin_15 // EN is named as Port 15

void Delay(uint32_t nTime)
{
	myTickCount = 0;
	while(myTickCount < (nTime* 10))
		;
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

void enable(int state)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,state);
	
}


//------------------------------------------------------------------------------
// Function Name : s_init
// Description : Send Instruction Function (RS=0 & RW=0)
//------------------------------------------------------------------------------

void s_init() 
{
	gpiostate(10,0); //RS
	gpiostate(9,0);  //R/W
//->BRR=RS;
//GPIOD->BRR=RW;
}
//------------------------------------------------------------------------------
// Function Name : s_data
// Description : Send Data Select routine(RS=1 & RW=0)
//------------------------------------------------------------------------------

void s_data() 
{
	gpiostate(10,1); //RS
	gpiostate(9,0);  //R/W
//GPIOD->BSRR=RS;
//GPIOD->BRR=RW;
}
//------------------------------------------------------------------------------
// Function Name : s_latch
// Description : Latch Data/Instruction on LCD Databus.
//------------------------------------------------------------------------------

void s_latch() 
{
enable(1);
Delay(10);
enable(0);
Delay(10);
}

void cmdlcdprint(int mode)
{

int k=0; 
char a[]=" PRASANNDUTT.COM";
char b[]="EMBEDDED SYSTEMS";
gpiostate(10,0); //RS
gpiostate(9,0);  //R/W
//GPIOD->BRR=RS; //Initialize RS=0 for selecting instruction Send
//GPIOD->BRR=RW; // Select RW=0 to write Instruction/data on LCD
//GPIOD->BSRR=EN; // EN=1 for unlatch. (used at initial condition)
enable(1);
Delay(10);

s_init(); //Call Instruction Select routine
GPIOD->ODR=0x0001; // Clear Display, Cursor to Home 
s_latch(); //Latch the above instruction 
GPIOD->ODR=0x0038; // Display Function (2 rows for 8-bit data; small) 
s_latch(); //Latch this above instruction 4 times
s_latch(); 
s_latch(); 
s_latch(); 
GPIOD->ODR=0x000E; // Display and Cursor on, Cursor Blink off 
s_latch(); //Latch the above instruction 
GPIOD->ODR=0x0010; // Cursor shift left 
s_latch(); //Latch the above instruction 
GPIOD->ODR=0x0006; // Cursor Increment, Shift off 
s_data(); //Change the input type to Data.(before it was instruction input)
s_latch(); //Latch the above instruction

for(k=0;a[k];k++)
{
GPIOD->ODR=a[k]; //It will send a[0]='P' as = '0x0050' on Port A.
s_latch(); //Latch the above instruction only once. Or it will clone each character twice if you latch twice.
}
gpiostate(10,0); //RS
gpiostate(9,0);  //R/W
//GPIOD->BRR=RS; //Initialize RS=0 for selecting instruction Send
//GPIOD->BRR=RW; // Select RW=0 to write Instruction/data on LCD
enable(1);
//GPIOD->BSRR=EN; // EN=1 for unlatch. (used at initial condition)

Delay(10);
GPIOD->ODR=0x00C0; // Move cursor to beginning of second row 
s_latch(); //Latch the above instruction
s_data(); //Change the input type to Data.(before it was instruction input)
for(k=0;b[k];k++)
{
GPIOD->ODR=b[k]; //It will send b[0]='E' as = '0x0044' on Port A.
s_latch();//Latch the above instruction only once. Or it will clone each character twice if you latch twice.
}
s_init(); 
}

ADD_CMD("lcdinit",cmdlcdinit,"               LCD initialization");
ADD_CMD("lcdprint",cmdlcdprint,"               LCD initialization");
