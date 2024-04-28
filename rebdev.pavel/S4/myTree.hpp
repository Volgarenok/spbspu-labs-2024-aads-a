#ifndef MYTREE_HPP
#define MYTREE_HPP

#include <functional>
#include <utility>

#include "treeNode.hpp"
#include "iterBase.hpp"

namespace rebdev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class AVLTree
  {
    using pair = std::pair< const Key, Value >;
    using node = TreeNode< pair >;

    public:
      using iterator = BaseIter< Key, Value, Compare, pair, node >;
      using const_iterator = BaseIter< Key, Value, Compare, const pair, const node >;

      AVLTree():
        headNode_(new node{nullptr, nullptr, nullptr, pair{}}),
        size_(0)
      {}
      ~AVLTree() noexcept
      {
        delete headNode_;
      }

      iterator begin()
      {
        node * beginNode = headNode_;
        while ((beginNode->left) != (nullptr))
        {
          beginNode = beginNode->left;
        }
        return iterator(beginNode);
      }
      iterator end()
      {
        node * beginNode = headNode_;
        while ((beginNode->right) != (nullptr))
        {
          beginNode = beginNode->right;
        }
        return iterator(beginNode);
      }
      const_iterator cbegin() const
      {
        return const_iterator(*begin());
      }
      const_iterator cend() const
      {
        return const_iterator(*end());
      }

      bool empty() const noexcept
      {
        return (size_ == 0);
      }
      size_t size() const noexcept
      {
        return size_;
      }

      iterator find(const Key & k)
      {
        return iterator(findBase(k));
      }
      const_iterator find(const Key & k) const
      {
        return const_iterator(findBase(k));
      }

    private:
      node * headNode_;
      size_t size_;

      node * findBase(const Key & k)
      {
        iterator it = begin();
        while (it != end())
        {
          if ((*it.first) == k)
          {
            return &it;
          }
        }
        return nullptr;
      }
  };
}

#endif
