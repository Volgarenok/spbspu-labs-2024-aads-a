#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>

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

    RBTree();
    // Tree(const Tree &otherT);
    // Tree(const Tree &&otherT);
    ~RBTree();

    // Tree &operator=(const Tree &otherT);
    // Tree &operator=(const Tree &&otherT);

    size_t getSize() const noexcept;
    bool empty() const noexcept; // fine

    iterator begin() const;
    iterator end() const;

    void insert(const T &val); // fine?
    // void remove()

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

    // void balance(Node *newNode)
    // {
    //   Node *uncle;
    //   while (newNode->parent_->color_ == detail::color_t::RED)
    //   {
    //     if (newNode->parent_ == newNode->parent_->parent_->left_)
    //     {
    //       uncle = newNode->parent_->parent_.right_;
    //       if (uncle->color_ == detail::color_t::RED)
    //       {
    //         newNode->parent_->color_ = detail::color_t::BLACK;
    //         uncle->color_ = detail::color_t::BLACK;
    //         newNode->parent_->parent_->color_ = detail::color_t::RED;
    //         newNode =
    //       }
    //     }
    //   }
    // }

  };

  template < class T >
  RBTree< T >::RBTree():
    root_(nullptr),
    size_(0)
  {}

  // template < class T >
  // Tree< T >::Tree(const Tree< T > &otherT)
  // {

  // }

  template < class T >
  RBTree< T >::~RBTree()
  {
    clear(root_);
  }

  // template < class T >
  // Tree< T > &Tree< T >::operator=(const Tree< T > &otherT)
  // {

  // }

  template < class T >
  bool RBTree< T >::empty() const noexcept
  {
    return root_ == nullptr;
  }

  template < class T >
  Iterator< T > RBTree< T >::begin() const
  {
    return iterator(root_);
  }

  template < class T >
  Iterator< T > RBTree< T >::end() const
  {
    return iterator(nullptr);
  }

  template < class T >
  void RBTree< T >::insert(const T &val)
  {
    Node *newNode = new Node(val);
    if (empty())
    {
      root_ = newNode;
      root_->color_ = detail::color_t::BLACK;
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
  void RBTree< T >::printInOrder() const noexcept
  {
    traversal(root_);
  }
}
#endif
