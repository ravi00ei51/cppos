#include "ipc.h"

/*
***********************************************************************************************************************
* Module Name - IPC
* Module description -
*
*
*
*
*
*
***********************************************************************************************************************
*/


/*
***********************************************************************************************************************
* Function name        - IPC
* Function description -
*
*
*
*
*
*
***********************************************************************************************************************
*/

BOOLEAN ipc::ipcCapture( uint32_t taskId, uint32_t timeout )
{
    BOOLEAN       retVal;
    BOOLEAN       isResourceAccquired;

    // Try to accquire the resource.
    isResourceAccquired = this->ipcAccquireResource();

    if( isResourceAccquired == FALSE )
    {
        /* Resource is not acquired. Pend the task on resource for given timeout */
        retVal = this->ipcListInsertData( taskId, timeout );
    }
    else
    {
        retVal = this->ipcAssignResourceToTask( taskId );
    }
    return retVal;
}

/*
***********************************************************************************************************************
* Function name        - IPC
* Function description -
*
*
*
*
*
*
***********************************************************************************************************************
*/

BOOLEAN ipc::ipcRelease( void )
{
    BOOLEAN       retVal;
    uint8_t       listSize;
    uint32_t      taskId;

    listSize = this->ipcListSize();

    if( listSize > 0 )
    {
        retVal = this->ipcListRemoveData( &taskId );
        if( retVal == TRUE )
        {
            retVal = this->ipcAssignResourceToTask( taskId );
        }
    }
    else
    {
        retVal = this->ipcReleaseResource();
    }
    return retVal;
}
