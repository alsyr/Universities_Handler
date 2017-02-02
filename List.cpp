/*
 Team 6
 */

/*
 List is the task manager of all 3 structures: the heap, the hash and the bst
 */

// Implementation file for the List class
#include <iostream>  // For cout and NULL
#include <iomanip>   // For setw
#include "List.h"

using namespace std;

/**~*~*
 Constructor
 *~**/
List::List()
{
    count = 0;
    arySize = TABLE_SIZE;
    bucketSize = BUCKET_SIZE;
    pHash = new Hash;
    pTree = new BST;
    pHeap = new Heap;
}

/**~*~*
 Insert data into the list
 Everytime a university is added to the program,
 The pointer to that data is added to all 3 structures
 *~**/
void List::insertList(University *univIn)
{
    pTree->insertBST(univIn);
    pHash->insertHash(univIn);
    pHeap->insertHeap(univIn);
    count++;
}

/**~*~*
 Search a Listed Table for a given target by getting the home address associated with.
 Then it is searched in the hashed table.
 if found, returns true, otherwise returns false.
 *~**/
bool List::searchListForDuplicate(int target, University &univ)
{
    return pHash->searchHash(target, univ);
}

/**~*~*
 Search a Listed Table for a given target by getting the home address associated with.
 Then it is searched in the hashed table.
 if found, returns true, passes back data and then resort the heap, otherwise returns false.
 *~**/
bool List::searchList(int target, University &univ)
{
    bool exist;
    exist = pHash->searchHash(target, univ);
    pHeap->sortHeap();

    return exist;
}

/**~*~*
 List data in hashed table sequence.
 *~**/
void List::displayList()
{
    cout << "\n********************************************************************\n";
    pHash->printHash();
    cout << "********************************************************************\n";
}

/**~*~*
 List data in key sequence by using the inorder traversal of the bst.
 *~**/
void List::displaySortedList()
{
    cout << "\n********************************************************************\n";
    pTree->inorderTraverse();
    cout << "********************************************************************\n";
}

/**~*~*
 Print indented tree of the bst.
 *~**/
void List::displayIndentedList()
{
    cout << "\n********************************************************************\n";
    pTree->indentedTraverse();
    cout << endl;
    cout << "********************************************************************\n";
}

/**~*~*
 Print statistics of the hashed table, such as number 
 of collisions, load factor and number of full buckets.
 *~**/
void List::displayHashStats()
{
    cout << "\n********************************************************************\n";
    pHash->statsHash();
    cout << "********************************************************************\n";
}

/**~*~*
 Delete a university from the list.
 *~**/
void List::deleteList(int target)
{
    pHash->deleleteHash(target);
	pTree->removeNode(target);
}

/**~*~*
Display the most frequently searched university by using the root of the heap.
 *~**/
void List::displayMostSearched()
{
    cout << "\n********************************************************************\n";
    if(pHeap->getTop()->searchCount != 0)
        pHeap->printHeapTop();
    else
        cout << "\tNo university has been searched yet." << endl;
    cout << "********************************************************************\n";
}

/**~*~*
 Write an output file based on hash table sequence
 *~**/
void List::writingTxt()
{
	pHash->writing();
    cout << "\n********************************************************************\n";
	cout << "\tDone! check the 'output' txt in the repertory file" << endl;
    cout << "********************************************************************\n";
}

/**~*~*
 Destructor
 *~**/
List::~List()
{
    delete pHash;
    delete pTree;
}