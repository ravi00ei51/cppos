#include "cortex-m3.h"

cortex_m3_cpu::cortex_m3_cpu(unsigned int x)
{
    this->r0 = x;
    this->r1 = x;
}

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

unsigned int cortex_m3_cpu::GetR0( void )
{
    return this->r0;
}

unsigned int cortex_m3_cpu::GetR1( void )
{
    return this->r1;
}

unsigned int cortex_m3_cpu::GetR2( void )
{
    return this->r2;
}

