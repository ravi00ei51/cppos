#include<schedInfo.h>
#include<task.h>

static uint8_t schedInstance[sizeof(sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>)];
uint8_t        schedInit1;

template<> sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedGetSchedInstance( void )
{
    sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION> * pSched;
    pSched = ( sched * )&( schedInstance[0] );
    if( schedInit1 != TRUE )
    {
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
    uint8_t     i;
    schedInfo * pTempSchedInfo;
    if( pSchedInfo != NULL )
    {
        for( i = 0; ( pTempSchedInfo != NULL ); i ++ )
        {
            retVal = this->schedulerList.listGetNodeData( pTempSchedInfo, i );

            if( ( retVal == TRUE ) && ( pTempSchedInfo != NULL ) )
            {
                if( pSchedInfo->priority < pTempSchedInfo->priority )
                {
                    retVal = this->schedulerList.listInsertNodeData( pSchedInfo, i ); 
                }
            }
        }
        if( pTempSchedInfo == NULL )
        {
            this->schedulerList.listInsertLastNodeData( pSchedInfo );
        }     
    }
    return retVal;
}

template<> BOOLEAN sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedRemoveSchedInfo( schedInfo * pSchedInfo )
{
    uint8_t pos;

    pos = this->schedulerList.listGetNodePosition( pSchedInfo );

    this->schedulerList.listRemoveNodeData( pSchedInfo, pos );

    return TRUE;
}

template<> uint32_t sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedGetNextTaskForExecution( void )
{
    schedInfo  * pSchedInfo;
    uint32_t     taskId;   

    this->schedulerList.listGetFirstNodeData( pSchedInfo );
    this->taskId = pSchedInfo->taskId;
    taskId = pSchedInfo->taskId; 
    return (taskId);
}

template<> uint32_t sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>::schedGetCurrentTaskForExecution( void )
{
    return (this->taskId);
}


