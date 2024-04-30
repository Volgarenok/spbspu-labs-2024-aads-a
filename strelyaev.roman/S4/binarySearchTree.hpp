#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <functional>
#include "node.hpp"
#include "listIterator.hpp"


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

      void push(T value)
      {
        insert(value, root);
      }

      void insert(T value, Node< T >* current_node)
      {
        if (!root)
        {
          root = new Node< T >(nullptr, nullptr, nullptr, value);
          size_++;
          return;
        }
        if (current_node == nullptr)
        {
          current_node = root;
        }

        if (Comp()(value, current_node->value_))
        {
          if (current_node->left_)
          {
            insert(value, current_node->left_);
          }
          else
          {
            current_node->left_ = new Node< T >(nullptr, current_node, nullptr, value);
            size_++;
          }
        }
        else
        {
          if (current_node->right_)
          {
            insert(value, current_node->right_);
          }
          else
          {
            current_node->right_ = new Node< T >(nullptr, current_node, nullptr, value);
            size_++;
          }
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

