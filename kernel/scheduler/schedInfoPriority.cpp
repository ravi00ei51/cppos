#include<schedInfo.h>
#include<task.h>

static uint8_t schedInstance[sizeof(sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>)];
//static sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> schedInstance
uint8_t        schedInit1;

template<> sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedGetSchedInstance( void )
{
    sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * pSched;
    pSched = ( sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * )&( schedInstance[0] );
    if( schedInit1 != TRUE )
    {
        memset( (uint8_t *)&schedInstance[0], 0x00u, sizeof(sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>) );
        pSched->schedulerList.listInit();
        pSched->taskId = 0u;
        schedInit1 = TRUE;
    }
    return( pSched );
}

template<> BOOLEAN sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedInitSchedInfo( schedInfo * pSchedInfo )
{
   pSchedInfo->taskId   = 0u;
   pSchedInfo->priority = 0u;
   return TRUE;
}

template<> BOOLEAN sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedUpdateSchedInfo( uint32_t taskId, schedInfo * pSchedInfo )
{
    pSchedInfo->taskId   = taskId;
    pSchedInfo->priority = task::taskGetTaskPriority(taskId);
    return TRUE;
}

template<> BOOLEAN sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedInsertSchedInfo( schedInfo * pSchedInfo )
{
    volatile BOOLEAN retVal;
    volatile uint8_t     i;
    schedInfo * pTempSchedInfo;
    if( pSchedInfo != NULL )
    {
        for( i = 0; ( pTempSchedInfo != NULL ); i ++ )
        {
            retVal = this->schedulerList.listGetNodeData( (void*&)pTempSchedInfo, (uint8_t)(i+1) );

            if( ( retVal == TRUE ) && ( pTempSchedInfo != NULL ) )
            {
                if( pSchedInfo->priority < pTempSchedInfo->priority )
                {
                    retVal = this->schedulerList.listInsertNodeData( (void*&)pSchedInfo, (uint8_t)(i+1) );
                    break;
                }
            }
        }
        if( pTempSchedInfo == NULL )
        {
            this->schedulerList.listInsertLastNodeData( (void*&)pSchedInfo );
        }
    }
    return retVal;
}

template<> BOOLEAN sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedRemoveSchedInfo( schedInfo * pSchedInfo )
{
    volatile uint8_t pos;
    BOOLEAN retVal;
    if( pSchedInfo != NULL )
    {
        pos = this->schedulerList.listGetNodePosition( (void*&)pSchedInfo );
        if( pos != NODE_NOT_FOUND )
        {
            this->schedulerList.listRemoveNodeData( (void*&)pSchedInfo, pos );
            retVal = TRUE;
        }
        else
        {
            retVal = FALSE;
        }
    }
    else
    {
        retVal = FALSE;
    }
    return retVal;
}

template<> uint32_t sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedGetNextTaskForExecution( void )
{
    schedInfo  * pSchedInfo;

    this->schedulerList.listGetFirstNodeData( (void*&)pSchedInfo );

    return (pSchedInfo->taskId);
}

template<> uint32_t sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedGetCurrentTaskForExecution( void )
{
    return (this->taskId);
}

template<> void sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedLock( void )
{
    sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * pSched;
    pSched = (sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> *)schedInstance[0];
    pSched->lock.tryLock();
}

template<> void sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedUnlock( void )
{
    sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * pSched;
    pSched = (sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> *)&schedInstance[0];
    pSched->lock.unlock();
}

template<> BOOLEAN sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::isSchedLocked( void )
{
    sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * pSched;
    pSched        = (sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> *)&schedInstance[0];

    return pSched->lock.status();
}

template<> void sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedExecuteScheduler( void )
{
    volatile uint32_t currentTaskId;
    volatile uint32_t nextTaskId;
    task *            pCurrentTask;
    task *            pNextTask;
    BOOLEAN           lockStatus;
    sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * pSched;

    nextTaskId = 0u;

    pSched        = sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedGetSchedInstance();
    lockStatus    = pSched->isSchedLocked();
    if( lockStatus == FALSE )
    {
        asm("cpsid i");
        currentTaskId = pSched->taskId;
        nextTaskId = pSched->schedGetNextTaskForExecution();
        pSched->taskId = nextTaskId;
        if( currentTaskId != nextTaskId )
        {
            pNextTask    = task::getTaskByTaskId( nextTaskId );
            pCurrentTask = task::getTaskByTaskId( currentTaskId );

            if( currentTaskId != 0 )
                pCurrentTask->cpuGetContext();
            asm("cpsie i");
            pNextTask->cpuSetContext();
        }
        asm("cpsie i");
    }
}
