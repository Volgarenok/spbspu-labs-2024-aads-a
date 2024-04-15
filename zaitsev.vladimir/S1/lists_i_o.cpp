#include "lists_i_o.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <limits>
#include "forward_list.hpp"

namespace zaitsev
{
  void input_lists(ForwardList< named_ullList >& list)
  {
    using List_t = ForwardList< unsigned long long >;
    std::string input;
    std::cin >> input;
    while (std::cin)
    {
      list.push_front({ input, List_t() });
      std::cin >> input;
      while (std::cin && !std::isalpha(input[0]))
      {
        list.front().second.push_front(std::stoull(input));
        std::cin >> input;
      }
      list.front().second.reverse();
    }
  }

  ullList print_lists(std::ostream& out, ForwardList< named_ullList >& list)
  {
    using ullListIt = ullList::iterator;
    if (list.empty())
    {
      return ullList(1,0);
    }
    ForwardList< std::pair< ullListIt, ullListIt > > list_of_iterators =
      { {list.begin()->second.begin(), (list.begin())->second.end()} };
    out << list.begin()->first;
    for (ForwardList< named_ullList >::iterator i = ++(list.begin()); i != list.end(); ++i)
    {
      out << " " << i->first;
      list_of_iterators.push_front({ i->second.begin(), i->second.end() });
    }
    list_of_iterators.reverse();
    out << '\n';

    ullList sums;
    ull sum = 1;
    bool overflow = false;
    while (sum)
    {
      sum = 0;
      size_t elements_nmb = 0;
      for (std::pair < ullListIt, ullListIt >& i : list_of_iterators)
      {
        if (i.first != i.second)
        {
          out << (elements_nmb++ ? " " : "") << *(i.first);
          if (std::numeric_limits< ull >::max() - sum >= *(i.first) && !overflow)
          {
            sum += *(i.first);
          }
          else
          {
            overflow = true;
          }
          ++(i.first);
        }
      }
      if (sum)
      {
        out << "\n";
        sums.push_front(sum);
      }
    }
    if (overflow)
    {
      sums.clear();
    }
    else if(sums.empty() && !list.empty())
    {
      sums.push_front(0);
    }
    return sums;
  }

  std::ostream& print_sums(std::ostream& out, ullList& sums)
  {
    sums.reverse();
    auto i = sums.begin();
    out << *(i++);
    for (; i != sums.end(); ++i)
    {
      out << " " << *i;
    }
    return out;
  }
}
