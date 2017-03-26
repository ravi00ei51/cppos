#ifndef _H_TASk_H_
#define _H_TASH_H_
#include "basetypes.h"
#include "cortex-m3.h"
#define MAX_TASK_NAME_LENGTH (10u)
enum taskState
{
    TASK_STATE_SUSPENDED,
    TASK_STATE_READY,
    TASK_STATE_WAIT,
    TASK_STATE_DELETE    
};

typedef enum taskState taskStateType;
typedef void(*taskFunctionType)(void);
class task:public cortex_m3_cpu
{
private:
    char                                          name[MAX_TASK_NAME_LENGTH];
    uint32_t                                       * pStack;
    unsigned int                                  stackSize;
    unsigned char                                 priority;
    taskStateType                                 state;   
    taskFunctionType                              pTaskFunction;
public:   
    //task(void);
    //~task(void);
    void taskCreateTask( char * taskName, uint32_t * pStatck,uint32_t size, uint8_t priority, taskFunctionType taskFunction );
    void taskDeleteTask(void);
    void taskGetTaskName( char * name );
    void taskSetTaskName( char * name );
    uint8_t taskGetTaskPriority(void);
    void taskSetTaskPriority(uint8_t);
    taskStateType taskGetTaskState(void);
    void taskSetTaskState(taskStateType);
};   
#endif
