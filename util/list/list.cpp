#include "node.h"
#include "list.h"
#include "task.h"
#include "schedInfo.h"

template <class T, uint32_t MAX_NUMBER_OF_NODES> list<T, MAX_NUMBER_OF_NODES>::list( void )
{
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_NODES; i++ )
    {
        this->listNodes[i].pPrev = NULL;
        this->listNodes[i].pNext = NULL;
        this->listNodes[i].pData = NULL;
    }  
    this->pHeadNode     = NULL;  
    this->listNodeCount = 0u;
}

/*template <class T, uint32_t MAX_NUMBER_OF_NODES> list<T, MAX_NUMBER_OF_NODES>::list( T * pData[], uint8_t numberOfNodes )
{
    uint8_t i;
    node<T> * pNode = NULL;
    node<T> * pLastNode = NULL;
    for( i = 0; i < MAX_NUMBER_OF_NODES; i++ )
    {
        this->listNodes[i].pPrev = NULL;
        this->listNodes[i].pNext = NULL;
        this->listNodes[i].pData = NULL;
    }
    
    if( numberOfNodes < MAX_NUMBER_OF_NODES )
    {
        for( i = 0; i < numberOfNodes; i++ )
        {
            pLastNode = pNode;
            pNode = this->listAllocateNode();
            if( pNode != NULL )
            {
                if( i == 0 )
                {
                    this->pHeadNode = pNode;
                    pNode->pPrev    = NULL;
                }
                else if( i == ( numberOfNodes - 1 ) )
                {
                    pLastNode->pNext = pNode;
                    pNode->pPrev     = pLastNode;
                    pNode->pNext     = NULL;
                }
                else
                {
                    pLastNode->pNext = pNode;
                    pNode->pPrev     = pLastNode;
                }
                this->listNodeCount++; 
            }
            else
            {
                break;
            }         
        }
    }
    else
    {
    }
     
}*/
template <class T, uint32_t maxNumberOfNodes> void list<T, maxNumberOfNodes>::listInit(void)
{
    uint8_t i;
    for( i = 0; i < maxNumberOfNodes; i++ )
    {
        this->listNodes[i].pPrev = NULL;
        this->listNodes[i].pNext = NULL;
        this->listNodes[i].pData = NULL;
    }
    this->pHeadNode     = NULL;
    this->listNodeCount = 0u;    
}
template <class T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listInsertNodeData( T *& pData )
{
    node<T> * pTempNode;
    node<T> * pNode;
    BOOLEAN   retVal;

    if( pData != NULL )
    {
        if( this->listNodeCount < maxNumberOfNodes )
        {
            pTempNode    = this->pHeadNode;
            pNode        = this->listAllocateNode();
            pNode->pData = pData;

            if( pNode != NULL )
            {
                if( pTempNode != NULL )
                {
                    while( pTempNode->pNext != NULL )
                    {
                           pTempNode = pTempNode->pNext;
                    }     
                    pTempNode->pNext = pNode;
                    pNode->pPrev     = pTempNode;
                    pNode->pNext     = NULL;
                }
                else
                {
                    this->pHeadNode = pNode;
                    pNode->pNext    = NULL;
                    pNode->pPrev    = NULL;
                }
                retVal = TRUE;
                this->listNodeCount++;
            }
            else
            {
                retVal = FALSE;
            }   
        }
        else
        {
            retVal = FALSE;
        }   
    }
    else
    {
        retVal = FALSE;
    }

    return retVal;
}

template <class T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listRemoveNodeData( T *& pData )
{
    node<T> * pTempNode;
    node<T> * pNode;   
    BOOLEAN   retVal;

    pTempNode = this->pHeadNode;

    if( ( this->listNodeCount > 0 ) && ( this->listNodeCount <= maxNumberOfNodes ) )
    {
        if( pTempNode != NULL )
        {
            while( pTempNode->pNext != NULL )
            {
                pTempNode = pTempNode->pNext; 
            }
            if( pTempNode->pPrev != NULL )
            {
                pNode            = pTempNode;
                pData            = pNode->pData;
                pTempNode        = pNode->pPrev;
                pTempNode->pNext = NULL;  
                pNode->pNext     = NULL;
                this->listNodeCount--;
                this->listFreeNode(pNode);
                retVal = TRUE;
            }
            else
            {
                pNode            = pTempNode;
                pData            = pNode->pData;
                pTempNode->pNext = NULL;
                pNode->pNext     = NULL;
                pNode->pNext     = NULL;
                this->listNodeCount--;
                this->listFreeNode(pNode);
                retVal = TRUE;
            }
        }
        else
        {
            retVal = FALSE;
        }
    }
    else
    {
        retVal = FALSE;
    }
    return retVal;
}

