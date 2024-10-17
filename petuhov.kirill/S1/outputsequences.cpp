#include "list.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>

namespace petuhov
{
  void outputSequences(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& sequences, List< size_t >& sums)
  {
    if (sequences.empty())
    {
      out << "0\n";
      return;
    }

    size_t max_length = 0;
    for (ConstIterator< std::pair< std::string, List< size_t > > > seq_it = sequences.cbegin(); seq_it != sequences.cend(); ++seq_it)
    {
      size_t length = 0;
      for (ConstIterator< size_t > num_it = seq_it->second.cbegin(); num_it != seq_it->second.cend(); ++num_it)
      {
        ++length;
      }
      if (length > max_length)
      {
        max_length = length;
      }
    }

    List< List< size_t > > columns;
    for (size_t i = 0; i < max_length; ++i)
    {
      List< size_t > column;
      for (ConstIterator< std::pair< std::string, List< size_t > > > seq_it = sequences.cbegin(); seq_it != sequences.cend(); ++seq_it)
      {
        ConstIterator< size_t > num_it = seq_it->second.cbegin();
        for (size_t j = 0; j < i; ++j)
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
      }
      column.reverse();
      columns.push_front(column);
    }

    columns.reverse();

    bool overflow = false;
    for (ConstIterator< List< size_t > > col_it = columns.cbegin(); col_it != columns.cend(); ++col_it)
    {
      size_t sum = 0;
      bool first = true;
      bool has_numbers = false;
      for (ConstIterator< size_t > num_it = col_it->cbegin(); num_it != col_it->cend(); ++num_it)
      {
        if (!first)
        {
          out << " ";
        }
        out << *num_it;
        if (*num_it > 0 && sum > std::numeric_limits< size_t >::max() - *num_it)
        {
          overflow = true;
        }
        sum += *num_it;
        has_numbers = true;
        first = false;
      }
      if (has_numbers)
      {
        sums.push_front(sum);
        out << "\n";
      }
    }
    sums.reverse();

    if (overflow)
    {
      throw std::overflow_error("Overflow occurred during summing");
    }

    if (sums.empty())
    {
      out << "0\n";
    }
  }
}
