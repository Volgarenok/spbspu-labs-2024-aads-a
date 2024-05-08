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
      using treeNode = TreeNode< Key, T, Compare >;

      std::pair< Key, T > firstValue_;
      std::pair< Key, T > secondValue_;
      treeNode* left_;
      treeNode* middle_;
      treeNode* right_;
      treeNode* parent_;
      size_t size_;
      Compare cmp_;

      TreeNode();
      explicit TreeNode(const std::pair< Key, T >& value);
      ~TreeNode() = default;

      bool find(const Key& key) const;
      T& get(const Key& key);
      const T& get(const Key& key) const;

      treeNode* add(const std::pair< Key, T >& value);
      treeNode* moveAdd(std::pair< Key, T >&& value);
      treeNode* split(const std::pair< Key, T >& value, treeNode* node);

      void fixOwn(treeNode* node);
      void fixNeighbour(const List< treeNode* >& nodes);

      void free(bool isFirst);

      treeNode* findNeighbour() const;
      bool isLeaf() const;
      void rotateRight();
      void rotateLeft();
      void littleRotateRight();
      void littleRotateLeft();

      void connect(treeNode* left, treeNode* middle, treeNode* right);
      void clear();
    };

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >::TreeNode():
      firstValue_(std::pair< Key, T >()),
      secondValue_(std::pair< Key, T >()),
      left_(nullptr),
      middle_(nullptr),
      right_(nullptr),
      parent_(nullptr),
      size_(0),
      cmp_(Compare())
    {}

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >::TreeNode(const std::pair< Key, T >& value):
      TreeNode()
    {
      add(value);
    }

    template< class Key, class T, class Compare >
    bool TreeNode< Key, T, Compare >::find(const Key& key) const
    {
      return firstValue_.first == key || (size_ == 2 && secondValue_.first == key);
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
      std::pair< Key, T > copy = value;
      return moveAdd(std::move(copy));
    }

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::moveAdd(std::pair< Key, T >&& value)
    {
      treeNode* newRoot = nullptr;
      if (size_ == 0)
      {
        firstValue_ = std::move(value);
        ++size_;
      }
      else if (size_ == 1)
      {
        secondValue_ = std::move(value);
        if (!cmp_(firstValue_.first, secondValue_.first))
        {
          std::swap(firstValue_, secondValue_);
        }
        ++size_;
      }
      else
      {
        Key valueKey = value.first;
        std::pair< Key, T > toSplit = std::move(value);
        if (cmp_(valueKey, firstValue_.first))
        {
          std::swap(firstValue_, toSplit);
        }
        else if (cmp_(secondValue_.first, valueKey))
        {
          std::swap(secondValue_, toSplit);
        }
        treeNode* newNode = new treeNode(std::move(secondValue_));
        --size_;

        newRoot = parent_->split(toSplit, newNode);
      }
      return newRoot;
    }

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::split(const std::pair< Key, T >& value, treeNode* node)
    {
      treeNode* newRoot = nullptr;
      if (!parent_)
      {
        newRoot = new treeNode();
        newRoot->parent_ = this;
        newRoot->middle_ = middle_;
        middle_ = newRoot;
        newRoot->split(value, node);
      }
      else
      {
        newRoot = add(value);
        fixOwn(node);
      }
      return newRoot;
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::fixOwn(treeNode* node)
    {
      List< treeNode* > nodes;
      if (node)
      {
        nodes.push_back(node);
      }
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
        fixNeighbour(nodes);
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::fixNeighbour(const List< treeNode* >& nodes)
    {
      treeNode* neighbour = findNeighbour();

      auto iterator = nodes.cbegin();
      if (!cmp_(firstValue_.first, neighbour->firstValue_.first))
      {
        connect(*iterator++, nullptr, *iterator++);
        neighbour->connect(*iterator++, nullptr, *iterator++);
      }
      else
      {
        neighbour->connect(*iterator++, nullptr, *iterator++);
        connect(*iterator++, nullptr, *iterator++);
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::free(bool isFirst)
    {
      if (isFirst)
      {
        std::swap(firstValue_, secondValue_);
      }
      secondValue_ = std::pair< Key, T >{};
      --size_;
    }

    template< class Key, class T, class Compare >
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::findNeighbour() const
    {
      treeNode* neighbour = nullptr;
      if (parent_->middle_ && parent_->middle_ != this)
      {
        neighbour = parent_->middle_;
      }
      else if (parent_->right_ && parent_->right_ != this)
      {
        neighbour = parent_->right_;
      }
      else
      {
        neighbour = parent_->left_;
      }
      return neighbour;
    }

    template< class Key, class T, class Compare >
    bool TreeNode< Key, T, Compare >::isLeaf() const
    {
      return !left_ && !right_ && !middle_;
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::littleRotateRight()
    {
      right_ = new TreeNode< Key, T, Compare >(secondValue_);
      free(false);
      add(middle_->secondValue_);
      middle_->free(false);
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::littleRotateLeft()
    {
      left_ = new TreeNode< Key, T, Compare >(firstValue_);
      free(true);
      add(middle_->firstValue_);
      middle_->free(true);
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::rotateRight()
    {
      if (middle_ || left_->size_ == 2)
      {
        if (size_ == 2)
        {
          right_ = new TreeNode< Key, T, Compare >(secondValue_);
          free(false);
        }
        else
        {
          right_ = new TreeNode< Key, T, Compare >(firstValue_);
          free(true);
        }
        right_->parent_ = this;
        if (middle_ && middle_->size_ == 2)
        {
          add(middle_->secondValue_);
          middle_->free(false);
        }
        else if (middle_)
        {
          right_->add(middle_->firstValue_);
          middle_->free(true);
          delete middle_;
          middle_ = nullptr;
        }
        else
        {
          add(left_->secondValue_);
          left_->free(false);
        }
        fixOwn(nullptr);
      }
      else
      {
        if (size_ == 2)
        {
          left_->add(firstValue_);
          free(true);
        }
        else
        {
          add(left_->firstValue_);
          delete left_;
          left_ = nullptr;
        }
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::rotateLeft()
    {
      if (middle_ || right_->size_ == 2)
      {
        if (left_)
        {
          left_->add(firstValue_);
        }
        else
        {
          left_ = new TreeNode< Key, T, Compare >(firstValue_);
          left_->parent_ = this;
        }
        free(true);
        if (middle_ && middle_->size_ == 2)
        {
          add(middle_->firstValue_);
          middle_->free(true);
        }
        else if (middle_)
        {
          left_->add(middle_->firstValue_);
          middle_->free(true);
          delete middle_;
          middle_ = nullptr;
        }
        else
        {
          add(right_->firstValue_);
          right_->free(true);
        }
        fixOwn(nullptr);
      }
      else
      {
        if (size_ == 2)
        {
          right_->add(secondValue_);
          free(false);
        }
        else
        {
          add(right_->firstValue_);
          delete right_;
          right_ = nullptr;
        }
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::connect(treeNode* left, treeNode* middle, treeNode* right)
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
