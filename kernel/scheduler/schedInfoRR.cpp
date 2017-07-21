#include<schedInfo.h>
#include<task.h>

static uint8_t schedInstance[sizeof(sched<SCHED_TYPE_RR>)];
uint8_t        schedInit;

template<> sched<SCHED_TYPE_RR> * sched<SCHED_TYPE_RR>::schedGetSchedInstance( void )
{
    sched<SCHED_TYPE_RR> * pSched;
    pSched = ( sched * )&( schedInstance[0] );
    if( schedInit != TRUE )
    {
        pSched->schedulerList.listInit();
        pSched->taskId = 0u;
        schedInit = TRUE;
    }
    return( pSched );
}

template<> BOOLEAN sched<SCHED_TYPE_RR>::schedInitSchedInfo( schedInfo * pSchedInfo )
{
   pSchedInfo->taskId   = 0u;
   pSchedInfo->priority = 0u; 
   return TRUE;
}

template<> BOOLEAN sched<SCHED_TYPE_RR>::schedUpdateSchedInfo( uint32_t taskId, schedInfo * pSchedInfo )
{
    pSchedInfo->taskId   = taskId;
    pSchedInfo->priority = task::taskGetTaskPriority(taskId);  
    return TRUE;
}

template<> BOOLEAN sched<SCHED_TYPE_RR>::schedInsertSchedInfo( schedInfo * pSchedInfo )
{
    volatile BOOLEAN retVal; 
    retVal = this->schedulerList.listInsertNodeData( pSchedInfo );
    return retVal;
}

template<> BOOLEAN sched<SCHED_TYPE_RR>::schedRemoveSchedInfo( schedInfo * pSchedInfo )
{
    uint8_t pos;
    BOOLEAN retVal;
    if( pSchedInfo != NULL )
    {
        pos = this->schedulerList.listGetNodePosition( pSchedInfo );
        if( pos != NODE_NOT_FOUND )
        {
            this->schedulerList.listRemoveNodeData( pSchedInfo, pos );
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

template<> uint32_t sched<SCHED_TYPE_RR>::schedGetNextTaskForExecution( void )
{
    schedInfo  * pSchedInfo;
    uint32_t     taskId;   
    this->schedulerList.listGetFirstNodeData( pSchedInfo );
    this->taskId = pSchedInfo->taskId;
    taskId = pSchedInfo->taskId;
    this->schedulerList.listRemoveFirstNodeData( pSchedInfo );
    this->schedulerList.listInsertLastNodeData( pSchedInfo );
   
    return (taskId);
}

template<> uint32_t sched<SCHED_TYPE_RR>::schedGetCurrentTaskForExecution( void )
{
    return (this->taskId);
}

template<> void sched<SCHED_TYPE_RR>::schedExecuteScheduler( void )
{
    volatile uint32_t currentTaskId;
    volatile uint32_t nextTaskId;
    task *            pCurrentTask;
    task *            pNextTask;
    sched<SCHED_TYPE_RR> * pSched;

    asm("cpsid i");

    nextTaskId = 0u;

    pSched        = sched<SCHED_TYPE_RR>::schedGetSchedInstance();
    currentTaskId = pSched->taskId;
    
    nextTaskId = pSched->schedGetNextTaskForExecution();
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

//template<SCHED_TYPE_RR> class sched;
