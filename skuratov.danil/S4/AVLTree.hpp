#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstddef>
#include "treeNode.hpp"
#include "constIteratorTree.hpp"

namespace skuratov
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree
  {
  public:
    AVLTree():
      root_(nullptr),
      cmp_(Compare()),
      size_(0)
    {}

    ~AVLTree()
    {
      clear();
    }

    AVLTree(const AVLTree& diff):
      root_(nullptr),
      cmp_(diff.cmp_),
      size_(0)
    {
      try
      {
        for (auto it = diff.cbegin(); it != diff.cend(); it++)
        {
          push(it->first, it->second);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    AVLTree(const AVLTree&& diff):
      root_(diff.root_),
      cmp_(diff.cmp_),
      size_(diff.size_)
    {
      diff.root_ = nullptr;
      diff.size_ = 0;
    }

    //operator==

    ConstIteratorTree cbegin() const noexcept
    {
      return ConstIteratorTree(root_);
    }

    ConstIteratorTree cend() const noexcept
    {
      return ConstIteratorTree(nullptr);
    }

    size_t size() const noexcept
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    void clear() noexcept
    {
      removeNode(root_);
      root_ = nullptr;
      size_ = 0;
    }

    void swap(AVLTree& diff)
    {
      std::swap(root_, diff.root_);
      std::swap(cmp_, diff.cmp_);
      std::swap(size_, diff.size_);
    }

    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);

  private:
    detail::TreeNode< Key, Value >* root_;
    Compare* cmp_;
    size_t size_;

    void removeNode(detail::TreeNode< Key, Value >* node)
    {
      if (node == nullptr)
      {
        return;
      }
      removeNode(node->left);
      removeNode(node->right);
      delete node;
    }
  };
}

#endif
