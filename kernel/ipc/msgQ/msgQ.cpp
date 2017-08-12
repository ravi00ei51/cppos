#include "msgQ.h"
#include "task.h"
#include "schedInfo.h"

static void memcpy ( uint8_t * dst, uint8_t * src, uint16_t size )
{
    while( size-- )
    {
        *dst++ = *src++;
    }
}

msgQ::msgQ(void)
{
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_QUEUE_NODES;i++ )
    {
        this->queueNode[i].size = 0u;
    }
    for( i = 0; i < MAX_NUMBER_OF_QUEUE_NODES;i++ )
    {
        this->pendNode[i].taskId = 0xFFFFFFFFu;
    }
    this->queueNodeCount = 0;
    this->pendQueueCount = 0;
}

msgQ::~msgQ(void)
{

}

queueNodeType * msgQ::msgQAllocateQueueNode( void )
{
    queueNodeType * pNode = NULL;
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_QUEUE_NODES;i++ )
    {
        if( this->queueNode[i].size == 0x0 )
        {
            pNode = &this->queueNode[i];
            break;
        }
    }
    return pNode;
}

void msgQ::msgQFreeQueueNode( queueNodeType * pNode )
{
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_QUEUE_NODES; i++ )
    {
        if( &(this->queueNode[i]) == pNode )
        {
            pNode->size = 0u;
            break;
        }
    }
}

pendNodeType * msgQ::msgQAllocatePendNode( void )
{
    pendNodeType * pNode = NULL;
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_PEND_NODES; i++ )
    {
        if( this->pendNode[i].taskId == 0xFFFFFFFF )
        {
            pNode = &this->pendNode[i];
            break;
        }
    }
    return pNode;
}

void msgQ::msgQFreePendNode( pendNodeType * pNode )
{
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_PEND_NODES; i++ )
    {
        if( &(this->pendNode[i]) == pNode )
        {
            pNode->taskId = 0xFFFFFFFF;
            break;
        }
    }
}

void msgQ::msgQPutNodeToQueue( uint8_t * pBuffer, uint8_t size )
{
    queueNodeType * pNode;
    if( ( pBuffer != NULL ) && ( size < MAX_BUFFER_SIZE ) )
    {
        pNode = msgQAllocateQueueNode();
        if( pNode != NULL )
        {
            pNode->size = size;
            memcpy( pNode->buffer, pBuffer, size );
            this->queue.listInsertNodeData( pNode );
            this->queueNodeCount++;
        }
    }
}

uint8_t msgQ::msgQGetNodeFromQueue( uint8_t * pBuffer )
{
    queueNodeType   qNode;
    queueNodeType * pNode = &qNode;

    uint8_t size = 0u;
    if( pBuffer != NULL )
    {
        this->queue.listRemoveNodeData( pNode, 1u );
        
        if( pNode != NULL )
        {
            memcpy( pBuffer, pNode->buffer, pNode->size );
            size = pNode->size;
            this->msgQFreeQueueNode( pNode ); 
            pNode = NULL;
            this->queueNodeCount--;
        } 
    }
    return size;
}

void msgQ::msgQPutNodeToPendList(queuePendListType listType, uint32_t taskId, uint32_t timeout, uint8_t * pBuffer, uint8_t size )
{
    pendNodeType * pNode;
    pNode = this->msgQAllocatePendNode();
    if( pNode != NULL )
    {
        pNode->taskId  = taskId;
        pNode->timeout = timeout;
        pNode->pBuffer = pBuffer;
        pNode->size    = size;
        this->pendList[listType].listInsertNodeData( pNode );
        this->pendQueueCount++;
        task::setTaskState( taskId, TASK_STATE_PENDED, TASK_STATE_INVOKE_LATER ); 
    }
}

