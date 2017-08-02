#ifndef __H_MSGQ_H__
#define __H_MSGQ_H__
#include "basetypes.h"
#include "list.h"
#define MAX_BUFFER_SIZE 10u
#define MAX_NUMBER_OF_PEND_NODES 10u
#define MAX_NUMBER_OF_QUEUE_NODES 10u

struct queueNode
{
    uint8_t    buffer[MAX_BUFFER_SIZE];
    uint8_t    size;
};
typedef struct queueNode queueNodeType;
enum queuePendList
{
   QUEUE_PEND_LIST_SEND,
   QUEUE_PEND_LIST_RECEIVE,
   QUEUE_PEND_LIST_MAX
};

typedef enum queuePendList queuePendListType;
struct pendNode
{
    uint32_t      taskId;
    uint32_t      timeout;
    queueNodeType nodeData;
};

typedef struct pendNode pendNodeType;
class msgQ
{
private:
    queueNodeType           queueNode[MAX_NUMBER_OF_QUEUE_NODES];
    pendNodeType            pendNode[MAX_NUMBER_OF_PEND_NODES];
    list<queueNodeType, 10> queue;
    list<pendNodeType,  6>  pendList[QUEUE_PEND_LIST_MAX];
    uint8_t                 queueNodeCount;
    uint8_t                 pendQueueCount;
    queueNodeType * msgQAllocateQueueNode( void );
    void            msgQFreeQueueNode( queueNodeType * );

    pendNodeType  * msgQAllocatePendNode( void );
    void            msgQFreePendNode( pendNodeType * );

    void    msgQPutNodeToPendList( queuePendListType listType, uint32_t taskId, uint32_t timeout, uint8_t * pBuffer );
    void    msgQGetNodeFromPendList( queuePendListType listType, uint8_t * pBuffer );

    void    msgQPutNodeToQueue( uint8_t * pBuffer, uint8_t size );
    uint8_t msgQGetNodeFromQueue( uint8_t * pBuffer ); 
public:
    msgQ(void);
   ~msgQ(void);    
    void msgQSend( uint8_t * buffer, uint8_t size, uint32_t timeout );
    void msgQReceive( uint8_t * buffer, uint8_t size, uint32_t timeout );     
};

#endif
