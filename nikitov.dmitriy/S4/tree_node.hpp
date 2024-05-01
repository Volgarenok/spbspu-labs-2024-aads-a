#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>
#include <functional>

namespace nikitov
{
  namespace detail
  {
    template< class Key, class T, class Compare = std::less< Key > >
    struct TreeNode
    {
      TreeNode();
      TreeNode(const std::pair< Key, T >& value);
      ~TreeNode() = default;

      bool find(const Key& key) const;
      T& get(const Key& key);
      const T& get(const Key& key) const;
      TreeNode< Key, T, Compare >* add(const std::pair< Key, T >& value);
      TreeNode< Key, T, Compare >* split(const std::pair< Key, T >& value);
      void clear();

      std::pair< Key, T > firstValue_;
      std::pair< Key, T > secondValue_;
      TreeNode< Key, T, Compare >* left_;
      TreeNode< Key, T, Compare >* middle_;
      TreeNode< Key, T, Compare >* right_;
      TreeNode< Key, T, Compare >* parent_;
      size_t size_;
      Compare cmp_;
    };

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >::TreeNode() :
      TreeNode(std::pair< Key, T >())
    {}

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >::TreeNode(const std::pair< Key, T >& value):
      firstValue_(value),
      secondValue_(std::pair< Key, T >()),
      left_(nullptr),
      middle_(nullptr),
      right_(nullptr),
      parent_(nullptr),
      size_(1),
      cmp_(Compare())
    {}

    template< class Key, class T, class Compare >
    bool TreeNode< Key, T, Compare >::find(const Key& key) const
    {
      bool isFound = (firstValue_.first == key);
      if (size_ == 2)
      {
        isFound = isFound || (secondValue_.first == key);
      }
      return isFound;
    }

    template< class Key, class T, class Compare >
    T& TreeNode< Key, T, Compare >::get(const Key& key)
    {
      if (size_ == 2 && secondValue_.first == key)
      {
        return secondValue_.second;
      }
      return firstValue_.second;
    }

    template< class Key, class T, class Compare >
    const T& TreeNode< Key, T, Compare >::get(const Key& key) const
    {
      if (size_ == 2 && secondValue_.first == key)
      {
        return secondValue_.second;
      }
      return firstValue_.second;
    }

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::add(const std::pair< Key, T >& value)
    {
      TreeNode< Key, T, Compare >* newRoot = nullptr;
      if (size_ == 1)
      {
        secondValue_ = value;
        if (!cmp_(firstValue_.first, secondValue_.first))
        {
          std::swap(firstValue_, secondValue_);
        }
        ++size_;
      }
      else
      {
        std::pair< Key, T > toSplit = value;
        if (cmp_(value.first, firstValue_.first))
        {
          toSplit = firstValue_;
          firstValue_ = value;
        }
        else if (cmp_(secondValue_.first, value.first))
        {
          toSplit = secondValue_;
          secondValue_ = value;
        }
        newRoot = split(toSplit);
      }
      return newRoot;
    }

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::split(const std::pair< Key, T >& value)
    {
      TreeNode< Key, T, Compare >* newRoot = nullptr;
      if (parent_->parent_)
      {
        newRoot = parent_->add(value);
      }
      else
      {
        parent_->middle_ = new TreeNode< Key, T, Compare >(value);
        parent_->middle_->parent_ = parent_;
        parent_ = parent_->middle_;
        newRoot = parent_;
      }

      if (parent_->left_ == this)
      {
        if (parent_->right_)
        {
          parent_->middle_ = new TreeNode< Key, T, Compare >(secondValue_);
          parent_->middle_->parent_ = parent_;
        }
        else
        {
          parent_->right_ = new TreeNode< Key, T, Compare >(secondValue_);
          parent_->right_->parent_ = parent_;
        }
      }
      else if (parent_->right_ == this)
      {
        if (parent_->left_)
        {
          parent_->middle_ = new TreeNode< Key, T, Compare >(firstValue_);
          parent_->middle_->parent_ = parent_;
        }
        else
        {
          parent_->left_ = new TreeNode< Key, T, Compare >(firstValue_);
          parent_->left_->parent_ = parent_;
        }
        firstValue_ = secondValue_;
      }
      else
      {
        TreeNode< Key, T, Compare >* newNode = nullptr;
        if (right_ && right_->size_ == 2)
        {
          newNode = new TreeNode< Key, T, Compare >(firstValue_);
          std::swap(firstValue_, secondValue_);
          parent_->left_ = newNode;
          newNode->left_ = left_;
          if (left_)
          {
            left_->parent_ = newNode;
          }
          newNode->right_ = middle_;
          parent_->right_ = this;
          left_ = nullptr;
        }
        else
        {
          newNode = new TreeNode< Key, T, Compare >(secondValue_);
          parent_->right_ = newNode;
          newNode->right_ = right_;
          if (right_)
          {
            right_->parent_ = newNode;
          }
          newNode->left_ = middle_;
          parent_->left_ = this;
          right_ = nullptr;
        }
        if (middle_)
        {
          middle_->parent_ = newNode;
        }
        newNode->parent_ = parent_;
        parent_->middle_ = nullptr;
        middle_ = nullptr;
      }
      secondValue_ = std::pair< Key, T >();
      --size_;

      return newRoot;
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::clear()
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
}
#endif
