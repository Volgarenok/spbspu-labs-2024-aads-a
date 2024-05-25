#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include "shell_sort.hpp"
#include "selection_sort.hpp"
#include "generate_numbers.hpp"

template< class Iter >
void printData(Iter first, Iter last, std::ostream & out)
{
  auto temp = first;
  ++temp;
  for (; temp != last; ++temp)
  {
    out << *first << " ";
    ++first;
  }
  out << *first << "\n";
}

int main()
{
  using namespace namestnikov;
  std::vector< int > vec = generateNumbers< int >(20);
  printData(vec.begin(), vec.end(), std::cout);
}
