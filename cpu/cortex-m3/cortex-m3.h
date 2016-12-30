#ifndef _H_CORTEX_M3_H_
#define _H_CORTEX_M3_H_
#include "basetypes.h"

#define COPY_TO_REGISTER_R0(var)     asm("mov r0, %[input]"::[input]"r"(var):)
#define COPY_FROM_REGISTER_R0(var)  asm("mov %[output],r0":[output]"=r"(var)::)
#define COPY_TO_REGISTER_R1(var)     asm("mov r1, %[input]"::[input]"r"(var):)
#define COPY_FROM_REGISTER_R1(var)  asm("mov %[output],r1":[output]"=r"(var)::)

class cortex_m3_cpu
{
private:
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r12;
    uint32_t r13;
    uint32_t r14;
    uint32_t r15;
    uint32_t r16;
public:
    cortex_m3_cpu(unsigned int);
    void saveCpuRegisters( void );
    void restoreCpuRegisters( void );
    unsigned int GetR0(void);
    unsigned int GetR1(void);
    unsigned int GetR2(void);

};

#endif
