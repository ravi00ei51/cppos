#include "interrupts.h"

using namespace std;

void interruptVector0( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(0u);
}


void interruptVector1( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(1u);         
}

void interruptVector2( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(2u);
}

void interruptVector3( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(3u);
}

void interruptVector4( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(4u);
}

void interruptVector5( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(5u);
}

void interruptVector6( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(6u);
}

void interruptVector7( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(7u);
}

void interruptVector8( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(8u);
}

void interruptVector9( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(9u);
}

void interruptVector10( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(10u);
}

void interruptVector11( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(11u);
}

void interruptVector12( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(12u);
}

void interruptVector13( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(13u);
}

void interruptVector14( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(14u);
}

void interruptVector15( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(15u);
}

void interruptVector16( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(16u);
}

void interruptVector17( void )
{
    interrupts * pObj;
    pObj = interrupts::getInterruptsObject();
    pObj->runVector(17u);
}

