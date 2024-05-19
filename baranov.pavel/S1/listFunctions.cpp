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
        auto temp_i = i->second.begin();
        std::advance(temp_i, ind);
        numbers.push_back(*temp_i);
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

