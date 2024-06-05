#ifndef BIDIRECTIONAL_LIST_HPP
#define BIDIRECTIONAL_LIST_HPP

#include <utility>
#include "bidirectional_iterator.hpp"
#include "bidirectional_node.hpp"
#include "const_bidirectional_iterator.hpp"

namespace namestnikov
{
  template< class T >
  class List
  {
  public:
    using base_node_t = detail::BaseListNode;
    using node_t = detail::BiListNode< T >;
    using iterator = ListIterator< T >;
    using const_iterator = ConstListIterator< T >;
  private:
    base_node_t * fakeNode_;
    size_t size_;
  };
}

#endif