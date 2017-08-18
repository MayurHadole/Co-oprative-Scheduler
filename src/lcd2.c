#include <stdint.h>
#include <stdio.h>
#include "common.h"
#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"

void functionCmd(uint32_t pin, uint32_t state);
void enable(uint32_t state);
void s_init();
void s_data();
void s_latch();
void Delay(uint32_t nTime);

GPIO_InitTypeDef  GPIO_InitStruct;




void Delay(uint32_t nTime)
{
uint32_t counter = 0;
while(counter <= nTime)
{
counter++;
}
}


//int  timingdelay = 0;
unsigned  int   count = 0;










void lcdinit(int mode)
{
if(mode != CMD_INTERACTIVE) {
    return;
  }
__GPIOD_CLK_ENABLE();

//GPIO_InitTypeDef  GPIO_InitStruct;
GPIO_InitStruct.Pin = (GPIO_PIN_7 |GPIO_PIN_5 |GPIO_PIN_6 |GPIO_PIN_8 | GPIO_PIN_9 
| GPIO_PIN_10|GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3 |GPIO_PIN_4);
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
GPIO_InitStruct.Alternate = 0;
HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);



__GPIOA_CLK_ENABLE();

//GPIO_InitTypeDef  GPIO_InitStruct;
GPIO_InitStruct.Pin = (GPIO_PIN_10);
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
GPIO_InitStruct.Alternate = 0;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);

/*
int k=0; 
char a[]=" PRASANNDUTT.COM";
char b[]="EMBEDDED SYSTEMS";

functionCmd(10,0); //Initialize RS=0 for selecting instruction Send
functionCmd(9,0); // Select RW=0 to write Instruction/data on LCD
enable(1); // EN=1 for unlatch. (used at initial condition)

Delay(10);

s_init(); //Call Instruction Select routine
GPIOD->ODR=0x0001; // Clear Display, Cursor to Home 
s_latch(); //Latch the above instruction 
//s_init();
GPIOD->ODR=0x0038; // Display Function (2 rows for 8-bit data; small) 
s_latch(); //Latch this above instruction 4 times
s_latch(); 
s_latch(); 
s_latch(); 
//s_init();
GPIOD->ODR=0x000E; // Display and Cursor on, Cursor Blink off 
s_latch(); //Latch the above instruction 
//s_init();
GPIOD->ODR=0x0010; // Cursor shift left 
s_latch(); //Latch the above instruction 
//s_init();
GPIOD->ODR=0x0006; // Cursor Increment, Shift off 
s_latch(); //Latch the above instruction
s_data(); //Change the input type to Data.(before it was instruction input)




for(k=0;a[k];k++)
{

GPIOD->ODR=a[k]; //It will send a[0]='P' as = '0x0050' on Port A.
s_latch(); //Latch the above instruction only once. Or it will clone each character twice if you latch twice.
}
functionCmd(10,0); //Initialize RS=0 for selecting instruction Send
functionCmd(9,0); // Select RW=0 to write Instruction/data on LCD
enable(1); // EN=1 for unlatch. (used at initial condition)

Delay(10);
GPIOD->ODR=0x00C0; // Move cursor to beginning of second row 
s_latch(); //Latch the above instruction
s_data(); //Change the input type to Data.(before it was instruction input)

for(k=0;b[k];k++)
{
//printf("ell\n");
GPIOD->ODR=b[k]; //It will send b[0]='E' as = '0x0044' on Port A.
s_latch();//Latch the above instruction only once. Or it will clone each character twice if you latch twice.
}
s_init(); 

return;*/

}




void lcdCmd(int mode)
{
if(mode != CMD_INTERACTIVE) {
    return;
  }
char* b;
fetch_string_arg(&b);

int k=0; 


__GPIOD_CLK_ENABLE();
//GPIO_InitTypeDef  GPIO_InitStruct;
GPIO_InitStruct.Pin = (GPIO_PIN_7 |GPIO_PIN_5 |GPIO_PIN_6 |GPIO_PIN_8 | GPIO_PIN_9 
| GPIO_PIN_10|GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3 |GPIO_PIN_4);
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
GPIO_InitStruct.Alternate = 0;
HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);



