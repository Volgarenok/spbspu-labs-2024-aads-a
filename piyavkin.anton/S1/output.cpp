#include "output.hpp"

void piyavkin::output(std::ostream& out, const pair_t pairs, size_t size, size_t max_size_list)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (i != 0)
    {
      out << ' ';
    }
    out << pairs[i].first;
  }
  out << '\n';
  if (max_size_list == 0)
  {
    out << 0;
    return;
  }
  size_t space = 0;
  for (size_t i = 0; i < max_size_list; ++i)
  {
    for (size_t j = 0; j < size; ++j)
    {
      try
      {
        auto val = pairs[j].second->get_element(i);
        if (j != space)
        {
          out << ' ';
        }
        out << val;
      }
      catch(const std::logic_error& e)
      {
        if (space == j)
        {
          ++space;
        }
      }
    }
    out << '\n';
  }
  size_t* sum = new size_t[max_size_list] {};
  const unsigned long long max = std::numeric_limits< unsigned long long >::max();
  for (size_t i = 0; i < max_size_list; ++i)
  {
    for (size_t j = 0; j < size; ++j)
    {
      try
      {
        auto val = pairs[j].second->get_element(i);
        if (max - sum[i] < val)
        {
          throw std::invalid_argument("Overflow");
        }
        sum[i] += val;
      }
      catch (const std::invalid_argument& e)
      {
        delete[] sum;
        throw;
      }
      catch(const std::logic_error& e)
      {
      }
    }
  }
  for (size_t i = 0; i < max_size_list; ++i)
  {
    if (i != 0)
    {
      out << ' ';
    }
    out << sum[i];
  }
  delete[] sum;
}
