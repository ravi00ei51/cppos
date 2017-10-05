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

BOOLEAN ipc::ipcCapture( uint32_t taskId, uint32_t timeout, void *& pData )
{
    BOOLEAN       retVal;
    BOOLEAN       isResourceAccquired;

    // Try to accquire the resource.
    isResourceAccquired = this->ipcAccquireResource();

    if( isResourceAccquired == FALSE )
    {
        /* Resource is not accquired. Pend the task on resource for given timeout */
        retVal = this->ipcListInsertData( taskId, timeout, pData );
    }
    else
    {
        retVal = this->ipcAssignResourceToTask( taskId, pData );
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
    void        * pData;

    listSize = this->ipcListSize();

    if( listSize > 0 )
    {
        retVal = this->ipcAssignResourceToTask( taskId, pData );

        if( retVal == TRUE )
        {
            this->ipcListRemoveData( &taskId, pData );
        }
    }
    else
    {
        retVal = this->ipcReleaseResource();
    }
    return retVal;
}

