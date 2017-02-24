#ifndef _H_NODE_H_
#define _H_NODE_H_

#define NULL                  ( 0U )

template <class T>class node
{
public: 
    node * pNextNode;
    node * pPrevNode;
    T    * pNodeData;
    unsigned char priority;
    unsigned int  dataSize;
    node( void );
    node( T * pData );
    ~node( void );
    void   nodeSetNodeData( T * pData );
    T    * nodeGetNodeData(void );
    void   nodeSetNodePriority( unsigned char priority );
    unsigned char nodeGetNodePriority( void );
};

#endif
