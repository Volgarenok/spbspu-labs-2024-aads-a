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

template< typename T >
void vyzhanov::outputList(std::ostream& output, const List< T >& list)
{
  auto curr = list.cbegin();
  auto end = list.cend();
  output << *list.cbegin();
  curr++;
  for (; curr != end; ++curr)
  {
    output << " " << *curr;
  }
  output << "\n";
}

void vyzhanov::outputNames(const List< pair >& list, std::ostream& output)
{
  auto curr = list.cbegin();
  auto end = list.cend();
  List< std::string > names;
  for (; curr != end; ++curr)
  {
     names.push_back(curr->first);
  }
  outputList(output, names);
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
    outputList(output, *it);
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
  outputList(output, sums);
}
