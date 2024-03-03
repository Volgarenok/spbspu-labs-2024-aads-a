#include "outputForwardList.hpp"

void novokhatskiy::outputForwardList(std::ostream& out, ForwardList<std::pair<std::string, ForwardList< unsigned long long > > >& pairs)
{
  using ull = unsigned long long;
  if (pairs.empty())
  {
    throw std::invalid_argument("Your list is empty");
  }
  ForwardIterator< std::pair<std::string, ForwardList< ull > > > iter = pairs.begin();
  size_t maxSize{};
  for (; iter != pairs.end(); iter++)
  {
    if (std::isalpha(iter->first[0]))
    {
      if (iter != pairs.begin())
      {
        out << ' ';
      }
      out << iter->first;
    }
    else
    {
      std::cout << ' ';
    }
    maxSize = std::max(maxSize, iter->second.max_size());
  }
  std::cout << '\n';
  ForwardList< ull > listOfSums;
  ull sum{};
  for (size_t i = 0; i < maxSize; i++)
  {
    for (auto j = pairs.begin(); j != pairs.end(); ++j)
    {
      ForwardIterator< ull > numberIter = j->second.begin();
      if (j->second.max_size() <= i)
      {
        continue;
      }
      numberIter = numberIter.moveIterator(i);
      if (sum != 0)
      {
        out << ' ';
      }
      out << *numberIter;
      sum += *numberIter;
    }
    out << '\n';
    listOfSums.push_front(sum);
    sum = 0;
  }
  listOfSums.reverse();
  for (auto i = listOfSums.begin(); i != listOfSums.end(); ++i)
  {
    if (i != listOfSums.begin())
    {
      out << ' ';
    }
    out << *i;
  }
  out << '\n';
}
