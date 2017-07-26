#include "node.h"
#include "task.h"
#include "schedInfo.h"
#include "semaphore.h"
template <class T> node<T>::node(void)
{
    this->pNext = NULL;
    this->pPrev = NULL;
    this->pData = NULL;
}
template <class T> node<T>::node( T * pData )
{
    this->pNext = NULL;
    this->pPrev = NULL;
    this->pData = pData;
}

/*template <class T> node<T>::~node(void)
{
}*/

template <class T> void  node<T>::nodeSetNodeData( T * pData )
{
    this->pData = pData;
}

template <class T> T * node<T>::nodeGetNodeData( void )
{
    return this->pData;
}

template <class T> void node<T>::nodeSetNodePriority( unsigned char priority )
{
    this->priority = priority;
}

template <class T> unsigned char node<T>::nodeGetNodePriority( void )
{
    return this->priority;
}

template class node<task>;
template class node<schedInfo>;
template class node<semData_t>;
