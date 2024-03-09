#ifndef OUTPUT_NAMED_LIST
#define OUTPUT_NAMED_LIST

#include <iosfwd>
#include "list.hpp"
#include "input_named_list.hpp"

namespace erohin
{
  std::ostream & printNames(std::ostream & output, const List< named_list > & list);
  void formOrderedNumLists(List < List< int_t > > & result, const List< named_list > & list);
  void formSumList(List< long_t > & result, const List < List< int_t > > & list);
  template< class T >
  std::ostream & printList(std::ostream & output, const List< T > & list)
  {
    if (!list.empty())
    {
      output << list.front();
    }
    else
    {
      return output;
    }
    auto current = ++list.cbegin();
    auto last = list.cend();
    while (current != last)
    {
      output << " " << *current;
      ++current;
    }
    return output;
  }
}
#endif

