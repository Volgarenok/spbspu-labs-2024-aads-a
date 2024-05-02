#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "TreeNode.hpp"

namespace chistyakov
{
  template< typename T >
  class Tree;

  template< typename T >
  class Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< T >;
    public:
      Iterator():
        TreeNode_(nullptr)
      {}

      Iterator(TreeTreeNode< T > * val):
        TreeNode_(val)
      {}

      ~Iterator() = default;
      Iterator(const Iterator< T > &) = default;
      Iterator< T > & operator=(const Iterator< T > & ) = default;

      bool operator==(const Iterator< T > & rhs) const
      {
        return treeNode_ == rhs.treeNode_;
      }

      bool operator!=(const Iterator< T > & rhs) const
      {
        return !(rhs == *this);
      }

      T & operator*()
      {
        return treeNode_->value_;
      }

      T * operator->()
      {
        return std::addressof(treeNode_->value_);
      }

      const T & operator*() const
      {
        return treeNode_->value_;
      }

      const T * operator->() const
      {
        return std::addressof(treeNode_->value_);
      }

    private:
      TreeNode< T > * treeNode_;
  };
}

#endif