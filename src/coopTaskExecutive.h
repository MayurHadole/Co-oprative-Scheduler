# ifndef TASK_EXECUTIVE_H
# define TASK_EXECUTIVE_H

int32_t TaskAdd(void (*f)(void *data), void *data);
int32_t TaskKill(int32_t id);
int32_t TaskCurrent(void);
int32_t TaskSwitcher(void);
void TaskInit(void);
void TaskNull(void*data);
void TaskA(void*data);
void TaskB(void*data);
//every document is 256 bytes

#endif
