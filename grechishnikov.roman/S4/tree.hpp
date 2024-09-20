#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <algorithm>
#include <cstddef>
#include "treeNode.hpp"
//#include "iterator.hpp"
#include "constTreeIterator.hpp"

namespace grechishnikov
{
  template< typename Key, typename T, typename Compare = std::less< Key > >
  class Tree
  {
  public:
    Tree();
    Tree(const Tree< Key, T, Compare >&);
    Tree(Tree<  Key, T, Compare>&& other) noexcept;
    ~Tree();

    Tree< Key, T, Compare >& operator=(const Tree< Key, T, Compare >&);
    Tree< Key, T, Compare >& operator=(Tree< Key, T, Compare >&&) noexcept;

//    Iterator< T > begin() noexcept;
    ConstTreeIterator< Key, T, Compare > cbegin() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear() noexcept;

    void swap(Tree< Key, T, Compare >&) noexcept;

    ConstTreeIterator< Key, T, Compare > insert(Key key, T&& value);

    ConstTreeIterator< Key, T, Compare > find(Key);
  private:
    void delTree(detail::Node< Key, T >*);

    size_t size_;
    Compare comp_;
    detail::Node< Key, T >* root_;
  };

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >::Tree():
    size_(0),
    comp_(Compare()),
    root_(nullptr)
  {}

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >::Tree(Tree< Key, T, Compare >&& other) noexcept:
    size_(0),
    comp_(Compare()),
    root_(nullptr)
  {
    swap(other);
  }

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >::~Tree()
  {
    clear();
  }

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >& Tree< Key, T, Compare >::operator=(const Tree< Key, T, Compare >& other)
  {
    Tree< Key, T, Compare > temp(other);
    swap(temp);
    return *this;
  }

  template< typename Key, typename T, typename Compare >
  Tree< Key, T, Compare >& Tree< Key, T, Compare >::operator=(Tree< Key, T, Compare >&& other) noexcept
  {
    if (root_ != other.root_)
    {
      clear();
      swap(other);
    }
    return *this;
  }

//  template< typename Key, typename T, typename Compare >
//  Iterator< T > Tree< T >::begin() noexcept
//  {
//    return Iterator< T >(head_);
//  }

//  template< typename Key, typename T, typename Compare >
//  Iterator< T > Tree< T >::end() noexcept
//  {
//    return Iterator< T >(nullptr);
//  }

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::cbegin() const noexcept
  {
    return ConstTreeIterator< Key, T, Compare >(root_);
  }

//  template< typename Key, typename T, typename Compare >
//  ConstTreeIterator< T > Tree< T >::cend() const noexcept
//  {
//    return ConstTreeIterator< T >(nullptr);
//  }

  template< typename Key, typename T, typename Compare >
  bool Tree< Key, T, Compare >::empty() const noexcept
  {
    return !root_;
  }

  template< typename Key, typename T, typename Compare >
  size_t Tree< Key, T, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::clear() noexcept
  {
    this->delTree(root_);
    root_ = nullptr;
    size_ = 0;
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::swap(Tree< Key, T, Compare >& other) noexcept
  {
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
    std::swap(root_, other.root_);
  }

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::insert(Key key, T&& value)
  {
    auto temp = new detail::Node< Key, T >(key, std::move(value), nullptr, nullptr, nullptr);
    if (!root_)
    {
      root_ = temp;
      size_ += 1;
      return ConstTreeIterator< Key, T, Compare >(temp);
    }
    detail::Node< Key, T >* rootNode = root_;
    detail::Node< Key, T >* prev = root_;
    while (rootNode)
    {
      prev = root_;
      if (comp_(key, root_->data_.first))
      {
        rootNode = rootNode->left_;
      }
      else
      {
        rootNode = rootNode->right_;
      }
    }
    if (comp_(key, prev->data_.first))
    {
      prev->left_ = temp;
    }
    else
    {
      prev->right_ = temp;
    }
    temp->parent_ = prev;
    return ConstTreeIterator< Key, T, Compare >(temp);
  }

  template< typename Key, typename T, typename Compare >
  void Tree< Key, T, Compare >::delTree(detail::Node< Key, T >* node)
  {
    if (node)
    {
      delTree(node->left_);
      delTree(node->right_);
      delete node;
    }
  }

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare > Tree< Key, T, Compare >::find(Key key)
  {
    auto tempRoot = root_;
    while (tempRoot)
    {
      if (!comp_(key, tempRoot->data_.first) and !comp_(tempRoot->data_.first, key))
      {
        return ConstTreeIterator< Key, T, Compare >(tempRoot);
      }
      if (comp_(key, tempRoot->data_.first))
      {
        tempRoot = tempRoot->left_;
      }
      else
      {
        tempRoot = tempRoot->right_;
      }
    }
    return ConstTreeIterator< Key, T, Compare >(nullptr);
  }
}

#endif
