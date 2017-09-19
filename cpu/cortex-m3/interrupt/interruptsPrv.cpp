#include "interrupts.h"

__attribute__((section(".interrupt00"))) void interruptVector0( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(0u);
}


__attribute__((section(".interrupt01"))) void interruptVector1( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(1u);         
}

__attribute__((section(".interrupt02"))) void interruptVector2( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(2u);
}

__attribute__((section(".interrupt03"))) void interruptVector3( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(3u);
}

__attribute__((section(".interrupt04"))) void interruptVector4( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(4u);
}

__attribute__((section(".interrupt05"))) void interruptVector5( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(5u);
}

__attribute__((section(".interrupt06"))) void interruptVector6( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(6u);
}

__attribute__((section(".interrupt07"))) void interruptVector7( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(7u);
}

__attribute__((section(".interrupt08"))) void interruptVector8( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(8u);
}

__attribute__((section(".interrupt09"))) void interruptVector9( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(9u);
}

__attribute__((section(".interrupt0A"))) void interruptVector10( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(10u);
}

__attribute__((section(".interrupt0B"))) void interruptVector11( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(11u);
}

__attribute__((section(".interrupt0C"))) void interruptVector12( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(12u);
}

__attribute__((section(".interrupt0D"))) void interruptVector13( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(13u);
}

__attribute__((section(".interrupt0E"))) void interruptVector14( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(14u);
}

__attribute__((section(".interrupt0F"))) void interruptVector15( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(15u);
}


