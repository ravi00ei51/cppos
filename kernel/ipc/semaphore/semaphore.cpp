#include "semaphore.h"

semaphore::semaphore( void )
{
}

void semaphore::semAccquire( uint32_t timeout )
{
    BOOLEAN val;
    shecd::schedLock();
    val = this->semLock.tryLock();
    this->semList.insert(currentTaskId);
    sched::schedUnlock();
    task::taskPend(currentTaskId);
}

void semaphore::semRelease( void )
{
    semResourceLock.lock();
    this->semLock.unlock();
    semResourceLock.unlock();
}   
