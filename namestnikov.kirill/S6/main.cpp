#include <algorithm>
#include <iostream>
#include "shell_sort.hpp"
#include "selection_sort.hpp"
#include "generate_numbers.hpp"
#include "test_sortings.hpp"

int main()
{
  using namespace namestnikov;
  std::vector< int > vec = generateNumbers< int >(20);
  testSortings(std::cout, vec, vec.size(), std::less< int >());
}
