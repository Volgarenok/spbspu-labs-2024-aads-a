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

  if (!namedLists.empty())
  {
    std::cout << namedLists.cbegin()->first;
    for (auto namedIter = ++namedLists.cbegin(); namedIter != namedLists.cend(); namedIter++)
    {
      std::cout << ' ' << namedIter->first;
    }
    std::cout << '\n';
  }

  size_t maxSize = 1;
  for (auto namedIter = namedLists.cbegin(); namedIter != namedLists.cend(); namedIter++)
  {
    maxSize = std::max(maxSize, namedIter->second.size());
  }

  List< size_t > temp;
  List< List< size_t > > outList(maxSize, temp);
  auto outIter = outList.begin();
  for (size_t i = 0; i < maxSize; i++)
  {
    for (auto iter = namedLists.cbegin(); iter != namedLists.cend(); iter++)
    {
      if (i < iter->second.size())
      {
        auto temp = iter->second.cbegin();
        std::advance(temp, i);
        outIter->push_back(*temp);
      }
    }
    outIter++;
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
