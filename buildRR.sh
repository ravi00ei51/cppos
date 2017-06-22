arm-none-eabi-c++ -DSCHEDULER_TYPE=SCHED_TYPE_RR -Os -Wall -std=c++14 -pedantic -Wextra -Wconversion -Wuninitialized -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -static -nostartfiles -findirect-inlining -fno-non-call-exceptions -fno-exceptions -fno-rtti -fno-implicit-templates -fno-use-cxa-atexit -fomit-frame-pointer -ffunction-sections -fdata-sections -g -mcpu=cortex-m3 -mthumb -o add.elf -T linker/cortex-m3/stm.ld -I./cpu/cortex-m3/ -I./base/ -I./util/list/ -I./util/node/ -I./kernel/interrupt -I./kernel/task -I./util/bitops -I./kernel/scheduler startup/cortex-m3/startup.s cpu/cortex-m3/cortex-m3.cpp main.cpp util/list/list.cpp util/node/node.cpp kernel/interrupt/int.cpp kernel/task/task.cpp kernel/scheduler/schedInfoRR.cpp kernel/scheduler/schedInfoPriority.cpp
arm-none-eabi-objcopy -O binary add.elf add.bin
