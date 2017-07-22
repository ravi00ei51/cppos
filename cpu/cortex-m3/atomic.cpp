#include <atomic.h>

static inline uint8_t __LDREXB(volatile uint8_t *addr)
{
    uint32_t result;
   asm volatile ("ldrexb %0, %1" : "=r" (result) : "Q" (*addr) );
   return ((uint8_t) result);    /* Add explicit type cast here */
}


static inline uint32_t __STREXB(uint8_t value, volatile uint8_t *addr)
{
   uint32_t result;

   asm volatile ("strexb %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
   return(result);
}

atomic::atomic(void)
{

}

atomic::~atomic(void)
{

}

BOOLEAN atomic::tryLock()
{
    BOOLEAN retVal = FALSE;

    if( !__LDREXB(&(this->state) ) ) 
    {
        __STREXB(1, &(this->state));
        retVal = TRUE;
    }
    else
    {
        retVal = FALSE;
    }

    return retVal;
}


void atomic::lock()
{
    do
    {
        if(__LDREXB(&(this->state))) continue;
    } while(__STREXB(1, &(this->state)));
}

void atomic::unlock()
{
    this->state = 0;
    return;
}
