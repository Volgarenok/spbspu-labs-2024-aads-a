#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <memory>
#include <initializer_list>

#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

namespace arakelyan
{
  template < class T >
  struct RBTree
  {
  public:
    using iterator = Iterator< T >;
    using const_iterator = ConstIterator< T >;

    RBTree();
    RBTree(const RBTree &otherT);//fine
    // RBTree(RBTree &&otherT);
    RBTree(std::initializer_list< T > otherT);//fine
    template < class Iterator_t >
    RBTree(Iterator_t it_start, Iterator_t it_end);//fine
    ~RBTree();//fine

    RBTree &operator=(const RBTree &otherT);//fine
    RBTree &operator=(RBTree &&otherT);//fine
    RBTree &operator=(std::initializer_list< T > otherT);//fine

    size_t getSize() const noexcept;
    bool empty() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    void insert(const T &val); // fine?
    // void remove()

    void swap(RBTree &otherT) noexcept;

    void printInOrder() const noexcept;

  private:
    using Node = detail::Node< T >;
    Node *root_;
    size_t size_;

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
        std::cout << node->data_ << ":" << node->color_ << " -- ";
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

  template < class T >
  RBTree< T >::RBTree():
    root_(nullptr),
    size_(0)
  {}

  template < class T >
  RBTree< T >::RBTree(const RBTree< T > &otherT):
    RBTree()
  {
    if (!otherT.empty())
    {
      copyFromRange(otherT.cbegin(), otherT.cend());
    }
  }

  template < class T >
  RBTree< T >::RBTree(std::initializer_list< T > otherT):
    RBTree(otherT.begin(), otherT.end())
  {}

  template < class T >
  template < class Iterator_t >
  RBTree< T >::RBTree(Iterator_t it_start, Iterator_t it_end):
    RBTree()
  {
    copyFromRange(it_start, it_end);
  }

  template < class T >
  RBTree< T >::~RBTree()
  {
    clear(root_);
  }

  template < class T >
  RBTree< T > &RBTree< T >::operator=(const RBTree< T > &otherT)
  {
    RBTree temp(otherT);
    if (this != std::addressof(temp))
    {
      swap(temp);
    }
    return *this;
  }

  template < class T >
  RBTree< T > &RBTree< T >::operator=(RBTree< T > &&otherT)
  {
    RBTree temp(std::move(otherT));
    if (this != std::addressof(temp))
    {
      clear(root_);
      swap(temp);
    }
    return *this;
  }

  template < class T >
  RBTree< T > &RBTree< T >::operator=(std::initializer_list< T > otherT)
  {
    clear(root_);
    copyFromRange(otherT.begin(), otherT.end());
    return *this;
  }

  template < class T >
  size_t RBTree< T >::getSize() const noexcept
  {
    return size_;
  }

  template < class T >
  bool RBTree< T >::empty() const noexcept
  {
    return root_ == nullptr;
  }

  template < class T >
  Iterator< T > RBTree< T >::begin() noexcept
  {
    return Iterator< T >(root_);
  }

  template < class T >
  Iterator< T > RBTree< T >::end() noexcept
  {
    return Iterator< T >(nullptr);
  }

  template < class T >
  ConstIterator< T > RBTree< T >::cbegin() const noexcept
  {
    return ConstIterator< T >(root_);
  }

  template < class T >
  ConstIterator< T > RBTree< T >::cend() const noexcept
  {
    return ConstIterator< T >(nullptr);
  }

  template < class T >
  void RBTree< T >::insert(const T &val)
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
      if (val < curNode->data_)
      {
        curNode = curNode->left_;
      }
      else
      {
        curNode = curNode->right_;
      }
    }
    newNode->parent_ = parent;
    if (val < parent->data_)
    {
      parent->left_ = newNode;
    }
    else if (val > parent->data_)
    {
      parent->right_ = newNode;
    }
    ++size_;
    // balance func.
  }

  template < class T >
  void RBTree< T >::swap(RBTree< T > &otherT) noexcept
  {
    std::swap(root_, otherT.root_);
  }

  template < class T >
  void RBTree< T >::printInOrder() const noexcept
  {
    traversal(root_);
  }
}
#endif
