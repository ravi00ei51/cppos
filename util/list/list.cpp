#include "list.h"
#include "task.h"
/*template <class T> list<T>::list( void )
{
}
*/
template <class T> list<T>::list( unsigned char maxSize )
{
    this->listMaxSize = maxSize;
    this->pHeadNode   = NULL;
    this->nodeCount   = 0;
}

/*template <class T> list<T>::list( T * pData )
{
}

template <class T> list<T>::list( unsigned char size, unsigned char priority )
{
}

template <class T> list<T>::list( unsigned char priority, T * pData )
{
}

template <class T> list<T>::list( unsigned char size, unsigned char priority, T * pData )
{
}*/

template <class T>  unsigned char list<T>::listCreateList( node<T> * pNode[], unsigned char size )
{
    unsigned char i = 0;
    unsigned char isAnyGivenNodeNULL = 0;
    unsigned char retVal = 0;
    if( (pNode != NULL ) )
    {
        for( i = 0; i < size; i++ )
        {
            if( pNode[i] == NULL )
            {
                isAnyGivenNodeNULL = 1;
            }
        }
       
        if( ( size <= this->listMaxSize ) && ( size >= 1 ) && ( isAnyGivenNodeNULL == 0 ) )
        {
            this->pHeadNode = pNode[0];
            pNode[0]->pPrevNode = NULL;

            for( i = 0; i < size-1; i++ )
            {
                pNode[i]->pNextNode   = pNode[i + 1];
                pNode[i+1]->pPrevNode = pNode[i];   
            }
            pNode[i]->pNextNode = NULL;
            i++;
            retVal = i;
        }
    }
    this->nodeCount = retVal;      
    return retVal;
}

template <class T> void list<T>::listDestroyList( void )
{
    this->pHeadNode = NULL;
}

template <class T> unsigned char list<T>::listInsertNode( node<T> * pNode )
{
    node<T> * pTempNode;
    if( this->pHeadNode == NULL )
    {
        this->pHeadNode  = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;
    }
    else
    {
        pTempNode = this->pHeadNode;

        while( pTempNode->pNextNode != NULL )
        {
            pTempNode = pTempNode->pNextNode;
        }

        pTempNode->pNextNode = pNode;  
        pNode->pPrevNode     = pTempNode;
    }
    if( this->nodeCount < this->listMaxSize )
    {
        this->nodeCount++;
    }
    return this->nodeCount;
}

template <class T> unsigned char list<T>::listInsertNode( node<T> * pNode, T * pData )
{
    node<T> * pTempNode;
    if( this->pHeadNode == NULL )
    {
        this->pHeadNode  = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;
    }
    else
    {
        pTempNode = this->pHeadNode;

        while( pTempNode->pNextNode != NULL )
        {
            pTempNode = pTempNode->pNextNode;
        }

        pTempNode->pNextNode = pNode;  
        pNode->pPrevNode     = pTempNode;
    }
    if( this->nodeCount < this->listMaxSize )
    {
        this->nodeCount++;
    }
    pNode->nodeSetNodeData( pData );

    return this->nodeCount; 
}

template <class T> unsigned char list<T>::listInsertNode( node<T> * pNode, unsigned char position )
{
    node<T> * pTempNode = NULL;
    node<T> * pNode1 = NULL;
    node<T> * pNode2 = NULL;
    unsigned char i = 0;

    if( this->pHeadNode != NULL )
    {
        pTempNode = this->pHeadNode;
        for( i = 0; i < position-1; i++ )
        {
            if( pTempNode->pNextNode == NULL )
            {
                break;
            }
            else
            {
                pTempNode = pTempNode->pNextNode;
            }
        }
    }
    else
    {
        this->pHeadNode  = pNode;
        pNode->pPrevNode = NULL;
        pNode->pNextNode = NULL;
        this->nodeCount++;
    }
    
    if( pTempNode != NULL )
    {
        if( pTempNode->pNextNode != NULL )
        {
            pNode1 = pTempNode;
            pNode2 = pTempNode->pNextNode;

            pNode1->pNextNode = pNode;
            pNode->pPrevNode  = pNode1;
            pNode->pNextNode  = pNode2;
            pNode2->pPrevNode = pNode;
            this->nodeCount++;
        }
        else
        {
            pTempNode->pNextNode = pNode;
            pNode->pPrevNode     = pTempNode;   
            pNode->pNextNode     = NULL;  
            this->nodeCount++;       
        }
    }
    return this->nodeCount; 
}

