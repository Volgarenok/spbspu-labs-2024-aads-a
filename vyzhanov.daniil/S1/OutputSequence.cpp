#include "OutputSequence.hpp"

size_t vyzhanov::maxListSize(const List< pair >& list)
{
  auto curr = list.cbegin();
  auto end = ++list.cend();
  size_t maxSize = curr->second.capacity();
  for (; curr != end; curr++)
  {
    maxSize = std::max(maxSize, curr->second.capacity());
  }
  return maxSize;
}

void vyzhanov::outputNames(const List< pair >& list, std::ostream& output)
{
  auto curr = list.cbegin();
  auto end = ++list.cend();
  for (; curr != end; ++curr)
  {
    output << curr->first << " ";
  }
  output  << "\n";
}

void vyzhanov::outputNums(List< pair >& list, std::ostream& output)
{
  size_t size = 0;
  size_t maxSize = maxListSize(list);
  List< List< size_t > > newList;
  for (; size <= maxSize; ++size)
  {
    auto curr = list.begin();
    auto end = list.end();
    List< size_t > localList;
    while (curr != ++list.end())
    {
      localList.push_back(curr->second.front());
      curr->second.pop_front();
      ++curr;
    }
    newList.push_back(localList);
  }
  auto it = newList.begin();
  while (it != newList.end())
  {
    auto curr = it->cbegin();
    while (curr != ++it->cend())
    {
      output << *curr << " ";
      curr++;
    }
    output << "\n";
    it++;
  }
  it = newList.begin();
  while (it != newList.end())
  {
    size_t sum = 0;
    auto curr = it->cbegin();
    while (curr != ++it->cend())
    {
      if (sum > std::numeric_limits< size_t >::max() - *curr)
      {
        throw std::out_of_range("overflow!");
      }
      sum += *curr;
      curr++;
    }
    output << sum << " ";
    it++;
  }
  output << "\n";
}
