#include "OutputSequence.hpp"

size_t vyzhanov::maxListSize(const List< pair >& list)
{
  auto curr = list.cbegin();
  auto end = list.cend();
  size_t maxSize = curr->second.capacity();
  for (; curr != end; ++curr)
  {
    maxSize = std::max(maxSize, curr->second.capacity());
  }
  return maxSize;
}

void vyzhanov::outputNames(const List< pair >& list, std::ostream& output)
{
  auto curr = ++list.cbegin();
  auto end = list.cend();
  output << list.cbegin()->first;
  for (; curr != end; ++curr)
  {
    output << " " << curr->first;
  }
  output << "\n";
}

void vyzhanov::outputNums(List< pair >& list, std::ostream& output)
{
  if (list.capacity() == 1 &&
    list.cbegin()->second.empty())
  {
    output << 0 << "\n";
    return;
  }
  size_t size = 0;
  size_t maxSize = maxListSize(list);
  List< List< size_t > > newList;
  for (; size < maxSize; ++size)
  {
    auto curr = list.begin();
    auto end = list.end();
    List< size_t > localList;
    while (curr != end)
    {
      if (!(curr->second.empty()))
      {
        localList.push_back(curr->second.front());
        curr->second.pop_front();
      }
      ++curr;
    }
    newList.push_back(localList);
  }
  auto it = newList.cbegin();
  for (; it != newList.cend(); it++)
  {
    auto curr = it->cbegin();
    output << *it->cbegin();
    curr++;
    while (curr != it->cend())
    {
      output << " " << *curr;
      curr++;
    }
    output << "\n";
  }

  it = newList.cbegin();
  List< size_t > sums;
  while (it != newList.cend())
  {
    size_t sum = 0;
    auto curr = it->cbegin();
    while (curr != it->cend())
    {
      if (sum > std::numeric_limits< size_t >::max() - *curr)
      {
        throw std::out_of_range("overflow!");
      }
      sum += *curr;
      curr++;
    }
    sums.push_back(sum);
    it++;
  }
  auto curr = sums.cbegin();
  output << *sums.cbegin();
  curr++;
  while (curr != sums.cend())
  {
    output << " " << *curr;
    curr++;
  }
  output << "\n";
}
