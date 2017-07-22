#ifndef _H_ATOMIC_H_
#define _H_ATOMIC_H_
#include "basetypes.h"
class atomic 
{
private:
   uint8_t state;
public:
   atomic();
   ~atomic();
   BOOLEAN tryLock();
   void lock();
   void unlock();
};
#endif
