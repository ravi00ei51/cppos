#include "semaphore.h"
#include "schedInfo.h"

semaphore::semaphore( void )
{
    this->ipcListInit();
    this->semLock.init();
}

void semaphore::semAccquire( uint32_t timeout )
{
    sched<SCHEDULER_TYPE> * pSched;
    uint32_t                taskId;
    void *                  pData = NULL;
    pSched = sched<SCHEDULER_TYPE>::schedGetSchedInstance();
    taskId = pSched->schedGetCurrentTaskForExecution();

    (void)this->ipcCapture( taskId, timeout, (void*&)pData );
}

void semaphore::semRelease( void )
{
    (void)this->ipcRelease();
}

BOOLEAN semaphore::ipcAccquireResource( void )
{
    BOOLEAN val;

    val    = this->semLock.tryLock();

    return val;
}


BOOLEAN semaphore::ipcAssignResourceToTask( uint32_t taskId, void *& pData )
{
    this->owner = taskId;
    if( pData == NULL )
    {
    }
    else
    {
    }
    return TRUE;
}

BOOLEAN semaphore::ipcReleaseResource( void )
{
    this->semLock.unlock();
    return TRUE;
}

void semaphore::semListUpdate( semaphore * semObj )
{
    semObj->ipcListTickFunction();
}
