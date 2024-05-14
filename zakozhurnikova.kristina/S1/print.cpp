#include "print.hpp"
#include <iostream>

size_t zakozhurnikova::getMaxSize(const List< pair >& l)
{
  size_t max = 0;
  for (auto p : l)
  {
    size_t size = p.second.size();
    max = std::max(max, size);
  }
  return max;
}

void zakozhurnikova::printNames(const List< pair >& l, std::ostream& out)
{
  for (auto it = l.begin(); it != l.end(); ++it)
  {
    out << it->first;
    auto temp = it;
    std::advance(temp, 1);
    if (temp != l.end())
    {
      out << ' ';
    }
  }
  if (l.size() != 0)
  {
    out << '\n';
  }
}

void zakozhurnikova::printByIndex(const List< pair > &l, std::ostream& out)
{
  size_t maxSize = getMaxSize(l);
  for (size_t i = 0; i < maxSize; ++i)
  {
    size_t printed = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
      if (i >= it->second.size())
      {
        continue;
      }
      auto temp = it->second.cbegin();
      std::advance(temp, i);
      out << (printed++ == 0 ? "" : " ") << *(temp);
    }
    out << '\n';
  }
}

void zakozhurnikova::printSums(const List< pair >& l, std::ostream& out)
{
  bool overflow = false;
  constexpr size_t max = std::numeric_limits< size_t >::max();
  size_t maxSize = getMaxSize(l);
  List< size_t > listSum;
  for (size_t i = 0; i < maxSize; ++i)
  {
    size_t sum = 0;
    for (auto p : l)
    {
      if (i >= p.second.size())
      {
        continue;
      }
      if (max - sum > *(std::next(p.second.cbegin(), i)))
      {
        sum += *(std::next(p.second.cbegin(), i));
      }
      else
      {
        overflow = true;
      }
    }
    listSum.push_back(sum);
  }
  if (overflow)
  {
    throw std::range_error("Failed input numbers with overflow");
  }
  for (auto it = listSum.begin(); it != listSum.end(); ++it)
  {
    out << *(it);
    if (std::next(it, 1) != listSum.end())
    {
      out << ' ';
    }
  }
  if (maxSize == 0)
  {
    out << "0";
  }
}
