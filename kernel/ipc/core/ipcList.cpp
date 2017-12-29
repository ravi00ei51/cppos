#include "ipcList.h"
#include "task.h"
void memset( uint8_t * pSrc, uint8_t val, uint32_t size )
{
    while( size-- )
    {
        *pSrc++ = val;
    }
}
void ipcList::ipcListInit(void)
{
    memset( (uint8_t *)&this->ipcNodes[0], 0xFFu, MAX_IPC_NODES*sizeof(ipcNodeType) );
}

ipcNodeType * ipcList::ipcListAllocateData( void )
{
    uint8_t i;
    for( i = 0; i < MAX_IPC_NODES;i++ )
    {
        if( ( this->ipcNodes[i].taskId == 0xFFFFFFFF ) && ( this->ipcNodes[i].timeout == 0xFFFFFFFF ) )
        {
            return (&this->ipcNodes[i]);
        }
    }
    return NULL;
}
void ipcList::ipcListFreeData( ipcNodeType * pNode )
{
    pNode->taskId  = 0xFFFFFFFF;
    pNode->timeout = 0xFFFFFFFF;
}

/*
***********************************************************************************************************************
*
*
*
*
*
*
*
*
*
*
***********************************************************************************************************************
*/

BOOLEAN ipcList::ipcListInsertData( uint32_t taskId, uint32_t timeout )
{
    BOOLEAN        retVal;
    ipcNodeType  * pIpcListData;

    pIpcListData = this->ipcListAllocateData();
    if( pIpcListData != NULL )
    {
        pIpcListData->taskId  = taskId;
        pIpcListData->timeout = timeout;
        this->memberList.listInsertNodeData( (void*&)pIpcListData );
        task::setTaskState( taskId, TASK_STATE_PENDED, TASK_STATE_INVOKE_NOW );
        retVal = TRUE;
    }
    else
    {
        retVal = FALSE;
    }
    return retVal;
}

/*
***********************************************************************************************************************
*
*
*
*
*
*
*
*
*
*
***********************************************************************************************************************
*/

BOOLEAN ipcList::ipcListRemoveData( uint32_t * pTaskId )
{
    BOOLEAN        retVal;
    ipcNodeType *  pIpcListData;

    retVal = this->memberList.listRemoveNodeData( (void*&)pIpcListData );

    if( retVal == TRUE )
    {
        *pTaskId = pIpcListData->taskId;
         task::setTaskState( *pTaskId, TASK_STATE_READY, TASK_STATE_INVOKE_NOW );
    }
    else
    {
        // Do Nothing
    }
    return retVal;
}

/*
***********************************************************************************************************************
*
*
*
*
*
*
*
*
*
*
***********************************************************************************************************************
*/

void ipcList::ipcListTickFunction( void )
{
    ipcNodeType  * pPendListData;
    uint32_t       taskId;
    uint8_t        i;
    for( i = 0; i < this->memberList.listNumberOfNodes(); i++ )
    {
        this->memberList.listGetNodeData( (void*&)pPendListData, i );
        pPendListData->timeout--;
        if( pPendListData->timeout == 0 )
        {
            taskId = pPendListData->taskId;
            this->memberList.listRemoveNodeData( (void*&)pPendListData, i );
            this->ipcListFreeData( pPendListData );
            task::setTaskState( taskId, TASK_STATE_READY, TASK_STATE_INVOKE_NOW );
        }
        else
        {
            // Do Nothing
        }
    }
}

uint8_t ipcList::ipcListSize( void )
{
    uint8_t retVal;
    retVal = this->memberList.listNumberOfNodes();
    return retVal;
}
