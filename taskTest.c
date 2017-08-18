/*  FILE          : taskTest.c
 *  PROJECT       : Operating systems task schedular
 *  PROGRAMMER    : Mayur Hadole (5783)
 *  FIRST VERSION : 2016-11-02
 *  DESCRIPTION   :
 *        This file demonstrates the use of task executive functions defined in taskExecutive.c
 *
 */

//header file inclusions

#include <stdio.h>
#include <stdint.h>
#include "stm32f3xx_hal.h"
#include "stm32f3_discovery.h"
#include "common.h"
#include "taskExecutive.h"

#define DELAYOF1SECOND 100


extern int32_t currentTask;   //current task is the global variable declared in taskExecutive.c


// FUNCTION     : function1
// DESCRIPTION  :
//      This function turns on all the leds in predefined pattern
// PARAMETERS   : void *data
// RETURNS      : void

void function1(void *data)
{
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
}


// FUNCTION     : function2
// DESCRIPTION  :
//      This function turns all the leds on at once
// PARAMETERS   : void *data
// RETURNS      : void

void function2(void *data)
{
	printf("Function 2 : All leds turned on together\n");
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
}


// FUNCTION     : function3
// DESCRIPTION  :
//      This function prints Function 1 on minicom
// PARAMETERS   : void *data
// RETURNS      : void

void function3(void *data)
{
	printf("Function 3\n");
}

// FUNCTION     : taskSuicide
// DESCRIPTION  :
//      This function kills the same task that it is assigned to  
// PARAMETERS   : void
// RETURNS      : void

void taskSuicide(void *data)
{
	printf("Task that will kill itself \n");
	TaskKill(currentTask);
}

// FUNCTION     : taskMurderer
// DESCRIPTION  :
//      This function kills another task 
// PARAMETERS   : void
// RETURNS      : void
void taskMurderer(void *data)
{
	printf("I will kill task 3 and then myself \n");
	TaskKill(2);   // kills the task 3
	TaskKill(currentTask); // kills itself
}

// FUNCTION     : CmdTaskInit
// DESCRIPTION  :
//      This function will call taskinit() to make all tasks array indexes to NULL.
// PARAMETERS   : void
// RETURNS      : void
void CmdTaskInit(int mode)
{
	if(mode != CMD_INTERACTIVE) 
	{
    		return;
  	}
	TaskInit();
}

// FUNCTION     : CmdTask
// DESCRIPTION  :
//      This function will call the taskSwitcher() function 10 times. This function is command to the minicom.
// PARAMETERS   : void
// RETURNS      : void
void CmdTask(int mode)
{
	if(mode != CMD_INTERACTIVE) 
	{
    		return;
  	}
	int i;
	for(i=0;i<=10;i++)
	{
		TaskSwitcher();
	}
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
			TaskAdd(function1,(void *)NULL);
			printf("(led pattern)function 1 added \n");
			break;
		}
		case 2: 
		{
			TaskAdd(function2,(void *)NULL);
			printf("(all leds at once)function 2 added \n");
			break;
		}
		case 3: 
		{
			TaskAdd(function3,(void *)NULL);
			printf("function 3 added \n");
			break;
		}
		case 4: 
		{
			TaskAdd(taskSuicide,(void *)NULL);
			printf("taskSuicide added \n");
			break;
		}
		case 5: 
		{
			TaskAdd(taskMurderer,(void *)NULL);
			printf("taskMurderer added \n");
			break;
		}
		default:
		{
			printf("wrong function number,try again");
		}
	}
}


void TaskDump(int32_t id)
{
	
}



ADD_CMD("taskInit", CmdTaskInit,"		Task initialization");
ADD_CMD("taskAdd", CmdTaskAdd,"	<function no>	add task");
ADD_CMD("task", CmdTask,"		Task");

