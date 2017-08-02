#ifndef __H_LIST_H__
#define __H_LIST_H__
#include "node.h"

template <class T, uint32_t MAX_NUMBER_OF_NODES> class list
{
private:
    node<T>    listNodes[MAX_NUMBER_OF_NODES];
    node<T> *  pHeadNode;
    uint8_t    listNodeCount;
public:
    list( void );
    list( T * pData[], uint8_t numberOfNodes );
    void listInit(void);
    node<T> * listAllocateNode(void);
    void    listFreeNode( node<T> * );
    BOOLEAN listInsertNodeData( T *& pData );
    BOOLEAN listRemoveNodeData( T *& pData );

    BOOLEAN listInsertNodeData( T *& pData, uint8_t pos );
    BOOLEAN listRemoveNodeData( T *& pData, uint8_t pos );

    BOOLEAN listGetNodeData( T *& pData, uint8_t pos );
    uint8_t listGetNodePosition( T *& pData );

    void listInsertFirstNodeData( T *& pData );
    void listRemoveFirstNodeData( T *& pData );

    void listInsertLastNodeData( T *& pData );
    void listRemoveLastNodeData( T *& pData );

    void listGetFirstNodeData( T *& pData );
    void listGetLastNodeData( T *& pData );
    uint8_t listNumberOfNodes( void );
};

#endif
