#ifndef _H_TASk_H_
#define _H_TASH_H_

#include "basetypes.h"
#include "cortex-m3.h"
#include "list.h"

#define MAX_TASK_NAME_LENGTH (10u)

enum taskState
{
    TASK_STATE_SUSPENDED,
    TASK_STATE_PENDED,
    TASK_STATE_READY,
    TASK_STATE_WAIT,
    TASK_STATE_DELETE,    
    TASK_STATE_MAX
};

typedef enum taskState taskStateType;
typedef void(*taskFunctionType)(void);

class task:public cortex_m3_cpu
{
private:
    char                  name[MAX_TASK_NAME_LENGTH];
    uint32_t            * pStack;
    unsigned int          stackSize;
    unsigned char         priority;
    taskStateType         state;   
    taskFunctionType      pTaskFunction;
    uint32_t              taskId;
    uint32_t              delay;
    static list<task, 6>  taskStateList[TASK_STATE_MAX];

    static BOOLEAN setTaskState( uint32_t, taskStateType );
    static taskStateType getTaskState( void );
    static task * getTaskByTaskId( uint32_t taskId );

public: 
    void           taskCreateTask( char * taskName, uint32_t * pStatck,uint32_t size, uint8_t priority, taskFunctionType taskFunction );
    void           taskDeleteTask( void );
    void           taskGetTaskName( char * name );
    void           taskSetTaskName( char * name );
    uint8_t        taskGetTaskPriority( void );
    static uint8_t taskGetTaskPriority( uint32_t taskId );
    void           taskSetTaskPriority( uint8_t );
    taskStateType  taskGetTaskState(void);
    void           taskSetTaskState(taskStateType);
    static BOOLEAN taskSuspendTask( uint32_t taskId );
    static BOOLEAN taskResumeTask( uint32_t taskId );
    static BOOLEAN taskDelayTask( uint32_t taskId, uint32_t delay );
    static BOOLEAN taskPendTask( uint32_t taskId );
    static BOOLEAN taskUnpendTask( uint32_t taskId );
};   

#endif
