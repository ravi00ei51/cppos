#ifndef __H_EVENTS_H__
#define __H_EVENTS_H__
#include "list.h"
#define MAX_NUMBER_OF_EVENT_NODES 6u
struct eventNode
{
    uint32_t taskId;
    uint8_t  mask;
    uint32_t  timeout;
    BOOLEAN  free;
};

typedef struct eventNode eventNodeType;

class events
{
private:
    eventNodeType              eventNodes[6];
    list<eventNodeType, 6> eventPendList;
    eventNodeType * eventAllocateEventNode( void );
    void            eventFreeEventNode( eventNodeType * pNode );
public:
    events(void);
   ~events(void);
    void eventSend( uint8_t maskId );
    void eventTaskReceive( uint32_t taskId, uint8_t mask, uint32_t timeout );
};

#endif
