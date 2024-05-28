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
        return !cmp(lhs->firstValue_.first, rhs->firstValue_.first);
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
      void fixErase();

      void littleRotateRight();
      void littleRotateLeft();
      void rotateRight();
      void rotateLeft();

      treeNode* findNeighbour() const;
      size_t countHeight() const;
      bool isLeaf() const;

      void freeFirst();
      void freeSecond();

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
    void TreeNode< Key, T, Compare >::fixErase()
    {
      if ((!left_ && right_) || (!right_ && left_) || (!middle_ && left_ && size_ == 2))
      {
        if (!right_)
        {
          rotateRight();
        }
        else
        {
          rotateLeft();
        }
        if (parent_->parent_ && !left_ && !right_)
        {
          fixErase();
        }
      }
      else
      {
        List< treeNode* > nodes;
        nodes.push_back(this);
        treeNode* neighbour = findNeighbour();
        if (neighbour->left_)
        {
          nodes.push_back(neighbour->left_);
        }
        if (neighbour->right_)
        {
          nodes.push_back(neighbour->right_);
        }
        if (neighbour->middle_)
        {
          nodes.push_back(neighbour->middle_);
        }
        nodes.sort(CompareNodes< Key, T, Compare >());
        auto iterator = nodes.cbegin();

        if (parent_->left_ == this)
        {
          parent_->left_ = nullptr;
          if (neighbour->size_ == 2)
          {
            if (parent_->size_ == 1)
            {
              parent_->rotateLeft();
            }
            else
            {
              parent_->littleRotateLeft();
            }
            parent_->left_->fixNeighbour(nodes);
          }
          else
          {
            if (parent_->size_ == 1)
            {
              parent_->rotateLeft();
              parent_->connect(*iterator++, *iterator++, *iterator++);
            }
            else
            {
              parent_->littleRotateLeft();
              parent_->left_->connect(*iterator++, *iterator++, *iterator++);
            }
          }
        }
        else
        {
          if (parent_->right_ == this)
          {
            parent_->right_ = nullptr;
          }
          else
          {
            parent_->middle_ = nullptr;
          }
          if (neighbour->size_ == 2)
          {
            if (parent_->size_ == 1)
            {
              parent_->rotateRight();
            }
            else
            {
              parent_->littleRotateRight();
            }
            parent_->right_->fixNeighbour(nodes);
          }
          else
          {
            if (parent_->size_ == 1)
            {
              parent_->rotateRight();
              parent_->connect(*iterator++, *iterator++, *iterator++);
            }
            else
            {
              parent_->littleRotateRight();
              parent_->right_->connect(*iterator++, *iterator++, *iterator++);
            }
          }
        }
      }
      if (parent_->findNeighbour() && (parent_->findNeighbour()->countHeight() != parent_->countHeight()))
      {
        parent_->fixErase();
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::littleRotateRight()
    {
      if (!right_)
      {
        right_ = new TreeNode< Key, T, Compare >(secondValue_);
        right_->parent_ = this;
        freeSecond();
      }
      else if (right_->size_ == 1)
      {
        right_->add(secondValue_);
        right_->parent_ = this;
        freeSecond();
      }
      else if (right_->size_ == 2)
      {
        middle_ = new TreeNode< Key, T, Compare >(secondValue_);
        middle_->parent_ = this;
        freeSecond();
        add(right_->firstValue_);
        right_->freeFirst();
      }
      else
      {
        if (middle_->size_ == 2)
        {
          right_->add(middle_->secondValue_);
          middle_->freeSecond();
        }
        else
        {
          right_->add(middle_->firstValue_);
          delete middle_;
          middle_ = nullptr;
        }
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::littleRotateLeft()
    {
      left_ = new TreeNode< Key, T, Compare >(firstValue_);
      left_->parent_ = this;
      freeFirst();
      left_->add(middle_->firstValue_);
      middle_->freeFirst();
      if (middle_->size_ == 2)
      {
        middle_->freeFirst();
      }
      else
      {
        delete middle_;
        middle_ = nullptr;
      }
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::rotateRight()
    {
      if (middle_ || left_->size_ == 2)
      {
        if (size_ == 2)
        {
          right_ = new TreeNode< Key, T, Compare >(secondValue_);
          freeSecond();
        }
        else
        {
          right_ = new TreeNode< Key, T, Compare >(firstValue_);
          freeFirst();
        }
        right_->parent_ = this;
        if (middle_ && middle_->size_ == 2)
        {
          add(middle_->secondValue_);
          middle_->freeSecond();
        }
        else if (middle_)
        {
          right_->add(middle_->firstValue_);
          middle_->freeFirst();
          delete middle_;
          middle_ = nullptr;
        }
        else
        {
          add(left_->secondValue_);
          left_->freeSecond();
        }
        fixOwn(nullptr);
      }
      else
      {
        if (size_ == 2)
        {
          left_->add(firstValue_);
          freeFirst();
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
        freeFirst();
        if (middle_ && middle_->size_ == 2)
        {
          add(middle_->firstValue_);
          middle_->freeFirst();
        }
        else if (middle_)
        {
          left_->add(middle_->firstValue_);
          middle_->freeFirst();
          delete middle_;
          middle_ = nullptr;
        }
        else
        {
          add(right_->firstValue_);
          right_->freeFirst();
        }
        fixOwn(nullptr);
      }
      else
      {
        if (size_ == 2)
        {
          right_->add(secondValue_);
          freeSecond();
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
    TreeNode< Key, T, Compare >* TreeNode< Key, T, Compare >::findNeighbour() const
    {
      treeNode* neighbour = nullptr;
      if (!parent_)
      {
        return nullptr;
      }
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
    size_t TreeNode< Key, T, Compare >::countHeight() const
    {
      const treeNode* node = this;
      size_t result = 0;
      while (node->left_)
      {
        ++result;
        node = node->left_;
      }
      return result;
    }

    template< class Key, class T, class Compare >
    bool TreeNode< Key, T, Compare >::isLeaf() const
    {
      return !left_ && !right_ && !middle_;
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::freeFirst()
    {
      std::swap(firstValue_, secondValue_);
      secondValue_ = std::pair< Key, T >{};
      --size_;
    }

    template< class Key, class T, class Compare >
    void TreeNode< Key, T, Compare >::freeSecond()
    {
      secondValue_ = std::pair< Key, T >{};
      --size_;
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
