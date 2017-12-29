#ifndef __H_LIST_H__
#define __H_LIST_H__
#include "basetypes.h"
#define MAX_NUMBER_OF_NODES (10u)
#define NODE_NOT_FOUND (0xFFu)
struct node
{
    struct node * pNext;
    void *        pData;
};

typedef struct node nodeType;
class list
{
private:
    node       listNodes[MAX_NUMBER_OF_NODES];
    node    *  pHeadNode;
    uint8_t    listNodeCount;
public:
    list( void );
    list( void * pData[], uint8_t numberOfNodes );
    void listInit(void);
    node  * listAllocateNode(void);
    void    listFreeNode( node * );
    node *  listFindNodeByPosition( uint8_t pos );
    BOOLEAN listInsertNodeData( void *& pData );
    BOOLEAN listRemoveNodeData( void *& pData );

    BOOLEAN listInsertNodeData( void *& pData, uint8_t pos );
    BOOLEAN listRemoveNodeData( void *& pData, uint8_t pos );

    BOOLEAN listGetNodeData( void *& pData, uint8_t pos );
    uint8_t listGetNodePosition( void *& pData );

    void listInsertFirstNodeData( void *& pData );
    void listRemoveFirstNodeData( void *& pData );

    void listInsertLastNodeData( void *& pData );
    void listRemoveLastNodeData( void *& pData );

    void listGetFirstNodeData( void *& pData );
    void listGetLastNodeData( void *& pData );
    uint8_t listNumberOfNodes( void );
};

#define listInsertFirstNodeData(x)    listInsertNodeData(x, 1)
#define listRemoveFirstNodeData(x)    listRemoveNodeData(x, 1)
#define listInsertLastNodeData(x)     listInsertNodeData(x)
#define listRemoveLastNodeData(x)     listRemoveNodeData(x)
#define listGetFirstNodeData(x)       listGetNodeData(x, 1);
#endif
