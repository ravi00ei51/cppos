#ifndef __H_ABSTRACT_INTERRUPT_H__
#define __H_ABSTRACT_INTERRUPT_H__

class absractInterrupts
{
private:
    
public:
    void install( uint32_t intNum );
    void deinstall( uint32_t intNum );
    virtual void handlerInterrupt( void );
};

#endif

