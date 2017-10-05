#ifndef __H_IPC_H__
#define __H_IPC_H__
#include "basetypes.h"
#include "ipcList.h"

class ipc:public ipcList
{
private:

public:
    BOOLEAN ipcCapture(uint32_t taskId, uint32_t timeout, void *& pData);
    BOOLEAN ipcRelease();
    virtual BOOLEAN ipcAccquireResource( void ) = 0;
    virtual BOOLEAN ipcAssignResourceToTask( uint32_t taskId, void *& pData ) = 0;
    virtual BOOLEAN ipcReleaseResource( void )=0;
};
#endif
