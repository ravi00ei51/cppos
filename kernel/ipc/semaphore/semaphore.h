#ifndef __H_SEMAPHORE_H__
#define __H_SEMAPHORE_H__

#include "basetypes.h"

template <semType> semaphore:public atomic
{
private:
    atomic     semLock;
    atomicList semList;
public:
    semaphore( void );
    void semAccquire( void );
    void semRelease( void );
};

#endif
