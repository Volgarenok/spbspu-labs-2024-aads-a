#ifndef TREE_HPP
#define TREE_HPP

#include <utility>
#include <functional>

namespace nikitov
{
  template< class Key, class T, class Compare = std::less< Key > >
  class Tree
  {
  public:
    Tree(Key& key, T& value);
    ~Tree() = default;

    void add(Key& key, T& value);

  private:
    std::pair< Key, T > firstValue_;
    std::pair< Key, T > secondValue_;
    Tree< Key, T, Compare >* left_;
    Tree< Key, T, Compare >* middle_;
    Tree< Key, T, Compare >* right_;
    Tree< Key, T, Compare >* parent_;
    size_t size_;
    Compare cmp_;
  };

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree(Key& key, T& value):
    firstValue_({ key, value }),
    secondValue_({ Key(), T() }),
    left_(nullptr),
    middle_(nullptr),
    right_(nullptr),
    parent_(nullptr),
    size_(1),
    cmp_(Compare())
  {}
}
#endif
