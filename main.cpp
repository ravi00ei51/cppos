#include "cortex-m3.h"

__attribute__((section(".test"))) void test_func(void)
{
    cortex_m3_cpu obj;
    obj.saveCpuRegisters();
    obj.restoreCpuRegisters();
}
