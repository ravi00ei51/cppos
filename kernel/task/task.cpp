#include "task.h"
/**
*********************************************************************************************************************************
* Name - taskCreate()
*
* Description - Function to create task for given task object. Function initializes all member variables of task object to their
*               initial value. Also it assigns the priority, stack, stack size and the function which need to be executed as 
*               part of the task execution. Function also initializes the CPU registers for the task and puts task into ready 
*               queue
*
* Param       - taskName: name of the task.
*               pStack  : pointer to a buffer which acts as stack for the task under execution.
*               size    : size of the stack buffer
*               priority: priority of the task
*               taskFunc: Function pointer to the task which needs to be executed
*
********************************************************************************************************************************/

void task::taskCreateTask( char * taskName, uint32_t * pStack, uint32_t size, uint8_t priority, taskFunctionType taskFunction )
{   
    uint8_t i;
    if( pStack != NULL )
    {
        if( ( priority > TASK_MINIMUM_PRIORITY ) && ( priority < TASK_MAXIMUM_PRIORITY ) )
        {
            if( taskFunction != NULL )
            {
                if( taskName != NULL )
                {
                    for( i = 0; i < 50;i++ )
                    {
                        if( taskName[i] != '\0' )
                        {
                            this->name[i] = taskName[i];
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    this->name[0] = '\0'; 
                }
                this->pStack        = pStack;
                this->stackSize     = size;
                this->priority      = priority;
                this->state         = TASK_STATE_CREATED;  
                this->pTaskFunction = taskFunction;       
                this->cpuPrepareForExecution(pStack, (uint32_t *)taskFunction, size);
                this->taskId        = (uint32_t)this;
                this->delay         = 0u;

                sched<SCHEDULER_TYPE>::schedInitSchedInfo( &(this->schedData) ); 
                setTaskState( this->taskId, TASK_STATE_READY, TASK_STATE_INVOKE_LATER );
            }
        }
    }
}

/**
*********************************************************************************************************************************
* Name - taskDelete
*
* Description - Function to delete an existing task.Function to create task for given task object. 
*
* Param       - taskName: name of the task.
*
********************************************************************************************************************************/
void task::taskDeleteTask( void )
{
    this->state = TASK_STATE_DELETE;
}

void task::taskGetTaskName( char * name )
{
    uint8_t i;
    if( name != NULL )
    {
        for( i = 0; i < MAX_TASK_NAME_LENGTH;i++ )
        {
            if( this->name[i] != '\0' )
            {
                name[i] = this->name[i];
            }
            else
            {
                break;
            }
        }
    }
}

void task::taskSetTaskName( char * name )
{
    uint8_t i;
    if( name != NULL )
    {
        for( i = 0; i < MAX_TASK_NAME_LENGTH;i++ )
        {
            if( name[i] != '\0' )
            {
                this->name[i] = name[i];
            }
            else
            {
                break;
            }
        }
    }
}

BOOLEAN task::taskSetTaskPriority( uint32_t taskId, uint8_t priority )
{
    task                  * pTask;
    sched<SCHEDULER_TYPE> * pSched;
    BOOLEAN                 val;
    schedInfo             * pSchedInfo;
    pTask = (task *)taskId;

    if( pTask != NULL )
    {
        asm("cpsid i");
        pTask->priority = priority;
        if( pTask->state == TASK_STATE_READY )
        {  
            pSched = sched<SCHEDULER_TYPE>::schedGetSchedInstance();
            
            if( pSched != NULL )
            {
                pSchedInfo = pTask->taskGetSchedInfo();
                pSched->schedUpdateSchedInfo( taskId, pSchedInfo );
                val = pSched->schedRemoveSchedInfo( pSchedInfo );

                if( val == TRUE )
                {
                    val = pSched->schedInsertSchedInfo( pSchedInfo );  
                } 
            }
            else
            {
                val = FALSE;
            }
        }
        else
        {
            val = TRUE;
        }
        asm("cpsie i");  
        asm("SVC #0");
    }
    else
    {
        val = FALSE;
    }
    return val;
}
uint8_t task::taskGetTaskPriority( uint32_t taskId )
{
    task * pTask;
    pTask = (task *)taskId;
    return pTask->priority;
}
void task::taskSetTaskState( taskStateType state )
{
    this->state = state;
}

taskStateType task::taskGetTaskState( void )
{
    return this->state;
}
volatile uint32_t tempTaskId;
task * task::getTaskByTaskId( uint32_t taskId )
{
    volatile task * pTask;
    pTask = (task *)taskId; 
    tempTaskId = taskId;
    return (task *)pTask;
}

schedInfo * task::taskGetSchedInfo( void )
{
    return ( &(this->schedData) );
}

list<task, 6> task::taskStateList[TASK_STATE_MAX];

BOOLEAN task::setTaskState( uint32_t taskId, taskStateType targetState, taskStateInvocationType invoke )
{
    taskStateType  currentState;
    BOOLEAN        retVal;
    task         * pTask;
    task         * pTemp;
    sched<SCHEDULER_TYPE>        * pSched;
    schedInfo    * pSchedInfo;
    uint8_t        pos;
    asm("cpsid i");
    pTask        = getTaskByTaskId( taskId );
    pTemp        = pTask;
    currentState = pTask->state;

    pSched     = sched<SCHEDULER_TYPE>::schedGetSchedInstance();
    pSchedInfo = pTask->taskGetSchedInfo();

    pSched->schedUpdateSchedInfo( taskId, pSchedInfo );
     
    if( currentState == TASK_STATE_CREATED )
    {
        taskStateList[targetState].listInsertNodeData( pTask );
        pSched->schedInsertSchedInfo( pSchedInfo );
        pTask->state = targetState;
        retVal = TRUE;
    }
    else if( currentState == TASK_STATE_READY )
    {
        if( currentState != targetState )
        {
            pos = taskStateList[currentState].listGetNodePosition( pTask ); 
            taskStateList[currentState].listRemoveNodeData( pTemp, pos );
            taskStateList[targetState].listInsertNodeData( pTask );  
            pSched->schedRemoveSchedInfo( pSchedInfo );
            pTask->state = targetState;
            retVal = TRUE;
        }
        else
        {
            retVal = TRUE;
        }
    } 
    else
    {
        if( targetState == TASK_STATE_READY )
        {
            pos = taskStateList[currentState].listGetNodePosition( pTask );
            taskStateList[currentState].listRemoveNodeData( pTemp, pos );
            taskStateList[targetState].listInsertNodeData( pTask );
            pSched->schedInsertSchedInfo( pSchedInfo );
            pTask->state = targetState;
            retVal = TRUE;  
        }
        else
        {
            retVal = FALSE;
        }
    }
    asm("cpsie i");
    if( invoke == TASK_STATE_INVOKE_NOW )
    {
        asm("SVC #0");
    }
    return retVal; 
}

BOOLEAN task::taskSuspendTask( uint32_t taskId )
{
    BOOLEAN retVal;
    retVal = setTaskState( taskId, TASK_STATE_SUSPENDED, TASK_STATE_INVOKE_NOW );
    return retVal;
}

BOOLEAN task::taskResumeTask( uint32_t taskId )
{
    BOOLEAN   retVal;
    task    * pTask;

    pTask = getTaskByTaskId( taskId );

    if( pTask->state == TASK_STATE_SUSPENDED )
    {
        retVal = setTaskState( taskId, TASK_STATE_READY, TASK_STATE_INVOKE_NOW );
    }
    else
    {
        retVal = FALSE;
    }
    return retVal;
}

BOOLEAN task::taskPendTask( uint32_t taskId )
{
    BOOLEAN retVal;
    retVal = setTaskState( taskId, TASK_STATE_PENDED, TASK_STATE_INVOKE_NOW );
    return retVal;
}

BOOLEAN task::taskUnpendTask( uint32_t taskId )
{
    BOOLEAN   retVal;
    task    * pTask;

    pTask = getTaskByTaskId( taskId );

    if( pTask->state == TASK_STATE_PENDED )
    {
        retVal = setTaskState( taskId, TASK_STATE_READY, TASK_STATE_INVOKE_NOW );
    }
    else
    {
        retVal = FALSE;
    }
    return retVal;
}


BOOLEAN task::taskDelayTask( uint32_t taskId, uint32_t delayInMs )
{
    BOOLEAN retVal;
    task * pTask;
    
    pTask        = (task*)taskId;//getTaskByTaskId( taskId );
    pTask->delay = delayInMs;         
    retVal       = setTaskState( taskId, TASK_STATE_WAIT, TASK_STATE_INVOKE_NOW );

    return retVal;
}

