/*
 Team 6
 */


// Specification file for the BST class
#ifndef BST_H
#define BST_H

#include <string>
#include "Object.h"
using namespace std;

class BST
{
private:
    struct BST_Node
    {
        University *university;  // The value in this node
        BST_Node *left;         // To point to the left node
        BST_Node *right;        // To point to the right node
    } ;
    
    BST_Node *root;       // root of the tree
    int count;            // number of nodes in the tree
    
public:
    // Constructor
    BST();
    
    // Destructor
    ~BST();
    
    // BST operations
    void insertBST(University *univIn);
    bool searchBST(int target, University &univ);
    void inorderTraverse() const;
    void indentedTraverse() const;
    int findSmallest();
    void removeNode(int target);
	void removeRootMatch();
	void removeMatch(BST_Node *p, BST_Node *q, bool left);
    
private:
    BST_Node *_search(int target);
    void _BST_InorderTraverse( BST_Node *root ) const;
    void _BST_Destroy(BST_Node *root);
    void _BST_IndentedTraverse(BST_Node *root, int level) const;
    int _findSmallest(BST_Node *ptr);
    void _removeNode(int target, BST_Node *ptr);
    
};
#endif
