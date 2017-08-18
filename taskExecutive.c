/*  FILE          : taskExecutive.c
 *  PROJECT       : Operating systems task schedular
 *  PROGRAMMER    : Mayur Hadole (5783)
 *  FIRST VERSION : 2016-11-02
 *  DESCRIPTION   :
 *        This file has the structuires, variables and definitions of the functions related to task managing like task ADD , task Kill etc
 *
 */
   
#include <stdio.h>                  //include header file of standard input output funtion
#include <stdint.h>                 // include standard integer datatype library
#include "stm32f3xx_hal.h"          // inlude hal library functions
#include "stm32f3_discovery.h"      // inlude hal discovery library functions
#include "common.h"                 //Include common.h 
#include "taskExecutive.h"          // header file for task schedular functions

#define MAX_TASKS 50         // Maxixmum number of tasks = 50

typedef struct Task_s        //Structure that will keep the pointer to the name of functions and void pointer to the void data for each fuction 
{
	void (*f)(void *data);  /* Task function */
	void *data;  		/* Private data pointer for this task */
}Task_t;

/* Process list */
Task_t tasks[MAX_TASKS];        // struct array of length 50
int32_t currentTask ;            // integer variable to save current task being executed

// FUNCTION     : TaskAdd
// DESCRIPTION  :
//      This function finds the empty slot in the struct array and assigns the function pointer and data pointer of that function to that
//           slot.
// PARAMETERS   : void (*f)(void *data)
//			void pointer pointing towards the funtion
//
//                void *data
//                      void pointer pointing towards the data
// RETURNS      : 
//               int32_t
//		       returns the index of task_t array in which the function was added

int32_t TaskAdd(void (*f)(void *data), void *data)
{
	/* for loop to find an empty slot */
	for(int i=0; i<MAX_TASKS; i++)       
	{
		if(tasks[i].f == NULL)        // if the void function pointer is NULL then
		{ 
			tasks[i].f = f;       // assign the passed function pointer to it
			tasks[i].data = data; // assign the assoiciated data pointer to it
			return i;             // return the index at whuch the function was added
		}
	}
	/* No slots available, return -1 */
	return -1;
}

// FUNCTION     : TaskInit
// DESCRIPTION  :
//      This function assings NULL to all the variables of all the indexes of task_t array 
// PARAMETERS   : void
// RETURNS      : void

void TaskInit(void)
{
	for(int i = 0 ; i < MAX_TASKS ; i++)   // for loop to go through each index of array
	{
		tasks[i].f = NULL;      // assigning NULL
		tasks[i].data = NULL;   // assigning NULL
	}
}


// FUNCTION     : TaskKill
// DESCRIPTION  :
//      This function kills the task by assigning NULL to the function and data pointer of the passed index of task_t array 
// PARAMETERS   : int32_t
//                       Index at which the function pointer is saved in task_t array
// RETURNS      : int32_t
//			 returns 1

int32_t TaskKill(int32_t id)
{
	tasks[id].f = NULL;
	tasks[id].data = NULL;
	return 1;
}

// FUNCTION     : TaskNext
// DESCRIPTION  :
//           Finds the next task to run 
// PARAMETERS   : void
// RETURNS      : static int32_t
//			 returns index of next task to be executed

static int32_t TaskNext(void)
{
	int32_t i;    
	uint32_t count=0; // to check if the next task is greater than maximum tasks
	i = currentTask;  // to get current task index in to the i
	do 
	{
		i = (i + 1) % MAX_TASKS;       // adds 1 to the i and divides it with 50 and ruturns remainder
					       // this will change the next task to 0 if the current task is maximum i.e 50  
		count++;   		       //increment count by 1
	} while((tasks[i].f == NULL) && (count <= MAX_TASKS));     // repeats the loop only if count is less than or
	return (count <= MAX_TASKS) ? i : -1;
}


// FUNCTION     : TaskCurrent
// DESCRIPTION  :
//      This function returns the index of curent task being executed
// PARAMETERS   : void
// RETURNS      : int32_t
//			 returns index of task being executed

int32_t TaskCurrent(void)
{
	currentTask = TaskNext();  // calls tasknext function which returns current task
	return currentTask;	   //return current task
}

// FUNCTION     : TaskSwitcher
// DESCRIPTION  :
//      This function calls the function pointed by current task
// PARAMETERS   : void
// RETURNS      : int32_t
//			 returns 1 when 
int32_t TaskSwitcher(void)
{
	currentTask = TaskNext();   //to get the index of next task
	if(currentTask < 0)    //if current task is less than 0 then
	{
		return -1;	
	}
	tasks[currentTask].f(tasks[currentTask].data);     //calls the function pointed by current index of tasks array with void data pointer as an argument
	return 1; 
}
















