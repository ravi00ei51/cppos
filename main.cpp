#include "cortex-m3.h"
#include "int.h"
#include "list.h"
#include<task.h>

void task1(void);
void task2(void);
static uint32_t stack1[50];
static uint32_t stack2[50];
extern int flash_sdata;
extern int ram_sdata;
extern int ram_edata;
extern int ram_0data;
uint8_t taskStart[2];
list<task> taskList1(6);
task tasks[2];
node<task> taskNode1(&tasks[0]);
node<task> taskNode2(&tasks[1]);

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
__attribute__((section(".test1"))) void test_func(void)
{
    char name1[10] = "task1";
    char name2[10] = "task2"; 
    node<task> * pTaskNode[2];
    taskStart[0] = 0x00;
    taskStart[1] = 0x00;
    pTaskNode[0] = &taskNode1;
    pTaskNode[1] = &taskNode2;
    x = 0;
    y = 0;

    clockSetup();    
    systickSetup();
    copyDataToRam();
    static_init();
    taskNode1.pNodeData->taskCreateTask(name1, &stack1[0], 50, 30, task1 );
    taskNode2.pNodeData->taskCreateTask(name2, &stack2[0], 50, 31, task2 );  
    taskList1.listCreateList( pTaskNode, 2 );     
    while(x < 2);
    while(y < 2);
    while(1);
}

void task1(void)
{
    do
    {
        x++;
        x++;
    }while(1);
}

void task2(void)
{
    do
    {
        y++;
        y++;
    }
    while(1);
}
