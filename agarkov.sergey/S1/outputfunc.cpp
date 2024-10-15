#include "outputfunc.hpp"
#include <limits>
#include <exception>

namespace
{
  template< typename Iterator >
  void advance(Iterator& iter, size_t n)
  {
    for (size_t i = 0; i < n && iter != Iterator(); ++i)
    {
      ++iter;
    }
  }
  constexpr size_t MAX = std::numeric_limits< size_t >::max();
  size_t trySum(const size_t& a, const size_t& b)
  {
    if (a >= MAX - b)
    {
      throw std::overflow_error("Sum overflow");
    }
    return a + b;
  }
}

void agarkov::outputName(std::ostream& out, const agarkov::ForwardList< agarkov::pair_t >& lists)
{
  out << (*(lists.cbegin())).first;
  for (auto iter = (lists.cbegin())++; iter != lists.cend(); ++iter)
  {
    out << ' ' << (*iter).first;
  }
  out << '\n';
}

void agarkov::outputNum(std::ostream& out, const agarkov::ForwardList< agarkov::pair_t >& lists)
{
  size_t max_length = lists.max_size();

  for (size_t i = 0; i < max_length; ++i)
  {
    bool has_elements = false;
    bool outed = false;
    for (auto iter = lists.cbegin(); iter != lists.cend(); ++iter)
    {
      const auto& pair = *iter;
      if (!pair.second.empty() && i < pair.second.max_size())
      {
        auto inner_iter = pair.second.cbegin();
        advance(inner_iter, i);
        if (outed)
        {
          out << ' ' << *inner_iter;
        }
        else
        {
          out << *inner_iter;
          outed = true;
        }
        has_elements = true;
      }
    }
    if (has_elements)
    {
      out << '\n';
    }
    else
    {
      out << 0;
    }
  }
}

void agarkov::outputSum(std::ostream& out, const agarkov::ForwardList< agarkov::pair_t >& lists)
{
  size_t max_length = lists.max_size();

  for (size_t i = 0; i < max_length; ++i)
  {
    size_t sum = 0;
    bool outed = false;
    bool has_elements = false;
    for (auto iter = lists.cbegin(); iter != lists.cend(); ++iter)
    {
      const auto& pair = *iter;
      if (!pair.second.empty() && i < pair.second.max_size())
      {
        auto inner_iter = pair.second.cbegin();
        advance(inner_iter, i);
        sum = trySum(sum,*inner_iter);
        has_elements = true;
      }
    }
    if (has_elements)
    {
      if (outed)
      {
        out << sum << ' ';
      }
      else
      {
        out << sum;
        outed = true;
      }
    }
  }
}
