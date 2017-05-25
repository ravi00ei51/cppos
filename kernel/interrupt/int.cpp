#include "int.h"
#include "node.h"
#include "list.h"
#include "task.h"
#include "schedInfo.h"
extern list<task,6> taskList1;
extern uint8_t  taskStart[2];
void systickSetup( void )
{
    SYSTICK_COUNTER_ENABLE();
    SYSTICK_TICKINT_COUNT_TO_ZERO();
    SYSTICK_CLK_SRC_AHB();
    SYSTICK_SET_LOAD_COUNTER(0x10000);
}

void clockSetup( void )
{
    RCC_SET_SYS_CLK_TO_HSI();
    asm("nop;");
    asm("nop;");
    asm("nop;");
    asm("nop;");
    asm("nop;");
    RCC_CLR_PLL_CLK();
    asm("nop;");
    asm("nop;");
    //RCC_SET_PLL_MUL_FACTOR_BIT1();
    RCC_SET_PLL_MUL_FACTOR_BIT2();
    RCC_SET_PLL_MUL_FACTOR_BIT3();
    //RCC_SET_PLL_MUL_FACTOR_BIT4();

    asm("nop;");
    asm("nop;");

    RCC_SET_PLL_SRC_TO_HSI();
    asm("nop;");
    asm("nop;");
    RCC_SET_SYS_CLK_TO_PLL();
    asm("nop;");
    asm("nop;");
    asm("nop;");
    asm("nop;");
    RCC_SET_PLL_CLK();
    asm("nop;");
    asm("nop;");
    asm("nop;");
    asm("nop;");
}
extern BOOLEAN schedInit;
schedInfo schedI;
static volatile uint32_t taskId;
__attribute__((section(".test"))) void systickInterruptFunction( void )
{
    //task * currentTask;
    volatile uint32_t currentTaskId;
    volatile uint32_t nextTaskId;
    task *   pCurrentTask;
    task *   pNextTask;
    sched<SCHED_TYPE_RR> * pSched;
    asm("cpsid i");   
    nextTaskId = 0u;
    pSched = sched<SCHED_TYPE_RR>::schedGetSchedInstance();
    currentTaskId = pSched->schedGetCurrentTaskForExecution();
    nextTaskId    = pSched->schedGetNextTaskForExecution();
    
    if( currentTaskId != nextTaskId )
    {
       pNextTask = task::getTaskByTaskId( nextTaskId );
       pCurrentTask = task::getTaskByTaskId( currentTaskId );
       if( currentTaskId != 0 )
       pCurrentTask->cpuGetContext();
       asm("cpsie i");
       pNextTask->cpuSetContext();
    } 
     
    /*{
        if( ( taskStart[0] == 0x00 ) && ( taskStart[1] == 0x00 ) )
        {
            taskStart[0] = 0x01;
            taskList1.listGetNodeData(currentTask, 1);
            asm("cpsie i");
            currentTask->cpuSetContext();
        }
        if( (taskStart[0] == 0x01 ) && ( taskStart[1] == 0x00 ) )
        {
            taskStart[1] = 0x01;
            taskStart[0] = 0x00;
            taskList1.listGetNodeData(currentTask, 1);
            currentTask->cpuGetContext();     
            taskList1.listGetNodeData(currentTask, 2);
            asm("cpsie i");
            currentTask->cpuSetContext();            
        }
        if( (taskStart[0] == 0x00 ) && ( taskStart[1] == 0x01 ) )
        {
            taskStart[1] = 0x00;
            taskStart[0] = 0x01;
            taskList1.listGetNodeData(currentTask, 2);
            currentTask->cpuGetContext();
            taskList1.listGetNodeData(currentTask, 1);
            asm("cpsie i");
            currentTask->cpuSetContext(); 
        }
    }*/
    asm("cpsie i");    
}

