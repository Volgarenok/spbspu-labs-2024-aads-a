#ifndef ITERATORS_FOR_S5
#define ITERATORS_FOR_S5

#include <iterator>
#include "stack.hpp"
#include "queue.hpp"
#include "AVLtree.hpp"
#include "AVLtreeNode.hpp"
#include "constIteratorTree.hpp"
#include "IteratorTree.hpp"

namespace novokhatskiy
{
  template< class Key, class T, class Compare>
  class Tree;

  template< class Key, class T, class Compare>
  class ConstIteratorTree;

  template< class Key, class T, class Compare>
  class IteratorTree;


  template< class Key, class T, class Compare = std::less< Key > >
  class ConstLnrIterator : public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_t = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
    friend class ConstIteratorTree < Key, T, Compare >;
    friend class Stack< T >;
    friend class Queue< T >;
  public:
    using ref = std::pair< Key, T >&;
    using point = std::pair< Key, T >*;

    point operator->() const
    {
      return std::addressof(stack.top()->value);
    }

    ref operator*() const
    {
      return stack.top()->value;
    }
    bool operator==(const ConstLnrIterator< Key, T, Compare >& other) const
    {
      return stack == other.stack;
    }

    bool operator!=(const ConstLnrIterator< Key, T, Compare >& other) const
    {
      return stack != other.stack;
    }

  private:
    Stack< detail::NodeTree< Key, T >* > stack;
  };
}

#endif
