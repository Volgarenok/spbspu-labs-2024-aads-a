#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>
#include <functional>
#include <list.hpp>

namespace nikitov
{
  namespace detail
  {
    template< class Key, class T, class Compare = std::less< Key > >
    struct TreeNode
    {
      using Node = TreeNode< Key, T, Compare >;
      TreeNode();
      TreeNode(const std::pair< Key, T >& value);
      ~TreeNode() = default;

      bool find(const Key& key) const;
      T& get(const Key& key);
      const T& get(const Key& key) const;
      TreeNode< Key, T, Compare >* add(const std::pair< Key, T >& value);
      TreeNode< Key, T, Compare >* split(const std::pair< Key, T >& value, Node* first, Node* second);
      void check(TreeNode< Key, T, Compare >* first, TreeNode< Key, T, Compare >* second);
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
    TreeNode< Key, T, Compare >::TreeNode():
      TreeNode(std::pair< Key, T >())
    {
      --size_;
    }

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
      if (size_ == 0)
      {
        firstValue_ = value;
        ++size_;
      }
      else if (size_ == 1)
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
        TreeNode< Key, T, Compare >* newNode = new TreeNode< Key, T, Compare >(secondValue_);
        secondValue_ = std::pair< Key, T >{};
        size_ = 1;
        if (parent_->left_ == this)
        {
          parent_->left_ = nullptr;
        }
        else if (parent_->right_ == this)
        {
          parent_->right_ = nullptr;
        }
        else if (parent_->parent_)
        {
          parent_->middle_ = nullptr;
        }
        newRoot = parent_->split(toSplit, this, newNode);
      }
      return newRoot;
    }

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::split(const std::pair< Key, T >& value, Node* first, Node* second)
    {
      TreeNode< Key, T, Compare >* newRoot = nullptr;
      if (!parent_)
      {
        middle_ = new TreeNode< Key, T, Compare >();
        middle_->parent_ = this;
        newRoot = middle_;
        newRoot->split(value, first, second);
      }
      else
      {
        newRoot = add(value);
        if (left_ && (!right_ && !middle_))
        {
          middle_ = first;
          right_ = second;
          first->parent_ = this;
          second->parent_ = this;
        }
        else if (right_ && (!left_ && !middle_))
        {
          middle_ = second;
          left_ = first;
          first->parent_ = this;
          second->parent_ = this;
        }
        else if (parent_->parent_)
        {
          check(first, second);
        }
        else
        {
          left_ = first;
          right_ = second;
          first->parent_ = this;
          second->parent_ = this;
        }
      }

      return newRoot;
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::check(TreeNode< Key, T, Compare >* first, TreeNode< Key, T, Compare >* second)
    {
      TreeNode< Key, T, Compare >* ownFirst = nullptr;
      TreeNode< Key, T, Compare >* ownSecond = nullptr;
      if (left_)
      {
        ownFirst = left_;
        ownSecond = middle_;
        if (right_)
        {
          ownSecond = right_;
        }
      }
      else
      {
        ownFirst = middle_;
        ownSecond = right_;
      }
      left_ = nullptr;
      right_ = nullptr;
      middle_ = nullptr;

      TreeNode< Key, T, Compare >* neigbour = nullptr;
      if (parent_->right_ == this)
      {
        neigbour = parent_->left_;
        if (parent_->middle_)
        {
          neigbour = parent_->middle_;
        }
      }
      else if (parent_->left_ == this)
      {
        neigbour = parent_->right_;
        if (parent_->middle_)
        {
          neigbour = parent_->middle_;
        }
      }
      else
      {
        neigbour = parent_->left_;
        if (!parent_->right_->right_)
        {
          neigbour = parent_->right_;
        }
      }
      TreeNode< Key, T, Compare >* one = nullptr;
      TreeNode< Key, T, Compare >* two = nullptr;
      TreeNode< Key, T, Compare >* three = nullptr;
      TreeNode< Key, T, Compare >* four = nullptr;
      if (cmp_(ownFirst->firstValue_.first, first->firstValue_.first))
      {
        one = ownFirst;
        if (cmp_(ownSecond->firstValue_.first, first->firstValue_.first))
        {
          two = ownSecond;
          three = first;
          four = second;
        }
        else
        {
          two = first;
          three = second;
          four = ownSecond;
          if (cmp_(ownSecond->firstValue_.first, second->firstValue_.first))
          {
            three = ownSecond;
            four = second;
          }
        }
      }
      else
      {
        one = first;
        if (cmp_(second->firstValue_.first, ownFirst->firstValue_.first))
        {
          two = second;
          three = ownFirst;
          four = ownSecond;
        }
        else
        {
          two = ownFirst;
          three = ownSecond;
          four = second;
          if (cmp_(second->firstValue_.first, ownSecond->firstValue_.first))
          {
            three = second;
            four = ownSecond;
          }
        }
      }

      if (cmp_(firstValue_.first, neigbour->firstValue_.first))
      {
        left_ = one;
        right_ = two;
        neigbour->left_ = three;
        neigbour->right_ = four;
      }
      else
      {
        left_ = three;
        right_ = four;
        neigbour->left_ = one;
        neigbour->right_ = two;
      }
      left_->parent_ = this;
      right_->parent_ = this;
      neigbour->left_->parent_ = neigbour;
      neigbour->right_->parent_ = neigbour;
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
