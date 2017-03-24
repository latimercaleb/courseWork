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
	BSTreeNode *rightPtr): dataItem(nodeDataItem), left(leftPtr), right(rightPtr)

	// Creates a binary search tree node containing data item elem, left
	// child pointer leftPtr, and right child pointer rightPtr.

{
	// initializer list used here
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>::BSTree(): root(NULL)

// Creates an empty tree.

{

}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>::BSTree(const BSTree &source)

// Creates an empty tree.

{
	if (this != &source) {
		*this = source;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= (const BSTree &sourceTree)

// Sets a tree to be equivalent to the tree "source".

{
	copyTree(this,sourceTree);
	return *this;
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
	while (sourcePtr != NULL) {
		p.dataItem = sourcePtr.dataItem;
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
	if (p == NULL) {
		p = new BSTreeNode(newDataItem, NULL, NULL);
	}
	else {
		if (p->dataItem < newDataItem){
			insertHelper(p->left, newDataItem);
		}
		else {
			insertHelper(p->right, newDataItem);
		}
	}
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
	if (isEmpty()) {
		return false;
	}
	else {
		if (p->dataItem.getKey() == searchKey){
			return true;
			searchDataItem = p->dataItem;
		}
		else {
			if (p->dataItem < searchDataItem) {
				return (retrieveHelper(p->left, searchKey,searchDataItem));
			}
			else {
				return(retrieveHelper(p->right, searchKey, searchDataItem));
			}
		}
	}
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
	if (p == NULL) {
		return false;
	}
	else {
		if (p->dataItem.getKey() == deleteKey) {
			p = NULL;
			return true;
		}
		else {
			if (p->dataItem.getKey() < deleteKey) {
				return removeHelper(p->left, deleteKey);
			}
			else {
				return removeHelper(p->right,deleteKey);
			}
		}
	}

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
	BSTreeNode *lastPtr;
	lastPtr = root;
	while (lastPtr != NULL) {
		lastPtr = lastPtr->right;
	}
	BSTreeNode *copyOfLast = new BSTreeNode(lastPtr->dataItem, NULL, NULL);
	delPtr = copyOfLast;
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
	if (root != NULL) {
		cout << root->dataItem.getKey() << " ";
		writeKeysHelper(p->left);
		writeKeysHelper(p->right);
	}
	else {
		return;
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
	if (p != NULL) {
		clearHelper(p->left);
		clearHelper(p->right);
		p = NULL;
	}
	else {
		return;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const

// Returns true if a tree is empty. Otherwise returns false.

{
	if (root == NULL) {
		return true;
	}
	else {
		return false;
	}
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
	int static result = 0;   // Result returned
	if (p == NULL) {
		return result;
	}
	else {
		return result + getHeightHelper(p->left);
		return result + getHeightHelper(p->right);
	}
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
	int static leftSum = 0;
	int static rightsum = 1; // one added here early to account for it needing to be added at the end
	if (p == NULL) {
		return leftSum + rightsum;
	}
	else {
		leftSum = leftSum + getCountHelper(p->left);
		rightSum = rightSum + getCounteHelper(p->right);
	}
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
	if (root == NULL) {
		return;
	}
	else {
		cout << p->dataItem << " ";
		writeKeysHelper(p->left, searchKey);
	}
}

#endif	// #ifdef BSTREE_CPP