#include "output.hpp"

using pair_t = std::pair< std::string, piyavkin::List< unsigned int >* >*;
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
  size_t* sum = new size_t[max_size_list] {};
  out << '\n';
  size_t space = 0;
  for (size_t i = 0; i < max_size_list; ++i)
  {
    for (size_t j = 0; j < size; ++j)
    {
      try
      {
        pairs[j].second->out_val(out, i, sum[i]);
        if (j + 1 < max_size_list - space)
        {
          out << ' ';
        }
      }
      catch (...)
      {
        ++space;
      }
    }
    out << '\n';
  }
  size_t sum_sum = 0;
  for (size_t i = 0; i < max_size_list; ++i)
  {
    if (i != 0)
    {
      out << ' ';
    }
    sum_sum += sum[i];
    out << sum[i];
  }
  if (sum_sum == 0)
  {
    out << 0;
  }
  delete[] sum;
}
