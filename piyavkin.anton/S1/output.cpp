#include "output.hpp"

size_t piyavkin::max_size_list(const list_t& list)
{
  size_t max_size_list = 0;
  auto it = list.cbegin();
  for (size_t i = 0; i < list.size(); ++i)
  {
    max_size_list = std::max(max_size_list, it->second.size());
    ++it;
  }
  return max_size_list;
}

void piyavkin::outputValue(std::ostream& out, const list_t& list)
{
  auto it = list.cbegin();
  size_t space = 0;
  for (size_t i = 0; i < max_size_list(list); ++i)
  {
    for (size_t j = 0; j < list.size(); ++j)
    {
      if (i < it->second.size())
      {
        auto val = it->second.cbegin();
        for (size_t k = 0; k < i; ++k)
        {
          ++val;
        }
        if (j != space)
        {
          out << ' ';
        }
        out << *val;
      }
      else
      {
        if (space == j)
        {
          ++space;
        }
      }
      ++it;
    }
    out << '\n';
    it = list.cbegin();
  }
}

piyavkin::List< unsigned long long > piyavkin::countSum(const list_t& list)
{
  auto it = list.cbegin();
  List< unsigned long long > sums;
  const unsigned long long max = std::numeric_limits< unsigned long long >::max();
  for (size_t i = 0; i < max_size_list(list); ++i)
  {
    size_t sum = 0;
    for (size_t j = 0; j < list.size(); ++j)
    {
      if (i < it->second.size())
      {
        auto val = it->second.cbegin();
        for (size_t k = 0; k < i; ++k)
        {
          ++val;
        }
        if (i != 0)
        {
          if (max - sum < *val)
          {
            throw std::logic_error("Overflow");
          }
        }
        sum += *val;
      }
      ++it;
    }
    sums.push_back(sum);
    it = list.cbegin();
  }
  return sums;
}
