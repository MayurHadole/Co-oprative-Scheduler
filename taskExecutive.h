#ifndef _TASK_EXECUTIVE_H
#define _TASK_EXECUTIVE_H

//prototypes
int32_t TaskAdd(void (*f)(void *data), void *data);
int32_t TaskKill(int32_t id);
int32_t TaskCurrent(void);
int32_t TaskSwitcher(void);
void TaskInit(void);

#endif




