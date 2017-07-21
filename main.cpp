#include "cortex-m3.h"
#include "int.h"
#include "list.h"
#include "schedInfo.h"
#include<task.h>
#include<atomic.h>
void task1(void);
void task2(void);
static uint32_t stack1[50];
static uint32_t stack2[50];
extern int flash_sdata;
extern int ram_sdata;
extern int ram_edata;
extern int ram_0data;
uint8_t taskStart[2];
list<task,6> taskList1;
task tasks[2];
extern uint8_t schedInit;
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
    for (void (**p)() = &__init_array_start; p < &__init_array_end; ++p) {
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
    atomic test;
    atomic test1;
    task * pTaskNode[2];
    xy = 0;
    test.lock();
    test1.unblockingLock();
    test.unlock();
    test1.unlock();
    taskStart[0] = 0x00;
    taskStart[1] = 0x00;
    pTaskNode[0] = &tasks[0];
    pTaskNode[1] = &tasks[1];
    x = 0;
    y = 0;
    x1 = 0;
    y1 = 0;
    schedInit = FALSE;
    schedInit1 = FALSE;
    schedI.taskId = 0;
    schedI.priority = 0;
 
    clockSetup();    
    systickSetup();
    copyDataToRam();
    static_init();
    tasks[0].taskCreateTask(name1, &stack1[0], 50, 30, task1 );
    tasks[1].taskCreateTask(name2, &stack2[0], 50, 31, task2 );  
    taskList1.listInsertNodeData( pTaskNode[0] );
    taskList1.listInsertNodeData( pTaskNode[1] );    
    xy = 1; 
    while(x < 2);
    while(y < 2);
    while(1);
}

void task1(void)
{  
    do
    {
        x++;
        if( ( x == 10000 ) && ( x1 == 0 ) )
        {
            //task::taskSetTaskPriority( (uint32_t)(&tasks[1]), (uint8_t)10 );
            task::taskPendTask( (uint32_t)(&tasks[0]) );
            x1 = 1;
        }
        if( ( x == 20000 ) && ( x1 == 1 ) )
        {
            task::taskPendTask( (uint32_t)(&tasks[0]) );
            //task::taskSetTaskPriority( (uint32_t)(&tasks[1]), (uint8_t)7 );
            x1 = 2;
        }   
        
    }while(1);
}

void task2(void)
{
    do
    {
        y++;
        if( ( y == 10000 ) && ( y1 == 0 ) )
        {
            //task::taskSetTaskPriority( (uint32_t)(&tasks[0]), (uint8_t)8 );
            task::taskUnpendTask( (uint32_t)(&tasks[0]) );
            y1 = 1;
        }
        
        if( ( y == 20000 ) && ( y1 == 1 ) )
        {
            task::taskUnpendTask( (uint32_t)(&tasks[0]) );
            //task::taskSetTaskPriority( (uint32_t)(&tasks[1]), (uint8_t)7 );
            y1 = 2;
        }
    }
    while(1);
}
