#include "cortex-m3.h"
#include "list.h"

static volatile unsigned int s[4] = {0xA,0xB,0xC,0xD};
static cortex_m3_cpu obj1(11);
extern int flash_sdata;
extern int ram_sdata;
extern int ram_edata;
extern int ram_0data;

static node<int> listNode1;
static node<int> listNode2;
static node<int> listNode3;
static node<int> listNode4;
static node<int> listNode5;
static list<int> taskList(6);


    extern unsigned int __init_array_start;
    extern unsigned int __init_array_end;

    inline void static_init()
    {
        unsigned int  * pFuncStart;
        unsigned int  * pFuncEnd;
        unsigned int  * pTemp;
        void  (* pFuncCount)();

        pFuncStart = (unsigned int *)&__init_array_start;
        pFuncEnd   = (unsigned int *)&__init_array_end;

        for( pTemp = pFuncStart; pTemp < pFuncEnd; pTemp++ )
        {
            pFuncCount = (void (*)())(*pTemp);
            pFuncCount();
        } 
    }

void copyDataToRam( void )
{
    unsigned int * pEnd;
    unsigned int   size;
    unsigned int * pSrc;
    unsigned int * pDst;
    unsigned int * rSrc;  
    unsigned int * addr;

    rSrc  = (unsigned int *) &ram_0data;
    pSrc  = (unsigned int *) &flash_sdata; 
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

__attribute__((section(".test"))) volatile void test_func(void)
{
    static volatile unsigned int res;
 
    node<int> * pNode[5]= { NULL, NULL, NULL, NULL, NULL};
    node<int> * pLastNode = NULL;
    
    copyDataToRam();
    static_init();
    pNode[0] = &listNode1;
    pNode[1] = &listNode2;
    pNode[2] = &listNode3;
    pNode[3] = &listNode4;
    pNode[4] = &listNode5;
    taskList.listCreateList( pNode, 5 );   
    pLastNode = taskList.listGetNodeByPosition(0);
    pLastNode = taskList.listGetNodeByPosition(1);
    pLastNode = taskList.listGetNodeByPosition(2);
    pLastNode = taskList.listGetNodeByPosition(3);
    pLastNode = taskList.listGetNodeByPosition(4);
    res = obj1.GetR0();
    res = obj1.GetR1();
    res = obj1.GetR2();
    obj1.saveCpuRegisters();
    obj1.restoreCpuRegisters();    
}