__GPIOA_CLK_ENABLE();

//GPIO_InitTypeDef  GPIO_InitStruct;
GPIO_InitStruct.Pin = (GPIO_PIN_10);
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
GPIO_InitStruct.Alternate = 0;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);

//Sets to 8-bit operation and selects 2-line display and 5 ×8 dot character font.
HAL_Delay(5);

functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,0);
functionCmd(5,1);
functionCmd(4,1);
functionCmd(3,1);
functionCmd(2,0);
functionCmd(1,0);
functionCmd(0,0);
Delay(70);
enable(0);

//Turns on display and cursor. All display is in space mode because of initialization.
HAL_Delay(5);
//enable(1);
functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,0);
functionCmd(5,0);
functionCmd(4,0);
functionCmd(3,1);
functionCmd(2,1);
functionCmd(1,1);
functionCmd(0,0);
Delay(70);
enable(0);


//Sets mode to increment the address by one and to shift the cursor to the 
//right at the time of write to the DD/CGRAM. Display is not shifted.
Delay(400);
//enable(1);
functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,0);
functionCmd(5,0);
functionCmd(4,0);
functionCmd(3,0);
functionCmd(2,1);
functionCmd(1,1);
functionCmd(0,0);
Delay(70);
enable(0);



for(k=0;b[k];k++)
{
Delay(400);
functionCmd(10,1);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);


GPIOD->ODR=b[k+1]; 


Delay(70);
enable(0);
}

Delay(400);
//enable(1);
functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,1);
functionCmd(6,1);
functionCmd(5,0);
functionCmd(4,0);
functionCmd(3,0);//N= 1 chooses twolines 5*8
functionCmd(2,0);//F =0
functionCmd(1,0);
functionCmd(0,0);
Delay(70);
enable(0);


for(k=0;b[k];k++)
{
Delay(400);
//functionCmd(10,1);
//functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);

//printf("ell\n");
GPIOD->ODR=b[k+1]; //It will send b[0]='E' as = '0x0044' on Port A.


Delay(70);
enable(0);
}

}




void cmdDisplay(int mode)
{

Delay(400);
//enable(1);
functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,0);
functionCmd(5,0);
functionCmd(4,0);
functionCmd(3,0);
functionCmd(2,0);
functionCmd(1,0);
functionCmd(0,1);
Delay(70);
enable(0);


}



void cmdCursorblink(int mode)
{
uint32_t state;
fetch_uint32_arg(&state);
Delay(400);
//enable(1);
functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,0);
functionCmd(5,0);
functionCmd(4,0);
functionCmd(3,1);
functionCmd(2,0);
functionCmd(1,0);
functionCmd(0,state);
Delay(70);
enable(0);


}


void cmdCursorOnOff(int mode)
{
uint32_t state;
fetch_uint32_arg(&state);
Delay(400);
//enable(1);
functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,0);
functionCmd(5,0);
functionCmd(4,0);
functionCmd(3,1);
functionCmd(2,0);
functionCmd(1,state);
functionCmd(0,0);
Delay(70);
enable(0);


}


ADD_CMD("lcdinit",lcdinit,"	lcd Initialization");
ADD_CMD("lcd",lcdCmd,"	prints commands on lcd");


ADD_CMD("clear",cmdDisplay,"	prints commands on lcd");
ADD_CMD("blink",cmdCursorblink,"	prints commands on lcd");
ADD_CMD("cursor",cmdCursorOnOff,"	prints commands on lcd");




void functionCmd(uint32_t pin, uint32_t state)
{
switch(pin)
{
case 0:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,state);
break;

case 1:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,state);
break;

case 2:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,state);
break;

case 3:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,state);
break;

case 4:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,state);
break;

case 5:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,state);
break;

case 6:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,state);
break;

case 7:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,state);
break;

case 9:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,state);
break;

case 10:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,state);
break;

default:
printf("wrong gpio");
break;
}


}

void enable(uint32_t state)
{

HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,state);

}


