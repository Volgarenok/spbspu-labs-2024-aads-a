#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "node.hpp"
#include "iterator.hpp"

namespace chistyakov
{
  template< typename Key, typename Value, typename Comp = std::less< Key > >
  class AVLTree
  {
    using pairKV = std::pair< const Key, Value >;
    public:
      AVLTree():
        size_(0),
        root_(nullptr),
        comp_(Comp)
      {}

      AVLTree(AVLTree && tmp):
        size_(tmp.size_),
        root_(tmp.root_),
        comp_(tmp.comp_)
      {
        tmp.size_ = 0;
        tmp.root_ = nullptr;
      }

      AVLTree & operator=(const AVLTree & tmp)
      {
        if (this != std::addressof(tmp))
        {
          AVLTree< pairKV > temper(tmp);
          swap(temper);
        }
        return *this;
      }

      AVLTree & operator=(const AVLTree && tmp)
      {
        if (this != std::addressof(tmp))
        {
          swap(tmp);
        }
        return *this;
      }

      ~AVLTree() = default;

      bool empty() const
      {
        return size_ == 0;
      }

      void swap(AVLTree tmp)
      {
        std::swap(tmp.size_, size_);
        std::swap(tmp.root_, root_);
        std::swap(tmp.comp_, comp_);
      }

      size_t size() const
      {
        return size_;
      }

      void insert(pairKV value)
      {
        Node * n = new Node(value);

        if (root_ == nullptr)
        {
          root_ = n;
        }
        else
        {
          Node * curr = root_;
          Node * parent = nullptr;

          while (current != nullptr)
          {
            parent = curr;

            if (comp_(value, root_->value))
            {
              curr = curr->left;
              if (curr == nullptr)
              {
                parent->left = n;
              }
            }
            else
            {
              curr = curr->right;
              if (curr == nullptr)
              {
                parent->right = n;
              }
            }
          }
        }
      }

    private:
      size_t size_;
      Node * root_;
      Comp comp_;
  };
}

#endif
