/*
 Team 6
 */


/*
 The heap keeps update the most searched universities
 */


// Implementation file for the Heap class
#include <iostream>  // For cout and NULL
#include <iomanip>   // For setw
#include "Heap.h"

using namespace std;


/**~*~*
 Constructor
 *~**/
Heap::Heap()
{
    theHeap = new ITEM_Heap*[TABLE_SIZE];
    
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        theHeap[i] = NULL;
    }
    
    numElements = 0;
    arrayLength = TABLE_SIZE;
}


//---------------------------------------
// Reheap after inserting item
//---------------------------------------
void Heap::reheapUp(int root, int bottom)
{
    int parent;
    ITEM_Heap *temp;
    
    // Check base case in recursive calls.  If bottom's index is greater
    // than the root index we have not finished recursively reheaping.
    if(bottom > root)
    {
        parent = (bottom -1) / 2;
        if(theHeap[parent]->university->searchCount < theHeap[bottom]->university->searchCount)
        {
            // Swap these two elements
            temp = theHeap[parent];
            theHeap[parent] = theHeap[bottom];
            theHeap[bottom] = temp;
            // Make recursive call till reheaping completed
            reheapUp(root, parent);
        }
    }
}


//---------------------------------------
// Reheap after removing item
//---------------------------------------
void Heap::reheapDown(int root, int bottom)
{
    int maxChild;
    int rightChild;
    int leftChild;
    ITEM_Heap *temp;
    
    leftChild = root * 2 + 1;          // Get index of root's left child
    rightChild = root * 2 + 2;          // Get index of root's right child
    
    // Check base case in recursive calls.  If leftChild's index is less
    // than or equal to the bottom index we have not finished recursively
    // reheaping.
    if(leftChild <= bottom)
    {
        if(leftChild == bottom)          // If this root has no right child then
        {
            maxChild = leftChild;     //     leftChild must hold max key
        }
        else
        {     //Get the one lowest in the tree (highest index in the array)
            if(theHeap[leftChild]->university->searchCount <= theHeap[rightChild]->university->searchCount)
                maxChild = rightChild;
            else
                maxChild = leftChild;
        }
        if(theHeap[root]->university->searchCount < theHeap[maxChild]->university->searchCount)
        {
            // Swap these two elements
            temp = theHeap[root];
            theHeap[root] = theHeap[maxChild];
            theHeap[maxChild] = temp;
            //Make recursive call till reheaping completed
            reheapDown(maxChild, bottom);
        }
    }
}


//---------------------------------------
// Add an item to the heap
//---------------------------------------
void Heap::insertHeap(University *univIn)
{
    if(numElements < arrayLength)
    {
        ITEM_Heap *newItem = new ITEM_Heap;
        newItem->university = univIn;
        
        theHeap[numElements] = newItem; // Copy item into array
        reheapUp(0, numElements);
        numElements++;
    }
}


//---------------------------------------
// Return number of elements in the heap
//---------------------------------------
int Heap::getNumElementsHeap()
{
    return numElements;
}


//---------------------------------------
// Print all the elements in the heap
//---------------------------------------
void Heap::printAllHeap()
{
    for(int i=0; i<numElements; i++)
    {
        cout << "Heap element " << i << " is: " << theHeap[i]->university->code << "-" <<
        theHeap[i]->university->name << " with searchCount: " << theHeap[i]->university->searchCount << endl;
    }
}


//---------------------------------------
// Print all the elements in the heap
//---------------------------------------
void Heap::printHeapTop()
{
    cout << "\n\tThe most searched university is:";
    cout << "\n\tName    : " << theHeap[0]->university->name;
    cout << "\n\tState   : " << theHeap[0]->university->state;
    cout << "\n\tTuition : " << theHeap[0]->university->tuition;
    cout << "\n\tCode    : " << theHeap[0]->university->code << endl << endl;
}


//---------------------------------------
// Delete item at the root
//---------------------------------------
void Heap::deleteTop()
{
    numElements--;
    // Copy last item into root
    theHeap[0] = theHeap[numElements];
    // Reheap the tree
    reheapDown(0, numElements - 1);
}


//---------------------------------------
// Get item at the root
//---------------------------------------
University *Heap::getTop()
{
    University *temp = theHeap[0]->university;
    return temp;
}


//---------------------------------------
// Sort the Heap
// Keep update the most searched university
// in the heap
//---------------------------------------
void Heap::sortHeap()
{
    for (int i = numElements-1; i >= 1; i--)
    {
        University *temp = theHeap[i]->university;
        theHeap[i]->university = theHeap[0]->university;
        theHeap[0]->university = temp;
        reheapUp(0, i);
    }
}


/**~*~*
 Destructor
 This function deletes all elements of the array.
 *~**/
Heap::~Heap()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        delete theHeap[i];
    delete[] theHeap;
}