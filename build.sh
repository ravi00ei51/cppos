arm-none-eabi-g++   -static -nostartfiles -fno-exceptions -fno-rtti -fno-implicit-templates -fno-use-cxa-atexit -ffunction-sections -flto -g -mcpu=cortex-m3 -mthumb -o add.elf -T linker/cortex-m3/stm.ld -I./cpu/cortex-m3/ -I./base/ -I./util/list/ -I./util/node/ startup/cortex-m3/startup.s cpu/cortex-m3/cortex-m3.cpp main.cpp util/list/list.cpp util/node/node.cpp
arm-none-eabi-objcopy -O binary add.elf add.bin