template <typename T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listInsertNodeData( T *& pData, uint8_t pos )
{
    uint8_t   i;
    node<T> * pTempNode1 = NULL;
    node<T> * pTempNode2 = NULL;
    node<T> * pNode;
    BOOLEAN   retVal;

    if( this->listNodeCount < maxNumberOfNodes )
    {   
        if( pos <= maxNumberOfNodes )
        {
            pNode = this->listAllocateNode();  

            if( pNode != NULL )
            {
                pTempNode1   = this->pHeadNode;
                pNode->pData = pData;  
                
                if( pTempNode1 != NULL )
                {
                    for( i = 0; ( i < ( pos - 1 ) ) && ( pTempNode1 != NULL ); i++ )
                    {
                        pTempNode2 = pTempNode1;
                        pTempNode1 = pTempNode1->pNext;         
                    }

                    if( ( i == ( pos - 1 ) ) )
                    {
                        if( ( pTempNode1 != NULL ) && ( pTempNode2 != NULL ) )
                        {
                            pTempNode2->pNext = pNode;
                            pTempNode1->pPrev = pNode;
                            pNode->pNext      = pTempNode1;
                            pNode->pPrev      = pTempNode2;
                            retVal            = TRUE;
                            this->listNodeCount++;
                        }
                        else if( ( pTempNode1 == NULL ) && ( pTempNode2 != NULL ) )
                        {
                            pTempNode2->pNext = pNode;
                            pNode->pNext      = NULL;
                            pNode->pPrev      = pTempNode2;
                            retVal            = TRUE;
                            this->listNodeCount++;
                        }  
                        else if( ( pTempNode1 != NULL ) && ( pTempNode2 == NULL ) )
                        {
                            pNode->pNext      = pTempNode1;
                            pNode->pPrev      = NULL;
                            pTempNode1->pPrev = pNode;
                            this->pHeadNode   = pNode;
                            retVal            = TRUE;
                            this->listNodeCount++;
                        }
                        else
                        {
                            retVal = FALSE;
                        }
                    }
                    else
                    {
                        retVal = FALSE;
                    }
                }
                else
                {
                    if( pos == 1 )
                    {
                        this->pHeadNode  = pNode;
                        pNode->pNext     = NULL;
                        pNode->pPrev     = NULL;
                        retVal           = TRUE; 
                        this->listNodeCount++;
                    }
                    else
                    {
                        retVal       = FALSE;
                    }
                }
            }
            else
            {
                retVal = FALSE;
            }
        }
        else
        {
            retVal = FALSE;
        }
    }
    else
    {
        retVal = FALSE;
    } 
    return retVal;   
}


template <typename T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listRemoveNodeData( T *& pData, uint8_t pos )
{
    uint8_t   i;
    node<T> * pTempNode1;
    node<T> * pTempNode2;
    node<T> * pNode;
    BOOLEAN   retVal;

    if( ( this->listNodeCount <= maxNumberOfNodes ) && ( this->listNodeCount > 0 ) )
    {
        if( ( pos <= this->listNodeCount ) && ( pos > 0 ) )
        {
            pNode = this->pHeadNode;
        
            if( pNode != NULL )
            {
                for( i = 0; (i < ( pos - 1 )) && ( pNode != NULL ); i++ )
                {
                    pNode = pNode->pNext;
                }
                if( ( i == ( pos - 1 ) ) && ( pNode != NULL ) )
                {
                    pData             = pNode->pData;
                    pTempNode1        = pNode->pNext;
                    pTempNode2        = pNode->pPrev;  
                    if( ( pTempNode1 != NULL ) && ( pTempNode2 != NULL ) ) 
                    {
                        pTempNode2->pNext = pTempNode1;
                        pTempNode1->pPrev = pTempNode2;
                    }
                    else if( ( pTempNode1 == NULL ) && ( pTempNode2 != NULL ) )
                    {
                        pTempNode2->pNext = NULL;
                    }
                    else if( ( pTempNode1 != NULL ) && ( pTempNode2 == NULL ) )
                    {
                        pTempNode1->pPrev = NULL;
                        this->pHeadNode   = pTempNode1;
                    }
                    else 
                    {
                    }
    
                    pNode->pNext      = NULL;
                    pNode->pPrev      = NULL;
                    
                    this->listFreeNode( pNode );
                    this->listNodeCount--;
                    retVal = TRUE;
                }
                else
                {
                    retVal = FALSE;
                }
            }
            else
            {
                retVal = FALSE;
            }
        }
        else
        {
            retVal = FALSE;
        }
    }
    else
    {
        retVal = FALSE;
    }
    return retVal;
}

template <class T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listGetNodeData( T *& pData, uint8_t pos )
{
    node<T> * pTempNode;
    uint8_t   i = 0;
    BOOLEAN   retVal;

    if( ( this->listNodeCount <= maxNumberOfNodes ) && ( this->listNodeCount > 0 ) )
    {
        if( ( pos <= this->listNodeCount ) && ( pos > 0 ) )
        {
            pTempNode = this->pHeadNode;
            
            if( pTempNode != NULL )
            {
                for( i = 0; (i < ( pos - 1 ) ) && ( pTempNode->pNext != NULL ); i++ )
                {
                    pTempNode = pTempNode->pNext;
                }
                if(  i == ( pos - 1 ) )
                {       
                     pData  = pTempNode->pData;
                     retVal = TRUE;
                }
                else
                {
                    pData  = NULL;
                    retVal = FALSE;
                }
            }
            else
            {
                pData  = NULL;
                retVal = FALSE;
            }
        }
        else
        {
            pData  = NULL;
            retVal = FALSE;
        }
    }
    else
    {
        pData  = NULL;
        retVal = FALSE;
    }

    return retVal;
}