uint8_t msgQ::msgQGetNodeFromPendList( queuePendListType listType, uint8_t * pBuffer, uint8_t size )
{
    pendNodeType * pNode = NULL;
    uint32_t taskId = 0xFFFFFFFF;
    taskStateType   state = TASK_STATE_DELETE; 
    task           *pTask;
    uint8_t         val;
    while( state == TASK_STATE_DELETE )
    {   
        this->pendList[listType].listGetFirstNodeData( pNode );
        if( pNode != NULL )
        {
            pTask = ( task * ) ( pNode->taskId );
            state = pTask->taskGetTaskState();
            if( state == TASK_STATE_DELETE )
            {
                this->pendList[listType].listRemoveFirstNodeData( pNode );
                this->msgQFreePendNode( pNode );
                this->pendQueueCount--;
            }
        }
        else
        {
            break;
        }
    }  

    if( pNode != NULL ) 
    {  
        taskId  = pNode->taskId;
        if( pNode->size < size )
        {
            val = pNode->size;
        }
        else
        {
            val = size;
        }
        if( listType == QUEUE_PEND_LIST_RECEIVE )
        {
            memcpy( pNode->pBuffer, pBuffer, val );
        }
        else
        {
            memcpy( pBuffer, pNode->pBuffer, val );
        }
        this->pendList[listType].listRemoveFirstNodeData( pNode );
        this->msgQFreePendNode( pNode ); 
        this->pendQueueCount--;
        task::setTaskState( taskId, TASK_STATE_READY, TASK_STATE_INVOKE_LATER );
    }
    else
    {
        val = 0u;
    }
    return val;
}

void msgQ::msgQSend( uint8_t * buffer, uint8_t size, uint32_t timeout )
{
    uint32_t  taskId;
    sched<SCHEDULER_TYPE> * pSched;
   
    pSched = sched<SCHEDULER_TYPE>::schedGetSchedInstance();

    taskId = pSched->schedGetCurrentTaskForExecution();

    /* Following cases could occur.
       1. if the queue is empty and a task is pend on receiveQ then give the message directly to receive task and remove the task from receive pendQ.
       2. if queue is empty and no receive task is waiting then add it to the msgQ.
       3. if queue is full then pend the task on pendQ
    */
           
    if( buffer != NULL )
    {
        sched<SCHEDULER_TYPE>::schedLock();
        if( this->queueNodeCount < MAX_NUMBER_OF_PEND_NODES )
        {
            if( size <= MAX_BUFFER_SIZE )
            {
                if( this->queueNodeCount == 0 )
                {
                    if( pendList[QUEUE_PEND_LIST_RECEIVE].listNumberOfNodes() > 0 )
                    {
                        // copy the message to target buffer  
                        this->msgQGetNodeFromPendList( QUEUE_PEND_LIST_RECEIVE, buffer, size );
                    }
                    else
                    {
                        this->msgQPutNodeToQueue( buffer, size );
                    }
                }
                else
                {
                    this->msgQPutNodeToQueue( buffer, size );
                }
            }
        }
        else
        {
            pSched = sched<SCHEDULER_TYPE>::schedGetSchedInstance();
            taskId = pSched->schedGetCurrentTaskForExecution();
            this->msgQPutNodeToPendList( QUEUE_PEND_LIST_SEND, taskId, timeout, buffer, size );           
        }
        sched<SCHEDULER_TYPE>::schedUnlock();
        asm("SVC #0");
    }
}

void msgQ::msgQReceive( uint8_t * buffer, uint8_t size, uint32_t timeout )
{
    uint8_t * pBuffer = NULL;
    uint32_t  taskId;
    uint8_t   tSize;
    sched<SCHEDULER_TYPE> * pSched;
    
    /* Following cases could occur.
       1. if the queue is empty then pend the task to receive pendQ.
       2. if queue is full or not empty then give top node message from queue to the 
          receiving task and insert a node from send pendQ.
    */

    if( buffer != NULL )
    {
        sched<SCHEDULER_TYPE>::schedLock();
        if( this->queueNodeCount > 0u )
        {
            this->msgQGetNodeFromQueue( buffer );
            if( this->pendQueueCount > 0 )
            {
                tSize = this->msgQGetNodeFromPendList( QUEUE_PEND_LIST_SEND, pBuffer, size );
                if( tSize < size )
                {
                    this->msgQPutNodeToQueue( pBuffer, tSize );
                } 
                else
                {
                    this->msgQPutNodeToQueue( pBuffer, size );
                }
            }  
            else
            {
            }
        }
        else
        {
            pSched = sched<SCHEDULER_TYPE>::schedGetSchedInstance();
            taskId = pSched->schedGetCurrentTaskForExecution();
            this->msgQPutNodeToPendList( QUEUE_PEND_LIST_RECEIVE, taskId, timeout, buffer, size );        
        }
    }
    sched<SCHEDULER_TYPE>::schedUnlock();
    asm("SVC #0"); 
}

