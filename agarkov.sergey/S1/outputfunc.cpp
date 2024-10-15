#include "outputfunc.hpp"

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
}

void agarkov::outputName(std::ostream& out, const agarkov::ForwardList< agarkov::pair_t >& lists)
{
  for (auto iter = lists.cbegin(); iter != lists.cend(); ++iter)
  {
    out << (*iter).first << ' ';
  }
  out << '\n';
}

void agarkov::outputNum(std::ostream& out, const agarkov::ForwardList< agarkov::pair_t >& lists)
{
  size_t max_length = lists.max_size();

  for (size_t i = 0; i < max_length; ++i)
  {
    bool has_elements = false;
    for (auto iter = lists.cbegin(); iter != lists.cend(); ++iter)
    {
      const auto& pair = *iter;
      if (!pair.second.empty() && i < pair.second.max_size())
      {
        auto inner_iter = pair.second.cbegin();
        advance(inner_iter, i);
        out << *inner_iter << ' ';
        has_elements = true;
      }
    }
    if (has_elements)
    {
      out << '\n';
    }
  }
}

void agarkov::outputSum(std::ostream& out, const agarkov::ForwardList< agarkov::pair_t >& lists)
{
  size_t max_length = lists.max_size();

  for (size_t i = 0; i < max_length; ++i)
  {
    size_t sum = 0;
    bool has_elements = false;
    for (auto iter = lists.cbegin(); iter != lists.cend(); ++iter)
    {
      const auto& pair = *iter;
      if (!pair.second.empty() && i < pair.second.max_size())
      {
        auto inner_iter = pair.second.cbegin();
        advance(inner_iter, i);
        sum += *inner_iter;
        has_elements = true;
      }
    }
    if (has_elements)
    {
      out << sum << ' ';
    }
  }
  out << '\n';
}
