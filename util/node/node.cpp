#include "node.h"
#include "task.h"
/*template <class T> node<T>::node(void)
{
    this->pPrevNode = NULL;
    this->pNextNode = NULL;
    this->pNodeData = NULL;
}*/

template <class T> node<T>::node( T * pData )
{
    this->pPrevNode = NULL;
    this->pNextNode = NULL;
    this->pNodeData = pData;
}

/*template <class T> node<T>::~node(void)
{
}*/

template <class T> void  node<T>::nodeSetNodeData( T * pData )
{
    this->pNodeData = pData;
}

template <class T> T * node<T>::nodeGetNodeData( void )
{
    return this->pNodeData;
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
