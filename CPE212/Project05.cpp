// Michael Agnew 10/25/23
// CPE 212/02 



#include <iostream>
#include <new>
#include "bstree.h"


using namespace std;

template <typename SomeType>
void BSTree<SomeType>::Delete(BSTreeNode<SomeType>*& treePtr, SomeType& item) 
{
    if (treePtr == NULL) // if treePtr is null, then throw NotFoundBSTree
    {
      throw (NotFoundBSTree());
    }
    if (treePtr->data == item) // if treePtr is the item, then call DeleteNode
    {
      item = treePtr->data;
      DeleteNode(treePtr);
    }
    else // otherwise
    {
      if (item < treePtr->data) // if item is less than treePtr, then call delete again
      {
        Delete(treePtr->leftPtr, item);
      
      }
      else // otherwise, call delete on the right ptr
      {
        Delete(treePtr->rightPtr, item);
      }
    }

}   // Delete()
  // Recursive function that traverses the tree starting at treePtr to locate the data value to be removed
  // Once located, DeleteNode is invoked to remove the value from the tree
  // If tree is not empty and item is NOT present, throw NotFoundBSTree	

template <typename SomeType>
void BSTree<SomeType>::DeleteNode(BSTreeNode<SomeType>*& treePtr)
{

     // declaring temp variable
    SomeType info;

    BSTreeNode<SomeType>* tempboy = NULL; // declaring temp pointer
 
    tempboy = treePtr; // setting temp equal to the tree ptr

    if (treePtr->leftPtr == NULL) // if treeptr->left is null, move to the right and delete temp
    {
        treePtr = treePtr->rightPtr;
        delete tempboy;
    }
    else if (treePtr->rightPtr == NULL) // if treeptr->right is null, move to the left and delete temp
    {
        treePtr = treePtr->leftPtr; 
        delete tempboy;
    }
    else
    {
        info = GetPredecessor(treePtr->leftPtr); // set info equal to the value returned by getpredecessor
        treePtr->data = info; // set the value of tree equal to info
        Delete(treePtr->leftPtr, info); // delete the value to the left of treeptr
    }

}  // DeleteNode()
  // Removes the node pointed to by treePtr from the tree
  // Hint:  calls GetPredecessor and Delete

template <typename SomeType>
void BSTree<SomeType>::Insert(BSTreeNode<SomeType>*& ptr, SomeType item)
{
  
  if (ptr == NULL) // if ptr is null, then make a new ptr
  {
    try{
      ptr = new BSTreeNode<SomeType>;
    }
    catch (std::bad_alloc)
    {
      throw (FullBSTree());
    }
    ptr->rightPtr = NULL; // set ptr.right to null

    ptr->leftPtr = NULL; // set ptr.left to null

    ptr->data = item; // set the value of ptr to item

  }
  else if (item < ptr->data) // if item is less than value of ptr, put it to the left
  {
    Insert(ptr->leftPtr, item);
  }
  else if (item == ptr->data) // if item is equal to ptr, throw already in BS tree
  {
    throw (FoundInBSTree());
  }
  else // otherwise, move to the right
  {
    Insert(ptr->rightPtr, item);
  }
}  // Insert()
  // Recursive function that finds the correct position of item and adds it to the tree
  // Throws FoundInBSTree if item is already in the tree	

template <typename SomeType>
void BSTree<SomeType>::Destroy(BSTreeNode<SomeType>*& ptr)
{
  if (ptr != NULL) // if the pointer is not null, then destroy stuff
  {
    Destroy(ptr->leftPtr); 

    Destroy(ptr->rightPtr);
    
    delete ptr; // deallocate ptr
  }

  return;
}  // Destroy()
  // Recursively deallocates every node in the tree pointed to by ptr

template <typename SomeType>
void BSTree<SomeType>::CopyTree(BSTreeNode<SomeType>*& copy, const BSTreeNode<SomeType>* originalTree)
{
  if (originalTree == NULL) // if originaltree is null, then set copy to null
  {
    copy = NULL;
  }
  else // otherwise,
  {
    copy = new BSTreeNode<SomeType>; // allocate new pointer copy

    copy->data = originalTree->data; // set value of copy equal to the value of originaltree

    CopyTree(copy->leftPtr, originalTree->leftPtr); // recursively copy left and right
    CopyTree(copy->rightPtr, originalTree->rightPtr);
  }
}  // CopyTree()
  // Recursively copies all data from original tree into copy

