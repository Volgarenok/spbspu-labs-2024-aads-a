#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <functional>
#include "node.hpp"
#include "treeIterator.hpp"


#include <iostream>

namespace strelyaev
{
  template< typename T, typename Comp = std::less< T > >
  class Tree
  {
    public:
      Tree():
        root(nullptr),
        size_(0)
      {}

      int getHeight(Node< T >* node)
      {
        if (!node)
        {
          return -1;
        }
        return node->height_;
      }

      int getBalance(Node< T >* node)
      {
        if (!node)
        {
          return 0;
        }
        return getHeight(node->right_) - getHeight(node->left_);
      }

      void updateHeight(Node< T >* node)
      {
        node->height_ = std::max(getHeight(node->left_), getHeight(node->right_)) + 1;
      }

       void rotateRight(Node< T >* node)
       {
        std::swap(node->left_->value_, node->value_);
        Node< T >* buffer = node->right_;
        node->right_ = node->left_;

        node->left_ = node->right_->left_;
        if (node->left_)
        {
          node->left_->parent_ = node;
        }

        node->right_->left_ = node->right_->right_;

        node->right_->right_ = buffer;
        if (buffer)
        {
          buffer->parent_ = node->right_;
        }

        updateHeight(node->right_);
        updateHeight(node);
       }

       void rotateLeft(Node< T >* node)
       {
        std::swap(node->right_->value_, node->value_);
        Node< T >* buffer = node->left_;
        node->left_ = node->right_;

        node->right_ = node->left_->right_;
        if (node->right_)
        {
          node->right_->parent_ = node;
        }

        node->left_->right_ = node->left_->left_;

        node->left_->left_ = buffer;
        if (buffer)
        {
          buffer->parent_ = node->left_;
        }

        updateHeight(node->left_);
        updateHeight(node);
       }

       void balance(Node< T >* node)
       {
        int balance = getBalance(node);
        if (balance == -2)
        {
          if (getBalance(node->left_) == 1)
          {
            rotateLeft(node->left_);
          }
          rotateRight(node);
        }
        else if (balance == 2)
        {
          if (getBalance(node->right_) == -1)
          {
            rotateRight(node->right_);
          }
          rotateLeft(node);
        }
       }

      void push(T value)
      {
        if (!root)
        {
          root = new Node< T >(nullptr, nullptr, nullptr, value);
          size_++;
          return;
        }
        Node< T >* current_node = root;
        Node< T >* parent = nullptr;
        while(current_node)
        {
          parent = current_node;
          if (Comp()(value, current_node->value_))
          {
            current_node = current_node->left_;
          }
          else
          {
            current_node = current_node->right_;
          }
        }
        if (Comp()(value, parent->value_))
        {
          parent->left_ = new Node< T >(nullptr, parent, nullptr, value);
        }
        else if (!Comp()(value, parent->value_))
        {
          parent->right_ = new Node< T >(nullptr, parent, nullptr, value);
        }
        size_++;
        while (parent)
        {
          updateHeight(parent);
          balance(parent);
          parent = parent->parent_;
        }
      }

      Iterator< T > begin() noexcept
      {
        Node< T >* current = root;
        while (current->left_)
        {
          current = current->left_;
        }
        return Iterator(current);
      }

      Iterator< T > end() noexcept
      {
        return Iterator< T >(nullptr);
      }

      bool empty()
      {
        return size_ == 0;
      }

    //private:
      Node< T >* root;
      size_t size_;
  };
}

#endif

