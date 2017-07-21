#include "semaphore.h"

semaphore::semaphore( void )
{
}

void semaphore::semAccquire( uint32_t timeout )
{
    BOOLEAN val;
    val = this->semLock.unblockingLock();
    if( val == TRUE )
    {
        this->semOwner = currentTaskId;
    }
    else
    {
        this->semList.insert(currentTaskId);
        task::taskPend(currentTaskId);
    }
}

void semaphore::semRelease( void )
{
}   
