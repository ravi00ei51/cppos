#ifndef __H_SEMAPHORE_H__
#define __H_SEMAPHORE_H__

template <semType> semaphore:public atomic
{
private:
    uint32_t semId;
    BOOLEAN  status;
    atomic   semLock;
public:
    semaphore( BOOLEAN status );
    semAccquire( void );
    semRelease( void );
};

#endif