template <class T> unsigned char list<T>::listRemoveNode( node<T> * pNode )
{
    node<T> * pNode1;
    node<T> * pNode2;
    if( ( pNode->pPrevNode != NULL ) && ( pNode->pNextNode != NULL ) )
    {
        pNode1 = pNode->pPrevNode;
        pNode2 = pNode->pNextNode;

        pNode1->pNextNode = pNode2;
        pNode2->pPrevNode = pNode1;
        pNode->pNodeData  = NULL;
        this->nodeCount--;
    }
    else if( ( pNode->pPrevNode != NULL ) && ( pNode->pNextNode == NULL ) )
    {
        pNode1 = pNode->pPrevNode;

        pNode1->pNextNode = NULL;
        pNode->pNodeData  = NULL;   
        this->nodeCount--;
    }
    else if( ( pNode->pPrevNode == NULL ) && ( pNode->pNextNode != NULL ) )
    {
        pNode2 = pNode->pNextNode;

        this->pHeadNode   = pNode2;
        pNode2->pPrevNode = NULL;
        pNode->pNodeData  = NULL;
        this->nodeCount--;
    }
    else
    {
        
    }
    return this->nodeCount;
}

template <class T> unsigned char list<T>::listRemoveNode( unsigned char position )
{
    node<T> * pTempNode = NULL;
    node<T> * pNode1;
    node<T> * pNode2;
    unsigned char i;

    if( this->pHeadNode != NULL )
    {
        pTempNode = this->pHeadNode;
        for( i = 0; i < position; i++ )
        {
            pTempNode = pTempNode->pNextNode;
            if( pTempNode == NULL )
            {
                break;
            }
        }
    }
    else
    {
        // List is empty. Nothing to remove.
    }
    if( pTempNode == NULL )
    {
        // Given position does not exist in the list. Nothing to remove.
    }
    else
    {
        pNode1 = pTempNode->pPrevNode;
        pNode2 = pTempNode->pNextNode;

        pNode1->pNextNode     = pNode2;
        pNode2->pPrevNode     = pNode1;
        pTempNode->pNodeData  = NULL;
        this->nodeCount--;        
    }
    return this->nodeCount;
}

