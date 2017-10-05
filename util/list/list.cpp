/********************************************************************************************************************************
* Module name - list.cpp
* Description - Module implemnts a doubly linked list, which serves as basic data structure for various kernel modules of 
* operating system. This module implements various APIs to manipulate a doubly linked list. Few of those APIs implement,
* insertion/deletion of a node, Getting info from a node, size of the list. Special APIs implemented to manipulate first and 
* last node of the list.
*
********************************************************************************************************************************/

/* Headers */

#include "node.h"             /* For nodes in the list  */
#include "list.h"             /* Header for list module */
#include "task.h"             /* Task header to define template list for various tasks lists, such as suspended tasks list, 
                                 delay task list */
#include "semaphore.h"        /* Semaphore header file to define template list for semaphore pend queue */
#include "schedInfo.h"        /* Scheduler header file to define template list for ready queue list for context switching */
#include "msgQ.h"
#include "events.h"
#include "ipcList.h"
/* typedefs */
/* Globals */

/********************************************************************************************************************************
* Name - list()
* Description - Constructor for list class. Initialization of different member variables is done by this function. 
* Parameters  - None
* Return      - None
********************************************************************************************************************************/

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
 
/********************************************************************************************************************************
* Name - listInit()
* Description - Initialization of different member variables is done by this function. This  function is same as the constructor 
*               except that this function can be used to reset  the list  while  running if  required. Any  data pointed by list 
*               node's will be lost. Hence when calling this function it need to be made sure that all data pointed by different 
*               node is handles properly. Improper use of this function can lead to memory leaks which  can be of great security 
*               risk.
* Parameters  - None
* Return      - None
********************************************************************************************************************************/
        

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

/********************************************************************************************************************************
* Name - listInsertNodeData()
* Description - This function inserts  node to the list with given data at the end of the list. This function can be used  as a 
*               simple API to create list. This function is overloaded by another version of this function in which node can be
*               inserted to a given position in the list. 
* Parameters  - Pointer to the data which needs to be held by the list's node. If NULL is passed then function simply returns an 
*               FALSE.
* Return      - Function retuen TRUE or FALSE depending upon the situation. If function inserts node sucessfully then it return 
*               TRUE otherwise FALSE. 
********************************************************************************************************************************/

template <class T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listInsertNodeData( T *& pData )
{
    node<T> * pTempNode;
    node<T> * pNode;
    BOOLEAN   retVal;
    /* Check if data pointer passed is valid */
    if( pData != NULL )
    {
        /* Check if the list is already maxed out */
        if( this->listNodeCount < maxNumberOfNodes )
        {
            /* Get head node */
            pTempNode    = this->pHeadNode;

            /* Allocate a new node to hold the data */
            pNode        = this->listAllocateNode();
            /* check if node is allocated successfully */
            if( pNode != NULL )
            {
                /* Node allocated successfully. Assign the data */
                pNode->pData = pData;
                /* Check if list is initialized by checking if head node is NULL or not. This means list 
                   already has existing nodes and last node need to be found. */
                if( pTempNode != NULL )
                {
                    /* List is initialized. look for the last node */ 
                    while( pTempNode->pNext != NULL )
                    {
                           pTempNode = pTempNode->pNext;
                    }
                    /* last node found. attach the new node at the end. */     
                    pTempNode->pNext = pNode;
                    pNode->pPrev     = pTempNode;
                    pNode->pNext     = NULL;
                }
                else
                {
                    /* list is empty. Hence add node at head Node */
                    this->pHeadNode = pNode;
                    pNode->pNext    = NULL;
                    pNode->pPrev    = NULL;
                }
                /* Node is successfully added. Increase node count for the list */
                retVal = TRUE;
                this->listNodeCount++;
            }
            else
            {
                /* Node cant be allocated. Set return value to indicate error */   
                retVal = FALSE;
            }   
        }
        else
        {
            /* List is already maxed out. Set return value to indicate error */ 
            retVal = FALSE;
        }   
    }
    else
    {
        /* Data assigned for Node is NULL. Set return value to indicate error */
        retVal = FALSE;
    }

    return retVal;
}

