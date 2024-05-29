#include "resultsPrinter.hpp"

#include <limits>

#include "list.hpp"

void belokurskaya::printNames(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& list)
{
  auto it = list.begin();
  if (it != list.end())
  {
    out << it->first;
    ++it;
  }

  for (; it != list.end(); ++it)
  {
    out << ' ' << it->first;
  }
}

void belokurskaya::printSequences(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& list)
{
  size_t maxLen = 0;
  for (const auto& pair : list)
  {
    if (pair.second.size() > maxLen)
    {
      maxLen = pair.second.size();
    }
  }

  for (size_t i = 0; i < maxLen; ++i)
  {
    bool first = true;
    for (const auto& pair : list)
    {
      if (i < pair.second.size())
      {
        if (!first)
        {
          out << ' ';
        }
        out << pair.second.at(i);
        first = false;
      }
    }
    out << '\n';
  }
}

void belokurskaya::printSums(std::ostream& output, const List< std::pair< std::string, List< size_t > > >& list)
{
  size_t maxLen = 0;
  for (const auto& pair : list)
  {
    if (pair.second.size() > maxLen)
    {
      maxLen = pair.second.size();
    }
  }

  if (maxLen == 0)
  {
    output << 0 << '\n';
    return;
  }

  List< size_t > sums;

  for (size_t i = 0; i < maxLen; ++i)
  {
    size_t sum = 0;
    for (const auto& pair : list)
    {
      if (i < pair.second.size())
      {
        sum += pair.second.at(i);
      }
    }
    sums.push_back(sum);
  }

  auto it = sums.begin();
  if (it != sums.end())
  {
    output << *it;
    ++it;
  }

  for (; it != sums.end(); ++it)
  {
    output << ' ' << *it;
  }
}
