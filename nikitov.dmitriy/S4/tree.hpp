#ifndef TREE_HPP
#define TREE_HPP

#include <utility>

namespace nikitov
{
  template< class Key, class T, class Compare >
  class Tree
  {
  public:
    Tree(Key key, T& value, Compare cmp = std::less< Key >);
    ~Tree() = default;

    void add();

  private:
    std::pair< Key, T > firstValue_;
    std::pair< Key, T > secondValue_;
    Tree< T >* left_;
    Tree< T >* middle_;
    Tree< T >* right_;
    Tree< T >* parent_;
    size_t size_;
    Compare cmp_;
  };

  template< class Key, class T, class Compare >
  Tree< Key, T, Compare >::Tree(Key key, T& value, Compare cmp = std::less< Key >):
    firstValue_({ key, value }),
    secondValue_({ Key(), T() }),
    left_(nullptr),
    middle_(nullptr),
    right_(nullptr),
    parent_(nullptr)
    size_(1),
    cmp_(cmp)
  {}
}
#endif