/********************************************************************************************************************************
* Name - listRemoveNodeData()
* Description - This function removes last node from the list.  This function deletes the node and passes the data pointed by 
*               node to the pointer passed as an argument. This function is overloaded by another version of this function in 
*               which node can be removed from a given position in the list. 
* Parameters  - Pointer to the data which needs to be held by the list's node. If NULL is passed then function simply returns an 
*               FALSE.
* Return      - Function retuen TRUE or FALSE depending upon the situation. If function removes node sucessfully then it return 
*               TRUE otherwise FALSE. 
********************************************************************************************************************************/

template <class T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listRemoveNodeData( T *& pData )
{
    node<T> * pTempNode;
    node<T> * pNode;   
    BOOLEAN   retVal;

    /* Check if list has nodes to remove and list is not maxed out */   
    if( ( this->listNodeCount > 0 ) && ( this->listNodeCount <= maxNumberOfNodes ) )
    {
        pTempNode = this->pHeadNode;
        /* Check if head node is NULL or not. We have already checked node count in the list hence  this is 
           an extra check to make sure that somehow the list is not corrupted. If head node is NULL at this 
           stage then it means that list is compromised or corrupted. */
        if( pTempNode != NULL )
        {
            /* Find the last node in the list by traversing the list until end */
            while( pTempNode->pNext != NULL )
            {
                pTempNode = pTempNode->pNext; 
            }
            /* last Node is found */
            if( pTempNode->pPrev != NULL )
            {
                /* Case: if last node is not the head node */
                pNode            = pTempNode;
                pData            = pNode->pData;   /* Assign data to passed argument */
                pTempNode        = pNode->pPrev;
                pTempNode->pNext = NULL;  
                pNode->pNext     = NULL;
                this->listNodeCount--;
                this->listFreeNode(pNode);
                retVal = TRUE;
            }
            else
            {
                /* Case: last node is head node */
                pNode            = pTempNode;
                pData            = pNode->pData;   /* Assign data to passed argument */
                pTempNode->pNext = NULL;
                pTempNode        = NULL; 
                pNode->pNext     = NULL;
                this->listNodeCount--;
                this->listFreeNode(pNode);
                retVal = TRUE;
            }
        }
        else
        {
            /* List is empty */
            retVal = FALSE;
        }
    }
    else
    {
        /* List is either empty or maxed out */    
        retVal = FALSE;
    }
    return retVal;
}

/**
*********************************************************************************************************************************
* Name - listInsertNodeData()
*
* Description - This function inserts  node to the list with given data at given position in the list. 
*
* Parameters  - Pointer to the data which needs to be held by the list's node. If NULL is passed then function simply returns an 
*               FALSE.
*               position where node need to be inserted in the list.
*
* Return      - Function retuen TRUE or FALSE depending upon the situation. If function inserts node sucessfully then it return 
*               TRUE otherwise FALSE. 
********************************************************************************************************************************/

