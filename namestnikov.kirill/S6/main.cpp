#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include "shell_sort.hpp"
#include "selection_sort.hpp"
#include "generate_numbers.hpp"
#include "test_sortings.hpp"

int main()
{
  using namespace namestnikov;
  std::vector< int > vec = generateNumbers< int >(20);
  printData(vec.begin(), vec.end(), std::cout);
  doSelectionSort(vec.begin(), vec.size(), std::less< int >());
  printData(vec.begin(), vec.end(), std::cout);
}
