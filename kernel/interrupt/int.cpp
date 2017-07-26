#include "int.h"
#include "node.h"
#include "list.h"
#include "task.h"
#include "schedInfo.h"
#include "semaphore.h"
extern list<task,6> taskList1;
extern uint8_t  taskStart[2];
extern semaphore semId;
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
extern volatile uint32_t xy;
__attribute__((section(".test"))) void systickInterruptFunction( void )
{
    //sched<SCHEDULER_TYPE>::schedExecuteScheduler(); 
    if( xy == 2 )
    {
        xy = 1;
        semaphore::semListUpdate( &semId );
    }
    else if( xy == 1 )
    {
        xy = 2;
        *((volatile uint32_t *)0xE000ED04) = 0x10000000;     
    }
    else
    {
        xy = 1;
    }
}

__attribute__((section(".testPendSV"))) void pendSVInterruptFunction( void )
{
    sched<SCHEDULER_TYPE>::schedExecuteScheduler();
}

__attribute__((section(".testSVC"))) void SVCInterruptFunction( void )
{
    *((volatile uint32_t *)0xE000ED04) = 0x10000000;
}
