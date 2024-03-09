#include <iostream>
#include "list.hpp"
#include "listFunctions.hpp"

int main()
{
  using namespace grechishnikov;

  List< namedList > namedLists = inputLists(std::cin);

  for (auto namedIter = namedLists.begin(); namedIter != namedLists.end(); namedIter++)
  {
    std::cout << namedIter->first;
    if (namedIter + 1 != namedLists.end())
    {
      std::cout << ' ';
    }
  }
  if (!namedLists.empty())
  {
    std::cout << '\n';
  }

  size_t maxSize = 0;
  for (auto namedIter = namedLists.begin(); namedIter != namedLists.end(); namedIter++)
  {
    maxSize = std::max(maxSize, namedIter->second.size());
  }
  for (size_t i = 0; i < maxSize; i++)
  {
    for (auto iter = namedLists.begin(); iter != namedLists.end(); iter++)
    {
      if (iter->second.size() > i)
      {
        std::cout << iter->second[i];
        if (iter + 1 != namedLists.end())
        {
          std::cout << ' ';
        }
      }
    }
    std::cout << '\n';
  }
  try
  {
    for (auto namedIter = namedLists.begin(); namedIter != namedLists.end(); namedIter++)
    {
      std::cout << countSum(namedIter->second) << ' ';
    }
    std::cout << '\n';
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
