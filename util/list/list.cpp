#include "list.h"

list::list(void)
{
   this->listInit();
}
void list::listInit(void)
{
   memset( (uint8_t *)this, 0x00u, sizeof(list) );
}

node * list::listFindNodeByPosition( uint8_t  pos )
{
    node * pNode = this->pHeadNode;
    pos--;
    while( ( pos != 0 ) && ( pNode != NULL ) )
    {
        pNode = pNode->pNext;
        pos--;
    }
    return pNode;
}

BOOLEAN list::listInsertNodeData( void *& pData )
{
    uint8_t listSize;
    BOOLEAN val;
    listSize = this->listNumberOfNodes();
    listSize++;
    val = this->listInsertNodeData( pData, listSize );
    return val;
}

BOOLEAN list::listRemoveNodeData( void *& pData )
{
    uint8_t listSize;
    BOOLEAN val;
    listSize = this->listNumberOfNodes();
    val = this->listRemoveNodeData( pData, listSize );
    return val;
}

BOOLEAN list::listInsertNodeData( void *& pData, uint8_t pos )
{
    node    * pTempNode1;
    node    * pTempNode2;
    node    * pNode;
    BOOLEAN   val = FALSE;
    uint8_t   numberOfNodes;

    numberOfNodes   = this->listNumberOfNodes();
    pNode           = this->listAllocateNode();
    if( pNode != NULL )
    {
        pNode->pData    = pData;
        numberOfNodes++;

        if( pos == 1 )
        {
            pTempNode1      = this->pHeadNode;
            this->pHeadNode = pNode;
            pNode->pNext    = pTempNode1;
        }
        else if( ( pos > 1 ) && ( pos <= numberOfNodes ) )
        {
            pos--;
            pTempNode2        = this->listFindNodeByPosition( pos );
            pTempNode1        = pTempNode2->pNext;
            pTempNode2->pNext = pNode;
            pNode->pNext      = pTempNode1;
        }
        else
        {

        }
        val = TRUE;
    }
    return val;
}

BOOLEAN list::listRemoveNodeData( void *& pData, uint8_t pos )
{
    node    * pTempNode1;
    node    * pTempNode2;
    BOOLEAN   val = FALSE;
    uint8_t   numberOfNodes;

    numberOfNodes = this->listNumberOfNodes();

    if( pos == 1 )
    {
        pTempNode1      = this->pHeadNode;
        this->pHeadNode = pTempNode1->pNext;
        pData           = pTempNode1->pData;
        val             = TRUE;
        this->listFreeNode( pTempNode1 );
    }
    else if( (pos > 1) && ( pos <= numberOfNodes ) )
    {
        pos--;
        pTempNode2        = this->listFindNodeByPosition( pos );
        pTempNode1        = pTempNode2->pNext;
        pTempNode2->pNext = pTempNode1->pNext;
        pData             = pTempNode1->pData;
        val               = TRUE;
        this->listFreeNode( pTempNode1 );
    }
    else
    {

    }

    return val;
}
BOOLEAN list::listGetNodeData( void *& pData, uint8_t pos )
{
    node    * pNode = NULL;
    BOOLEAN   val = FALSE;

    if( pos > 0 )
    {
        pos--;
        pNode = this->pHeadNode;
        while( ( pos != 0 ) && ( pNode != NULL ) )
        {
            pNode = pNode->pNext;
            pos--;
        }
        if( pNode != NULL )
        {
            pData = pNode->pData;
            val   = TRUE;
        }
        else
        {
            pData = NULL;
            val   = FALSE;
        }
    }
    else
    {
        val = FALSE;
    }
    return val;
}

uint8_t list::listGetNodePosition( void *& pData )
{
    node    * pNode;
    uint8_t   val = 0;
    pNode = this->pHeadNode;
    if( pNode != NULL )
    {
        while( pNode != NULL )
        {
            val++;
            if( pNode->pData == pData )
            {
                break;
            }
        }
    }
    return val;
}

/*void list::listInsertFirstNodeData( void *& pData )
{
    (void)this->listInsertNodeData( pData, 1 );
}
void list::listRemoveFirstNodeData( void *& pData )
{
    (void)this->listRemoveNodeData( pData, 1 );
}

void list::listInsertLastNodeData( void *& pData )
{
    (void)this->listInsertNodeData( pData );
}
void list::listRemoveLastNodeData( void *& pData )
{
    (void)this->listRemoveNodeData( pData );
}

void list::listGetFirstNodeData( void *& pData )
{
    (void)this->listGetNodeData( pData, 1 );
}*/
void list::listGetLastNodeData( void *& pData )
{
    uint8_t listSize;
    listSize = this->listNumberOfNodes();
    (void)this->listGetNodeData( pData, listSize );
}
uint8_t list::listNumberOfNodes( void )
{
    node    * pNode;
    uint8_t   val = 0;

    if( this->pHeadNode != NULL )
    {
        pNode = pHeadNode;
        while( pNode != NULL )
        {
            val++;
            pNode = pNode->pNext;
        }
    }
    return val;
}

node * list::listAllocateNode(void)
{
    uint8_t i;
    node * pNode = NULL;
    for( i = 0; i < MAX_NUMBER_OF_NODES; i++ )
    {
        if( ( this->listNodes[i].pNext == NULL ) && ( this->listNodes[i].pData == NULL ) )
        {
             pNode = &this->listNodes[i];
             break;
        }
    }
    return (node *)pNode;
}
/********************************************************************************************************************************
* Private function for class list
********************************************************************************************************************************/

void list::listFreeNode( node * pNode )
{
    pNode->pNext = NULL;
    pNode->pData = NULL;
}
