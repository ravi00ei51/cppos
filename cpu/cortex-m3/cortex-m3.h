#ifndef _H_CORTEX_M3_H_
#define _H_CORTEX_M3_H_
#include "basetypes.h"


#define COPY_TO_REGISTER_R0(var)     asm("mov r0, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R1(var)     asm("mov r1, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R2(var)     asm("mov r2, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R3(var)     asm("mov r3, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R4(var)     asm("mov r4, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R5(var)     asm("mov r5, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R6(var)     asm("mov r6, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R7(var)     asm("mov r7, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R8(var)     asm("mov r8, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R9(var)     asm("mov r9, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R10(var)    asm("mov r10, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R11(var)    asm("mov r11, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R12(var)    asm("mov r12, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R13(var)    asm("mov r13, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_PSP(var)    asm("msr psp, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R14(var)    asm("mov r14, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R15(var)    asm("mov r15, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_R16(var)    asm("mov r16, %[input]"::[input]"r"(var):)
#define COPY_TO_REGISTER_CONTROL(var)    asm("msr control, %[input]"::[input]"r"(var):)

#define COPY_FROM_REGISTER_R0(var)  asm("mov %[output],r0":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R1(var)  asm("mov %[output],r1":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R2(var)  asm("mov %[output],r2":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R3(var)  asm("mov %[output],r3":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R4(var)  asm("mov %[output],r4":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R5(var)  asm("mov %[output],r5":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R6(var)  asm("mov %[output],r6":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R7(var)  asm("mov %[output],r7":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R8(var)  asm("mov %[output],r8":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R9(var)  asm("mov %[output],r9":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R10(var) asm("mov %[output],r10":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R11(var) asm("mov %[output],r11":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R12(var) asm("mov %[output],r12":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R13(var) asm("mov %[output],r13":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_PSP(var) asm("mrs %[output],psp":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R14(var) asm("mov %[output],r14":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R15(var) asm("mov %[output],r15":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_R16(var) asm("mov %[output],r16":[output]"=r"(var)::)
#define COPY_FROM_REGISTER_CONTROL(var) asm("mrs %[output],control":[output]"=r"(var)::)

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
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;
    uint32_t ctrlMask;
    uint32_t mask;
public:
    void cpuSetContext(void);
    void cpuGetContext(void);
    void cpuPrepareForExecution( uint32_t * pStack, uint32_t * pFunc, uint32_t stackSize );
};

#endif
