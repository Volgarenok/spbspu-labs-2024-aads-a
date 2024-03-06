#include <iostream>
#include <string>
#include "forward_list.hpp"
#include "stack.hpp"
#include "queue.hpp"

int main()
{
  using namespace spiridonov;
  spiridonov::NamedList lists[100];
  int numLists = 0;

  spiridonov::Queue<int> queue;
  spiridonov::Stack<int> stack;

  while (std::cin >> lists[numLists].name)
  {
    char c;
    std::cin >> std::noskipws;
    while (std::cin >> c && c != '\n')
    {
      if (std::isdigit(c))
      {
        std::cin.putback(c);
        int num;
        std::cin >> num;
        lists[numLists].list.push_back(num);
      }
    }
    std::cin >> std::skipws;
    numLists++;
  }
  int totalSize = 0;

  for (size_t i = 0; i < numLists; i++)
  {
    totalSize = std::max(totalSize, lists[i].list.get_size());
  }

  for (size_t i = 0; i < numLists; ++i)
  {
    std::cout << lists[i].name << " ";
  }

  std::cout << "\n";
  for (size_t i = 0; i < totalSize; i++)
  {
    for (size_t j = 0; j < numLists; j++)
    {
      if (i < lists[j].list.get_size())
      {
        std::cout << lists[j].list[i] << " ";
        queue.push(lists[j].list[i]);
      }
    }
  }
  std::cout << "\n";

  if (totalSize > 0)
  {
    int sum = 0;
    for (size_t i = 0; i < numLists; i++)
    {
      for (size_t j = 0; j < lists[i].list.get_size(); j++)
      {
        sum += lists[i].list[j];
      }
      std::cout << sum << " ";
    }
    std::cout << "\n";
  }

  else
  {
    std::cout << "Unable to calculate sum as no lists are entered." << "\n";
  }

  return 0;
}
