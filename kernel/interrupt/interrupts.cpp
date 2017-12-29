#include "interrupts.h"
static uint8_t interruptsObj[sizeof(interrupts)];

interrupts::interrupts( void )
{
    this->initialize();
}

interrupts::~interrupts( void )
{
    this->initialize();
}

void interrupts::initialize( void )
{
    this->init = FALSE;
    memset((uint8_t *)&this->vectorTable[0],0x00u, INTERRUPT_VECTOR_TABLE_SIZE*sizeof( this->vectorTable[0] ) );
}

void interrupts::setVector( uint32_t intNum, void (*&pFunc)( void ) )
{
    if( intNum < INTERRUPT_VECTOR_TABLE_SIZE )
    {
        this->vectorTable[intNum] = pFunc;
    }
}

void interrupts::getVector( uint32_t intNum, void (*&pFunc)( void ) )
{
    if( intNum < INTERRUPT_VECTOR_TABLE_SIZE )
    {
        pFunc = this->vectorTable[intNum];
    }
}

void interrupts::runVector( uint32_t intNum )
{
    if( this->vectorTable[intNum] != NULL )
    {
        this->vectorTable[intNum]();
    }
}

interrupts * interrupts::getInterruptsObject( void )
{
    interrupts * pObj = (interrupts *)&interruptsObj[0];
    if( pObj->init != TRUE )
    {
        pObj->initialize();
        pObj->init = TRUE;
    }
    else
    {
        //Do Nothing
    }
    return (interrupts *)&interruptsObj[0];
}

