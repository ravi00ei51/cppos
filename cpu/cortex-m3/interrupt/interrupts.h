#ifndef __H_INTERRUPTS_H__
#define __H_INTERRUPTS_H__
#define INTERRUPT_VECTOR_TABLE_SIZE  15
//#define NULL 0
#define FALSE 0
#define TRUE 1
typedef unsigned char BOOLEAN;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
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
