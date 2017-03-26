#include "cortex-m3.h"

void cortex_m3_cpu::cpuGetContext(void)
{
    COPY_FROM_REGISTER_R4(this->r4);
    COPY_FROM_REGISTER_R5(this->r5);
    COPY_FROM_REGISTER_R6(this->r6);
    COPY_FROM_REGISTER_R7(this->r7);
    COPY_FROM_REGISTER_R8(this->r8);
    COPY_FROM_REGISTER_R9(this->r9);
    COPY_FROM_REGISTER_R10(this->r10);
    COPY_FROM_REGISTER_R11(this->r11);  
    asm("mrs r3, psp");
    COPY_FROM_REGISTER_R3(this->sp);
}

void cortex_m3_cpu::cpuSetContext(void)
{
    COPY_TO_REGISTER_R4(this->r4);
    COPY_TO_REGISTER_R5(this->r5);
    COPY_TO_REGISTER_R6(this->r6);
    COPY_TO_REGISTER_R7(this->r7);
    COPY_TO_REGISTER_R8(this->r8);
    COPY_TO_REGISTER_R9(this->r9);
    COPY_TO_REGISTER_R10(this->r10);
    COPY_TO_REGISTER_R11(this->r11);   
    COPY_TO_REGISTER_R3(this->sp);
    asm("msr psp, r3");
    asm("mov lr, #0xFFFFFFFD");
    asm("mov r3, #0x3");
    asm("msr control, r3");
    asm("isb");
    asm("bx lr");

}

void cortex_m3_cpu::cpuPrepareForExecution( uint32_t * pStack, uint32_t * pFunc, uint32_t stackSize )
{
     this->r0       = 0U;
     this->r1       = 0U;
     this->r2       = 0U;
     this->r3       = 0U;
     this->r4       = 0U;
     this->r5       = 0U;
     this->r6       = 0U;
     this->r7       = 0U;
     this->r8       = 0U;
     this->r9       = 0U;
     this->r10      = 0U;
     this->r11      = 0U;
     this->r12      = 0U;
     this->sp       = (uint32_t)(&pStack[stackSize-8]);
     this->lr       = (uint32_t)0;
     this->pc       = (uint32_t)pFunc;
     this->xpsr     = 0x21000000;
     this->ctrlMask = 0x03;
     this->mask     = 0x00;
     pStack[stackSize-1] = this->xpsr;
     pStack[stackSize-2] = this->pc;
     pStack[stackSize-3] = this->lr;
     pStack[stackSize-4] = this->r12;
     pStack[stackSize-5] = this->r3;
     pStack[stackSize-6] = this->r2;
     pStack[stackSize-7] = this->r1;
     pStack[stackSize-8] = this->r0; 
}
