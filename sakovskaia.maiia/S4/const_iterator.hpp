#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP
#include <functional>
#include "node.hpp"

namespace sakovskaia
{
  template < typename Key, typename Value, typename Comp >
  class Tree;

  template < typename Key, typename Value, typename Comp = std::less< Key > >
  class ConstIterTree
  {
    friend class Tree< Key, Value, Comp >;

    public:
      using Node = detail::TreeNode< Key, Value >;

      bool operator==(const ConstIterTree & other) const
      {
        return current_ == other.current_;
      }

      bool operator!=(const ConstIterTree & other) const
      {
        return current_ != other.current_;
      }

      std::pair< Key, Value > & operator*() const
      {
        return current_->data;
      }

      std::pair< Key, Value > * operator->() const
      {
        return std::addressof(current_->data);
      }

      ConstIterTree< Key, Value, Comp > & operator++()
      {
        if (current_ == nullptr)
        {
          return * this;
        }
        if (current_->right != nullptr)
        {
          current_ = current_->right;
          while (current_->left != nullptr)
          {
            current_ = current_->left;
          }
        }
        else
        {
          Node * temp;
          do
          {
            temp = current_;
            current_ = current_->parent;
          }
          while (current_ != nullptr && temp == current_->right);
        }
        return * this;
      }

      ConstIterTree< Key, Value, Comp > operator++(int)
      {
        ConstIterTree tempIter = * this;
        ++(* this);
        return tempIter;
      }

    private:
      Node * current_;
      explicit ConstIterTree(Node * nodePtr):
        current_(nodePtr)
      {}
  };
}

#endif
