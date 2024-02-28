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
  for (size_t i = 0; i < max_size_list; ++i)
  {
    for (size_t j = 0; j < size; ++j)
    {
      try
      {
        auto val = pairs[j].second->get_element(i);
        if (j != 0)
        {
          out << 'X';
        }
        out << val;
      }
      catch(const std::logic_error& e)
      {
        break;
      }
    }
    out << '\n';
  }
}
