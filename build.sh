arm-none-eabi-c++ -DSCHEDULER_TYPE=SCHED_TYPE_PRIORITY_BASED_PEMEPTION -Os -g -Wall -std=c++14 -pedantic -Wextra -Wconversion -Wuninitialized -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -static -nostartfiles -findirect-inlining -fno-non-call-exceptions -fno-exceptions -fno-rtti -fno-implicit-templates -fno-use-cxa-atexit -fomit-frame-pointer -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -o add.elf -T linker/cortex-m3/stm.ld -I./cpu/cortex-m3/native -I./cpu/cortex-m3/atomic -I./cpu/cortex-m3/interrupt -I./base/ -I./util/list/ -I./util/node/ -I./kernel/interrupt -I./kernel/task -I./util/bitops -I./kernel/scheduler -I./kernel/ipc/semaphore -I./kernel/ipc/msgQ -I./kernel/ipc/events startup/cortex-m3/startup.s cpu/cortex-m3/native/cortex-m3.cpp cpu/cortex-m3/interrupt/interruptsPrv.cpp main.cpp util/list/list.cpp util/node/node.cpp kernel/interrupt/int.cpp kernel/interrupt/interrupts.cpp kernel/task/task.cpp kernel/scheduler/schedInfoPriority.cpp cpu/cortex-m3/atomic/atomic.cpp kernel/ipc/semaphore/semaphore.cpp kernel/ipc/msgQ/msgQ.cpp kernel/ipc/events/events.cpp
arm-none-eabi-objcopy -O binary add.elf add.bin
rm -rf elfDetails.txt
readelf -all add.elf >> elfDetails.txt
