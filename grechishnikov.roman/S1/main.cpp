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

  for (auto namedIter = namedLists.cbegin(); namedIter != namedLists.cend(); namedIter++)
  {
    std::cout << namedIter->first;
    if (namedIter + 1 != namedLists.cend())
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
  List< List< size_t > > outList(maxSize, temp);
  for (size_t i = 0; i < maxSize; i++)
  {
    for (auto iter = namedLists.cbegin(); iter != namedLists.cend(); iter++)
    {
      if (i < iter->second.size())
      {
        outList[i].push_back(*(iter->second.cbegin() + i));
      }
    }
  }

  for (auto outIter = outList.cbegin(); outIter != outList.cend(); outIter++)
  {
    outputList(*outIter, std::cout);
    if (!outIter->empty())
    {
      std::cout << '\n';
    }
  }

  try
  {
    List< size_t > sumList;
    for (auto outIter = outList.cbegin(); outIter != outList.cend(); outIter++)
    {
      sumList.push_back(countSum(*outIter));
    }
    outputList(sumList, std::cout);
    std::cout << '\n';
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
