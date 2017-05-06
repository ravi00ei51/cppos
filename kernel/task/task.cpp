#include "task.h"

void task::taskCreateTask( char * taskName, uint32_t * pStack, uint32_t size, uint8_t priority, taskFunctionType taskFunction )
{   
    uint8_t i;
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
    this->state         = TASK_STATE_SUSPENDED;  
    this->pTaskFunction = taskFunction;       
    this->cpuPrepareForExecution(pStack, (uint32_t *)taskFunction, size);
    this->taskId        = (uint32_t)taskId;
    this->delay         = 0u;
}

void task::taskDeleteTask( void )
{
    this->state = TASK_STATE_DELETE;
}

void task::taskGetTaskName( char * name )
{
    uint8_t i;

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

void task::taskSetTaskName( char * name )
{
    uint8_t i;

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

uint8_t task::taskGetTaskPriority( void )
{
    return this->priority;
}

void task::taskSetTaskPriority( uint8_t priority )
{
    this->priority = priority;
}
uint8_t task::taskGetTaskPriority( uint32_t taskId )
{
    task * pTask;
    pTask = getTaskByTaskId( taskId );
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

task * task::getTaskByTaskId( uint32_t taskId )
{
    return (task *)taskId;
}

list<task, 6> task::taskStateList[TASK_STATE_MAX];

BOOLEAN task::setTaskState( uint32_t taskId, taskStateType targetState )
{
    taskStateType  currentState;
    BOOLEAN        retVal;
    task         * pTask;

    pTask = getTaskByTaskId( taskId );
    currentState = pTask->state;

    if( currentState == TASK_STATE_READY )
    {
        if( currentState != targetState )
        {
            taskStateList[currentState].listRemoveNodeData( pTask );
            taskStateList[targetState].listInsertNodeData( pTask );  
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
            taskStateList[currentState].listRemoveNodeData( pTask );
            taskStateList[targetState].listInsertNodeData( pTask );
            pTask->state = targetState;
            retVal = TRUE;  
        }
        else
        {
            retVal = FALSE;
        }
    }
    return retVal; 
}

BOOLEAN task::taskSuspendTask( uint32_t taskId )
{
    BOOLEAN retVal;
    retVal = setTaskState( taskId, TASK_STATE_SUSPENDED );
    return retVal;
}

BOOLEAN task::taskResumeTask( uint32_t taskId )
{
    BOOLEAN   retVal;
    task    * pTask;

    pTask = getTaskByTaskId( taskId );

    if( pTask->state == TASK_STATE_SUSPENDED )
    {
        retVal = setTaskState( taskId, TASK_STATE_READY );
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
    retVal = setTaskState( taskId, TASK_STATE_PENDED );
    return retVal;
}

BOOLEAN task::taskUnpendTask( uint32_t taskId )
{
    BOOLEAN   retVal;
    task    * pTask;

    pTask = getTaskByTaskId( taskId );

    if( pTask->state == TASK_STATE_PENDED )
    {
        retVal = setTaskState( taskId, TASK_STATE_READY );
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
    
    pTask        = getTaskByTaskId( taskId );
    pTask->delay = delayInMs;         
    retVal       = setTaskState( taskId, TASK_STATE_WAIT );

    return retVal;
}

