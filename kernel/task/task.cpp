#include "task.h"
#define NULL ((void*)0)
/*task::task(void)
{
}

task::~task(void)
{
}*/

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

void task::taskSetTaskState( taskStateType state )
{
    this->state = state;
}

taskStateType task::taskGetTaskState( void )
{
    return this->state;
}

