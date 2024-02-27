#include "output.hpp"

using pair_t = std::pair< std::string, piyavkin::List< unsigned long long >* >*;
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
    space = 0;
    for (size_t j = 0; j < size; ++j)
    {
      try
      {
        pairs[j].second->out_val(out, i, sum[i], space);
      }
      catch(const std::invalid_argument& e)
      {
        delete[] sum;
        throw;
      }      
    }
    out << '\n';
  }
  // const ListIterator< unsigned long long > cit(nullptr);
  // bool flag = false;
  // for (size_t i = 0; i < max_size_list; ++i)
  // {
  //   for (size_t j = 0; j < size; ++j)
  //   {
  //     auto it = pairs[j].second->begin();
  //     for (size_t k = 0; k < i; ++k)
  //     {
  //       if (it != cit)
  //       {
  //         ++it;
  //       }
  //       else
  //       {
  //         flag = true;
  //       }
  //     }
  //     if (!flag)
  //     {
  //       out << *it;
  //     }
  //   }
  // }

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
