#include "task.h"

task::task(void)
{
}

task::~task(void)
{
}

void task::taskCreateTask( char * taskName, unsigned int * stack, unsigned int size, unsigned int priority )
{
    unsigned char i;
    if( stack != NULL )
    {
        if( taskName != NULL )
        {
            for( i = 0; i < MAX_TASK_NAME_LENGTH;i++ )
            {
                if( taskName[i] != '\0' )
                {
                    this->taskName[i] = taskName[i];
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            this->taskName[0] = '\0'; 
        }
        this->stackPointer = stack;
        this->stackSize    = size;
        this->priority     = priority;
        this->state        = TASK_STATE_SUSPENDED;  
    }    
}


