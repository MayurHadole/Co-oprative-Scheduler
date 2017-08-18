/*  FILE          : coopTaskTest.c
 *  PROJECT       : Operating systems task schedular
 *  PROGRAMMER    : Mayur Hadole (7475783)
 *  FIRST VERSION : 2016-11-30
 *  DESCRIPTION   :
 *        This file demonstrates the use of task executive functions defined in cooptaskExecutive.c
 *
 */


/*Declaring the headers*/
#include<stdio.h>
#include<stdint.h>
#include"common.h"
#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "coopTaskExecutive.h"  //header file including the function prototypes

#define DELAYOF1SECOND 100

// FUNCTION     : Task1
// DESCRIPTION  :
//      This function prints Task 1 on minicom
// PARAMETERS   : void *data
// RETURNS      : void

void Task1(void *data)
{
	
	printf(" Task 1 starts \n");
	//variable to save led numbers from 0 to 7
	//Initialized to zero for even numbered while loop
	int8_t ledIndex = 0 ;
	//While loop to turn on even numbered LEds (0,2,4,6)
	while(ledIndex <= 6)
	{
		//Turn ON led stored in led index 
		BSP_LED_On(ledIndex);
		//if the timer register/variable value is more than 1 sencond then 
		if(myTickCount > DELAYOF1SECOND )
		{
			//Turn OFF led stored in led index 
			BSP_LED_Off(ledIndex);
			//reset the timer variable to zero
			myTickCount = 0;
			//increment the ledindex by 2 so only even numbered leds will be turned on
			ledIndex += 2;
		}
	}

	//led index initialized to 7 for odd numbered while loop
	ledIndex = 7;
	//While loop to turn on odd numbered LEds (7,5,3,1) in deascending order
	while (ledIndex >= 1 )
	{
		//Turn ON led stored in led index 	
		BSP_LED_On(ledIndex);
		//if the timer register/variable value is more than 1 sencond then 
		if(myTickCount > DELAYOF1SECOND )
		{
			//Turn OFF led stored in led index 
			BSP_LED_Off(ledIndex);
			//reset the timer variable to zero
			myTickCount = 0;
			//increment the ledindex by 2 so only even numbered leds will be turned on
			ledIndex -= 2;
		}
	}	
	TaskSwitcher();   // task yields
	printf(" Task 1 ends \n");
}

// FUNCTION     : Task2
// DESCRIPTION  :
//      This function prints Task 2 on minicom
// PARAMETERS   : void *data
// RETURNS      : void
void Task2(void *data)
{
	printf(" Task 2 starts \n");
	int ledIndex = 0;            // ledIndex
	for(ledIndex = 0; ledIndex < 8; ledIndex++)  // for loop to turn on all the leds
	{
		BSP_LED_On(ledIndex);
	}
	ledIndex = 0;	
	if(myTickCount > DELAYOF1SECOND )
	for(int ledIndex = 0; ledIndex < 8; ledIndex++) // for loop to turn off all the leds
	{
		BSP_LED_Off(ledIndex);
	}
	ledIndex = 0;
	myTickCount=0; //resetting timer
	TaskSwitcher(); // task yields
	printf(" Task 2 ends \n");
}

// FUNCTION     : Task3
// DESCRIPTION  :
//      This function prints Task 3 on minicom
// PARAMETERS   : void *data
// RETURNS      : void
void Task3(void *data)
{
	printf(" Task 3 starts \n");
	TaskSwitcher();  // task yields
	printf(" Task 3 ends \n");
}

// FUNCTION     : Task4
// DESCRIPTION  :
//      This function prints Task 4 on minicom
// PARAMETERS   : void *data
// RETURNS      : void
void Task4(void *data)
{
	printf(" Task 4 starts \n");
	TaskSwitcher();  // task yields
	printf(" Task 4 ends \n");
}

// FUNCTION     : Task5
// DESCRIPTION  :
//      This function prints Task 5 on minicom
// PARAMETERS   : void *data
// RETURNS      : void
void Task5(void *data)
{
	printf(" Task 5 starts \n");
	TaskSwitcher();  // task yields
	printf(" Task 5 ends \n");
}
/*Initialisising Task*/
void TaskInitialise1(int mode)
{
 	TaskInit();
}


// FUNCTION     : CmdTaskAdd
// DESCRIPTION  :
//      This function will add tasks to the tasks array so that task switcher will execute them.
// PARAMETERS   : void
// RETURNS      : void

void CmdTaskAdd(int mode)
{
	if(mode != CMD_INTERACTIVE) 
	{
    		return;
  	}
	uint32_t rc,functionNumber;
	rc = fetch_uint32_arg(&functionNumber);   // to fetch integer argument from minicom
  	if(rc) // if user does not enter the integer argument then
	{
    		printf("missing function Number\n");
    	return;
	}
	switch(functionNumber)  // switch statement to add functions depending upon the integer argument
	{
		case 1: 
		{
			TaskAdd(Task1,(void *)NULL);
			printf("(led pattern)function 1 added \n");
			break;
		}
		case 2: 
		{
			TaskAdd(Task2,(void *)NULL);
			printf("(all leds at once)function 2 added \n");
			break;
		}
		case 3: 
		{
			TaskAdd(Task3,(void *)NULL);
			printf("Task 3 added \n");
			break;
		}
		case 4: 
		{
			TaskAdd(Task4,(void *)NULL);
			printf("task 4 added \n");
			break;
		}
		case 5: 
		{
			TaskAdd(Task5,(void *)NULL);
			printf("task 5 added \n");
			break;
		}
		default:
		{
			printf("wrong function number,try again");
		}
	}
}
 

// FUNCTION     : CmdCooperativeSwitcher
// DESCRIPTION  :
//      This function will call the taskSwitcher() function to starts the co-operative task switching
// PARAMETERS   : void
// RETURNS      : void
void CmdCooperativeSwitcher(int mode)
 {
 	if(mode!= CMD_INTERACTIVE)
 	{
     		return;
 	}
 printf("Tasks Initialised \n");
 TaskSwitcher();
 printf("Task Switcher in action\n");
   
 }

ADD_CMD("taskInit",TaskInitialise1,"Task that starts cooperative switching");
ADD_CMD("CoopSwitch",CmdCooperativeSwitcher,"Task that starts cooperative switching");
ADD_CMD("Add", CmdTaskAdd," < task no. > Add Tasks for Cooperative Switching");
