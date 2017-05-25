#ifndef _H_SHCEDINFO_H_
#define _H_SHCEDINFO_H_
#include "basetypes.h"
#include "list.h"

enum schedAlgo
{
    SCHED_TYPE_RR,
    SCHED_TYPE_PRIORITY_BASED_PEMEPTION
};
#define CURRENT_SCHED_ALGO   SCHED_TYPE_RR
typedef enum schedAlgo schedType;

struct schedInfo
{
    uint32_t taskId;
    uint8_t  priority;
};

template <schedType> class sched
{
private:
    list<schedInfo, 6>  schedulerList;
    uint32_t            taskId;
    sched();
public:
    static sched * schedGetSchedInstance( void );
    static BOOLEAN schedInitSchedInfo( schedInfo * pSchedInfo );
    BOOLEAN  schedUpdateSchedInfo( uint32_t taskId, schedInfo * pSchedInfo );
    BOOLEAN schedInsertSchedInfo( schedInfo * pSchedInfo );
    BOOLEAN schedRemoveSchedInfo( schedInfo * pSchedInfo );
    uint32_t schedGetNextTaskForExecution( void );
    uint32_t schedGetCurrentTaskForExecution( void );
};

/*template <> class sched<SCHED_TYPE_RR>
{
private:
    list<schedInfo, 6>  schedulerList;
    uint32_t            taskId;
    sched();
public:
    static sched * schedGetSchedInstance( void );
    static BOOLEAN schedInitSchedInfo( schedInfo * pSchedInfo );
    BOOLEAN  schedUpdateSchedInfo( uint32_t taskId, schedInfo * pSchedInfo );
    BOOLEAN schedInsertSchedInfo( schedInfo * pSchedInfo );
    BOOLEAN schedRemoveSchedInfo( schedInfo * pSchedInfo );
    uint32_t schedGetNextTaskForExecution( void );
    uint32_t schedGetCurrentTaskForExecution( void );
};

template <> class sched<SCHED_TYPE_PRIORITY_BASED_PEMEPTION>
{
private:
    list<schedInfo, 6>  schedulerList;
    uint32_t            taskId;
    sched();
public:
    static sched * schedGetSchedInstance( void );
    static BOOLEAN schedInitSchedInfo( schedInfo * pSchedInfo );
    BOOLEAN  schedUpdateSchedInfo( uint32_t taskId, schedInfo * pSchedInfo );
    BOOLEAN schedInsertSchedInfo( schedInfo * pSchedInfo );
    BOOLEAN schedRemoveSchedInfo( schedInfo * pSchedInfo );
    uint32_t schedGetNextTaskForExecution( void );
    uint32_t schedGetCurrentTaskForExecution( void );
};*/ 
#endif
