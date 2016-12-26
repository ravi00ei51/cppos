arm-none-eabi-c++  -static -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -g -mcpu=cortex-m3 -mthumb -o add.elf -T linker/cortex-m3/stm.ld -I./cpu/cortex-m3/ -I./base/  startup/cortex-m3/startup.s cpu/cortex-m3/cortex-m3.cpp main.cpp
arm-none-eabi-objcopy -O binary add.elf add.bin
