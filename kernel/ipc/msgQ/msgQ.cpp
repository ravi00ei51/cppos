#include "msgQ.h"
void memcopy( uint8_t * dst, uint8_t * src, uint32_t size )
{
    while(size--)
    *dst++ = *src++;
}
msgQ::msgQ( uint8_t numberOfMsgs )
{
    msgQWriteLock.semCountInit( numberOfMsgs, numberOfMsgs );
    msgQReadLock.semCountInit( 0, numberOfMsgs );
    memset( (uint8_t *)&this->nodes[0], 0xFFu, MSG_Q_MAX_SIZE*sizeof(msgType) );
}

msgType * msgQ::msgQAllocate( void )
{
    uint8_t i;
    for( i = 0;i < MSG_Q_MAX_SIZE;i++)
    {
        if( this->nodes[i].size == 0xFFFFFFFF )
        {
            return &(this->nodes[i]);
        }
    }
    return NULL;
}

void msgQ::msgQFree( msgType * pData )
{
    pData->size = 0xFFFFFFFF;
}

void msgQ::msgQSend( uint32_t timeout, uint8_t * pData, uint32_t size )
{
    msgType * pMsgType;
    msgQWriteLock.semAccquire( timeout );
    pMsgType = this->msgQAllocate();
    if( pMsgType != NULL )
    {
        memcopy( (uint8_t*)pMsgType->buffer, (uint8_t*)pData, size );
        pMsgType->size = size;
        (void)this->queue.listInsertFirstNodeData( (void*&)pMsgType );
        msgQReadLock.semRelease();
    }
}

uint32_t msgQ::msgQReceive( uint32_t timeout, uint8_t * pData )
{
    msgType * pMsgType;
    this->msgQReadLock.semAccquire( timeout );
    this->queue.listRemoveFirstNodeData( (void*&)pMsgType );
    memcopy((uint8_t*)pData, (uint8_t*)pMsgType->buffer, pMsgType->size );
    this->msgQWriteLock.semRelease();
    return pMsgType->size;
}
