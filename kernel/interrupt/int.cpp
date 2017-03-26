#include "int.h"
#include "node.h"
#include "list.h"
#include "task.h"
extern list<task> taskList1;
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

__attribute__((section(".test"))) void systickInterruptFunction( void )
{
    node<task> * currentTask;

    {
        if( ( taskStart[0] == 0x00 ) && ( taskStart[1] == 0x00 ) )
        {
            taskStart[0] = 0x01;
            currentTask = taskList1.listGetNodeByPosition(0);
            currentTask->pNodeData->cpuSetContext();
        }
        if( (taskStart[0] == 0x01 ) && ( taskStart[1] == 0x00 ) )
        {
            taskStart[1] = 0x01;
            taskStart[0] = 0x00;
            currentTask = taskList1.listGetNodeByPosition(0);
            currentTask->pNodeData->cpuGetContext();     
            currentTask = taskList1.listGetNodeByPosition(1);
            currentTask->pNodeData->cpuSetContext();            
        }
        if( (taskStart[0] == 0x00 ) && ( taskStart[1] == 0x01 ) )
        {
            taskStart[1] = 0x00;
            taskStart[0] = 0x01;
            currentTask = taskList1.listGetNodeByPosition(1);
            currentTask->pNodeData->cpuGetContext();     
            currentTask = taskList1.listGetNodeByPosition(0);
            currentTask->pNodeData->cpuSetContext(); 
        }
    }    
}

