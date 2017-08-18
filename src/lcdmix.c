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

return;
}




void lcdCmd(int mode)
{
if(mode != CMD_INTERACTIVE) {
    return;
  }
char b[]="EMBEDDED SYSTEMS";
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
Delay(10);

functionCmd(10,0);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
functionCmd(7,0);
functionCmd(6,0);
functionCmd(5,1);
functionCmd(4,1);
functionCmd(3,1);//N= 1 chooses twolines 5*8
functionCmd(2,0);//F =0
functionCmd(1,0);
functionCmd(0,0);
Delay(70);
enable(0);

//Turns on display and cursor. All display is in space mode because of initialization.
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
functionCmd(3,1);//N= 1 chooses twolines 5*8
functionCmd(2,1);//F =0
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
functionCmd(3,0);//N= 1 chooses twolines 5*8
functionCmd(2,1);//F =0
functionCmd(1,1);
functionCmd(0,0);
Delay(70);
enable(0);


//Writes H. DDRAM has already been selected by initialization when the power was turned on.
//The cursor is incremented by one and shifted to the right.
Delay(400);
functionCmd(10,1);
functionCmd(9,0);
Delay(100);
enable(1);
Delay(250);
for(int k=0;b[k];k++)
{
//printf("ell\n");
GPIOD->ODR=b[k]; //It will send b[0]='E' as = '0x0044' on Port A.
s_latch();//Latch the above instruction only once. Or it will clone each character twice if you latch twice.
}
Delay(70);
enable(0);
//functionCmd(10,0);
}


void testpin(int mode)
{
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_10);
Delay(10);
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_10);
}

ADD_CMD("lcdinit",lcdinit,"	lcd Initialization");
ADD_CMD("lcdprint",lcdCmd,"	prints commands on lcd");

ADD_CMD("test",testpin,"	prints commands on lcd");






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
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,state);
break;

case 10:
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,state);
break;

default:
printf("Enter between 0-10\n");
break;
}


}

void enable(uint32_t state)
{

HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,state);

}





//------------------------------------------------------------------------------
// Function Name : s_init
// Description : Send Instruction Function (RS=0 & RW=0)
//------------------------------------------------------------------------------

void s_init() 
{
functionCmd(10,0); //Initialize RS=0 for selecting instruction Send
functionCmd(9,0); // Select RW=0 to write Instruction/data on LCD


}
//------------------------------------------------------------------------------
// Function Name : s_data
// Description : Send Data Select routine(RS=1 & RW=0)
//------------------------------------------------------------------------------

void s_data() 
{
functionCmd(10,1); //Initialize RS=0 for selecting instruction Send
functionCmd(9,0); // Select RW=0 to write Instruction/data on LCD

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


