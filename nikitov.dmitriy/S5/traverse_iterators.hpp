#ifndef TRAVERSE_ITERATORS_HPP
#define TRAVERSE_ITERATORS_HPP

#include <iterator>

namespace nikitov
{
  template< class Key, class T, class Compare >
  class Tree;

  template< class Key, class T, class Compare = std::less< Key > >
  class LNRIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  };

  template< class Key, class T, class Compare = std::less< Key > >
  class RNLIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  };

  template< class Key, class T, class Compare = std::less< Key > >
  class BreadthIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  };

}
#endif