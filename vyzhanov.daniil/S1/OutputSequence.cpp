kk#include "OutputSequence.hpp"

std::ostream& vyzhanov::outputList(std::ostream& output, const List< size_t >& list)
{
  auto curr = list.cbegin();
  auto end = list.cend();
  end--;
  while (curr != end)
  {
    output << *curr << " ";
    curr++;
  }
  return output << *curr;
}

size_t vyzhanov::maxListSize(const List< pair >& list)
{
  size_t maxSize = 0;
  auto curr = list.cbegin();
  for (; curr != list.cend(); ++curr)
  {
    maxSize = std::max(maxSize, curr->second.capacity());
  }
  return maxSize;
}

void vyzhanov::outputNames(const List< pair >& list, std::ostream& output)
{
  auto curr = list.cbegin();
  auto end = list.cend();
  for (; curr != end; ++curr)
  {
    output << curr->first << " ";
  }
  output << end->first << "\n";
}

void vyzhanov::outputNums(List< pair >& list, std::ostream& output)
{
  size_t size = 0;
  size_t maxSize = maxListSize(list);
  List< List< size_t > > newList;
  for (; size < maxSize; ++size)
  {
    auto curr = list.begin();
    List< size_t > localList;
    while (curr != list.end())
    {
      if (curr->second.capacity() > 0)
      {
        localList.push_back(curr->second.front());
        curr->second.pop_front();
      }
      ++curr;
    }
    newList.push_back(localList);
  }
  auto it = newList.begin();
  auto end = newList.end();
  while (it != end)
  {
    outputList(output, *it);
    output << '\n';
    it++;
  }
}

void vyzhanov::printSums(const List< pair >& l, std::ostream& out)
{

}#include "OutputSequence.hpp"

std::ostream& vyzhanov::outputList(std::ostream& output, const List< size_t >& list)
{
  auto curr = list.cbegin();
  auto end = list.cend();
  end--;
  while (curr != end)
  {
    output << *curr << " ";
    curr++;
  }
  return output << *curr;
}

size_t vyzhanov::maxListSize(const List< pair >& list)
{
  size_t maxSize = 0;
  auto curr = list.cbegin();
  for (; curr != list.cend(); ++curr)
  {
    maxSize = std::max(maxSize, curr->second.capacity());
  }
  return maxSize;
}

void vyzhanov::outputNames(const List< pair >& list, std::ostream& output)
{
  auto curr = list.cbegin();
  auto end = list.cend();
  for (; curr != end; ++curr)
  {
    output << curr->first << " ";
  }
  output << end->first << "\n";
}

void vyzhanov::outputNums(List< pair >& list, std::ostream& output)
{
  size_t size = 0;
  size_t maxSize = maxListSize(list);
  List< List< size_t > > newList;
  for (; size < maxSize; ++size)
  {
    auto curr = list.begin();
    List< size_t > localList;
    while (curr != list.end())
    {
      if (curr->second.capacity() > 0)
      {
        localList.push_back(curr->second.front());
        curr->second.pop_front();
      }
      ++curr;
    }
    newList.push_back(localList);
  }
  auto it = newList.begin();
  auto end = newList.end();
  while (it != end)
  {
    outputList(output, *it);
    output << '\n';
    it++;
  }
}

void vyzhanov::printSums(const List< pair >& l, std::ostream& out)
{

}