template <typename SomeType>
SomeType BSTree<SomeType>::GetPredecessor(BSTreeNode<SomeType>* treePtr) const
{

  while (treePtr->rightPtr != NULL) // while the treeptr.right is not null, move it all the way to the right 
  {
    treePtr = treePtr->rightPtr; 
  }
    return (treePtr->data); // return the value of treeptr
}  // GetPredecessor()
  // Finds the largest data value in the tree pointed to by treePtr and returns that data value
  // as the functions return value

template <typename SomeType>
int BSTree<SomeType>::CountNodes(BSTreeNode<SomeType>* treePtr) const
{
  if (treePtr == NULL) // if treeptr is null, then return 0
  {
    return 0;
  }
  else
  {
    return (CountNodes(treePtr->leftPtr) + CountNodes(treePtr->rightPtr) + 1); // do thing
  }
}  // CountNodes()
  // Recursive function that counts every node in the tree pointed to by treePtr and returns the
  // count as the function return value

template <typename SomeType>
int BSTree<SomeType>::LevelCount(BSTreeNode<SomeType>* treePtr) const
{ // every count you need to add one
    if (rootPtr == NULL) // if root is null, then the tree is empty
    {
      throw (EmptyBSTree());
    }
    if (treePtr == NULL) // of the treeptr is empty, then also return 0
    {
      return 0;      
    }
    return (max(LevelCount(treePtr->leftPtr), LevelCount(treePtr->rightPtr)) + 1); // otherwise, return the correct thing
}  // LevelCount()
  // Recursive function that traverses the entire tree to determine the total number of levels in the tree

template <typename SomeType>
int BSTree<SomeType>::FindLevel(BSTreeNode<SomeType>* treePtr, SomeType item) const
{
  int level = 0; // set a level equal to 0
    if (treePtr == NULL)
    {
        return level;       // if the treeptr is null, then return the value of level
    }
    else if (item < treePtr->data)
    {
        return (FindLevel(treePtr->leftPtr, item)+1); // if the item is less than the value of treeptr then return it to the left +1
    }
    else if (item > treePtr->data)
    {
        return (FindLevel(treePtr->rightPtr, item)+1); // do the same but to the right
    }
    else
    { // otherwise just return 0 because yes
        return 0;
    } 
    
}  // FindLevel()
  // Recursive function that traverses the tree looking for item and returns the level where
  // item was found

/*************************************************YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYEEEEEEEEEEESSSSSSSSSSSSSSSSS PRIVATE*************************************************/

template <typename SomeType>
BSTree<SomeType>::BSTree()
{
    BSTreeNode<SomeType>* rootPtr = NULL;
}  // BSTree()
  // Default constructor initializes root pointer to NULL

template <typename SomeType>
BSTree<SomeType>::BSTree(const BSTree<SomeType>& someTree)
{
  CopyTree(rootPtr, someTree.rootPtr);
}  // BSTree() 
  // Copy constructor for BSTree
  // Hint:  calls CopyTree

template <typename SomeType>
void BSTree<SomeType>::operator=(const BSTree<SomeType>& originalTree)
{
  if (&originalTree == this) // operator stuff
  {
    return;
  }

  CopyTree(rootPtr, originalTree.rootPtr); // copytree
}  // operator=() 
  // Overloaded assignment operator for BSTree.
  // Hint:  calls CopyTree

template <typename SomeType>
BSTree<SomeType>::~BSTree()
{
  Destroy(rootPtr);
}  // ~BSTree()
  // Destructor deallocates all tree nodes
  // Hint:  calls the private helper function Destroy

template <typename SomeType>
void BSTree<SomeType>::InsertItem(SomeType item)
{
  try
  {
    Insert(rootPtr, item);
  }
  catch (std::bad_alloc)
  {
    throw (FullBSTree());

    return;
  }

}  // InsertItem()
  // Inserts item into BSTree;  if tree already full, throws FullBSTree exception
  // If item is already in BSTree, throw FoundInBSTree exception
  // Hint:  calls the private helper function Insert

