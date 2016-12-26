#ifndef _H_NODE_H_
#define _H_NODE_H_

#define NULL                  ( 0U )

class node
{
public: 
    node * pNextNode;
    node * pPrevNode;
    void * pNodeData;
    unsigned char priority;
    unsigned int  dataSize;
    node( void );
    node( void * pData );
    ~node( void );
    void   nodeSetNodeData( void * pData );
    void * nodeGetNodeData(void );
    void   nodeSetNodePriority( unsigned char priority );
    unsigned char nodeGetNodePriority( void );
};

#endif
