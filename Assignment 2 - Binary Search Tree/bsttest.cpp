/**
 * Testing BST - Binary Search Tree functions
 *
 * This file has series of tests for BST
 * Each test is independent and uses assert statements
 * Test functions are of the form
 *
 *      test_netidXX()
 *
 * where netid is UW netid and XX is the test number starting from 01
 *
 * Test functions can only use the public functions from BST
 * testBSTAll() is called from main in main.cpp
 * testBSTAll calls all other functions
 * @author Multiple
 * @date ongoing
 */

#include "bst.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor
{
public:
  // never create an instance of TreeVisitor object
  // we'll just use the static functions
  TreeVisitor() = delete;

  // insert output to SS rather than cout, so we can test it
  static stringstream SS;

  // get SS as a string
  static string getSS() 
  {
	  return SS.str();
  }

  // set SS to be empty string
  static void resetSS()
  { 
	  SS.str(string());
  }

  // instead of cout, insert item into SS, a stringstream object
  static void visitor(const string &Item) 
  {
	  SS << Item; 
  }

  // instead of cout, insert item into SS, a stringstream object
  static void visitor(const int &Item) 
  {
	  SS << Item;
  }
};

// initialize the static variable
//  warning: initialization of 'SS' with static storage duration
//  may throw an exception that cannot be caught [cert-err58-cpp]
//  Not sure how to do it without making code harder to read
//  NOLINTNEXTLINE
stringstream TreeVisitor::SS;

template <class T> void visitorSimple(const T &Item) {
  cout << "visitorSimple: " << Item;
}

/**
 * Test functions by Yusuf Pisan
 */

// Testing ==
void testPisan01() {
  cout << "Starting testPisan01" << endl;
  cout << "* Testing == and !=" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  // == and != for empty trees
  assert(B1 == B2 && (!(B1 != B2)));
  B1.add("c");
  B2.add("c");
  B3.add("b");
  // == and !- for 1-Node trees B1, B2, B3
  assert(B1 == B2 && (!(B1 != B2)));
  assert(B1 != B3 && (!(B1 == B3)));
  cout << "Ending testPisan01" << endl;
}

// Testing == in detail
void testPisan02() {
  cout << "Starting testPisan02" << endl;
  cout << "* Testing == and != with more detail" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  // == for 5-Node trees B1, B2
  assert(B1 == B2 && (!(B1 != B2)));

  BST<string> B4(B3);
  // copy constructor for 1-Node trees B3, B4
  assert(B3 == B4 && (!(B3 != B4)));

  BST<string> B5(B1);
  // copy constructor for 5-Node trees B1, B5
  assert(B1 == B5 && (!(B5 != B1)));

  BST<string> B7("b");
  // 1-param constructor for 1-Node trees B3, B7
  assert(B3 == B7 && (!(B3 != B7)));

  cout << "Ending testPisan02" << endl;
}

// Testing traversal
void testPisan03() {
  cout << "Starting testPisan03" << endl;
  cout << "* Testing traversal" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  TreeVisitor::resetSS();
  B1.inOrderTraverse(TreeVisitor::visitor);
  string Result = "acfgx";
  assert(TreeVisitor::getSS() == Result);

  // testing out simpleVisitor to demonstrate
  // any function that has a matching signature can be called
  B1.inOrderTraverse(visitorSimple);

  TreeVisitor::resetSS();
  B1.preOrderTraverse(TreeVisitor::visitor);
  Result = "cafgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.postOrderTraverse(TreeVisitor::visitor);
  Result = "axgfc";
  assert(TreeVisitor::getSS() == Result);

  cout << "Visual check B1:" << endl;
  cout << B1 << endl;
  cout << "Ending testPisan03" << endl;
}

/**
 * Test functions by Sample Sample
 */

// Testing samplefunctionality
void testSample01() {
  cout << "Starting testSample01" << endl;
  cout << "* Testing copy" << endl;
  BST<int> B1;
  B1.add(4);
  B1.add(7);
  B1.add(8);
  B1.add(25);
  B1.add(1);
  B1.add(30);
  B1.add(19);
  cout << B1 << endl;
  cout << "* Testing rebalance" << endl;
  B1.rebalance();
  cout << B1 << endl;
  cout << "* Testing remove" << endl;
  BST<int> B2;
  B2.add(15);
  B2.add(9);
  B2.add(20);
  B2.add(6);
  B2.add(12);
  B2.add(17);
  B2.add(21);
  B2.add(2);
  B2.add(8);
  B2.add(11);
  B2.add(14);
  cout << B2 << endl;
  B2.remove(9);
  cout << B2 << endl;
  cout << "* Testing clear" << endl;
  BST<int> B3 = B1;
  cout << B3 << endl;
  B3.clear();
  cout << B3 << endl;
  assert(B3.isEmpty() && "isEmpty is not right");
  assert(B2.getHeight() == 4 && " getHeight is not right");
  assert(B2.numberOfNodes() == 10 && " numberOfNodes is not right");
  assert(B2.contains(21) && "contains is not right");
  cout << "Ending testSample01" << endl;
}

// Calling all test functions
void testBSTAll() 
{	
  testPisan01();
  cout << endl;
  testPisan02();
  cout << endl;
  testPisan03();
  cout << endl;
  testSample01();
}