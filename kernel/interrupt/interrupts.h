#ifndef __H_INTERRUPTS_H__
#define __H_INTERRUPTS_H__
#include "basetypes.h"

#define INTERRUPT_VECTOR_TABLE_SIZE  15
#define INTERRUPT_SYSTICK_NUM    ( 0xDu )
#define INTERRUPT_PENDSV_NUM    ( 0xCu )
#define INTERRUPT_SVC_NUM        ( 0x9u )

class interrupts
{
private:
    void (*vectorTable[INTERRUPT_VECTOR_TABLE_SIZE])( void );
    BOOLEAN init;
public:  
    interrupts( void );
    ~interrupts( void );
    void initialize( void );
    void setVector( uint32_t intNum, void (*pFunc)( void ) );
    void getVector( uint32_t intNum, void (*pFunc)( void ) );
    void runVector( uint32_t intNum );
    static interrupts * getInterruptsObject( void );
};

#endif
