#ifndef TREE_HPP
#define TREE_HPP
#include <cstddef>
#include "treenode.hpp"
#include "treeiterator.hpp"

namespace piyavkin
{
  template< class Key, class T, class Compare = std::less< Key > >
  class Tree
  {
  public:
    using val_type = std::pair< const Key, T >;
    Tree():
      root_(nullptr),
      cmp_(Compare()),
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
    void swap(Tree< Key, T, Compare >& mp)
    {
      std::swap(root_, mp.root_);
      std::swap(cmp_, mp.cmp_);
      std::swap(size_, mp.size_);
    }
    /*std::pair< TreeIterator< Key, T, Compare >, bool >*/void insert(const val_type& val)
    {
      detail::Node< Key, T >* node = new detail::Node< Key, T >(val.first, nullptr, nullptr, nullptr, val.second);
      detail::Node< Key, T >* curr_node = root_;
      detail::Node< Key, T >* parent_node = nullptr;
      while (curr_node != nullptr)
      {
        if (cmp_(curr_node->key_, node->key_))
        {
          if (!curr_node->right_)
          {
            parent_node = curr_node;
          }
          curr_node = curr_node->right_;
        }
        else
        {
          if (!curr_node->left_)
          {
            parent_node = curr_node;
          }
          curr_node = curr_node->left_;
        }
      }
      if (!parent_node)
      {
        root_ = node;
      }
      else if (cmp_(parent_node->key_, node->key_))
      {
        parent_node->right_ = node;
      }
      else
      {
        parent_node->left_ = node;
      }
      node->parent_ = parent_node;
      ++size_;
      //splay();
    }
  // private:
    detail::Node< Key, T >* root_;
    Compare cmp_;
    size_t size_;
  };
}
#endif