//--------------------------------------------------------------------
//
//  Laboratory 9                                            BSTree.cpp
//
//  ** SOLUTION: Linked implementation of the Binary Search Tree ADT **
//
//--------------------------------------------------------------------

#ifndef BSTREE_CPP
#define BSTREE_CPP

#include <new>
#include <iostream>
#include "BSTree.h"

using namespace std;

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType &nodeDataItem,
	BSTreeNode *leftPtr,
	BSTreeNode *rightPtr)

	// Creates a binary search tree node containing data item elem, left
	// child pointer leftPtr, and right child pointer rightPtr.

	: dataItem(nodeDataItem),
	left(leftPtr),
	right(rightPtr)

{}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>::BSTree()

// Creates an empty tree.

	: root(0)

{}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>::BSTree(const BSTree &source)

// Creates an empty tree.

	: root(0)

{
	copyTree(source);
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= (const BSTree &sourceTree)

// Sets a tree to be equivalent to the tree "source".

{
	// Avoid accidentally trying to set object to itself.
	// Calling clear() on an object, then copying the deleted data doesn't work.
	// Although this may seems like overkill and an unlikely scenario, it can happen, 
	if (this != &sourceTree)
	{
		clear();
		copyTree(sourceTree);
		return *this;
	}
	else
	{
		return *this;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::copyTree(const BSTree<DataType, KeyType> &sourceTree)

// Sets a tree to be equivalent to the tree "source".

{
	copyTreeHelper(root, sourceTree.root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::copyTreeHelper(BSTreeNode *&p, const BSTreeNode *sourcePtr)

// Recursive helper function that helps set a tree to be equivalent to another tree.

{
	if (p != 0) {
		p = new BSTreeNode(sourcePtr->DataItem, 0, 0);
		copyTreeHelper(p->left, sourcePtr->left);
		copyTreeHelper(p->right, sourcePtr->right);
	}
}

//--------------------------------------------------------------------
template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>:: ~BSTree()

// Frees the memory used by a tree.

{
	clear();
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::insert(const DataType &newDataItem)

// Inserts newDataItem into a tree. If an data item with the same key
// as newDataItem already exists in the tree, then updates that
// data item's data with newDataItem's data.

{
	insertHelper(root, newDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode *&p,
	const DataType &newDataItem)

	// Recursive helper function for insert. Inserts newDataItem in
	// the subtree pointed to by p.

{
	if (p == 0) // Insert
		p = new BSTreeNode(newDataItem, 0, 0);
	else if (newDataItem.getKey() < p->dataItem.getKey())
		insertHelper(p->left, newDataItem);                  // Search left
	else if (newDataItem.getKey() > p->dataItem.getKey())
		insertHelper(p->right, newDataItem);                 // Search right
	else
		p->dataItem = newDataItem;                           // Update
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType &searchDataItem) const

// Searches a tree for the data item with key searchKey. If the data item
// is found, then copies the data item to searchDataItem and returns true.
// Otherwise, returns false with searchDataItem undefined.

{
	return retrieveHelper(root, searchKey, searchDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode *p,
	const KeyType& searchKey,
	DataType &searchDataItem) const

	// Recursive helper function for retrieve. Searches the subtree
	// pointed to by p.

{
	bool result;   // Result returned

	if (p == 0)
	{
		// Fell off the tree while searching. Item is not in tree.
		result = false;
	}
	else if (searchKey < p->dataItem.getKey())
	{
		// Key is smaller than current node. Search to left.
		result = retrieveHelper(p->left, searchKey, searchDataItem);
	}
	else if (searchKey > p->dataItem.getKey())
	{
		// Key is larger than current node. Search to right.
		result = retrieveHelper(p->right, searchKey, searchDataItem);
	}
	else
	{
		// Found the desired item
		searchDataItem = p->dataItem;
		result = true;
	}

	return result;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)

// Removes the data item with key deleteKey from a tree. If the
// data item is found, then deletes it from the tree and returns true.
// Otherwise, returns false.

{
	return removeHelper(root, deleteKey);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode *&p, const KeyType& deleteKey)

// Recursive helper function for remove. Searches the subtree
// pointed to by p for the node with key deleteKey. If this node is
// found, then does one of the following:
//
//    - If the node is missing one or more children, then links
//      around it and deletes it.
//
//    - Otherwise, uses cutRightmost to replace the data in the
//      node with the data in the rightmost descendant of the node's
//      left child and deletes that node.

{
	BSTreeNode *delPtr;  // Pointer to node to delete
	int result;                 // Result returned

	if (p == 0)
		result = false;                           // Search failed
	else if (deleteKey < p->dataItem.getKey())
		result = removeHelper(p->left, deleteKey);    // Search left
	else if (deleteKey > p->dataItem.getKey())
		result = removeHelper(p->right, deleteKey);   // Search right
	else
	{                                            // Found
		delPtr = p;
		if (p->left == 0)
		{
			p = p->right;                    // No left child
			delete delPtr;
		}
		else if (p->right == 0)
		{
			p = p->left;                     // No right child
			delete delPtr;
		}
		else
			// Node has both children: removing is more complex.
		{

			// ** Start implemtation option #1
			// Find node with largest key smaller than p's key.
			BSTreeNode* temp = p->left;
			while (temp->right) {
				temp = temp->right;
			}
			// Copy node data to p
			p->dataItem = temp->dataItem;
			// And remove the node whose data was copied to p.
			removeHelper(p->left, temp->dataItem.getKey());

			/*
			// ** Start implemtation option #2. Looks simpler here,
			// but there is all of cutRightmost to deal with.
			cutRightmost(p->left,delPtr);
			delete delPtr;
			*/
		}
		result = true;
	}

	return result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::cutRightmost(BSTreeNode *&r,
	BSTreeNode *&delPtr)

	// Recursive helper function for removeHelper in implementation
	// option #2. Traces down a sequence of right children. Copies the 
	// data from the last node in the sequence into the node pointed 
	// to delPtr, sets delPtr to point to the last node in the sequence, 
	// and links around this node.

{
	if (r->right != 0)
		cutRightmost(r->right, delPtr);   // Continue down to the right
	else
	{
		delPtr->dataItem = r->dataItem;
		delPtr = r;
		r = r->left;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::writeKeys() const

// Outputs the keys in a tree in ascending order.

{
	writeKeysHelper(root);
	cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode *p) const

// Recursive helper for writeKeys. 
// Outputs the keys in the subtree pointed to by p.

{
	if (p != 0)
	{
		writeKeysHelper(p->left);
		cout << p->dataItem.getKey() << " ";
		writeKeysHelper(p->right);
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clear()

// Removes all the nodes from a tree.

{
	clearHelper(root);
	root = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode *p)

// Recursive helper for clear. Clears the subtree pointed to by p.

{
	if (p != 0)
	{
		// Use post-order traversal. Otherwise get into trouble by
		// referencing p->left and/or p->right after p had been deallocated.
		clearHelper(p->left);
		clearHelper(p->right);
		delete p;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const

// Returns true if a tree is empty. Otherwise returns false.

{
	return root == 0;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showStructure() const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showHelper(BSTreeNode *p,
	int level) const

	// Recursive helper for showStructure. 
	// Outputs the subtree whose root node is pointed to by p. 
	// Parameter level is the level of this node within the tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem.getKey();   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);          // Output left subtree
	}
}

//--------------------------------------------------------------------
//                         Programming Exercise 2
//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getHeight() const

// Returns the height of a tree.

{
	return getHeightHelper(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode *p) const

// Recursive helper for height. Returns the height of
// the subtree pointed to by p -- that is, the length of the longest
// path from the node pointed to by p to any leaf node.

{
	int l,        // Length of the longest path thru the left child
		r,        // Length of the longest path thru the right child
		result;   // Result returned

	if (p == 0)
		result = 0;                    // Leaf node
	else
	{
		l = getHeightHelper(p->left) + 1;    // Get height of left subtree
		r = getHeightHelper(p->right) + 1;   // Get height of right subtree
		if (l >= r)                  // Return larger
			result = l;
		else
			result = r;
	}

	return result;
}

template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getCount() const

// Returns the number of nodes in the tree

{
	return getCountHelper(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode *p) const

// Recursive partner of the getCount() function. Returns the count of
// the subtree pointed to by p -- that is, the number of nodes in the
// left child + number of nodes in the right child + 1

{
	if (p == 0) {
		return 0;
	}

	return getCountHelper(p->left) + getCountHelper(p->right) + 1;
}

//--------------------------------------------------------------------
//                         Programming Exercise 3
//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::writeLessThan(const KeyType& searchKey) const

// Outputs the keys in a tree that are less than searchKey.

{
	writeLTHelper(root, searchKey);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::writeLTHelper(BSTreeNode *p,
	const KeyType& searchKey) const

	// Recursive helper function for writeLessThan. Outputs the keys
	// in the subtree pointed to by p that are less than searchKey.

{
	if (p != 0)
	{
		writeLTHelper(p->left, searchKey);
		if (searchKey > p->dataItem.getKey())
		{
			cout << p->dataItem.getKey() << endl;
			writeLTHelper(p->right, searchKey);
		}
	}
}

#endif	// #ifdef BSTREE_CPP