template <typename T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listInsertNodeData( T *& pData, uint8_t pos )
{
    uint8_t   i;
    node<T> * pTempNode1 = NULL;
    node<T> * pTempNode2 = NULL;
    node<T> * pNode;
    BOOLEAN   retVal;
    /* Check if list is not maxed out */
    if( this->listNodeCount < maxNumberOfNodes )
    {   
        /* 
           list still has spaces to fill. Check if the location to fill in the list is valid.
           For example if the list has two nodes and current node need to be inserted at 4th 
           position then its not possible because 3rd node is not yet filled. Only valid 
           location for this example are 1st, 2nd and 3rd. 
        */
        if( pos <= ( this->listNodeCount + 1 ) )
        {
            /* Position of node is validated. Allocate a new node now */
            pNode = this->listAllocateNode();
  
            /* Check if node is allocated successfully */
            if( pNode != NULL )
            {
                /* Assign data to the node and locate head node of the list to traverse the list */
                pTempNode1   = this->pHeadNode;
                pNode->pData = pData;  
                /* Check if head node is not NULL */ 
                if( pTempNode1 != NULL )
                {
                    /* 
                      Traverse to the intended position in the list and save the node at intended 
                      position and after that 
                    */
                    for( i = 0; ( i < ( pos - 1 ) ) && ( pTempNode1 != NULL ); i++ )
                    {
                        pTempNode2 = pTempNode1;
                        pTempNode1 = pTempNode1->pNext;         
                    }

                    if( ( i == ( pos - 1 ) ) )
                    {
                        if( ( pTempNode1 != NULL ) && ( pTempNode2 != NULL ) )
                        {
                            /* Case: location is in between two nodes */
                            pTempNode2->pNext = pNode;
                            pTempNode1->pPrev = pNode;
                            pNode->pNext      = pTempNode1;
                            pNode->pPrev      = pTempNode2;
                            retVal            = TRUE;
                            this->listNodeCount++;
                        }
                        else if( ( pTempNode1 == NULL ) && ( pTempNode2 != NULL ) )
                        {
                            /* location is at the end of the list */
                            pTempNode2->pNext = pNode;
                            pNode->pNext      = NULL;
                            pNode->pPrev      = pTempNode2;
                            retVal            = TRUE;
                            this->listNodeCount++;
                        }  
                        else if( ( pTempNode1 != NULL ) && ( pTempNode2 == NULL ) )
                        {
                            /* location is at the start i.e. just after head node */
                            pNode->pNext      = pTempNode1;
                            pNode->pPrev      = NULL;
                            pTempNode1->pPrev = pNode;
                            this->pHeadNode   = pNode;
                            retVal            = TRUE;
                            this->listNodeCount++;
                        }
                        else
                        {
                            /* Code should never reach here. But if it does something is wrong with the list */
                            retVal = FALSE;
                        }
                    }
                    else
                    {
                        /* Code should never reach here. But if it does something is wrong with the list */
                        retVal = FALSE;
                    }
                }
                else
                {
                    if( pos == 1 )
                    {
                        /* Case: node to be inserted at head node */           
                        this->pHeadNode  = pNode;
                        pNode->pNext     = NULL;
                        pNode->pPrev     = NULL;
                        retVal           = TRUE; 
                        this->listNodeCount++;
                    }
                    else
                    {
                        /* Code should never reach here. But if it does something is wrong with the list */
                        retVal       = FALSE;
                    }
                }
            }
            else
            {
                /* node allocation failed */
                retVal = FALSE;
            }
        }
        else
        {
            /* location of insertion is invalid */
            retVal = FALSE;
        }
    }
    else
    {
        /* List is maxed out */
        retVal = FALSE;
    } 
    return retVal;   
}

/**
*********************************************************************************************************************************
* Name - listRemoveNodeData()
*
* Description - This function removes a node from given positionthe list.  This function deletes the node and passes the data 
*               pointed by node to the pointer passed as an argument.
* 
* Parameters  - Pointer to the data which needs to be held by the list's node. If NULL is passed then function simply returns an 
*               FALSE.
*               position from where node need to be deleted.
*
* Return      - Function retuen TRUE or FALSE depending upon the situation. If function removes node sucessfully then it return 
*               TRUE otherwise FALSE. 
********************************************************************************************************************************/

template <typename T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listRemoveNodeData( T *& pData, uint8_t pos )
{
    uint8_t   i;
    node<T> * pTempNode1;
    node<T> * pTempNode2;
    node<T> * pNode;
    BOOLEAN   retVal;
    /* Check if list is not empty or corrupted */
    if( ( this->listNodeCount <= maxNumberOfNodes ) && ( this->listNodeCount > 0 ) )
    {
        /* Check if position of node to be removed is in valid range */ 
        if( ( pos <= this->listNodeCount ) && ( pos > 0 ) )
        {
            /* Get head Node */
            pNode = this->pHeadNode;
            /* 
               Check if Head node is NULL, i.e. list is initialized. This is an extra check 
               as node count already confimrd that list is initialized. If this step  fails 
               the list is either compromised or corrupted 
            */
            if( pNode != NULL )
            {
                /* Find the intended node location */
                for( i = 0; (i < ( pos - 1 )) && ( pNode != NULL ); i++ )
                {
                    pNode = pNode->pNext;
                }
                if( ( i == ( pos - 1 ) ) && ( pNode != NULL ) )
                {
                    /* Node is found. Assign data to argument pointer */
                    pData             = pNode->pData;
                    pTempNode1        = pNode->pNext;
                    pTempNode2        = pNode->pPrev;  
                    
                    if( ( pTempNode1 != NULL ) && ( pTempNode2 != NULL ) ) 
                    {
                        /* Case: if node is between two valid nodes */
                        pTempNode2->pNext = pTempNode1;
                        pTempNode1->pPrev = pTempNode2;
                    }
                    else if( ( pTempNode1 == NULL ) && ( pTempNode2 != NULL ) )
                    {
                        /* Case: if node last node in the list */ 
                        pTempNode2->pNext = NULL;
                    }
                    else if( ( pTempNode1 != NULL ) && ( pTempNode2 == NULL ) )
                    {
                        /* if the node is first node in the list */
                        pTempNode1->pPrev = NULL;
                        this->pHeadNode   = pTempNode1;
                    }
                    else 
                    {
                    }
                    /* Free the node */
                    pNode->pNext      = NULL;
                    pNode->pPrev      = NULL;
                    
                    this->listFreeNode( pNode );
                    this->listNodeCount--;
                    retVal = TRUE;
                }
                else
                {
                    /* Node is not found. List is compromised, corrupted or some race issue has occurred */
                    retVal = FALSE;
                }
            }
            else
            {
                /* Node is not allocated successfully */
                retVal = FALSE;
            }
        }
        else
        {
            /* Given node position is invalid */
            retVal = FALSE;
        }
    }
    else
    {
        /* List is empty */ 
        retVal = FALSE;
    }
    return retVal;
}