template <class T, uint32_t maxNumberOfNodes> uint8_t list<T, maxNumberOfNodes>::listGetNodePosition( T *& pData )
{
    node<T> * pTempNode;
    uint8_t   i = 1;
    BOOLEAN   nodeFound;
    
    pTempNode = this->pHeadNode;    
    
    while( pTempNode != NULL )
    {
        if( pTempNode->pData == pData )
        {
            nodeFound = TRUE;
        }

        if( nodeFound == TRUE )
        {
            break;
        }   

        pTempNode = pTempNode->pNext;
        i++;
    }
      
    if( nodeFound == FALSE )
    {
        i = NODE_NOT_FOUND;
    }
    return i;  
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listInsertFirstNodeData( T *& pData )
{
    node<T> * pTempNode;
    
    pTempNode = this->listAllocateNode();
    
    if( pTempNode != NULL )
    {
        pTempNode->pData = pData;
        if( this->pHeadNode != NULL )
        {
            this->pHeadNode->pPrev = pTempNode;
            pTempNode->pNext       = this->pHeadNode;
            this->pHeadNode        = pTempNode;
            pTempNode->pPrev       = NULL;
        }
        else
        {
            pTempNode->pNext       = NULL;
            pTempNode->pPrev       = NULL;
            this->pHeadNode        = pTempNode;  
        } 
        this->listNodeCount++;
    }
    else
    {
    }
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listRemoveFirstNodeData( T *& pData )
{
    node<T> * pTempNode;
    
    pTempNode              = this->pHeadNode;

    if( pTempNode != NULL )
    {
        pData                  = pTempNode->pData;
        if( pTempNode->pNext != NULL )
        {
            this->pHeadNode        = pTempNode->pNext;
            this->pHeadNode->pPrev = NULL;
        }
        else
        {
            this->pHeadNode = NULL; 
        }
        this->listFreeNode( pTempNode );
        this->listNodeCount--;
    }
    else
    {

    }
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listInsertLastNodeData( T *& pData )
{
    node<T> * pTempNode;
    node<T> * pNode;
    
    pTempNode = this->pHeadNode;
    pNode     = this->listAllocateNode();
    if( pNode != NULL )
    {
        pNode->pData = pData;
        if( pTempNode != NULL )
        {
            while( pTempNode->pNext != NULL )
            {
                pTempNode = pTempNode->pNext;
            }
    
            if( pTempNode != NULL )
            {
                pTempNode->pNext = pNode;
                pNode->pPrev     = pTempNode;    
                this->listNodeCount++;
            }
            else
            {
                
            }
        }
        else
        {
            this->pHeadNode = pNode;
            this->listNodeCount++;
        }

    }    
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listRemoveLastNodeData( T *& pData )
{
    node<T> * pNode;
    
    pNode = this->pHeadNode;

    if( pNode != NULL )
    {
        while( pNode->pNext != NULL )
        {
            pNode = pNode->pNext;
        }

        if( pNode != NULL )
        {
            pData               = pNode->pData;
            pNode->pPrev->pNext = NULL;
            pNode->pPrev        = NULL;
            pNode->pData        = NULL;
        }
        else
        {
            this->pHeadNode = pNode;
        }
        this->listFreeNode(pNode);
        this->listNodeCount--; 
    }
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listGetFirstNodeData( T *& pData )
{
    node<T> * pTempNode;

    pTempNode = this->pHeadNode;

    if( pTempNode != NULL )
    {
        pData = pTempNode->pData;
    }
    else
    {
        pData = NULL;
    }
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listGetLastNodeData( T *& pData )
{
    node<T> * pTempNode;

    pTempNode = this->pHeadNode;
    while( pTempNode->pNext != NULL )
    {
        pTempNode = pTempNode->pNext;
    }
    if( pTempNode != NULL )
    {
        pData = pTempNode->pData;
    }
    else
    {
        pData = NULL;
    }    
}
template <class T, uint32_t MAX_NUMBER_OF_NODES> node<T> * list<T, MAX_NUMBER_OF_NODES>::listAllocateNode(void)
{
    uint8_t i;
    for( i = 0; i < MAX_NUMBER_OF_NODES; i++ )
    {
        if( ( this->listNodes[i].pNext == NULL ) && ( this->listNodes[i].pPrev == NULL ) && ( this->listNodes[i].pData == NULL ) )
        {
             return (&this->listNodes[i]);
        }
    }
    return (node<T> *)NULL;
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listFreeNode( node<T> * pNode )
{
    pNode->pNext = NULL;
    pNode->pPrev = NULL;
    pNode->pData = NULL;
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listPrintNodeData( void )
{
    node<T> * pTempNode;
    pTempNode = this->pHeadNode;
    if( pTempNode != NULL )
    {
        while( pTempNode != NULL )
        {
            pTempNode = pTempNode->pNext;  
        }
    }
    else
    {
    }
}

template class list<task, 6>;
template class list<schedInfo, 6>;
