#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include "node.hpp"

namespace baranov
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T, typename Compare >
  class Iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    friend class Tree< Key, T, Compare >;
    using this_t = Iterator< Key, T, Compare >;
    Iterator();
    ~Iterator() = default;
    Iterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;
  private:
    Node< Key, T > * node_;
  };
}

#endif

