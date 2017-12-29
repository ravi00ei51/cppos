#include "interrupts.h"

static void interruptExecute( uint8_t num )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(num);
}
__attribute__((section(".interrupt00"))) void interruptVector0( void )
{
    interruptExecute(0u);
}


__attribute__((section(".interrupt01"))) void interruptVector1( void )
{
    interruptExecute(1u);
}

__attribute__((section(".interrupt02"))) void interruptVector2( void )
{
    interruptExecute(2u);
}

__attribute__((section(".interrupt03"))) void interruptVector3( void )
{
    interruptExecute(3u);
}

__attribute__((section(".interrupt04"))) void interruptVector4( void )
{
    interruptExecute(4u);
}

__attribute__((section(".interrupt05"))) void interruptVector5( void )
{
    interruptExecute(5u);
}

__attribute__((section(".interrupt06"))) void interruptVector6( void )
{
    interruptExecute(6u);
}

__attribute__((section(".interrupt07"))) void interruptVector7( void )
{
    interruptExecute(7u);
}

__attribute__((section(".interrupt08"))) void interruptVector8( void )
{
    interruptExecute(8u);
}

__attribute__((section(".interrupt09"))) void interruptVector9( void )
{
    interruptExecute(9u);
}

__attribute__((section(".interrupt0A"))) void interruptVector10( void )
{
    interruptExecute(10u);
}

__attribute__((section(".interrupt0B"))) void interruptVector11( void )
{
    interruptExecute(11u);
}

__attribute__((section(".interrupt0C"))) void interruptVector12( void )
{
    interruptExecute(12u);
}

__attribute__((section(".interrupt0D"))) void interruptVector13( void )
{
    interruptExecute(13u);
}

__attribute__((section(".interrupt0E"))) void interruptVector14( void )
{
    interruptExecute(14u);
}

__attribute__((section(".interrupt0F"))) void interruptVector15( void )
{
    interruptExecute(15u);
}


