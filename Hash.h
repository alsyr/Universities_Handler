/*
 Team 6
 */


// Specification file for the Hashed Table class
#ifndef HASH_H
#define HASH_H

#include <string>
#include "Object.h"
using namespace std;

class Hash
{
private:
    struct ITEM_Hash
    {
        University *bucket[BUCKET_SIZE];
        int bucketIndex;
        bool isTheBucketFull = false;
    };
    
    ITEM_Hash **theTable;
    int collision;
    double numberKeys;
    int fullBuckets;
    
public:
    // Constructor
    Hash();
    
    // Destructor
    ~Hash();
    
    // Binary Tree operations
    void insertHash(University *univIn);
    bool searchHash(int target, University &univ);
    void displayHash();
    void printHash();
    void statsHash();
    void writing();
    void deleleteHash(int code);
    int hashFunc(int key);
};
#endif
