#include "listFunctions.hpp"

void baranov::readByElement(listOfLists & outList, ds_t & inList)
{
  size_t ind = 0;
  while (true)
  {
    List< size_t > numbers;
    auto end = inList.end();
    for (auto i = inList.begin(); i != end; ++i)
    {
      if (ind < i->second.size())
      {
        numbers.push_back(*(i->second.begin() + ind));
      }
    }
    outList.push_back(numbers);
    ++ind;
  }
}

