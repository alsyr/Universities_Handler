/*
 Team 6
 */


// Specification file for the Heap class
#ifndef HEAP_H
#define HEAP_H

#include <string>
#include "Object.h"
using namespace std;

class Heap
{
private:
    struct ITEM_Heap
    {
        University *university;
    };
    
    ITEM_Heap **theHeap;   // Pointer to dynamically allocated array
    int numElements;        // Number of elements in the heap
    int arrayLength;        // Size of the array
    
public:
    // Constructor
    Heap();
    
    // Destructor
    ~Heap();
    
    // Heap operations
    void reheapDown(int root, int bottom);   // Reheap after removing item
    void reheapUp(int root, int bottom);     // Reheap after inserting item
    void insertHeap(University *univIn);            // Add an item to the heap
    //bool Enqueue(int key, double data);      // Add an item to the heap
    void deleteTop();                       // Delete the item at the root
    University * getTop();                       // Delete the item at the root
    int getNumElementsHeap();                    // Return number of elements in the heap
    void printAllHeap();                         // Print all the elements in the heap
    void printHeapTop();                         // Print the root of the heap
    void sortHeap();                               // Sort an existing heap
    
    
};
#endif
