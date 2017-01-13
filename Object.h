/*
 Team 6
 */


/*
 Object is the data shared by all structures of the program
 */


// Specification file for the Hashed Table class
#ifndef OBJECT_h
#define OBJECT_h

#include <string>

using namespace std;

const int TABLE_SIZE = 41;
const int BUCKET_SIZE = 3;

struct University
{
    string name;
    string state;
    int tuition;
    int code;
    int searchCount=0;
};

#endif
