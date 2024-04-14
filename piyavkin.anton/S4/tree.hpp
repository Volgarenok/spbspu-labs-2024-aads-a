#ifndef TREE_HPP
#define TREE_HPP
#include <cstddef>
#include "treenode.hpp"

namespace piyavkin
{
  template< class Key, class T, class Compare = std::less< Key > >
  class Tree
  {
  public:
    Tree():
      root_(nullptr),
      size_(0)
    {}
    size_t size() const noexcept
    {
      return size_;
    }
    bool empty() const noexcept
    {
      return size_ == 0;
    }
  private:
    detail::Node< Key, T, Compare >* root_;
    size_t size_;
  };
}
#endif