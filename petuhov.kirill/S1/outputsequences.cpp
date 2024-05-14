#include "outputsequences.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>

namespace petuhov
{
  void outputSequences(std::ostream& out, const List< std::pair< std::string, List< unsigned long long > > >& sequences, List< unsigned long long >& sums)
  {
    if (sequences.empty())
    {
      out << "0\n";
      return;
    }

    int max_length = 0;
    for (ConstIterator< std::pair< std::string, List< unsigned long long > > > seq_it = sequences.cbegin(); seq_it != sequences.cend(); ++seq_it)
    {
      int length = 0;
      for (ConstIterator< unsigned long long > num_it = seq_it->second.cbegin(); num_it != seq_it->second.cend(); ++num_it)
      {
        ++length;
      }
      if (length > max_length)
      {
        max_length = length;
      }
    }

    List< List< unsigned long long > > columns;
    for (int i = 0; i < max_length; ++i)
    {
      List< unsigned long long > column;
      for (ConstIterator< std::pair< std::string, List< unsigned long long > > > seq_it = sequences.cbegin(); seq_it != sequences.cend(); ++seq_it)
      {
        ConstIterator< unsigned long long > num_it = seq_it->second.cbegin();
        for (int j = 0; j < i; ++j)
        {
          if (num_it != seq_it->second.cend())
          {
            ++num_it;
          }
        }
        if (num_it != seq_it->second.cend())
        {
          column.push_front(*num_it);
        }
        else
        {
          column.push_front(static_cast< unsigned long long >(-1));
        }
      }
      column.reverse();
      columns.push_front(column);
    }

    columns.reverse();

    for (ConstIterator< List< unsigned long long > > col_it = columns.cbegin(); col_it != columns.cend(); ++col_it)
    {
      unsigned long long sum = 0;
      bool first = true;
      bool has_numbers = false;
      for (ConstIterator< unsigned long long > num_it = col_it->cbegin(); num_it != col_it->cend(); ++num_it)
      {
        if (*num_it != static_cast< unsigned long long >(-1))
        {
          if (!first)
          {
            out << " ";
          }
          out << *num_it;
          sum += *num_it;
          has_numbers = true;
          first = false;
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
