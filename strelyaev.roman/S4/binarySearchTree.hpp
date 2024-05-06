#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <functional>
#include "node.hpp"
#include "treeIterator.hpp"
#include "constTreeIterator.hpp"


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

      ~Tree()
      {
        clear(root);
        root = nullptr;
      }

      void swap(Tree< T >& other) noexcept
      {
        std::swap(other.root, root);
        std::swap(other.size_, size_);
      }

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

      void erase(ConstIterator< T > it)
      {
        if (!root || !it.node_)
        {
          return;
        }

        Node< T >* node = it.node_;

        if (!node->left_ && !node->right_)
        {
          if (node->isRoot())
          {
            size_--;
            delete node;
            root = nullptr;
            return;
          }
          else
          {
            if (node->isLeftChild())
            {
              node->parent_->left_ = nullptr;
            }
            else
            {
              node->parent_->right_ = nullptr;
            }
            delete node;
            size_--;
            return;
          }
        }

        if (!node->left_ || !node->right_)
        {
          Node< T >* child = nullptr;
          if (node->left_)
          {
            child = node->left_;
          }
          else
          {
            child = node->right_;
          }
          if (node->isRoot())
          {
            root = child;
          }
          else
          {
            if (node->isLeftChild())
            {
              node->parent_->left_ = child;
            }
            else
            {
              node->parent_->right_ = child;
            }
            child->parent_ = node->parent_;
          }
          delete node;
          size_--;
          return;
        }

        Node< T >* successor = node->right_;
        while (successor->left_)
        {
          successor = successor->left_;
        }

        if (successor->parent_ != node)
        {
          if (successor->right_)
          {
            successor->right_->parent_ = successor->parent_;
          }
          successor->parent_->left_ = successor->right_;
          successor->right_ = node->right_;
          node->right_->parent_ = successor;
        }

        if (node->isRoot())
        {
          root = successor;
        }
        else
        {
          if (node->isLeftChild())
          {
            node->parent_->left_ = successor;
          }
          else
          {
            node->parent_->right_ = successor;
          }
        }
        successor->parent_ = node->parent_;
        successor->left_ = node->left_;
        node->left_->parent_ = successor;
        delete node;
        size_--;
      }

      void erase(const T& k)
      {
        auto it = find(k);
        erase(it);
      }

      Iterator< T > begin() noexcept
      {
        Node< T >* current = root;
        while (current->left_)
        {
          current = current->left_;
        }
        return Iterator< T >(current);
      }

      Iterator< T > end() noexcept
      {
        return Iterator< T >(nullptr);
      }

      ConstIterator< T > cbegin() const noexcept
      {
        Node< T >* current = root;
        while (current->left_)
        {
          current = current->left_;
        }
        return ConstIterator(current);
      }

      ConstIterator< T > cend() const noexcept
      {
        return ConstIterator< T >(nullptr);
      }

      ConstIterator< T > find(const T& value)
      {
        Node< T >* current = root;
        while (current)
        {
          if (current->value_ == value)
          {
            return ConstIterator< T >(current);
          }
          else if (Comp()(current->value_, value))
          {
            current = current->right_;
          }
          else
          {
            current = current->left_;
          }
        }
        return ConstIterator< T >(current);
      }

      bool empty() noexcept
      {
        return size_ == 0;
      }

      size_t size() noexcept
      {
        return size_;
      }

      void clear(Node< T >* node)
      {
        if (node != nullptr)
        {
          clear(node->left_);
          clear(node->right_);
          delete node;
        }
      }

    private:
      Node< T >* root;
      size_t size_;
  };
}

#endif