/**
*********************************************************************************************************************************
* Function name - listGetNodeData()
*
* Description - This function returns the data held by a node at given position in the list. Please note that  unlike 
*               listRemoveNodeData() this function does not remove the node from list. it simply provides the data to 
*               the caller.The list remains same before and after this function call.
* 
* Parameters  - Pointer to the data which will hold the data at given position in the list.
*               position of the node from which data need to be retrived.
* 
* Return      - Function returns TRUE or FALSE depending upon the situation. If function retrives the data sucessfully then it 
*               returns TRUE otherwise FALSE. 
********************************************************************************************************************************/

template <class T, uint32_t maxNumberOfNodes> BOOLEAN list<T, maxNumberOfNodes>::listGetNodeData( T *& pData, uint8_t pos )
{
    node<T> * pTempNode;
    uint8_t   i = 0;
    BOOLEAN   retVal;
    /* Check if list is not empty */
    if( ( this->listNodeCount <= maxNumberOfNodes ) && ( this->listNodeCount > 0 ) )
    {
        /* Check if enquired position is valid or not */    
        if( ( pos <= this->listNodeCount ) && ( pos > 0 ) )
        {
            /* Get head node */
            pTempNode = this->pHeadNode;
            /*
               Check if head node is NULL or not. Head not should not be NULL as we have verified that 
               list is not empty by checking node count. If head node is NULL then it means that  list
               is either compromised or some corruption has happened.
            */
            if( pTempNode != NULL )
            {
                /* Traverse list to find the node */
                for( i = 0; (i < ( pos - 1 ) ) && ( pTempNode->pNext != NULL ); i++ )
                {
                    pTempNode = pTempNode->pNext;
                }
                /* Node is found */
                if(  i == ( pos - 1 ) )
                {  
                     /* Assign data to passed pointer */     
                     pData  = pTempNode->pData;
                     retVal = TRUE;
                }
                else
                {
                    /* Node not found */
                    pData  = NULL;
                    retVal = FALSE;
                }
            }
            else
            {
                /* list is empty or corrupted */
                pData  = NULL;
                retVal = FALSE;
            }
        }
        else
        {
            /* position is not valid */   
            pData  = NULL;
            retVal = FALSE;
        }
    }
    else
    {
        /* List is empty */
        pData  = NULL;
        retVal = FALSE;
    }

    return retVal;
}

/**
*********************************************************************************************************************************
* Function name - listGetNodePosition()
*
* Description - This function returns the position of the node which holds a given data in the list.
* 
* Parameters  - Pointer to the data whose position need to be located in the list.
* 
* Return      - Function returns position of the node for given data. If data is not present in the list then function returns 
*               NODE_NOT_FOUND. For a programmer its not a good idea to make any assumptions about NODE_NOT_FOUND as it can 
*               change in different version of the OS.
********************************************************************************************************************************/

