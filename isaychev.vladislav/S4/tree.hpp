#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <stdexcept>
#include "treeIter.hpp"

namespace isaychev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class BSTree
  {
    using Tree = BSTree< Key, Value, Compare >;
    using node_t = detail::TreeNode< Key, Value >;
    using const_iterator = ConstTreeIter< Key, Value, Compare >;
    using iterator = TreeIter< Key, Value, Compare >;

   public:
    BSTree();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    size_t size() const noexcept;
    void clear() noexcept;
    void swap(Tree & other) noexcept;
    iterator find(const Key & key);
    const_iterator find(const Key & key) const;
    //at();
    //operator[]();

   private:
    node_t * root_;
    Compare cmp_;
    size_t size_;
    // node_t dummy_node;

    void delete_tree(node_t * ptr) noexcept;
  };

  template < class Key, class Value, class Compare >
  BSTree< Key, Value, Compare >::BSTree():
   root_(nullptr),
   cmp_(),
   size_(0)
  {}

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::begin()
  {
    return TreeIter< Key, Value, Compare >(traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::end()
  {
    return TreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::begin() const
  {
    return ConstTreeIter< Key, Value, Compare >(traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::end() const
  {
    return ConstTreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::cbegin() const
  {
    return ConstTreeIter< Key, Value, Compare >(traverse_left(root_));
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::cend() const
  {
    return ConstTreeIter< Key, Value, Compare >();
  }

  template < class Key, class Value, class Compare >
  size_t BSTree< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::delete_tree(node_t * root) noexcept
  {
    if (root)
    {
      delete_tree(root->left);
      delete_tree(root->right);
      delete root;
    }
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::clear() noexcept
  {
    delete_tree(root_);
  }

  template < class Key, class Value, class Compare >
  void BSTree< Key, Value, Compare >::swap(Tree & other) noexcept
  {
    std::swap(root_, other.root_);
    std::swap(cmp_, other.cmp_);
    std::swap(size_, other.size_);
  }

  template < class Key, class Value, class Compare >
  TreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::find(const Key & key)
  {
    node_t * current = root_;
    while (current)
    {
      if (key == current->data.first)
      {
        return TreeIter< Key, Value, Compare >(current);
      }
      if (cmp_(key, current->data.first))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    return end();
  }

  template < class Key, class Value, class Compare >
  ConstTreeIter< Key, Value, Compare > BSTree< Key, Value, Compare >::find(const Key & key) const
  {
    node_t * current = root_;
    while (current)
    {
      if (key == current->data.first)
      {
        return ConstTreeIter< Key, Value, Compare >(current);
      }
      if (cmp_(key, current->data.first))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    return cend();
  }

/*  template < class Key, class Value, class Compare >
  T & BSTree< Key, Value, Compare >::at(const Key & key)
  {
  }*/

  //operator[]();
}

#endif
