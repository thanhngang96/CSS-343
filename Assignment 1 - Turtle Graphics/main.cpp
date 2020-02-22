/**
 * A generic main file
 * @file main.cpp
 *
 *
 * @author Yusuf Pisan
 * @date 24 Sep 2019
 */

#include <iostream>

// forward declaration, testAll is defined in another file
void testAll();
void test0();
void test1();
void test2();
void test3();
void test4();

int main() {
  testAll();
  std::cout << "Done!" << std::endl;
  system("pause");
  return 0;
}

