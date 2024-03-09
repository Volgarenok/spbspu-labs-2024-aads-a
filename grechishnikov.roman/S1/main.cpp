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
  catch (std::logic_error &e)
  {
    std::cout << 0 << '\n';
    return 0;
  }

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

  size_t maxSize = 1;
  for (auto namedIter = namedLists.begin(); namedIter != namedLists.end(); namedIter++)
  {
    maxSize = std::max(maxSize, namedIter->second.size());
  }

  List< size_t > temp;
  List< List< size_t > > outList;
  outList.assign(maxSize, temp);
  for (size_t i = 0; i < maxSize; i++)
  {
    for (auto iter = namedLists.begin(); iter != namedLists.end(); iter++)
    {
      if (i < iter->second.size())
      {
        outList[i].push_back(iter->second[i]);
      }
    }
  }

  for (auto outIter = outList.begin(); outIter != outList.end(); outIter++)
  {
    outputList(*outIter, std::cout);
    if (!outIter->empty())
    {
      std::cout << '\n';
    }
  }

  try
  {
    for (auto outIter = outList.begin(); outIter != outList.end(); outIter++)
    {
      std::cout << countSum(*outIter);
      if (outIter + 1 != outList.end())
      {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
