#ifndef TREE_HPP
#define TREE_HPP
#include <functional>

namespace piyavkin
{
  template< class Key, class T, class Compare = std::less< Key > >
  class Tree
  {
  public:
    Tree():
      data(T()),
      right(nullptr),
      left(nullptr),
      parent(nullptr),
      cmp(Compare())
    {}
  private:
    T data;
    Tree< Key, T, Compare >* right;
    Tree< Key, T, Compare >* left;
    Tree< Key, T, Compare >* parent;
    Compare cmp;
  };
}
#endif