#include <iostream>
#include "list.hpp"
#include "listFunctions.hpp"

int main()
{
  using namespace grechishnikov;

  List< namedList > namedLists;
  try
  {
    namedLists = inputLists(std::cin);
  }
  catch (const std::logic_error &e)
  {
    return 0;
  }

  for (auto namedIter = namedLists.begin(); namedIter != namedLists.end(); namedIter++)
  {
    std::cout << namedIter->first << ' ';
  }
  std::cout << '\n';

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
        std::cout << iter->second[i] << ' ';
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
