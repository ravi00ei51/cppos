#ifndef _H_LIST_H_
#define _H_LIST_H_
#include "node.h"

class list
{
private:
    unsigned char   listMaxSize;
    node          * pHeadNode;
    unsigned char   nodeCount; 
public:
    list( void );
    list( unsigned char maxSize );
    list( void * pData );
    list( unsigned char size, unsigned char priority );
    list( unsigned char priority, void * pData );
    list( unsigned char size, unsigned char priority, void * pData );

    unsigned char listCreateList( node * pNode[], unsigned char size );
    void listDestroyList( void );
    
    unsigned char listInsertNode( node * pNode );
    unsigned char listInsertNode( node * pNode, void * pData );
    unsigned char listInsertNode( node * pNode, unsigned char position );
    unsigned char listRemoveNode( node * pNode );
    unsigned char listRemoveNode( void * pData, unsigned int dataSize );
    unsigned char listRemoveNode( unsigned char position );

    unsigned char listInsertNodeByAcsendingPriority( node * pNode );
    unsigned char listInsertNodeByAcsendingPriority( node * pNode, void * pData );
    unsigned char listInsertNodeByAcsendingPriority( node * pNode, unsigned char position );

    unsigned char listInsertNodeByDescendingPriority( node * pNode );
    unsigned char listInsertNodeByDescendingPriority( node * pNode, void * pData );
    unsigned char listInsertNodeByDescendingPriority( node * pNode, unsigned char position );

    unsigned char listInsertFirstNode( node * pNode );
    unsigned char listInsertLastNode( node * pNode );
    unsigned char listRemoveFirstNode( node * pNode );
    unsigned char listRemoveLastNode( node * pNode );

    node * listGetNodeByPriority( unsigned char priority );
    node * listGetNodeByPosition( unsigned char position );
    node * listGetFirstNode( void );
    node * listGetLastNode( void );
};

#endif
