/*  FILE          : CoopTaskExecutive.c
 *  PROJECT       : Operating systems task schedular
 *  PROGRAMMER    : Mayur Hadole (7475783)
 *  FIRST VERSION : 2016-11-30
 *  DESCRIPTION   :
 *        This file has the structures, variables and definitions of the functions related to co-operative task managing like task ADD , task Kill etc
 *
 */

/*Declaring the headers*/
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include"common.h"
#include "stm32f3xx_hal.h"
#include "coopTaskExecutive.h" //header file including the function prototypes

#define MAX_TASKS       10
#define TASK_STACK_SIZE 0x100

int32_t currentTask;     // integer variable to save current task being executed

/* Space for process stacks. */
uint32_t stacks[MAX_TASKS][TASK_STACK_SIZE];

//process control block structure to save all the registers before task switching
typedef struct PCB_s 
{
	/* Storage for r4-r14 */
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t sl;
	uint32_t fp;
	uint32_t ip;
	uint32_t lr;
	uint32_t sp;  /* Note location...*/
} PCB_t;


typedef struct Task_s 
{
	void (*f)(void *data);  /* Task function */
	void *data;             /* Private data pointer for this task */
	uint32_t *stack;        /* Pointer to top of task's stack */
	PCB_t pcb;  /* Process control block */
} Task_t;

Task_t tasks[MAX_TASKS];


// FUNCTION     : TaskNull
// DESCRIPTION  :
//      This function has a forever loop. This task will be executed when no tasks are available to execute
// PARAMETERS   : void *data
// RETURNS      : void
void TaskNull(void* data)
{
 while(1)
 {
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
 	if(( id < 0) || (id >= MAX_TASKS))
 	{
  		 printf("Out of Range \n");
   		return -1 ;
   	}
   	if(tasks[id].f == NULL)
   	{
    		printf("\n ALready Dead");
    		return -1;
   	}
  	tasks[id].f = NULL;
  	tasks[id].data =NULL;
  	return id ;
}
   

// FUNCTION     : TaskShell
// DESCRIPTION  :
//			This function calls current task and then kill it without using the stack features of compiler 
// PARAMETERS   : void
// RETURNS      : static void
// Attribute    :To avoid having the compiler generate any stack accesses at the entry and exit of the function this function use an attribute to make the function Naked


__attribute__((naked)) static void TaskShell(void)
{
	/* call the appropriate Task Function */
	tasks[currentTask].f(tasks[currentTask].data);
	/* Terminate this task */
	TaskKill(currentTask);
	/* Call scheduler, Never returns */
	TaskSwitcher();
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
	uint32_t count=0;   // to check if the next task is greater than maximum tasks
  
	i = currentTask - 1;    // to get current task index in to the i
	do 
	{
    		/* NOTE: for this expression to work correctly, MAX_TASKS must be an EVEN number */
    		i = ((i + 1) % (MAX_TASKS-1))+1;  // adds 1 to the i and divides it with 10 and ruturns remainder
					       	  // this will change the next task to 0 if the current task is maximum i.e 10 
    		count++;
  	}while((tasks[i].f == NULL) && (count <= MAX_TASKS));   // repeats the loop only if count is less than or equal to MAXTASKS or equal to NULL
  	return (count <= MAX_TASKS) ? i : -1;
}

// FUNCTION     : TaskInit
// DESCRIPTION  :
//      This function assings NULL to all the variables of all the indexes of task_t array and also adds the pointer to tasknull function at index 0
// PARAMETERS   : void
// RETURNS      : void

void TaskInit(void)
{
	for(int i = 0 ; i<MAX_TASKS ; i++)
	{
	  	tasks[i].f    = NULL; //assigning NULL the variable
	  	tasks[i].data = NULL; //assigning NULL to the variable
	}
	tasks[0].f =TaskNull;  //assiassigning TaskNull function's pointer to the the variable
	tasks[0].data = NULL;  //assigning NULL to the variable
	currentTask = 0;
}

// FUNCTION     : TaskSwitcher
// DESCRIPTION  :
//
//	this function selects the next task to run. If no thread is ready to run, it will re-enable the default TAskNull task.Then
//      it will get the addresses of the current and next PCB's. Inline assembly is used to save and restore the contexts.
//      Then it returns to the function in the restored context
// PARAMETERS   : void
// RETURNS      : int32_t
//			 returns 1 when 
int32_t TaskSwitcher(void)
{
  	int32_t nextTask;
  	register uint32_t *currentPCB asm("r0");     //register int pointer that points to RO register
  	register uint32_t *nextPCB asm("r1");        //register int pointer that points to R1 register
  	//printf("Task switcher called\n\n");
  	nextTask = TaskNext();       // getting the id of next Task    
  	if(nextTask < 0)
  	{
  		/* In the case of no tasks to run,return to the original thread */
  		  printf("TaskSwitcher(): No tasks to run!\n");
  		  nextTask = 0;
  	}
  	/* If the current task is the only one  to be running, just return */
  	if(nextTask == currentTask)
	{
        	return 0;
	}
  	currentPCB = &(tasks[currentTask].pcb.r4);   
  	nextPCB = &(tasks[nextTask].pcb.r4);
  	currentTask = nextTask;     
  	asm volatile (                  //Inline assembly is used to save and restore the contexts.
    	"stm %[current]!,{r4-r12,r14}\n\t"
    	"str sp, [%[current]]\n\t"
    	"ldm %[next]!,{r4-r12,r14}\n\t"
    	"ldr sp, [%[next]]\n\t"
    	: /* No Outputs */
    	: [current] "r" (currentPCB), [next] "r"
   	 (nextPCB) /* Inputs */: /* 'No' Clobbers */);
    	/* We are now on the other context */
   	 return 0;
  }

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
 	/* Fill in initial PCB */ 	/* for loop to find an empty slot */
 	for( int i=0; i<MAX_TASKS; i++) 
 	{
 		memset(&(tasks[i].pcb),0,sizeof(tasks[i].pcb));
 		tasks[i].pcb.sp =(uint32_t)(&(stacks[i][TASK_STACK_SIZE-4]));
 		tasks[i].pcb.fp =(uint32_t)(&(stacks[i][TASK_STACK_SIZE-4]));
 		tasks[i].pcb.lr =(uint32_t)TaskShell;
 		/* Put an initial stack frame on too */
 		stacks[i][TASK_STACK_SIZE-1]=(uint32_t)(TaskShell);
 		if(tasks[i].f == NULL)
 		{
 			tasks[i].f = f;				// assign the passed function pointer to it
 			tasks[i].data = data;			// assign the assoiciated data pointer to it
 			tasks[i].stack = stacks[i];		// assign the assoiciated stack to it
 			return i;				// return the index at whuch the function was added
 		}
 	}
 	return -1;
}



