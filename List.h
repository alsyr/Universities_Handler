/*
 Team 6
 */

// Specification file for the List class
#ifndef LIST_h
#define LIST_h

#include <string>
#include "Hash.h"
#include "BST.h"
#include "Heap.h"
#include "Object.h"
using namespace std;

class List
{
private:
    int count;
    int arySize;
    int bucketSize;
    Hash *pHash;
    BST *pTree;
    Heap *pHeap;
    
public:
    // Constructor
    List();
    
    // Destructor
    ~List();
    
    // Binary Tree operations
    void insertList(University *univIn);
    bool searchList(int target, University &univ);
    bool searchListForDuplicate(int target, University &univ);
    void displayList();
    void displaySortedList();
    void displayIndentedList();
    void displayHashStats();
    void print();
    void stats();
    void deleteList(int target);
    void displayMostSearched();
    void writingTxt();
    
};

#endif
