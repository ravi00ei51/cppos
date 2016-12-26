#include "list.h"
#include <iostream>

using namespace std;

void test_listCreateListTest1()
{
    unsigned int size = 10;
    list listObj(10);
    size = (unsigned int)listObj.listCreateList( NULL, 2 );
    cout<< "Size is "<<size<<endl;
}

void test_listCreateListTest2()
{
    unsigned int size = 10;
    list listObj(10);
    node * pNode[5];
    node   listNode[4];
   
    pNode[0] = &listNode[0];
    pNode[1] = &listNode[1];
    pNode[2] = &listNode[2];
    pNode[3] = &listNode[3];
    pNode[4] = NULL;
    size = (unsigned int)listObj.listCreateList( pNode, 5 );
 
    cout<< "Size is "<<size<<endl;
}

void test_listCreateListTest3()
{
    unsigned int size = 10;
    list listObj1(10);
    node * pNode[5];
    node   listNode[5];
    node * pTempNode;
    pNode[0] = &listNode[0];
    pNode[1] = &listNode[1];
    pNode[2] = &listNode[2];
    pNode[3] = &listNode[3];
    pNode[4] = &listNode[4];
    size = (unsigned int)listObj1.listCreateList( pNode, 5 );
    cout<< "Size is "<<size<<endl;
    pTempNode = listObj1.listGetFirstNode();

    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode->pNextNode)<<endl; 
}

void test_listInsertNodeTest1()
{
    unsigned int size = 10;
    list listObj1(10);
    node * pNode[5];
    node   listNode[5];
    node * pTempNode;

    size = (unsigned int)listObj1.listInsertNode( &listNode[0] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[1] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[2] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[3] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[4] );
    cout<< "Size is "<<size<<endl;
    pTempNode = listObj1.listGetFirstNode();

    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[4]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode->pNextNode)<<endl;
}

void test_listInsertNodeTest2()
{
    unsigned int size = 10;
    list listObj1(10);
    node * pNode[5];
    node   listNode[5];
    node * pTempNode;
    unsigned char pos = 0;
    size = (unsigned int)listObj1.listInsertNode( &listNode[0], pos );
    cout<< "Size is "<<size<<endl;
    pos++;
    size = (unsigned int)listObj1.listInsertNode( &listNode[1], pos );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[2], pos );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[3], pos );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[4], pos );
    cout<< "Size is "<<size<<endl;
    pTempNode = listObj1.listGetFirstNode();

    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[4]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode->pNextNode)<<endl;

}

void test_listRemoveNodeTest1()
{
    unsigned int size = 10;
    list listObj1(10);
    node * pNode[5];
    node   listNode[5];
    node * pTempNode;

    size = (unsigned int)listObj1.listInsertNode( &listNode[0] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[1] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[2] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[3] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[4] );
    cout<< "Size is "<<size<<endl;
    pTempNode = listObj1.listGetFirstNode();

    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[4]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode->pNextNode)<<endl;
    
    size = listObj1.listRemoveNode( &listNode[2] );
    cout<<endl;
    cout<< "Size is "<<size<<endl;
    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
}

void test_listInsertNodeTest3()
{
    unsigned int size = 10;
    unsigned int data[5] = { 15, 52, 23, 14, 35};
    unsigned int dataVal;
    list listObj1(10);
    node * pNode[5];
    node   listNode[5];
    node * pTempNode; 
    unsigned char pos = 0;
    size = (unsigned int)listObj1.listInsertNode( &listNode[0], (void *)&data[0]  );
    cout<< "Size is "<<size<<endl;
    pos++; 
    size = (unsigned int)listObj1.listInsertNode( &listNode[1], (void *)&data[1] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[2], (void *)&data[2] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[3], (void *)&data[3] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[4], (void *)&data[4] );
    cout<< "Size is "<<size<<endl;
    pTempNode = listObj1.listGetFirstNode();

    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[4]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode->pNextNode)<<endl;

    dataVal = *((unsigned int *)(pTempNode->nodeGetNodeData()));
    cout<<"Data is "<<dataVal<<endl;
    dataVal = *((unsigned int *)(pTempNode->pNextNode->nodeGetNodeData()));
    cout<<"Data is "<<dataVal<<endl;
    dataVal = *((unsigned int *)(pTempNode->pNextNode->pNextNode->nodeGetNodeData()));
    cout<<"Data is "<<dataVal<<endl;
    dataVal = *((unsigned int *)(pTempNode->pNextNode->pNextNode->pNextNode->nodeGetNodeData()));
    cout<<"Data is "<<dataVal<<endl;
    dataVal = *((unsigned int *)(pTempNode->pNextNode->pNextNode->pNextNode->pNextNode->nodeGetNodeData()));
    cout<<"Data is "<<dataVal<<endl;
}

void test_listRemoveNodeTest2()
{
    unsigned int size = 10;
    list listObj1(10);
    node * pNode[5];
    node   listNode[5];
    node * pTempNode;

    size = (unsigned int)listObj1.listInsertNode( &listNode[0] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[1] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[2] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[3] );
    cout<< "Size is "<<size<<endl;
    size = (unsigned int)listObj1.listInsertNode( &listNode[4] );
    cout<< "Size is "<<size<<endl;
    pTempNode = listObj1.listGetFirstNode();

    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[4]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode->pNextNode)<<endl;

    size = listObj1.listRemoveNode( 2 );
    cout<<endl;
    cout<< "Size is "<<size<<endl;
    cout<<"Address is "<<&listNode[0]<<" "<<(pTempNode)<<endl;
    cout<<"Address is "<<&listNode[1]<<" "<<(pTempNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[2]<<" "<<(pTempNode->pNextNode->pNextNode)<<endl;
    cout<<"Address is "<<&listNode[3]<<" "<<(pTempNode->pNextNode->pNextNode->pNextNode)<<endl;
}


int main()
{
   test_listCreateListTest1();
   test_listCreateListTest2();
   test_listCreateListTest3();
   test_listInsertNodeTest1();
   test_listInsertNodeTest2();
   test_listRemoveNodeTest1();
   test_listInsertNodeTest3(); 
   test_listRemoveNodeTest2();
}

 
