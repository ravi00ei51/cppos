#include "list.h"
#include <iostream>
using namespace std;
list::list( void )
{
}

list::list( unsigned char maxSize )
{
    this->listMaxSize = maxSize;
    this->pHeadNode   = NULL;
    this->nodeCount   = 0;
}

list::list( void * pData )
{
}

list::list( unsigned char size, unsigned char priority )
{
}

list::list( unsigned char priority, void * pData )
{
}

list::list( unsigned char size, unsigned char priority, void * pData )
{
}

unsigned char list::listCreateList( node * pNode[], unsigned char size )
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
            retVal = i+1;
        }
    }
    this->nodeCount = retVal;      
    return retVal;
}

void list::listDestroyList( void )
{
    this->pHeadNode = NULL;
}

unsigned char list::listInsertNode( node * pNode )
{
    node * pTempNode;
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

unsigned char list::listInsertNode( node * pNode, void * pData )
{
    node * pTempNode;
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

unsigned char list::listInsertNode( node * pNode, unsigned char position )
{
    node * pTempNode = NULL;
    node * pNode1 = NULL;
    node * pNode2 = NULL;
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
        cout<<"1. The position is "<<(unsigned int)i<<" "<<pTempNode<<endl;
    }
    else
    {
        cout<<"2. The position is "<<(unsigned int)i<<" "<<pTempNode<<endl;
        this->pHeadNode  = pNode;
        pNode->pPrevNode = NULL;
        pNode->pNextNode = NULL;
        this->nodeCount++;
    }
    
    if( pTempNode != NULL )
    {
        if( pTempNode->pNextNode != NULL )
        {
            cout<<"3. The position is "<<(unsigned int)i<<" "<<pTempNode<<endl; 
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
            cout<<"4. The position is "<<(unsigned int)i<<" "<<pTempNode<<endl;
            pTempNode->pNextNode = pNode;
            pNode->pPrevNode     = pTempNode;   
            pNode->pNextNode     = NULL;  
            this->nodeCount++;       
        }
    }
    return this->nodeCount; 
}

unsigned char list::listRemoveNode( node * pNode )
{
    node * pNode1;
    node * pNode2;
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

unsigned char list::listRemoveNode( unsigned char position )
{
    node * pTempNode;
    node * pNode1;
    node * pNode2;
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

unsigned char list::listInsertNodeByAcsendingPriority( node * pNode )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node *        pTempNode;
    node *        pNode1;
    node *        pNode2;

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
}

unsigned char list::listInsertNodeByAcsendingPriority( node * pNode, void * pData )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node *        pTempNode;
    node *        pNode1;
    node *        pNode2;
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
}

unsigned char list::listInsertNodeByDescendingPriority( node * pNode )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node *        pTempNode;
    node *        pNode1;
    node *        pNode2;

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

}

unsigned char list::listInsertNodeByDescendingPriority( node * pNode, void * pData )
{
    unsigned char inserNodePriority;
    unsigned char tempNodePriority;
    node *        pTempNode;
    node *        pNode1;
    node *        pNode2;
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

}

unsigned char list::listInsertFirstNode( node * pNode )
{
    node * pNode1;
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
}

unsigned char list::listInsertLastNode( node * pNode )
{
    node * pTempNode;
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
}

unsigned char list::listRemoveFirstNode( node * pNode )
{
    node * pNode1;
    if( this->pHeadNode == NULL )
    {
    }
    else
    {
        pNode = this->pHeadNode;
        pNode1 = this->pHeadNode->pNextNode;
        pNode1->pPrevNode = NULL;
        this->pHeadNode = pNode1;
    }
    
}

unsigned char list::listRemoveLastNode( node * pNode )
{
    node * pTempNode;

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
}


node * list::listGetNodeByPriority( unsigned char priority )
{
    node * pTempNode;
    unsigned char tempPriority;
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

node * list::listGetNodeByPosition( unsigned char position )
{
    node * pTempNode;
    node * pNode1;
    node * pNode2;
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

node * list::listGetFirstNode( void )
{
    node * pTempNode;

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

node * list::listGetLastNode( void )
{
    node * pTempNode;
    pTempNode = this->pHeadNode;

    while( pTempNode->pNextNode != NULL )
    {
        pTempNode = pTempNode->pNextNode;
    }

    return pTempNode;
}
   
