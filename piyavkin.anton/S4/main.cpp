#include <iostream>
#include "tree.hpp"

int main()
{
  piyavkin::Tree< int, int > tree;
  std::cout << tree.data;
}