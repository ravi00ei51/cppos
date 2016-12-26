#include "cortex-m3.h"

void cortex_m3_cpu::saveCpuRegisters( void )
{
    volatile uint32_t x=100;
    COPY_TO_REGISTER_R0(x);
    x = 10;
    COPY_TO_REGISTER_R1(x); 
    x = 12;
}

void cortex_m3_cpu::restoreCpuRegisters( void )
{    
    volatile uint32_t x = 50;
    COPY_FROM_REGISTER_R0(x);
    x = 10;
    COPY_FROM_REGISTER_R1(x);
    x = 111;
}

