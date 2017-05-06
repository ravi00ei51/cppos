#ifndef _H_SHCEDINFO_H_
#define _H_SHCEDINFO_H_
#include "basetypes.h"
#include "list.h"

struct schedInfo
{
    uint32_t taskId;
    uint8_t  priority;
};

class sched
{
private:
    list<schedInfo, 6>  schedulerList;
public:
    BOOLEAN  schedUpdateSchedInfo( uint32_t taskId, schedInfo * pSchedInfo );
    BOOLEAN  schedInsertSchedInfo( schedInfo * pSchedInfo );
    BOOLEAN  schedRemoveSchedInfo( schedInfo * pSchedInfo );
    uint32_t schedGetTaskForExecution( void );
};

#endif
