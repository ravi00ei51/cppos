#ifndef __H_SEMAPHORE_H__
#define __H_SEMAPHORE_H__
#include "ipc.h"
#include "atomic.h"
#include "basetypes.h"

class semaphore:public ipc
{
private:
    uint32_t owner;
    atomic  semLock;
public:
    semaphore(void);
    BOOLEAN ipcAccquireResource( void );
    BOOLEAN ipcAssignResourceToTask( uint32_t taskId, void *& pData );
    BOOLEAN ipcReleaseResource( void );
    void semAccquire( uint32_t );
    void semRelease( void );
    static void semListUpdate( semaphore * pSemObj );
};

#endif
