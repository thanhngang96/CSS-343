// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the Data
// Uses templates to store any type of Data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

template <class T> class BST {
  // display BST tree in a human-readable format
  friend ostream &operator<<(ostream &Out, const BST &Bst) {
    Bst.printSideways(Out, Bst.Root);
    Out << endl;
    Bst.printVertical(Out, Bst.Root);
    return Out;
  }

private:
  // Node for BST
  struct Node {
    T Data;
    struct Node *Left;
    struct Node *Right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // root of the tree
  Node *Root{ nullptr };

  // height of a Node, nullptr is 0, Root is 1, static, no access to 'this'
  static int getHeight(const Node *N) 
  {
	  if (N == nullptr)
	  {
		  return 0;
	  }
	  return max(1 + getHeight(N->Left), 1 + getHeight(N->Right));
  }

  /**
   * print tree sideways with root on left
                6
            2
                5
        0
                4
            1
                3
   */
  // convenience function, do not modify
  static ostream &printSideways(ostream &Out, const Node *Curr, int Level = 0) {
    const static char SP = ' ';
    const static int ReadabilitySpaces = 4;
    if (!Curr)
      return Out;
    printSideways(Out, Curr->Right, ++Level);
    Out << setfill(SP) << setw(Level * ReadabilitySpaces) << SP;
    Out << Curr->Data << endl;
    printSideways(Out, Curr->Left, Level);
    return Out;
  }

  // centers the string to be printed
  // convenience function, do not modify
  static ostream &centeredPrint(ostream &Out, int Space, const string &Str,
                                char FillChar = ' ') {
    auto StrL = static_cast<int>(Str.length());
    int Extra = (Space - StrL) / 2;
    if (Extra > 0) {
      Out << setfill(FillChar) << setw(Extra + StrL) << Str;
      Out << setfill(FillChar) << setw(Space - Extra - StrL) << FillChar;
    } else {
      Out << setfill(FillChar) << setw(Space) << Str;
    }
    return Out;
  }

  /**
   * print tree with the root at top
   *
      _____0______
   __1___      __2___
  3     4     5     6
   *
  **/
  // convenience function, do not modify
  static ostream &printTreeLevel(ostream &Out, queue<const Node *> &Q,
                                 int Width, int Depth, int MaxDepth) {
    const static char SP = ' ';
    const static char UND = '_';
    int Nodes = 0;
    int MaxN = int (pow(2, Depth - 1));
    int SpaceForEachItem = int (Width * pow(2, MaxDepth - 1) / MaxN); // NOLINT
    string Bigspace = string(static_cast<uint64_t>(SpaceForEachItem / 4), SP);
    while (Nodes++ < MaxN) {
      const Node *Tp = Q.front();
      Node *TpL = nullptr;
      Node *TpR = nullptr;
      Q.pop();
      string Label = "N";
      if (Tp) {
        stringstream Ss;
        Ss << Tp->Data;
        Label = Ss.str();
        TpL = Tp->Left;
        TpR = Tp->Right;
      }
      char Filler = Depth == MaxDepth ? SP : UND;
      if (Depth == MaxDepth) {
        centeredPrint(Out, SpaceForEachItem, Label, Filler);
      } else {
        Out << Bigspace;
        centeredPrint(Out, SpaceForEachItem / 2, Label, Filler);
        Out << Bigspace;
        Q.push(TpL);
        Q.push(TpR);
      }
    }
    Out << endl;
    return Out;
  }

  // helper function for displaying tree sideways, works recursively
  // convenience function, do not modify
  static ostream &printVertical(ostream &Out, Node *Curr) {
    const static int WIDTH = 6; // must be even
    if (!Curr)
      return Out << "[__]";
    // figure out the maximum depth which determines how wide the tree is
    int MaxDepth = getHeight(Curr);
    queue<const Node *> Q;
    Q.push(Curr);
    for (int Depth = 1; Depth <= MaxDepth; ++Depth) {
      printTreeLevel(Out, Q, WIDTH, Depth, MaxDepth);
    }
    return Out;
  }

  // recursively traverses through the tree and copy all nodes
  void copyHelper(Node* N)
  {
	  if (N != nullptr)
	  {
		  add(N->Data);
		  copyHelper(N->Left);
		  copyHelper(N->Right);
	  }
  }

  // counts number of nodes recursively
  static int nodeCounter(Node* N)
  {
	  if (N == nullptr)
	  {
		  return 0;
	  }
	  return 1 + nodeCounter(N->Left) + nodeCounter(N->Right);
  }

  // recursively traverses through tree N and add Item 
  bool addHelper(const T& Item, Node*& N)
  {
	  // when reaching the right place, creates a new Node and
	  // sets Item its data.
	  if (N == nullptr)
	  {
		  N = new Node;
		  N->Data = Item;
		  N->Left = nullptr;
		  N->Right = nullptr;
		  return true;
	  }
	  // traverses left if item is less than N->Data.
	  if (Item < N->Data)
	  {
		  return addHelper(Item, N->Left);
	  }
	  // traverse right if item is greater than N->Data.
	  if (Item > N->Data)
	  {
		  return addHelper(Item, N->Right);
	  }
	  // return false if duplicate Item (Item == N->Data)
	  return false;
  }

  // recursively traverses through tree N and remove Item 
  bool removeHelper(const T& Item, Node*& N)
  {
	  // base case when cannot find the Item.
	  if (N == nullptr)
	  {
		  return false;
	  }
	  // traverses left if item is less than N->Data.
	  if (Item < N->Data)
	  {
		  return removeHelper(Item, N->Left);
	  }
	  // traverses right if item is greater than N->Data.
	  if (Item > N->Data)
	  {
		  return removeHelper(Item, N->Right);
	  }
	  // when Item is found
	  // deletes N when it has no child.
	  if (N->Left == nullptr && N->Right == nullptr)
	  {
		  delete N;
		  N = nullptr;
		  return true;
	  }
	  // deletes N when it has 1 right child.
	  if (N->Left == nullptr)
	  {
		  Node* DelNode = N;
		  N = N->Right;
		  delete DelNode;
	  }
	  // deletes N when it has 1 left child.
	  if (N->Right == nullptr)
	  {
		  Node* DelNode = N;
		  N = N->Left;
		  delete DelNode;
	  }
		  // deletes N when it has 2 children.
	  else
	  {
		  //traverses right once then go find the last left node.
		  Node* DelNode = findLeftmost(N->Right);
		  N->Data = DelNode->Data;
		  return removeHelper(DelNode->Data, N->Right);
	  }
		  return false;
  }

  // traverses left till reaching the leftmost node.
  Node* findLeftmost(Node* N) {
	  Node* Temp = N;
	  
	  while (Temp != nullptr && Temp->Left != nullptr)
	  {
		  Temp = Temp->Left;
	  }
	  return Temp;
  }

  // recursively traverses through tree N and check if Item is in the tree
  static bool containsHelper(const T& Item, Node* N) 
  {
	  // cannot find Item in the tree
	  if (N == nullptr)
	  {
		  return false;
	  }
	  // return true when Item is found in the tree
	  if (N->Data == Item)
	  {
		  return true;
	  } 
	  // traverses left if item is less than N->Data.
	  if (Item < N->Data)
	  {
		  return containsHelper(Item, N->Left);
	  }
	  // traverses right if item is greater than N->Data.
	  if (Item > N->Data)
	  {
		  return containsHelper(Item, N->Right);
	  }
	  return false;
  }

  // recursively traverses through tree N in in-order
  static void inOrderHelper(void Visit(const T& Item), Node* N) 
  {
	  // base case when node is empty
	  if (N == nullptr)
	  {
		  return;
	  }
	  // traverse left subtree first
	  inOrderHelper(Visit, N->Left);
	  // visit then parent
	  Visit(N->Data); 
	  // finally traverse Right
	  inOrderHelper(Visit, N->Right);
  }

  // recursively traverses through tree N in pre-order
  static void preOrderHelper(void Visit(const T& Item), Node* N) 
  {
	  // base case when node is empty
	  if (N == nullptr)
	  {
		  return;
	  }
	  // visit parent first
	  Visit(N->Data);
	  // then traverse left subtree
	  preOrderHelper(Visit, N->Left);
	  // finally traverse right subtree
	  preOrderHelper(Visit, N->Right);
  }

  // recursively traverses through tree N in post-order
  static void postOrderHelper(void Visit(const T& Item), Node* N) 
  {
	  // base case when node is empty
	  if (N == nullptr)
	  {
		  return;
	  }
	  // traverse left subtree first
	  postOrderHelper(Visit, N->Left);
	  // then traverse right subtree
	  postOrderHelper(Visit, N->Right);
	  // finally visit parent
	  Visit(N->Data);
  }

  // stores nodes in an array in Inorder traversal
  // so the array will be sorted in the end.
  void storeBSTInArray(T NodesArray[], Node* N, int& Index)
  {
	  //base case 
	  if (N == nullptr)
	  {
		  return;
	  }  
	  // traverses left and stores nodes in the array
	  storeBSTInArray(NodesArray, N->Left, Index);
	  // adds Data to the array incrementally
	  NodesArray[Index++] = N->Data;
	  // traverses right and stores nodes in the array
	  storeBSTInArray(NodesArray, N->Right, Index);
  }

  // recursively builds a balanced BST from a sorted array
  Node* buildBSTFromArray(const T NodesArray[], int Start, int End)
  {
	  // base case when there are only two elements in the array
	  if (Start > End)
	  {
		  return nullptr;
	  }
	  // creates a temp root which data is the middle element of the array
	  int Mid = (Start + End) / 2;
	  auto TempRoot = new Node;
	  TempRoot->Data = NodesArray[Mid];
	  TempRoot->Left = nullptr;
	  TempRoot->Right = nullptr;
	  // constructs from left to right subtrees
	  TempRoot->Left = buildBSTFromArray(NodesArray, Start, Mid - 1);
	  TempRoot->Right = buildBSTFromArray(NodesArray, Mid + 1, End);
	  return TempRoot;
  }

  // traverses in post-order to clear children nodes before the parent node
  void clearHelper(Node* N)
  {
	  // base case when all nodes are cleared
	  if (N == nullptr)
	  {
		  return;
	  }
	  // traverses left and right first to clear all children nodes
	  clearHelper(N->Left);
	  clearHelper(N->Right);
	  // then delete parent nodes
	  delete N;
	  N = nullptr;
  }
  // operator== helper function to compare two trees
  bool isIdentical(Node *Lhs, Node *Rhs) const
  {
	  // base case when two nodes are both empty
	  if (Lhs == nullptr && Rhs == nullptr) 
	  {
		  return true;
	  }
	  // base case when one of them is empty
	  if ((Lhs == nullptr && Rhs != nullptr) 
		  || (Lhs != nullptr && Rhs == nullptr)) 
	  {
		  return false;
	  }
	  // base case when data of two nodes are different. 
	  if (Lhs->Data != Rhs->Data)
	  {
		  return false;
	  }
	  // traverses through both trees and compares data.
	  return (isIdentical(Lhs->Left, Rhs->Left) 
		  && isIdentical(Lhs->Right, Rhs->Right));
  }

public:
  // default constructor, empty tree
  BST()
  {
	  Root = nullptr;
  }

  // constructor, tree with root
  explicit BST(const T &RootItem) 
  {
	  Root = new Node;
	  Root->Data = RootItem;
	  Root->Left = nullptr;
	  Root->Right = nullptr;
  }

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (i.e. rebalance)
  // Assume the given array is sorted
  // Assignment specification
  // NOLINTNEXTLINE
  BST(const T Arr[], int N)
  {
	  //build a new tree using a sorted array.
	  Root = buildBSTFromArray(Arr, 0, N - 1);
  }

  // copy constructor
  BST(const BST<T> &Bst)
  {
	  Root = nullptr;
	  copyHelper(Bst.Root);
  }

  // destructor
  virtual ~BST() 
  {
	  clear();
  }

  // true if no nodes in BST
  bool isEmpty() const 
  {
	  return (Root == nullptr);
  }

  // Get the height of the tree
  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int getHeight() const 
  {
	  if (isEmpty())
	  {
		  return 0;
	  }
	  return getHeight(Root);
  }

  // Number of nodes in BST
  // 0 if empty, 1 if only root, otherwise
  // number of nodes are left nodes + right nodes + 1
   int numberOfNodes() const
  {	  
	  return nodeCounter(Root);
  }

  // add a new item, return true if successful
  // return false if the item is a duplicate
  bool add(const T &Item)
  {
	  return addHelper(Item, Root);
  }

  // remove item, return true if successful
  bool remove(const T &Item) 
  {
	  return removeHelper(Item, Root); 
  }

  // true if item is in BST
  bool contains(const T &Item) const 
  { 
	  return containsHelper(Item, Root);
  }

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inOrderTraverse(void Visit(const T &Item)) const 
  {
	  inOrderHelper(Visit, Root);
  }

  // preorder traversal: root-left-right
  void preOrderTraverse(void Visit(const T &Item)) const 
  { 
	  preOrderHelper(Visit, Root);
  }

  // postorder traversal: left-right-root
  void postOrderTraverse(void Visit(const T &Item)) const 
  {
	  postOrderHelper(Visit, Root);
  }


  // create dynamic array (not a vector)
  // copy all the items to the array
  // and then read the array to re-create this tree from scratch
  // so that resulting tree is balanced
  void rebalance() 
  {
	  // create a dynamic array,
	  // the length will be the number of nodes in the tree
	  int ArrayLength = numberOfNodes();
	  auto NodesArray = new T[ArrayLength];
	  int Index = 0;
	  // copies all nodes from the tree and stores in the array
	  storeBSTInArray(NodesArray, Root, Index);
	  // deletes everything in the tree
	  clear();
	  // builds the new balanced tree from a sorted array
	  Root = buildBSTFromArray(NodesArray, 0, ArrayLength - 1);
	  // frees the memory after using the dynamic array
	  delete[] NodesArray;
	  NodesArray = nullptr;
  }

  // delete all nodes in tree
  void clear() 
  {
	  clearHelper(Root);
	  Root = nullptr;
  }

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BST<T> &Other) const
  {
	  return isIdentical(Root, Other.Root); 
  }

  // not == to each other
  bool operator!=(const BST<T> &Other) const
  {  
	  return !isIdentical(Root, Other.Root);
  }
};

#endif // BST_HPP
