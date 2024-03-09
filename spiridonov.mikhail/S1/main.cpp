#include <iostream>
#include <string>
#include "forward_list.hpp"

using namespace spiridonov;

int main()
{
  NamedList lists[100];
  size_t numLists = 0;
  size_t sums[100] = { 0 };
  int totalSize = 0;

  while (std::cin >> lists[numLists].name)
  {
    char c;
    while (std::cin.get(c) && c != '\n')
    {
      if (std::isdigit(c))
      {
        std::cin.putback(c);
        int num;
        std::cin >> num;
        lists[numLists].list.push_back(num);
        sums[numLists] += num;
      }
    }
    numLists++;
  }

  totalSize = 0;
  for (int i = 0; i < numLists; i++)
  {
    totalSize = std::max(totalSize, lists[i].list.get_size());
  }

  for (size_t i = 0; i < numLists; ++i)
  {
    std::cout << lists[i].name << " ";
  }
  std::cout << "\n";

  for (size_t i = 0; i < totalSize; ++i)
  {
    for (size_t j = 0; j < numLists; ++j)
    {
      List<int>::iterator it = lists[j].list.begin();
      for (size_t k = 0; k < i; ++k)
      {
        ++it;
      }
      if (it != lists[j].list.end())
      {
        std::cout << *it << " ";
      }
    }
    std::cout << "\n";
  }

  for (size_t i = 0; i < numLists; ++i)
  {
    int sum = 0;
    List<int>::iterator it = lists[i].list.begin();
    while (it != lists[i].list.end())
    {
      sum += *it;
      ++it;
    }
    sums[i] = sum;
  }

  for (size_t i = 0; i < numLists; ++i)
  {
    std::cout << sums[i] << " ";
  }
  std::cout << "\n";

  return 0;
}
