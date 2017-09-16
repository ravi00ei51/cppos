#include "abstractInterrupts.h"

void abstractInterrupts::install( uint32_t intNum )
{
    interrupts * pObj = interrupts::getInterruptsObject();
    pObj->setVector( intNum, this->handlerInterrupt );
}

void abstractInterrupts::deinstall( uint32_t intNum )
{
    interrupts * pObj = interrupts::getInterruptsObject();
    pObj->setVector( intNum, NULL );
}

void abstractInterrupts::handlerInterrupt( void )
{
    while(1);
}
