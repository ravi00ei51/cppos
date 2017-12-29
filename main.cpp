#include "cortex-m3.h"
#include "int.h"
#include "list.h"
#include "schedInfo.h"
#include<task.h>
#include<atomic.h>
#include<semaphore.h>
#include<semCount.h>
#include<msgQ.h>
#include<events.h>
void task1(void);
void task2(void);
static uint32_t stack1[50];
static uint32_t stack2[50];
msgQ   queueMsg(1);
extern int flash_sdata;
extern int ram_sdata;
extern int ram_edata;
extern int ram_0data;
uint8_t taskStart[2];
//events eventObj;
list taskList1;
task tasks[2];
//extern uint8_t schedInit;
extern uint8_t schedInit1;
extern schedInfo schedI;

inline void static_init()
{
    // Start and end points of the constructor list,
    // defined by the linker script.
    extern void (*__init_array_start)();
    extern void (*__init_array_end)();

    // Call each function in the list.
    // We have to take the address of the symbols, as __init_array_start *is*
    // the first function pointer, not the address of it.
    for (void (**p)() = &__init_array_start; p < &__init_array_end; ++p)
    {
        (*p)();
    }
}
void copyDataToRam( void )
{
    unsigned int * pEnd;
    unsigned int * pDst;
    unsigned int * addr;

    pDst  = (unsigned int *) &ram_sdata;
    pEnd  = (unsigned int *) &ram_edata;
    addr  = (unsigned int *)((unsigned int)&flash_sdata + (unsigned int)&ram_sdata - (unsigned int)&ram_0data);

    while( pDst < pEnd )
    {
        *pDst = *addr;
         pDst++;
         addr++;
    }
}
volatile uint32_t x;
volatile uint32_t y;
volatile uint32_t x1;
volatile uint32_t y1;
volatile uint32_t xy;
__attribute__((section(".test1"))) void test_func(void)
{
    char name1[10] = "task1";
    char name2[10] = "task2";

    //task * pTaskNode[2];
    xy = 0;

    taskStart[0] = 0x00;
    taskStart[1] = 0x00;
    //pTaskNode[0] = &tasks[0];
    //pTaskNode[1] = &tasks[1];
    x = 0;
    y = 0;
    x1 = 0;
    y1 = 0;
    //schedInit = FALSE;
    schedInit1 = FALSE;
    schedI.taskId = 0;
    schedI.priority = 0;

    clockSetup();
    systickSetup();
    interruptInit();
    //copyDataToRam();
    static_init();
    tasks[0].taskCreateTask(name1, &stack1[0], 50, 30, task1 );
    tasks[1].taskCreateTask(name2, &stack2[0], 50, 31, task2 );
    //taskList1.listInsertNodeData( (void*&)pTaskNode[0] );
    //taskList1.listInsertNodeData( (void*&)pTaskNode[1] );
    //taskList1.listInsertNodeData( (void*&)pTaskNode[2] );
    //taskList1.listInsertNodeData( (void*&)pTaskNode[3] );
    xy = 1;
    while(x < 2);
    while(y < 2);
    while(1);
}
//semCount semC(1);
semaphore semId;
void task1(void)
{
    volatile uint8_t recv[6] = "Here";
    do
    {
        x++;
        if( ( x == 10000 ) && ( x1 == 0 ) )
        {
            //task::taskSetTaskPriority( (uint32_t)(&tasks[1]), (uint8_t)10 );
            //sched<SCHEDULER_TYPE>::schedLock();
            //task::taskPendTask( (uint32_t)(&tasks[0]) );
            //semId.semAccquire(1000);
            //semC.semAccquire(1000);
            //eventObj.eventTaskReceive( (uint32_t)&tasks[0], 1, 1000 );
            x1 = 1;
        }
        if( ( x == 20000 ) && ( x1 == 1 ) )
        {
            //task::taskPendTask( (uint32_t)(&tasks[0]) );
            //task::taskSetTaskPriority( (uint32_t)(&tasks[1]), (uint8_t)7 );
            queueMsg.msgQReceive( 1000, (uint8_t *)recv );
            x1 = 2;
            //queueMsg.msgQReceive( 1000, (uint8_t *)recv );
            //x1 = 3;
            //queueMsg.msgQReceive( 1000, (uint8_t *)recv );
            //x1 = 4;
            //queueMsg.msgQReceive( 1000, (uint8_t *)recv );
            //x1 = 5;
        }

    }while(1);
}

void task2(void)
{
    volatile uint8_t buf[6] ="Hell";
    do
    {
        y++;
        if( ( y == 10000 ) && ( y1 == 0 ) )
        {
            //task::taskSetTaskPriority( (uint32_t)(&tasks[0]), (uint8_t)8 );
            //task::taskPendTask( (uint32_t)(&tasks[1]) );
            semId.semAccquire(1000);
            //semC.semAccquire(1000);
            //task::taskUnpendTask( (uint32_t)(&tasks[0]) );
            queueMsg.msgQSend( 1000, (uint8_t *)buf, 5u );
            //buf[4] = '1';
            //queueMsg.msgQSend( 1000, (uint8_t *)buf, 5u );
            //buf[4] = '2';
            //queueMsg.msgQSend( 1000, (uint8_t *)buf, 5u );
            //buf[4] = '3';
            //queueMsg.msgQSend( 1000, (uint8_t *)buf, 5u );
            //eventObj.eventSend( 1 );
            y1 = 1;
        }

        if( ( y == 20000 ) && ( y1 == 1 ) )
        {
            //semId.semRelease();
            //semC.semRelease();
            //task::taskSetTaskPriority( (uint32_t)(&tasks[1]), (uint8_t)7 );
            y1 = 2;
        }
    }
    while(1);
}


