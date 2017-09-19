#include "interrupts.h"
static uint8_t interruptsObj[sizeof(interrupts)];

interrupts::interrupts( void )
{
    uint32_t i;
    this->init = FALSE;
    for( i = 0u; i < INTERRUPT_VECTOR_TABLE_SIZE; i++ )
    {
        this->vectorTable[i] = NULL;
    }
}

interrupts::~interrupts( void )
{
    uint32_t i;
    this->init = FALSE;
    for( i = 0u; i < INTERRUPT_VECTOR_TABLE_SIZE; i++ )
    {
        this->vectorTable[i] = NULL;
    }
}

void interrupts::initialize( void )
{
    uint32_t i;
    this->init = FALSE;
    for( i = 0u; i < INTERRUPT_VECTOR_TABLE_SIZE; i++ )
    {   
        this->vectorTable[i] = NULL;
    }
}

void interrupts::setVector( uint32_t intNum, void (*pFunc)( void ) )
{
    if( intNum < INTERRUPT_VECTOR_TABLE_SIZE )
    {
        this->vectorTable[intNum] = pFunc;
    }
}

void interrupts::getVector( uint32_t intNum, void (*pFunc)( void ) )
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

