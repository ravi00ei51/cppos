#ifndef _H_PENDLIST_H_
#define _H_PENDLIST_H_
#include "basetypes.h"
#include "list.h"
#define MAX_IPC_NODES (6U)
struct ipcNode
{
    uint32_t taskId;
    uint32_t timeout;
};

typedef ipcNode ipcNodeType;

class ipcList
{
private:
    list           memberList;
    ipcNodeType    ipcNodes[MAX_IPC_NODES];
    ipcNodeType *  ipcListAllocateData();
    void           ipcListFreeData( ipcNodeType * );
public:
    void    ipcListInit(void);
    BOOLEAN ipcListInsertData( uint32_t taskId, uint32_t timeout );
    BOOLEAN ipcListRemoveData( uint32_t * taskId );
    uint8_t ipcListSize();
    void    ipcListTickFunction( void );
};

#endif