template <class T> unsigned char list<T>::listInsertNodeByAcsendingPriority( node<T> * pNode )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node<T> *        pTempNode;
    node<T> *        pNode1;
    node<T> *        pNode2;

    pTempNode = this->pHeadNode;
    if( pTempNode != NULL )
    {
        tempNodePriority = pTempNode->nodeGetNodePriority();
        inserNodePriority = pNode->nodeGetNodePriority();

        while( ( inserNodePriority > tempNodePriority ) && ( pTempNode->pNextNode != NULL ) )
        {
            pTempNode        = pTempNode->pNextNode;
            tempNodePriority = pTempNode->nodeGetNodePriority();
        }
        pNode1 = pTempNode;
        pNode2 = pTempNode->pNextNode;
        if( ( pNode1 != NULL ) && ( pNode2 != NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode2->pPrevNode = pNode;
            pNode->pPrevNode  = pNode1;
            pNode->pNextNode  = pNode2;
        }
        else if( ( pNode1 != NULL ) && ( pNode2 == NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode->pPrevNode = pNode1;
            pNode->pNextNode = NULL;
        }
        else
        {
        } 
    }
    else
    {
        this->pHeadNode = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;
 
    }   
    return (unsigned char)0; 
}

template <class T> unsigned char list<T>::listInsertNodeByAcsendingPriority( node<T> * pNode, T * pData )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node<T> *        pTempNode;
    node<T> *        pNode1;
    node<T> *        pNode2;
    pTempNode = this->pHeadNode;
    if( pTempNode != NULL )
    {
        tempNodePriority = pTempNode->nodeGetNodePriority();
        inserNodePriority = pNode->nodeGetNodePriority();

        while( ( inserNodePriority > tempNodePriority ) && ( pTempNode->pNextNode != NULL ) )
        {
            pTempNode        = pTempNode->pNextNode;
            tempNodePriority = pTempNode->nodeGetNodePriority();
        }
        pNode1 = pTempNode;
        pNode2 = pTempNode->pNextNode;
        if( ( pNode1 != NULL ) && ( pNode2 != NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode2->pPrevNode = pNode;
            pNode->pPrevNode  = pNode1;
            pNode->pNextNode  = pNode2;
        }
        else if( ( pNode1 != NULL ) && ( pNode2 == NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode->pPrevNode = pNode1;
            pNode->pNextNode = NULL;
        }
        else
        {
        }
    }
    else
    {
        this->pHeadNode = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;

    } 
    pNode->nodeSetNodeData( pData );  
    return (unsigned char)0;
}

template <class T> unsigned char list<T>::listInsertNodeByDescendingPriority( node<T> * pNode )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node<T> *        pTempNode;
    node<T> *        pNode1;
    node<T> *        pNode2;

    pTempNode = this->pHeadNode;

    if( pTempNode != NULL )
    {
        tempNodePriority = pTempNode->nodeGetNodePriority();
        inserNodePriority = pNode->nodeGetNodePriority();

        while( ( inserNodePriority < tempNodePriority ) && ( pTempNode->pNextNode != NULL ) )
        {
            pTempNode        = pTempNode->pNextNode;
            tempNodePriority = pTempNode->nodeGetNodePriority();
        }
        pNode1 = pTempNode;
        pNode2 = pTempNode->pNextNode;
        if( ( pNode1 != NULL ) && ( pNode2 != NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode2->pPrevNode = pNode;
            pNode->pPrevNode  = pNode1;
            pNode->pNextNode  = pNode2;
        }
        else if( ( pNode1 != NULL ) && ( pNode2 == NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode->pPrevNode = pNode1;
            pNode->pNextNode = NULL;
        }
        else
        {
        }
    }
    else
    {
        this->pHeadNode = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;

    }
    
    return (unsigned char)0;
}

template <class T> unsigned char list<T>::listInsertNodeByDescendingPriority( node<T> * pNode, T * pData )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node<T> *     pTempNode;
    node<T> *     pNode1;
    node<T> *     pNode2;
    pTempNode = this->pHeadNode;
    if( pTempNode != NULL )
    {
        tempNodePriority = pTempNode->nodeGetNodePriority();
        inserNodePriority = pNode->nodeGetNodePriority();

        while( ( inserNodePriority < tempNodePriority ) && ( pTempNode->pNextNode != NULL ) )
        {
            pTempNode        = pTempNode->pNextNode;
            tempNodePriority = pTempNode->nodeGetNodePriority();
        }
        pNode1 = pTempNode;
        pNode2 = pTempNode->pNextNode;
        if( ( pNode1 != NULL ) && ( pNode2 != NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode2->pPrevNode = pNode;
            pNode->pPrevNode  = pNode1;
            pNode->pNextNode  = pNode2;
        }
        else if( ( pNode1 != NULL ) && ( pNode2 == NULL ) )
        {
            pNode1->pNextNode = pNode;
            pNode->pPrevNode = pNode1;
            pNode->pNextNode = NULL;
        }
        else
        {
        }
    }
    else
    {
        this->pHeadNode = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;

    }
    pNode->nodeSetNodeData( pData );
    return (unsigned char)0;
}

template <class T> unsigned char list<T>::listInsertFirstNode( node<T> * pNode )
{
    node<T> * pNode1;
    if( this->pHeadNode != NULL )
    {
        pNode1 = this->pHeadNode;

        this->pHeadNode   = pNode;
        pNode->pNextNode  = pNode1;
        pNode->pPrevNode  = NULL;
        pNode1->pPrevNode = pNode;
    }    
    else
    {
        this->pHeadNode  = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;
    }
    return (unsigned char)0;
}

template <class T> unsigned char list<T>::listInsertLastNode( node<T> * pNode )
{
    node<T> * pTempNode;
    if( this->pHeadNode != NULL )
    {
        pTempNode = this->pHeadNode;

        while( pTempNode->pNextNode != NULL )
        {
            pTempNode = pTempNode->pNextNode;
        }

        pTempNode->pNextNode = pNode;
        pNode->pPrevNode     = pTempNode;
        pNode->pNextNode     = NULL;
    }
    else
    {
        this->pHeadNode  = pNode;
        pNode->pNextNode = NULL;
        pNode->pPrevNode = NULL;
    }
    return (unsigned char)0;
}

template <class T> unsigned char list<T>::listRemoveFirstNode( node<T> * pNode )
{
    node<T> * pNode1;
    if( this->pHeadNode == NULL )
    {
        pNode = NULL;
    }
    else
    {
        pNode = this->pHeadNode;
        pNode1 = this->pHeadNode->pNextNode;
        pNode1->pPrevNode = NULL;
        this->pHeadNode = pNode1;
    }
    
    return (unsigned char)0;
}

template <class T> unsigned char list<T>::listRemoveLastNode( node<T> * pNode )
{
    node<T> * pTempNode;

    if( this->pHeadNode != NULL )
    {
        pTempNode = this->pHeadNode;

        while( pTempNode->pNextNode != NULL )
        {
            pTempNode = pTempNode->pNextNode;
        }
        pNode = pTempNode;
        
        pTempNode->pPrevNode->pNextNode = NULL;
    }
    else
    {

    }
    return (unsigned char)0;    
}


template <class T> node<T> * list<T>::listGetNodeByPriority( unsigned char priority )
{
    node<T> * pTempNode;
    unsigned char tempPriority = 0xFF;
    pTempNode = this->pHeadNode;
    if( pTempNode != NULL )
    {
        while( ( pTempNode != NULL ) && ( tempPriority != priority ) )
        {
            pTempNode = pTempNode->pNextNode;
            tempPriority = pTempNode->nodeGetNodePriority(); 
        } 
    }
    else
    {
    }
    return pTempNode;
}

template <class T> node<T> * list<T>::listGetNodeByPosition( unsigned char position )
{
    node<T> * pTempNode;
    unsigned char i;

    pTempNode = this->pHeadNode;
    
    if( pTempNode != NULL )
    {
        for( i = 0; i < position; i++ )
        {
            if( pTempNode != NULL )
            {
                pTempNode = pTempNode->pNextNode;
            }
            else
            {
                break; 
            }  
        }
        
    }
    return pTempNode;
}

template <class T> node<T> * list<T>::listGetFirstNode( void )
{
    node<T> * pTempNode;

    if( this->pHeadNode != NULL )
    {
        pTempNode = this->pHeadNode;
    }
    else
    {
        pTempNode = NULL;
    }

    return pTempNode;   
}

template <class T> node<T> * list<T>::listGetLastNode( void )
{
    node<T> * pTempNode;
    pTempNode = this->pHeadNode;

    while( pTempNode->pNextNode != NULL )
    {
        pTempNode = pTempNode->pNextNode;
    }

    return pTempNode;
}
template class list<task>; 

