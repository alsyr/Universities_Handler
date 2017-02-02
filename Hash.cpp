/*
 Team 6
 */

/*
 The hash makes the search function of the global function faster
 */


// Implementation file for the Hash class
#include <iostream>  // For cout and NULL
#include <iomanip>   // For setw
#include <fstream>
#include "Hash.h"

using namespace std;

/**~*~*
 Constructor
 *~**/
Hash::Hash()
{
    theTable = new ITEM_Hash*[TABLE_SIZE];
    
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        theTable[i] = NULL;
    }
    collision = 0;
    numberKeys = 0;
    fullBuckets = 0;
}

/**~*
 hashFunction is the function
 which get int key and return
 the home address
 *~*/
int Hash::hashFunc(int key)
{
    return key % TABLE_SIZE;
}

/**~*~*
 Insert data into a Hashed Table
 *~**/
void Hash::insertHash(University *univIn)
{
    int index = hashFunc(univIn->code); //Finding the home address
    
    //If the address is occupied and the bucket is not full
    if (theTable[index] != NULL && !theTable[index]->isTheBucketFull)
    {
        //Inserting the data in the next empty slot in the bucket
        theTable[index]->bucket[theTable[index]->bucketIndex] = univIn;
        collision++; //Incrementing the number of collision for that bucket
        //Incrementing the counter of full buckets and setting to true the witness
        if(theTable[index]->bucketIndex == BUCKET_SIZE-1)
        {
            fullBuckets++;
            theTable[index]->isTheBucketFull = true;
        }
    }
    
    //If the address is occupied and the bucket is full
    else if (theTable[index] != NULL && theTable[index]->isTheBucketFull)
    {
        cout << "Error, the bucket " << index << " is full." << endl;
    }
    
    else //If the address is empty
    {
        ITEM_Hash *newItem = new ITEM_Hash;
        newItem->bucket[0] = univIn;

        theTable[index] = newItem;
    }
    
    theTable[index]->bucketIndex++; //Increment the index of the bucket for a potential collision
    numberKeys++; //Increment the number of keys inserted in the hashed table
}


/**~*~*
 Search a Hashed Table for a given target by getting the home address associated with.
 if found, returns true and passes back data, otherwise returns false.
 *~**/
bool Hash::searchHash(int target, University &univ)
{
    int index = hashFunc(target); //Finding the home address
    if (theTable[index] != NULL)
    {
        for (int i=0; i<theTable[index]->bucketIndex; i++)
        {
            if (theTable[index]->bucket[i]->code == target)
            {
                univ = *(theTable[index]->bucket[i]);
                theTable[index]->bucket[i]->searchCount++;
                return true;
            }
        }
    }
    return false;
}

/**~*~*
 Display the contents of the hash table as a list.
 *~**/
void Hash::displayHash()
{
    cout << endl;
    for (int i=0; i<TABLE_SIZE; i++)
    {
        if(theTable[i] != NULL)
        {
            for (int j=0; j<theTable[i]->bucketIndex; j++)
                cout << theTable[i]->bucket[j]->code << " " << theTable[i]->bucket[j]->name << endl;
        }
    }
}

/**~*~*
 Write an output file based on hash table sequence
 *~**/
void Hash::writing()
{
	ofstream outFile;
	outFile.open("output.txt");
    
    for (int i=0; i<TABLE_SIZE; i++)
    {
        if(theTable[i] != NULL)
        {
            for (int j=0; j<BUCKET_SIZE; j++)
            {
                if(theTable[i]->bucket[j] != NULL)
                {
                    outFile << theTable[i]->bucket[j]->name << endl;
                    outFile << theTable[i]->bucket[j]->state << endl;
                    outFile << theTable[i]->bucket[j]->tuition << endl;
                    outFile << theTable[i]->bucket[j]->code << endl;
                }

            }
        }
    }
    outFile.close();
}

/**~*~*
 Print the hashed table by showing the bucket number, empty slots and indent synonyms.
 *~**/
void Hash::printHash()
{
    for (int i=0; i<TABLE_SIZE; i++)
    {
        cout << "Bucket " << i << ":" << endl;
        if(theTable[i] != NULL && theTable[i]->bucket[0] != NULL)
        {
            for (int j=0; j<BUCKET_SIZE; j++)
            {
                cout << setw(20) << right << "Location " << j << ": ";
                if(theTable[i]->bucket[j] != NULL)
                    cout << theTable[i]->bucket[j]->code << " " << theTable[i]->bucket[j]->name << endl;
                else
                    cout << endl;
            }
        }
    }
}

/**~*~*
 Show statistics, such as number of collisions,
 load factor and number of full buckets.
 *~**/
void Hash::statsHash()
{
    cout << setw(32) << left << "\tThe number of collisions is: " << setw(8) << right << collision << "\n";
    cout << setw(32) << left << "\tThe load factor is: " << setw(8) << right << (numberKeys/TABLE_SIZE)*100 << "%\n";
    cout << setw(32) << left << "\tThe number of full buckets is: " << setw(8) << right << fullBuckets << "\n";
}

/**~*
 delete the data from the table
 *~*/
void Hash::deleleteHash(int code)
{
    int index = hashFunc(code); //Finding the home address;
    bool found = false;
    ITEM_Hash* ptr = theTable[index];
    for(int i = 0; i < BUCKET_SIZE && found == false; i++)
    {
        University test;
        if(searchHash(code, test))
           {
        if(ptr->bucket[i]->code == code)
        {
			found = true;
            ptr->bucket[i] = NULL;
            if(ptr->bucketIndex>1)
                collision--; //Decrement the number of collisions in the hashed table
            if(i < ptr->bucketIndex-1)
            {
                //cout << "this case and the bucketindex is " << ptr->bucketIndex << endl;
                //cout << "bucket[k] is " << ptr->bucket[ptr->bucketIndex-1]->code << " " << ptr->bucket[ptr->bucketIndex-1]->name << endl;
                ptr->bucket[i] = ptr->bucket[ptr->bucketIndex-1];
                ptr->bucket[ptr->bucketIndex-1] = NULL;
            }
            ptr->bucketIndex--;
            numberKeys--; //Decrement the number of keys inserted in the hashed table
			cout << "Now it is deleted" << endl;
        }
           }
    }
    if(!found)
        cout << "School code " << code << " does not exist" << endl;
}

/**~*~*
 Destructor
 This function deletes all elements of the array.
 *~**/
Hash::~Hash()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        delete theTable[i];
    delete[] theTable;
}