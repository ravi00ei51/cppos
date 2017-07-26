#ifndef __H_SEMAPHORE_H__
#define __H_SEMAPHORE_H__

#include "basetypes.h"
#include "atomic.h"
#include "list.h"
struct semData
{
    uint32_t taskId;
    uint32_t timeout;
};

typedef struct semData semData_t;

class semaphore
{
private:
    atomic            semLock;
    semData_t         semResource[6];
    uint32_t          semOwner;
    list<semData_t,6> semList;
    uint8_t           numberOfPendingTasks;
    BOOLEAN     semListInsert( uint32_t taskId, uint32_t timeout );
    BOOLEAN     semListRemove( uint32_t taskId );
    semData_t * semAllocateData( void );
    void        semFreeData( semData_t * );
public:
    semaphore( void );
    void semAccquire( uint32_t );
    void semRelease( void );
    static void semListUpdate( semaphore * pSemObj );
};

#endif