template <class T, uint32_t maxNumberOfNodes> uint8_t list<T, maxNumberOfNodes>::listGetNodePosition( T *& pData )
{
    node<T> * pTempNode = NULL;
    uint8_t   i = 1;
    uint8_t   retVal;
    BOOLEAN   nodeFound = FALSE;
    
    /* Check if list is not empty */
    if( ( this->listNodeCount > 0 ) && ( this->listNodeCount < maxNumberOfNodes ) )
    {
        pTempNode = this->pHeadNode;   
        /*
          Check if head node is NULL or not. Head not should not be NULL as we have verified that 
          list is not empty by checking node count. If head node is NULL then it means that  list
          is either compromised or some corruption has happened.
        */

        if( pTempNode != NULL )
        {
            /* Match given data to the data present at each node in the list. At first match break from the loop */
            for( i = 0; i < this->listNodeCount; i++ )
            {
                if( pTempNode->pData == pData )
                {
                    nodeFound = TRUE;
                    retVal    = i;
                    retVal++;
                    i         = this->listNodeCount;
                 }
                 else
                 {
                     pTempNode = pTempNode->pNext;
                 }
            }
        }
    }
    
    if( nodeFound == FALSE )
    {
        retVal = NODE_NOT_FOUND;
    }
    return (uint8_t)retVal;  
}

/**
*********************************************************************************************************************************
* Function name - listInsertFirstNodeData()
*
* Description - As the function name suggests this function inserts a node at first position in the list with given data.
* 
* Parameters  - Pointer to the data which needs to be held at first position in the list.
* 
* Return      - None
********************************************************************************************************************************/

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listInsertFirstNodeData( T *& pData )
{
    (void)this->listInsertNodeData( pData, 1u );
}

/**
*********************************************************************************************************************************
* Function name - listRemoveFirstNodeData()
*
* Description - As the function name suggests this function removes node at first position in the list.
* 
* Parameters  - Pointer which points to the data held by first node( which is removed ).
* 
* Return      - None
********************************************************************************************************************************/

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listRemoveFirstNodeData( T *& pData )
{
    this->listRemoveNodeData( pData, 1u );   
}

/**
*********************************************************************************************************************************
* Function name - listInsertLastNodeData()
*
* Description - As the function name suggests this function inserts a node at the end of the list with given data.
* 
* Parameters  - Pointer to the data which needs to be put at the end of the list.
* 
* Return      - None
********************************************************************************************************************************/

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listInsertLastNodeData( T *& pData )
{
    (void)this->listInsertNodeData( pData ); 
}

/**
*********************************************************************************************************************************
* Function name - listRemoveLastNodeData()
*
* Description - As the function name suggests this function removes the node at the end of the list.
* 
* Parameters  - Pointer which holds the data of the node removed.
* 
* Return      - None
********************************************************************************************************************************/

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listRemoveLastNodeData( T *& pData )
{
    (void)this->listInsertNodeData( pData ); 
}

/**
*********************************************************************************************************************************
* Function name - listGetFirstNodeData()
*
* Description - As the function name suggests this function returns the data held by first node in the list. This function does 
*               not remove the node from the list. List remains same before and after execution of this function.
* 
* Parameters  - Pointer which holds the data of the first node after this function is executed.
* 
* Return      - None
********************************************************************************************************************************/

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listGetFirstNodeData( T *& pData )
{
    (void)this->listGetNodeData( pData, 1u );    
}

/**
*********************************************************************************************************************************
* Function name - listGetLastNodeData()
*
* Description - As the function name suggests this function returns the data held by last node in the list. This function does 
*               not remove the node from the list. List remains same before and after execution of this function.
* 
* Parameters  - Pointer which holds the data of the last node after this function is executed.
* 
* Return      - None
********************************************************************************************************************************/

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listGetLastNodeData( T *& pData )
{
        (void)this->listGetNodeData( pData, this->listNodeCount ); 
}


/********************************************************************************************************************************
* Private function for class list
********************************************************************************************************************************/

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
/********************************************************************************************************************************
* Private function for class list
********************************************************************************************************************************/

template <class T, uint32_t MAX_NUMBER_OF_NODES> void list<T, MAX_NUMBER_OF_NODES>::listFreeNode( node<T> * pNode )
{
    pNode->pNext = NULL;
    pNode->pPrev = NULL;
    pNode->pData = NULL;
}

template <class T, uint32_t MAX_NUMBER_OF_NODES> uint8_t list<T, MAX_NUMBER_OF_NODES>::listNumberOfNodes( void )
{
    return this->listNodeCount;
}
template class list<task, 6>;
template class list<schedInfo, 6>;
template class list<queueNode, 10u>;
template class list<pendNode, 6u>;
template class list<eventNodeType, 6>;
template class list<ipcNodeType, 6>;
