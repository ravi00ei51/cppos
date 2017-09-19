#include "events.h"
#include "task.h"
#include "schedInfo.h"

events::events( void )
{
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_EVENT_NODES; i++ )
    {
        this->eventNodes[i].free = TRUE;
    }
}

events::~events( void )
{

}
eventNodeType * events::eventAllocateEventNode( void )
{
    uint8_t i;
    eventNodeType * pNode =  NULL;
    for( i = 0; i < MAX_NUMBER_OF_EVENT_NODES; i++ )
    {
        if( this->eventNodes[i].free == TRUE )
        {
            this->eventNodes[i].free = FALSE;
            pNode = &(this->eventNodes[i]);
            break;
        }   
    }
    return pNode;
}

void events::eventFreeEventNode( eventNodeType * pNode )
{
    if( pNode != NULL )
    {
        pNode->free = TRUE;
    }
}

void events::eventSend( uint8_t maskId )
{
    uint32_t mask = 0u;
    uint32_t taskId = 0xFFFFFFFFu;  
    uint32_t i = 0u;
    eventNodeType * pNode = NULL;
    if( this->eventPendList.listNumberOfNodes() > 0u )
    {
        sched<SCHEDULER_TYPE>::schedLock();
        mask = ( 1u << maskId );
        for( i = 1; i <= this->eventPendList.listNumberOfNodes(); i++ )
        {
            this->eventPendList.listGetNodeData( pNode, 1u );
            if( pNode->mask & mask )
            {
                this->eventPendList.listRemoveNodeData( pNode );
                taskId = pNode->taskId;
                this->eventFreeEventNode( pNode );
                task::setTaskState( taskId, TASK_STATE_READY, TASK_STATE_INVOKE_LATER ); 
            }
        }
        sched<SCHEDULER_TYPE>::schedUnlock();
        asm("SVC #0");
    }
    else
    {
    }

}

void events::eventTaskReceive( uint32_t taskId, uint8_t mask, uint32_t timeout )
{
    task          * pTask = NULL;
    eventNodeType * pNode = NULL;
    sched<SCHEDULER_TYPE>::schedLock();
    pTask = (task *)taskId;
    if( pTask != NULL )
    {
        pNode = this->eventAllocateEventNode();
        if( pNode != NULL )
        {
            mask           = (uint8_t)(1 << mask);
            pNode->taskId  = taskId;
            pNode->mask    = mask;
            pNode->timeout = timeout;
            this->eventPendList.listInsertNodeData( pNode );
            task::setTaskState( pNode->taskId, TASK_STATE_PENDED, TASK_STATE_INVOKE_LATER );
        } 
    }
    else
    {
    }
    sched<SCHEDULER_TYPE>::schedUnlock();
    asm("SVC #0");
}
