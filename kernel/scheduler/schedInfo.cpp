#include<schedInfo.h>
#include<task.h>
BOOLEAN sched::schedUpdateSchedInfo( uint32_t taskId, schedInfo * pSchedInfo )
{
    pSchedInfo->taskId   = taskId;
    pSchedInfo->priority = task::taskGetTaskPriority(taskId);  
    return TRUE;
}

BOOLEAN sched::schedInsertSchedInfo( schedInfo * pSchedInfo )
{
    this->schedulerList.listInsertNodeData( pSchedInfo );
    return TRUE;
}

BOOLEAN sched::schedRemoveSchedInfo( schedInfo * pSchedInfo )
{
    this->schedulerList.listRemoveNodeData( pSchedInfo );
    return TRUE;
}

uint32_t sched::schedGetTaskForExecution( void )
{
    schedInfo  * pSchedInfo;

    this->schedulerList.listGetFirstNodeData( pSchedInfo );
    this->schedulerList.listRemoveNodeData( pSchedInfo );
    this->schedulerList.listInsertLastNodeData( pSchedInfo );   

    return pSchedInfo->taskId;
}
