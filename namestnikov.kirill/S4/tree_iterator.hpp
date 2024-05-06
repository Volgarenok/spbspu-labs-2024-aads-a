#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iterator>
#include <cassert>
#include "tree_node.hpp"

namespace namestnikov
{
  template< class Key, class Value, class Compare >
  class Tree;

  template< class Key, class Value, class Compare >
  class IteratorTree: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    friend class Tree< Key, Value, Compare >;
    using pair_key_t = std::pair< const Key, Value >;
    using node_t = TreeNode< pair_key_t >;
    using iterator = IteratorTree< Key, Value, Compare >;
  public:
    IteratorTree():
      node_(nullptr)
    {}
    IteratorTree(const iterator &) = default;
    iterator & operator=(const iterator &) = default;
    IteratorTree(iterator && other) noexcept = default;
    iterator & operator=(iterator && other) noexcept = default;
    bool operator==(const iterator & other) const
    {
      return (node_ == other.node_);
    }
    bool operator!=(const iterator & other) const
    {
      return !(*this == other);
    }
    pair_key_t & operator*()
    {
      return node_->data;
    }
    const pair_key_t & operator*() const
    {
      return node_->data;
    }
    pair_key_t * operator->()
    {
      return std::addressof(node_->data);
    }
    const pair_key_t * operator->() const
    {
      return std::addressof(node_->data);
    }
  private:
    node_t * node_;
    explicit IteratorTree(node_t * node):
      node_(node)
    {}
  };
}

#endif