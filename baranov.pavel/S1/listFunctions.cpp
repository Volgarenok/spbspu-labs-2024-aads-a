#include "listFunctions.hpp"

void baranov::readByElement(listOfLists & outList, ds_t & inList)
{
  size_t ind = 0;
  auto end = inList.end();
  while (true)
  {
    List< size_t > numbers;
    for (auto i = inList.begin(); i != end; ++i)
    {
      if (ind < i->second.size())
      {
        numbers.push_back(*(i->second.begin() + ind));
      }
    }
    if (!numbers.empty())
    {
      outList.push_back(numbers);
      ++ind;
    }
    else
    {
      break;
    }
  }
}

