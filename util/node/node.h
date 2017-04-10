#ifndef _H_NODE_H_
#define _H_NODE_H_
#include "basetypes.h"
//#define NULL                  ( 0U )
template <class T>class node
{
public: 
    node * pNext;
    node * pPrev;
    T    * pData;
    unsigned char priority;
    unsigned int  dataSize;
    node( void );
    node( T * pData );
    //~node( void );
    void   nodeSetNodeData( T * pData );
    T    * nodeGetNodeData(void );
    void   nodeSetNodePriority( unsigned char priority );
    unsigned char nodeGetNodePriority( void );
};

#endif
