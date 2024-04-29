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
    Tree();
    Tree(const Key& key, const T& value);
    ~Tree() = default;

    void add(const Key& key, const T& value);
    void clear();

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
  Tree< Key, T, Compare >::Tree():
    Tree(Key(), T())
  {}

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree(const Key& key, const T& value):
    firstValue_({ key, value }),
    secondValue_({ Key(), T() }),
    left_(nullptr),
    middle_(nullptr),
    right_(nullptr),
    parent_(nullptr),
    size_(1),
    cmp_(Compare())
  {}

  template< class Key, class T, class Compare >
  void Tree< Key, T, Compare >::add(const Key& key, const T& value)
  {
    secondValue_ = { key, value };
    if (!cmp_(firstValue_.first, secondValue_.first))
    {
      std::swap(firstValue_, secondValue_);
    }
    ++size_;
  }

  template< class Key, class T, class Compare >
  void Tree< Key, T, Compare >::clear()
  {
    if (left_)
    {
      left_->clear();
      delete left_;
    }
    if (middle_)
    {
      middle_->clear();
      delete middle_;
    }
    if (right_)
    {
      right_->clear();
      delete right_;
    }
  }
}
#endif
