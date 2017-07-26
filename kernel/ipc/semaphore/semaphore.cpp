#include "semaphore.h"
#include "task.h"
#include "schedInfo.h"


semaphore::semaphore( void )
{
    uint8_t i;
    this->numberOfPendingTasks = 0u;
    this->semLock.init();
    for( i = 0;i < 6u; i++ )
        this->semResource[i].taskId = 0xFFFFFFFFu;
}

void semaphore::semAccquire( uint32_t timeout )
{
    BOOLEAN     val;
    uint32_t    taskId;
    sched<SCHEDULER_TYPE> * pSched;

    pSched = sched<SCHEDULER_TYPE>::schedGetSchedInstance();
    
    taskId = pSched->schedGetCurrentTaskForExecution();

    val  = this->semLock.tryLock();

    if( val == TRUE )
    {
        this->semOwner = taskId;
    }
    else
    {
        this->semListInsert( taskId, timeout );
        task::setTaskState( taskId, TASK_STATE_PENDED, TASK_STATE_INVOKE_NOW );
    }
}

void semaphore::semRelease( void )
{
    BOOLEAN val;
    semData_t * pData = NULL;

    this->semLock.unlock();
    if( this->numberOfPendingTasks != 0u )
    {
        val  = this->semLock.tryLock();

        if( val == TRUE )
        {
            this->semList.listGetFirstNodeData(pData);
            this->semOwner = pData->taskId;
            this->semList.listRemoveFirstNodeData(pData);
            this->numberOfPendingTasks--;
            task::setTaskState( this->semOwner, TASK_STATE_READY, TASK_STATE_INVOKE_NOW );
        }
    }
    else
    {
        this->semOwner = 0xFFFFFFFFu;
    } 
    
}

void semaphore::semListUpdate( semaphore * semObj )
{
    uint8_t     i;
    BOOLEAN     val;
    semData_t * pData;
    if( semObj->numberOfPendingTasks != 0u )
    {
        val  = semObj->semLock.tryLock();

        if( val == TRUE )
        {
            semObj->semList.listGetFirstNodeData(pData);
            semObj->semOwner = pData->taskId;
            semObj->semList.listRemoveFirstNodeData(pData);
            semObj->numberOfPendingTasks--;
        }

        for( i = 1; i <= semObj->numberOfPendingTasks; i++ )
        {
            semObj->semList.listGetNodeData( pData, i ); 
            pData->timeout--;
 
           if( pData->timeout <= 0u )
            {
                semObj->semListRemove( pData->taskId );
                semObj->numberOfPendingTasks--;
                task::setTaskState( pData->taskId, TASK_STATE_READY, TASK_STATE_INVOKE_LATER );           
            }
        }
        task::setTaskState( semObj->semOwner, TASK_STATE_READY, TASK_STATE_INVOKE_LATER );
    }
}

semData_t * semaphore::semAllocateData( void )
{
    uint8_t i;
    BOOLEAN dataFound = FALSE;
    semData_t * pData;
    for( i = 0u; i < 6u; i++ )
    {
         if( this->semResource[i].taskId == 0xFFFFFFFF ) 
         {
             pData = &(this->semResource[i]);
             dataFound = TRUE;
             i = 7u;
         }    
    }

    if( dataFound == FALSE )
    {
        pData = NULL;
    }
    return pData;
}   

void semaphore::semFreeData( semData_t * pData )
{
    uint8_t     i;
    semData_t * pTemp;
    
    for( i = 0u; i < 6u; i++ )
    {
        pTemp = &this->semResource[i];

        if( pTemp == pData )
        {
            pData->taskId  = 0xFFFFFFFFu;
            pData->timeout = 0xFFFFFFFFu;
            i = 7u;
        }
    }
}

BOOLEAN semaphore::semListInsert( uint32_t taskId, uint32_t timeout )
{
    semData_t * pData = NULL;
    BOOLEAN     val;

    pData = this->semAllocateData();

    if( pData != NULL )
    {
        pData->taskId  = taskId;
        pData->timeout = timeout;
        val = this->semList.listInsertNodeData( pData );
        if( val == TRUE )
            this->numberOfPendingTasks++;
    }
    else
    {
        val = FALSE;
    }
    return val;    
}

BOOLEAN semaphore::semListRemove( uint32_t taskId )
{
    BOOLEAN val = FALSE;
    uint8_t i;
    semData_t * pData;
    for( i = 0u; i < 6u; i++ )
    {
        if( this->semResource[i].taskId == taskId )
        {
            pData = &this->semResource[i];
            this->semList.listRemoveNodeData( pData );
            this->semFreeData( pData );
            this->numberOfPendingTasks--;
            val = TRUE;
        }
    }
    return val;
}
