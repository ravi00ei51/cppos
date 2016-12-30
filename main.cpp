#include "cortex-m3.h"

static volatile unsigned int s[4] = {0xA,0xB,0xC,0xD};
static cortex_m3_cpu obj1(11);
extern int flash_sdata;
extern int ram_sdata;
extern int ram_edata;
extern int ram_0data;

extern "C"
{
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
    pSrc  = (unsigned int *) &flash_sdata; //0x08005000;
    pDst  = (unsigned int *) &ram_sdata; //0x20000000;
    pEnd  = (unsigned int *) &ram_edata; //0x20001000;
    addr  = (unsigned int *)((unsigned int)&flash_sdata + (unsigned int)&ram_sdata - (unsigned int)&ram_0data);
    while( pDst < pEnd )
    {
        *pDst = *addr;
         pDst++;
         addr++;  
    } 
}

__attribute__((section(".test"))) void test_func(void)
{
    static volatile unsigned int res;
    //cortex_m3_cpu obj1(10);
    copyDataToRam();
    static_init();
    res = obj1.GetR0();
    res = obj1.GetR1();
    res = obj1.GetR2();
    obj1.saveCpuRegisters();
    obj1.restoreCpuRegisters();
}

