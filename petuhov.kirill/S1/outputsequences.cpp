#include "outputsequences.hpp"

namespace petuhov
{
  void outputSequences(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequences, List< int >& sums)
  {
    int max_length = 0;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      int length = 0;
      for (auto num_it = it->second.cbegin(); num_it != it->second.cend(); ++num_it)
      {
        ++length;
      }
      if (length > max_length)
      {
        max_length = length;
      }
    }

    List< List< int > > columns;
    for (int i = 0; i < max_length; ++i)
    {
      List< int > column;
      for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
      {
        auto num_it = it->second.cbegin();
        int index = 0;
        while (num_it != it->second.cend() && index < i)
        {
          ++num_it;
          ++index;
        }
        if (num_it != it->second.cend() && index == i)
        {
          column.push_front(*num_it);
        }
        else
        {
          column.push_front(-1);
        }
      }
      column.reverse();
      columns.push_front(column);
    }
    columns.reverse();

    for (auto col_it = columns.cbegin(); col_it != columns.cend(); ++col_it)
    {
      int sum = 0;
      bool has_numbers = false;
      bool first = true;
      for (auto num_it = col_it->cbegin(); num_it != col_it->cend(); ++num_it)
      {
        if (*num_it != -1)
        {
          if (!first)
          {
            out << " ";
          }
          first = false;
          out << *num_it;
          sum += *num_it;
          has_numbers = true;
        }
      }
      if (has_numbers)
      {
        sums.push_front(sum);
        out << "\n";
      }
    }
    sums.reverse();
  }
}
