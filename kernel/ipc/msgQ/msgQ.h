#ifndef __H_MSGQ_H__
#define __H_MSGQ_H__

#include "basetypes.h"
#include "semCount.h"
#include "list.h"

#define MSG_Q_MAX_SIZE (6u)
struct msgType
{
    uint8_t buffer[20];
    uint32_t size;
};

class msgQ
{
private:
    semCount                      msgQWriteLock;
    semCount                      msgQReadLock;
    msgType                       nodes[MSG_Q_MAX_SIZE];
    list                          queue;
    void msgQFree( msgType * pData );
    msgType * msgQAllocate( void );
public:
    msgQ(uint8_t numberOfMsgs);

    void msgQSend( uint32_t timeout, uint8_t * pData, uint32_t size );
    uint32_t msgQReceive( uint32_t timeout, uint8_t * pData );
};

#endif
