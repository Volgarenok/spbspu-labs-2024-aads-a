#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <utility>

#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

namespace arakelyan
{
  template < class Key, class Value, class Comparator = std::less< Key > >
  struct RBTree
  {
  public:
    using iterator = Iterator< Key, Value, Comparator >;
    using const_iterator = ConstIterator< Key, Value, Comparator >;
    using value_t = std::pair< Key, Value >;

    RBTree();
    RBTree(const RBTree &otherT);//fine
    // RBTree(RBTree &&otherT);
    RBTree(std::initializer_list< value_t > otherT);//fine
    template < class Iterator_t >
    RBTree(Iterator_t it_start, Iterator_t it_end);//fine
    ~RBTree();//fine

    RBTree &operator=(const RBTree &otherT);//fine
    RBTree &operator=(RBTree &&otherT);//fine
    RBTree &operator=(std::initializer_list< value_t > otherT);//fine

    size_t getSize() const noexcept;
    bool empty() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    void insert(const value_t &val); // fine?
    // void remove()

    void swap(RBTree &otherT) noexcept;

    void printInOrder() const noexcept;

  private:
    using Node = detail::Node< Key, Value >;
    Node *root_;
    size_t size_;
    Comparator comp;

    void clear(Node *node)
    {
      if (node)
      {
        clear(node->left_);
        clear(node->right_);
        delete node;
      }
    }

    void traversal(Node *node) const noexcept
    {
      if (node)
      {
        traversal(node->left_);
        std::cout << node->data_.first << ":" << node->data_.second << " col:" << node->color_ << " -> ";
        traversal(node->right_);
      }
    }

    template < class Iterator_t >
    void copyFromRange(Iterator_t it_start, Iterator_t it_end)
    {
      for (auto it = it_start; it != it_end; ++it)
      {
        insert(*it);
      }
    }

    // void someFixInput()
    // void someFixDelete()
    // void leftRotate()
    // void rightTorate()
  };

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::RBTree():
    root_(nullptr),
    size_(0)
  {}

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::RBTree(const RBTree< Key, Value, Comparator > &otherT):
    RBTree()
  {
    if (!otherT.empty())
    {
      copyFromRange(otherT.cbegin(), otherT.cend());
    }
  }

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::RBTree(std::initializer_list< std::pair< Key, Value > > otherT):
    RBTree(otherT.begin(), otherT.end())
  {}

  template < class Key, class Value, class Comparator >
  template < class Iterator_t >
  RBTree< Key, Value, Comparator >::RBTree(Iterator_t it_start, Iterator_t it_end):
    RBTree()
  {
    copyFromRange(it_start, it_end);
  }

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator >::~RBTree()
  {
    clear(root_);
  }

  template < class Key, class Value, class Comparator  >
  RBTree< Key, Value, Comparator > &RBTree< Key, Value, Comparator >::operator=(const RBTree< Key, Value, Comparator > &otherT)
  {
    RBTree temp(otherT);
    if (this != std::addressof(temp))
    {
      swap(temp);
    }
    return *this;
  }

  template < class Key, class Value, class Comparator  >
  RBTree< Key, Value, Comparator > &RBTree< Key, Value, Comparator >::operator=(RBTree< Key, Value, Comparator > &&otherT)
  {
    RBTree temp(std::move(otherT));
    if (this != std::addressof(temp))
    {
      clear(root_);
      swap(temp);
    }
    return *this;
  }

  template < class Key, class Value, class Comparator >
  RBTree< Key, Value, Comparator > &RBTree< Key, Value, Comparator >::operator=(std::initializer_list< std::pair< Key, Value > > otherT)
  {
    clear(root_);
    copyFromRange(otherT.begin(), otherT.end());
    return *this;
  }

  template < class Key, class Value, class Comparator >
  size_t RBTree< Key, Value, Comparator >::getSize() const noexcept
  {
    return size_;
  }

  template < class Key, class Value, class Comparator >
  bool RBTree< Key, Value, Comparator >::empty() const noexcept
  {
    return root_ == nullptr;
  }

  template < class Key, class Value, class Comparator  >
  Iterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::begin() noexcept
  {
    return Iterator< Key, Value, Comparator >(root_);
  }

  template < class Key, class Value, class Comparator  >
  Iterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::end() noexcept
  {
    return Iterator< Key, Value, Comparator >(nullptr);
  }

  template < class Key, class Value, class Comparator  >
  ConstIterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::cbegin() const noexcept
  {
    return ConstIterator< Key, Value, Comparator >(root_);
  }

  template < class Key, class Value, class Comparator  >
  ConstIterator< Key, Value, Comparator > RBTree< Key, Value, Comparator >::cend() const noexcept
  {
    return ConstIterator< Key, Value, Comparator >(nullptr);
  }

  template < class Key, class Value, class Comparator  >
  void RBTree< Key, Value, Comparator >::insert(const std::pair< Key, Value > &val)
  {
    Node *newNode = new Node(val);
    if (empty())
    {
      root_ = newNode;
      root_->color_ = detail::color_t::BLACK;
      ++size_;
      return;
    }
    Node *curNode = root_;
    Node *parent = nullptr;
    while (curNode)
    {
      parent = curNode;
      if (comp(val.first, curNode->data_.first))
      {
        curNode = curNode->left_;
      }
      else
      {
        curNode = curNode->right_;
      }
    }
    newNode->parent_ = parent;
    if (comp(val.first, parent->data_.first))
    {
      parent->left_ = newNode;
    }
    else if (!comp(val.first,parent->data_.first))
    {
      parent->right_ = newNode;
    }
    ++size_;
    // balance func.
  }

  template < class Key, class Value, class Comparator  >
  void RBTree< Key, Value, Comparator >::swap(RBTree< Key, Value, Comparator > &otherT) noexcept
  {
    std::swap(root_, otherT.root_);
  }

  template < class Key, class Value, class Comparator  >
  void RBTree< Key, Value, Comparator >::printInOrder() const noexcept
  {
    traversal(root_);
  }
}
#endif
