#ifndef _H_LIST_H_
#define _H_LIST_H_
#include "node.h"

template <class T> class list
{
private:
    unsigned char   listMaxSize;
    node<T>       * pHeadNode;
    unsigned char   nodeCount; 
public:
    list( void );
    list( unsigned char maxSize );
    list( T * pData );
    list( unsigned char size, unsigned char priority );
    list( unsigned char priority, T * pData );
    list( unsigned char size, unsigned char priority, T * pData );

    unsigned char listCreateList( node<T> * pNode[], unsigned char size );
    void listDestroyList( void );
    
    unsigned char listInsertNode( node<T> * pNode );
    unsigned char listInsertNode( node<T> * pNode, T * pData );
    unsigned char listInsertNode( node<T> * pNode, unsigned char position );
    unsigned char listRemoveNode( node<T> * pNode );
    unsigned char listRemoveNode( T * pData, unsigned int dataSize );
    unsigned char listRemoveNode( unsigned char position );

    unsigned char listInsertNodeByAcsendingPriority( node<T> * pNode );
    unsigned char listInsertNodeByAcsendingPriority( node<T> * pNode, T * pData );
    unsigned char listInsertNodeByAcsendingPriority( node<T> * pNode, unsigned char position );

    unsigned char listInsertNodeByDescendingPriority( node<T> * pNode );
    unsigned char listInsertNodeByDescendingPriority( node<T> * pNode, T * pData );
    unsigned char listInsertNodeByDescendingPriority( node<T> * pNode, unsigned char position );

    unsigned char listInsertFirstNode( node<T> * pNode );
    unsigned char listInsertLastNode( node<T> * pNode );
    unsigned char listRemoveFirstNode( node<T> * pNode );
    unsigned char listRemoveLastNode( node<T> * pNode );

    node<T> * listGetNodeByPriority( unsigned char priority );
    node<T> * listGetNodeByPosition( unsigned char position );
    node<T> * listGetFirstNode( void );
    node<T> * listGetLastNode( void );
};

#endif
