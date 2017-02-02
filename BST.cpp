/*
 Team 6
 */

/*
 BST keeps sorted the universities by their unique key, the code
 */


// Implementation file for the BST class
#include <iostream>  // For cout and NULL
#include "BST.h"

using namespace std;

/**~*~*
 Constructor
 *~**/
BST::BST()
{
    root = NULL;
    count = 0;
}

/**~*~*
 This function calls a recursive function to traverse the
 tree in inorder
 *~**/
void BST::inorderTraverse() const
{
    _BST_InorderTraverse(root);
}

/**~*~*
 Inorder Traversal of the Binary Tree by recursion:
 Left-Root-Right
 *~**/
void BST::_BST_InorderTraverse(BST_Node *root) const
{
    if (root)
    {
        _BST_InorderTraverse(root->left);
        cout << root->university->code << " " << root->university->name << endl;
        _BST_InorderTraverse(root->right);
    }
}

/**~*~*
 Insert data into a BST
 *~**/
void BST::insertBST(University *univIn)
{
    BST_Node *newNode;
    BST_Node *pWalk;
    BST_Node *parent;
    
    // allocate the new node
    newNode = new BST_Node;
    newNode->university  = univIn;
    newNode->left  = NULL;
    newNode->right = NULL;

    if (!root) // tree is empty
        root = newNode;
    else
    {
        pWalk = root;
        while( pWalk )
        {
            parent   = pWalk;
            if( univIn->code < pWalk->university->code )
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }
        
        // insert the new node
        if( univIn->code < parent->university->code ) // no left child
            parent->left  = newNode;
        else
            parent->right = newNode;
    }
    
    count++;
}

/**~*~*
 This function traverses the binary tree in postorder and deletes every node
 *~**/
void BST::_BST_Destroy(BST_Node *root)
{
    if (root)
    {
        _BST_Destroy(root->left);
        _BST_Destroy(root->right);
        delete root;
    }
    return;
}

/**~*~*
 Search a BST for a given target: if found, returns true and passes back
 data, otherwise returns false. It calls the private _search to locate the node.
 *~**/
bool BST::searchBST(int target, University &univ)
{
    BST_Node *found = _search(target);
    if (found)
    {
        univ = *found->university;
        return true;
    }
    return false;
}

/**~*~*
 Locates the node that contains a given target in a BST:
 - if found returns a pointer to that node
 - if not found returns NULL
 *~**/
BST::BST_Node* BST::_search(int target)
{
    if (!root) // tree is empty
        return NULL;
    
    // tree is not empty
    BST_Node *pWalk = root;
    while( pWalk )
    {
        if( target < pWalk->university->code )
            pWalk = pWalk->left;
        else
            if( target > pWalk->university->code )
                pWalk = pWalk->right;
            else
                return pWalk; // found
    }
    
    return NULL; // not found
}

/**~*~*
 This function calls a recursive function to prints
 the tree as an intented list
 *~**/
void BST::indentedTraverse() const
{
    if(root)
        cout << endl;
        _BST_IndentedTraverse(root, 1);
}

/**~*~*
 This function traverse recursively the tree Right-Root-Left
 order and prints elements as an indented list using the parameter
 int level as a counter to keep track of the level in which the node is
 *~**/
void BST::_BST_IndentedTraverse(BST_Node *root, int level) const
{
    if(root->right)
        _BST_IndentedTraverse(root->right, level+1);
    
    //Create space based on the level
    for(int i=1; i<level; i++)
        cout << "\t";
    cout << level << ". ";
    cout << root->university->code << endl;
    
    if(root->left)
        _BST_IndentedTraverse(root->left, level+1);
}

/*************************************
 This function find the smallest
 number(code) from the root of the tree
 *******************************************/
int BST::findSmallest()
{
	return _findSmallest(root);
}

/*************************************
 This function find the smallest
 number(code) from the pointer that pluged into
 the function
 *******************************************/
int BST::_findSmallest(BST_Node *ptr)
{
	if(!root)
	{
		cout << "The tree is empty" << endl;
		return -1;
	}
	else
	{
		if(ptr->left != NULL)
			return _findSmallest(ptr->left);
		else
			return ptr->university->code;
	}
}

/*************************************
 This function call the private function
 to remove the node
 *******************************************/
void BST::removeNode(int target)
{
	_removeNode(target, root);
}

/*************************************
 This function bridge between
 removeNode function and removeRootMatch func
 *******************************************/
void BST::_removeNode(int target, BST_Node *parent)
{
	if(!root)
		cout << "The tree is empty" << endl;
	else
	{
		if(root->university->code == target)
			removeRootMatch();
		else
		{
			if(target < parent->university->code && parent->left != NULL)
			{
				if(parent->left->university->code == target)
					removeMatch(parent, parent->left, true);
				else
					_removeNode(target, parent->left);
			}
			else if(target > parent->university->code && parent->right != NULL)
			{
				if(parent->right->university->code == target)
					removeMatch(parent, parent->right, false);
				else
					_removeNode(target, parent->right);
			}
			else
				cout << "The code " << target << " was not founded" << endl;
		}
	}
}

/*************************************
 This function call the private function
 to remove the node
 *******************************************/
void BST::removeRootMatch()
{
	if(!root)
		cout << "The tree is empty" << endl;
	else
	{
		BST_Node *ptr = root;
		int num = root->university->code;
		int sNum;
		///root has 0 child
		if(root->left == NULL && root->right == NULL)
		{
			root = NULL;
			delete ptr;
		}
		///root has 1 child
		else if(root->left == NULL && root->right != NULL)
		{
			root = root->right;
			ptr->right = NULL;
			delete ptr;
			cout << "Deleted!\n";
		}
		else if(root->left != NULL && root->right == NULL)
		{
			root = root->left;
			ptr->left = NULL;
			delete ptr;
			cout << "Deleted!\n";
		}
		else
		{
			sNum = _findSmallest(root->right);
			BST_Node *p = _search(sNum);
			root->university->tuition = p->university->tuition;
			root->university->state = p->university->state;
			root->university->name = p->university->name;
			_removeNode(sNum, root);
			root->university->code = sNum;
		}
	}
}

/*************************************
 This function actually
 delete the node
 *******************************************/
void BST::removeMatch(BST_Node *parent, BST_Node *match, bool left)
{
	if(!root)
		cout << "The tree is empty" << endl;
	else
	{
		BST_Node *ptr;
		int num = match->university->code;
		int sNum;
		if(match->left == NULL && match->right == NULL)
		{
			ptr = match;
			if(left == true)
				parent->left = NULL;
			else
				parent->right = NULL;
			delete ptr;
			cout << "Deleted!\n";
		}
		else if(match->left == NULL && match->right != NULL)
		{
			if(left == true)
				parent->left = match->right;
			else
				parent->right = match->right;
			match->right = NULL;
			ptr = match;
			delete ptr;
		}
		else if(match->left != NULL && match->right == NULL)
		{
			if(left == true)
				parent->left = match->left;
			else
				parent->right = match->left;
			match->left = NULL;
			ptr = match;
			delete ptr;
		}
		else
		{
			sNum = _findSmallest(match->right);
			BST_Node *p = _search(sNum);
			match->university->tuition = p->university->tuition;
			match->university->state = p->university->state;
			match->university->name = p->university->name;
			_removeNode(sNum, match);
			match->university->code = sNum;
		}
	}
}

/**~*~*
 Destructor
 This function calls a recursive function to delete all nodes in the binary tree
 *~**/
BST::~BST()
{
    if (root)
        _BST_Destroy(root);
}