template <typename SomeType>
SomeType BSTree<SomeType>::DeleteItem(SomeType item)
{
  if (BSTree<SomeType>::IsEmpty())
  {
    throw EmptyBSTree();
  }
  if (!BSTree<SomeType>::IsEmpty() && rootPtr == NULL)
  {
    throw (NotFoundBSTree());
  }
  Delete(rootPtr, item);
  return item;

}  // DeleteItem()
  // Deletes item from BSTree if item is present AND returns object via function return value
  // If tree is empty, throw the EmptyBSTree exception
  // If tree is not empty and item is NOT present, throw NotFoundBSTree
  // Hint:  calls the private helper function Delete

template <typename SomeType>
void BSTree<SomeType>::MakeEmpty()
{
  Destroy(rootPtr);
  rootPtr = NULL;
}  // MakeEmpty()
  // Deallocates all BSTree nodes and sets root pointer to NULL
  // Hint:  calls the private helper function Destroy

template <typename SomeType>
int BSTree<SomeType>::Size() const
{
    return CountNodes(rootPtr);
}  // Size()
  // Returns total number of data values stored in tree

template <typename SomeType>
bool BSTree<SomeType>::IsFull() const
{
    BSTreeNode<SomeType>* jeremy; // jeremy

    try 
    {
      jeremy = new BSTreeNode<SomeType>; // new jeremy

      delete jeremy; // kill jeremy
      return false;
    }
    catch (std::bad_alloc exception)
    {
      return true;
    }
}  // IsFull()
  // Returns true if BSTree is full; returns false otherwise

template <typename SomeType>
bool BSTree<SomeType>::IsEmpty() const
{
  if (rootPtr == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}  // IsEmpty()
  // Returns true if BSTree is empty; returns false otherwise

template <typename SomeType>
SomeType BSTree<SomeType>::Min() const
{
  BSTreeNode<SomeType>* temp = NULL;
  SomeType pablo;
  temp = rootPtr;
  if (temp == NULL)
  {
    throw (EmptyBSTree());
  }
  while (temp != NULL)
  {
    pablo = temp->data;
    temp = temp->leftPtr;

  }

  return (pablo);
}  // Min()
  // Returns minimum value in tree; throws EmptyBSTree if tree is empty

template <typename SomeType>
SomeType BSTree<SomeType>::Max() const
{
  BSTreeNode<SomeType>* temp = NULL; // initialize a new pointer to null

  SomeType juan; // make a new sometype variable named juan

  temp = rootPtr; // set the temporary pointer equal to the root

  if (temp == NULL)
  {
    throw (EmptyBSTree());
  }
  while (temp != NULL)
  {
    juan = temp->data;
    temp = temp->rightPtr;

  }

  return (juan);
}  // Max()
  // Returns maximum value in tree; throws EmptyBSTree if tree is empty

template <typename SomeType>
int BSTree<SomeType>::TotalLevels() const
{
  if (rootPtr == NULL)
  {
    throw (EmptyBSTree());
  }
  return (LevelCount(rootPtr)); // also throws empty
}  // TotalLevels()
  // Returns the maximum level value for current tree contents
  // Levels are numbered 0, 1, ..., N-1.  This function returns N
  // Throws EmptyBSTree if empty
  // Hint:  calls the private helper function LevelCount

template <typename SomeType>
int BSTree<SomeType>::Level(SomeType item) const
{
    if (BSTree<SomeType>::IsEmpty())
    {
        throw (EmptyBSTree());
    }
    else if (!BSTree<SomeType>::IsEmpty() && rootPtr == NULL)
    {
      throw (NotFoundBSTree());
    }
    else
    {
        return (FindLevel(rootPtr, item));
    }
}  // Level()
  // Returns the level within the BSTree at which the value item is found
  // If tree is empty, throws EmptyBSTree
  // If tree is not empty and item is not found, throws NotFoundBSTree
  // Hint:  calls the private helper function FindLevel
