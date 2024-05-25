#include <algorithm>
#include <iostream>
#include <list>
#include "shell_sort.hpp"
#include "selection_sort.hpp"

int main()
{
  using namespace namestnikov;
  std::list< int > temp({4, 1, 3, 2});
  doShellSort(temp.begin(), temp.size(), std::less< int >());
  for (auto it = temp.begin(); it != temp.end(); ++it)
  {
    std::cout << *it;
  }
  doSelectionSort(temp.begin(), temp.size(), std::less< int >());
  for (auto it = temp.begin(); it != temp.end(); ++it)
  {
    std::cout << *it;
  }
}
