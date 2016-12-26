#include "node.h"

node::node(void)
{
    this->pPrevNode = NULL;
    this->pNextNode = NULL;
    this->pNodeData = NULL;
}

node::node( void * pData )
{
    this->pPrevNode = NULL;
    this->pNextNode = NULL;
    this->pNodeData = pData;
}

node::~node(void)
{
}

void node::nodeSetNodeData( void * pData )
{
    this->pNodeData = pData;
}

void * node::nodeGetNodeData( void )
{
    return this->pNodeData;
}

void node::nodeSetNodePriority( unsigned char priority )
{
    this->priority = priority;
}

unsigned char node::nodeGetNodePriority( void )
{
    return this->priority;
}
