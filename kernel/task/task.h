#ifndef _H_TASk_H_
#define _H_TASH_H_

class task: public dll
{
private:
    char            taskName[MAX_TASK_NAME_LENGTH];
    cpuRegType      registers;
    stackPtrType  * stackPointer;
    unsigned int    stackSize;
    unsigned char   priority;
    taskStateType   state;   
public:   
    task(void);
    ~task(void);
    void taskCreateTask(void);
    void taskDeleteTask(void);
    void taskGetTaskName(void);
    void taskSetTaskName(void);
    void taskGetTaskPriority(void);
    void taskSetTaskPriority(void);
    void taskGetTaskState(void);
    void taskSuspendTask(void);
    void taskActivateTask(void);
}   
#endif
