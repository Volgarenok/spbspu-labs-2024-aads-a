#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>
#include <functional>
#include <list.hpp>

namespace nikitov
{
  namespace detail
  {
    template< class Key, class T, class Compare >
    struct TreeNode;

    template< class Key, class T, class Compare >
    struct CompareNodes
    {
      bool operator()(const TreeNode< Key, T, Compare >* lhs, const TreeNode< Key, T, Compare >* rhs)
      {
        Compare cmp;
        return cmp(lhs->firstValue_.first, rhs->firstValue_.first);
      }
    };

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
      TreeNode< Key, T, Compare >* split(const std::pair< Key, T >& value, Node* node);
      void check(TreeNode< Key, T, Compare >* node);
      void checkNeighbour(const List< TreeNode< Key, T, Compare >* >& nodes);
      void connect(Node* left, Node* middle, Node* right);
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
        --size_;
        newRoot = parent_->split(toSplit, newNode);
      }
      return newRoot;
    }

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::split(const std::pair< Key, T >& value, Node* node)
    {
      TreeNode< Key, T, Compare >* newRoot = nullptr;
      if (!parent_)
      {
        newRoot = new TreeNode< Key, T, Compare >();
        newRoot->parent_ = this;
        newRoot->middle_ = middle_;
        middle_ = newRoot;
        newRoot->split(value, node);
      }
      else
      {
        newRoot = add(value);
        check(node);
      }

      return newRoot;
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::check(TreeNode< Key, T, Compare >* node)
    {
      List< TreeNode< Key, T, Compare >* > nodes;
      nodes.push_back(node);
      if (left_)
      {
        nodes.push_back(left_);
      }
      if (right_)
      {
        nodes.push_back(right_);
      }
      if (middle_)
      {
        nodes.push_back(middle_);
      }

      nodes.sort(CompareNodes< Key, T, Compare >());
      auto iterator = nodes.cbegin();
      if (nodes.size() == 2)
      {
        connect(*iterator++, nullptr, *iterator++);
      }
      else if (nodes.size() == 3)
      {
        connect(*iterator++, *iterator++, *iterator++);
      }
      else
      {
        checkNeighbour(nodes);
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::checkNeighbour(const List< TreeNode< Key, T, Compare >* >& nodes)
    {
      TreeNode< Key, T, Compare >* neigbour = nullptr;
      if (parent_->middle_ && parent_->middle_ != this)
      {
        neigbour = parent_->middle_;
      }
      else if (parent_->right_ && parent_->right_ != this)
      {
        neigbour = parent_->right_;
      }
      else
      {
        neigbour = parent_->left_;
      }

      auto iterator = nodes.cbegin();
      if (!cmp_(firstValue_.first, neigbour->firstValue_.first))
      {
        connect(*iterator++, nullptr, *iterator++);
        neigbour->connect(*iterator++, nullptr, *iterator++);
      }
      else
      {
        neigbour->connect(*iterator++, nullptr, *iterator++);
        connect(*iterator++, nullptr, *iterator++);
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::connect(Node* left, Node* middle, Node* right)
    {
      left_ = left;
      middle_ = middle;
      right_ = right;
      left->parent_ = this;
      right->parent_ = this;
      if (middle_)
      {
        middle_->parent_ = this;
      }
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
